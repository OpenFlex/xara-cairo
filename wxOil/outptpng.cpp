/*
 * xara-cairo, a vector drawing program
 *
 * Based on Xara XL, Copyright (C) 1993-2006 Xara Group Ltd.
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 */


#include "camtypes.h"
//#include "andy.h"
#include "progress.h"		// For hourglass stuff

//#include "resource.h"		// _R(IDS_OUT_OF_MEMORY)
//#include "filtrres.h"		// _R(IDS_UNKNOWN_PNG_ERROR)
//#include "nev.h"			// _R(IDW_CANCELEXPORT)

#include "outptpng.h"
#include "pngutil.h"
#include "png.h"

// Replacements for some libpng functions
#include "pngfuncs.h"


#define	new	CAM_DEBUG_NEW

/********************************************************************************************

>	OutputPNG::OutputPNG()

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/5/96
	Purpose:	Default constructor for the class. Just sets up the pointers to our buffers
				that may be used to be null so that the TidyUp function can do its job.
	SeeAlso:	OutputPNG::TidyUp
	SeeAlso:	OutputDIB;

********************************************************************************************/

OutputPNG::OutputPNG()
{
	OutputFile = NULL;
	lpBitmap = NULL;
	ExportBuffer = NULL;
	DoExportConvert = NULL;
	OutputForward = FALSE;

	DestBitmapInfo = NULL;
	DestBitmapBytes = NULL;
}


/********************************************************************************************

>	BOOL OutputPNG::StartFile( CCLexFile *File, LPBITMAPINFOHEADER lpHeader, LPRGBQUAD Palette,
							   UINT32 OutputDepth, DWORD CompressionType, UINT32 FinalHeight,
							   UINT32 FinalHeight, INT32 ExportSize, UINT32 DitherType )

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/5/96
	Inputs:		lpHeader	contains width & DPI of source & dest. biHeight & depth ignored.
				Palette		pointer to bmiColor struct, or NULL if not used (can be temporary)
				OutputDepth	depth of bitmap required on disk
				CompressionType	in this case is used to pass in the transparency and interlace
							information as PNGs are always compressed. Passed in as a number between
							0 .. 3 which maps onto the TI_PNG filter types.
				FinalHeight	output of entire bitmap on disk
				ExportSize		The set progress bar size 
				DitherType		The type of dithering being used
	Returns:	TRUE if worked, FALSE if failed (error will be set accordingly but not reported)
	Purpose:	Get ready to write a PNG to disk, maybe in chunks. In the DIB case we go out
				to disk, in this case we store the bitmap for possible later use in applying a
				transparency mask to it.
	Errors:		Calls SetError on FALSE returns.
	SeeAlso:	OutputPNG::WriteBlock;OutputPNG::TidyUp
	Scope:		Public

********************************************************************************************/

BOOL OutputPNG::StartFile( LPBITMAPINFOHEADER lpHeader, LPLOGPALETTE Palette,
						   UINT32 OutputDepth, DWORD CompressionType,
						   UINT32 FinalHeight, INT32 ExportSize, UINT32 DitherType )
{
	TRACEUSER( "Jonathan", _T("PNG write: Start\n"));
	ERROR2IF( lpHeader==NULL , FALSE, "OutputPNG::StartFile NULL lpHeader");

	// Set up memory pointers to NULL
	if (DestBitmapInfo && DestBitmapBytes)
	{
		FreeDIB( DestBitmapInfo, DestBitmapBytes );
		DestBitmapInfo = NULL;
		DestBitmapBytes = NULL;	
	}
//	DestBitmapInfo = NULL;
//	DestBitmapBytes = NULL;
	if (OutputPalette)
	{
		CCFree(OutputPalette);
		OutputPalette = NULL;
	}
//	OutputPalette = NULL;
	IsFirstStrip = TRUE;
	HeightWritten = 0;

	// remember input args
	BitmapInfo = *lpHeader;								// take a copy of user's header
	CurrentExportSize = ExportSize;						// size set up for the progress bar
	HeightWanted = FinalHeight;							// the actual height of the export required
	Dither = DitherType;

	// We will need to have the entire image present before writing out so that we can
	// cope with interlacing and transparency, so create that DIB
	// Set up the information header for the dib which we hold during export
	UINT32 LineWidth = DIBUtil::ScanlineSize( BitmapInfo.biWidth, OutputDepth );
	INT32 PalSize = 0;			
	BOOL ok = SetUpInfoHeader(lpHeader, OutputDepth, CompressionType, LineWidth, FinalHeight, &PalSize);

	// Claim memory for the bitmap
	if (ok)
	{
		DestBitmapInfo = AllocDIB( BitmapInfo.biWidth, FinalHeight, OutputDepth, &DestBitmapBytes );
		ok = (DestBitmapInfo != NULL) && (DestBitmapBytes != NULL);
	}

	// Transfer across the required other bits of info
	if (ok)
	{
		DestBitmapInfo->bmiHeader.biXPelsPerMeter = BitmapInfo.biXPelsPerMeter;
		DestBitmapInfo->bmiHeader.biYPelsPerMeter = BitmapInfo.biYPelsPerMeter;
		DestBitmapInfo->bmiHeader.biClrUsed = PalSize;
	}

	// Point the place to put the next strip of data at the start ready for the first strip
	pNextStrip = DestBitmapBytes;	
	
	// Take a copy of the palette
	if (ok && PalSize && Palette)
	{
		const size_t TotalPal = sizeof(LOGPALETTE) + ( sizeof(PALETTEENTRY) * PalSize );
		OutputPalette = (LPLOGPALETTE)CCMalloc( TotalPal );
		if (OutputPalette != NULL)
			memcpy( OutputPalette, Palette, TotalPal );
		else
			ok = FALSE;
	}

	// Clean up if an error happened
	if (!ok)
	{
		// Free up the DIB that we have just created
		FreeDIB( DestBitmapInfo, DestBitmapBytes );
		DestBitmapInfo = NULL;
		DestBitmapBytes = NULL;	
		if (OutputPalette != NULL)
		{
			CCFree(OutputPalette);
			OutputPalette = NULL;
		}
	}

	return ok;
}

/********************************************************************************************

>	BOOL OutputPNG::ReStartFile(LOGPALETTE* pNewPal)

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/7/96
	Inputs:		pNewPal - New (optimised) palette to use
	Returns:	TRUE if worked, FALSE if failed
	Purpose:	Called to reset output before outputing another in a run of multiple images
	SeeAlso:	OutputPNG::StartFile; OutputGIF::ReStartFile;

********************************************************************************************/

BOOL OutputPNG::ReStartFile(LOGPALETTE* pNewPal)
{
	// Reset member variables
	IsFirstStrip = TRUE;
	HeightWritten = 0;
	pNextStrip = DestBitmapBytes;	

	if (pNewPal!=NULL)
	{
		ERROR2IF(OutputPalette==NULL, FALSE, "No output palette");
		ERROR3IF(pNewPal->palNumEntries != OutputPalette->palNumEntries, "Different sized palettes");

		const size_t PalSize = sizeof(PALETTEENTRY) * pNewPal->palNumEntries-1;
		memcpy( OutputPalette->palPalEntry, pNewPal->palPalEntry, PalSize );
	}
	
	return TRUE;
}


/********************************************************************************************

>	BOOL OutputPNG::SetUpInfoHeader(const LPBITMAPINFOHEADER lpHeader, const UINT32 OutputDepth,
									const DWORD CompressionType,
									const UINT32 LineWidth, const UINT32 FinalHeight,
									INT32 * pPalSize)

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/5/96
	Inputs:		lpHeader	contains width & DPI of source & dest. biHeight & depth ignored.
				OutputDepth	depth of bitmap required on disk
				CompressionType	BI_RGB only supported (or CC_BMPTYPE for 32-bit with trans)
				LineWidth 	destination line width
				FinalHeight	output of entire bitmap on disk
	Outputs:	pPalSize	pointer to an integer PalSize variable which is the palette size
	Returns:	TRUE if worked, FALSE if failed (error will be set accordingly but not reported)
	Purpose:	Set up the information header for the DIB.
	Errors:		Calls SetError on FALSE returns.
	SeeAlso:	OutputPNG::StartFile; OutputPNG::WriteBlock; OutputPNG::TidyUp
	Scope:		Public

********************************************************************************************/

BOOL OutputPNG::SetUpInfoHeader(const LPBITMAPINFOHEADER lpHeader, const UINT32 OutputDepth,
								const DWORD CompressionType,
								const UINT32 LineWidth, const UINT32 FinalHeight,
								INT32 * pPalSize)
{
	ERROR2IF(pPalSize == NULL,FALSE,"OutputPNG::SetUpInfoHeader Null pPalSize");

	SourceBitmapDepth = lpHeader->biBitCount;
	BitmapInfo.biBitCount = OutputDepth;

	const WORD DestDepth = BitmapInfo.biBitCount;

	// source bitmap not necessarily same as required file depth
	// make sure we can handle conversion
	BOOL FormatOK = FALSE;
	*pPalSize = 0;

	switch (SourceBitmapDepth)
	{
		case 32:
			{
				switch (DestDepth)
				{
					case 32:
						{
							// 32->32 might use our special type CC_BMPTYPE
							FormatOK = TRUE;
						}
						break;
					case 24:
						{
							// 32->24 bit is fine
							FormatOK = TRUE;
						}
						break;
					case 8:
						{
							// 32->8 is OK
							FormatOK = TRUE;
							*pPalSize = 256;
						}
						break;
					case 4:
						{
							// 32->4 is OK
							FormatOK = TRUE;
							*pPalSize = 16;
						}
						break;
					case 1:
						{
							// 32->1 is OK
							FormatOK = TRUE;
							*pPalSize = 2;
						}
						break;
					default:
						// other source formats here
						break;
				}
				
			}
			break;
		case 8:
			if (DestDepth==8)
			{
				// 8->8 is OK
				FormatOK = TRUE;
				*pPalSize = 256;
			}
			break;
		default:
			// other source formats here
			break;
	}

	if (!FormatOK)
	{
		Error::SetError( _R(IDE_FORMATNOTSUPPORTED) );
		return FALSE;
	}

	BitmapInfo.biSizeImage = LineWidth * FinalHeight;

	return TRUE;
}

/********************************************************************************************


	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/7/96
	Inputs:		File - output file object
				TransColour - the index of the transparent colour (-1 for no transparency)
	Outputs:	-
	Returns:	TRUE if worked, FALSE if failed
	Purpose:	Writes out the file header for the cached bitmap within this class
	SeeAlso:	OutputPNG::OutputPNGHeader 
	SeeAlso:	OutputGIF::OutputGifFileHeader (both ones)

********************************************************************************************/

BOOL OutputPNG::OutputPNGHeader(CCLexFile *File, INT32 TransColour, BOOL InterlaceState)
{
	return OutputPNGHeader(File, &(DestBitmapInfo->bmiHeader), InterlaceState, TransColour, OutputPalette);
}

/********************************************************************************************

>	BOOL OutputPNG::OutputPNGHeader(CCLexFile *, LPBITMAPINFOHEADER,
									BOOL Interlace, INT32 Transparent,
									LPLOGPALETTE = NULL, LPRGBQUAD pQuadPalette = NULL)

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/5/96
	Inputs:		File			file to output to
				pInfo			pointer to the bitmap info header
				InterlaceState	True if want interlacing, False otherwise
				TransparentColour	The transparent colour required
				pPalette		pointer to a palette in LOGPALETTE form (defaults to NULL)
				OR
				pQuadPalette	pointer to a palette in RGBQUAD form (defaults to NULL)	
	Outputs:	-
	Returns:	TRUE if worked, FALSE if failed (error will be set accordingly but not reported)
	Purpose:	Output a PNG header for the specified bitmap to the file.
				If neither palette is specifed then none will be output.
	Errors:		Calls SetError on FALSE returns.
	SeeAlso:	OutputPNG::StartFile; OutputPNG::WriteBlock; OutputPNG::TidyUp
	Scope:		static

********************************************************************************************/

BOOL OutputPNG::OutputPNGHeader(CCLexFile *File, LPBITMAPINFOHEADER pInfo,
								BOOL InterlaceState, INT32 TransparentColour,
								LPLOGPALETTE pPalette, LPRGBQUAD pQuadPalette)
{
	ERROR2IF(File==NULL,FALSE,"OutputPNG::OutputPNGHeader File pointer is null");
	if (pInfo == NULL)
		pInfo = &(DestBitmapInfo->bmiHeader);
	ERROR2IF(pInfo==NULL,FALSE,"OutputPNG::OutputPNGHeader BitmapInfo pointer is null");
	//ERROR2IF(pPalette==NULL && pQuadPalette==NULL,FALSE,"OutputPNG::OutputPNGHeader Bitmap palette pointer is null");

	TRACEUSER( "Jonathan", _T("PNG write: Interlace: %s\n"), InterlaceState ? _T("Yes") : _T("No"));

	// Note file in our class variable as used by all the low level routines
	OutputFile = File;

	// Note the specified transparency and interlace states in our class variables
	Interlace = InterlaceState;
	if (TransparentColour != -1)
		Transparent = TRUE;
	else
		Transparent = FALSE;

	// We are just about to start so set the PNG exception handling up with our CCFile pointer
	PNGUtil::SetCCFilePointer(File);
	
	// Must set the exception throwing flag to True and force reporting of errors to False.
	// This means that the caller must report an error if the function returns False.
	// Any calls to CCFile::GotError will now throw a file exception and should fall into
	// the catch handler at the end of the function.
	// Replaces the goto's that handled this before.
	BOOL OldThrowingState = File->SetThrowExceptions( TRUE );
	BOOL OldReportingState = File->SetReportErrors( FALSE );

	// PNG related items (NOTE: p at end means pointer and hence implied *)
	png_ptr		= NULL;
	info_ptr	= NULL;

	palette = NULL;

	try
	{
		// Work out the palette size 
		INT32 PalSize = pInfo->biClrUsed;		// How many entries in palette
TRACEUSER( "Jonathan", _T("PNG write: PalSize = %d\n"),PalSize);

		// Set up the class variables
		// First the width/height of the bitmap
	    Width = pInfo->biWidth;
	    Height = pInfo->biHeight;
TRACEUSER( "Jonathan", _T("PNG write: Width = %d Height = %d\n"),Width,Height);

		BitsPerPixel = pInfo->biBitCount;

	    // Start up the PNG writing code

		// allocate the necessary structures
		// Use the default handlers
		png_ptr = png_create_write_struct_2(
			PNG_LIBPNG_VER_STRING,	// libpng version
			0,						// Optional pointer to be sent with errors
			camelot_png_error,		// Function called in case of error
			camelot_png_warning,	// Function called for warnings
			0,						// Optional pointer to be sent with mem ops
			camelot_png_malloc,		// Function called to alloc memory
			camelot_png_free		// Function called to free memory
			);

		if (!png_ptr)
			File->GotError( _R(IDS_OUT_OF_MEMORY) );

		info_ptr = png_create_info_struct(png_ptr);
		if (!info_ptr)
		{
			png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
			File->GotError( _R(IDS_OUT_OF_MEMORY) );
		}

		// set up the input control to the fstream class
		// If not a disk file then panic for the present moment
		// Could use the memfile functions for reading and writing as they give us what
		// we want. Use the io_ptr and 
		iostream* pFStream = File->GetIOFile();
		if (pFStream == NULL)
		{
			TRACEUSER( "Jonathan", _T("PNG write: OutputPNG::OutputPNGHeader No access to IOStream!"));
			File->GotError( _R(IDS_UNKNOWN_PNG_ERROR) );
		}

		// Should use our own function
		png_set_write_fn(png_ptr, pFStream, camelot_png_write_data, camelot_png_flush_data);
		// png_init_io(png_ptr, pFStream);

		// You now have the option of modifying how the compression library
		// will run.  The following functions are mainly for testing, but
		// may be useful in certain special cases, like if you need to
		// write png files extremely fast and are willing to give up some
		// compression, or if you want to get the maximum possible compression
		// at the expense of slower writing.  If you have no special needs
		// in this area, let the library do what it wants, as it has been
		// carefully tuned to deliver the best speed/compression ratio.
		// See the compression library for more details.
    
		// turn on or off filtering (1 or 0)
		//png_set_filtering(png_ptr, 1);

		// compression level (0 - none, 6 - default, 9 - maximum)
		//png_set_compression_level(png_ptr, Z_BEST_COMPRESSION);
		//png_set_compression_mem_level(png_ptr, 8);
		//png_set_compression_strategy(png_ptr, Z_DEFAULT_STRATEGY);
		//png_set_compression_window_bits(png_ptr, 15);
		//png_set_compression_method(png_ptr, 8);

		// - this describes which optional chunks to write to the
		// file.  Note that if you are writing a
		// PNG_COLOR_TYPE_PALETTE file, the PLTE chunk is not
		// optional, but must still be marked for writing.  To
		// mark chunks for writing, OR valid with the 
		// appropriate PNG_INFO_<chunk name> define.
		png_get_valid(png_ptr, info_ptr, 0);
		
		// resolution of image
		png_set_invalid(png_ptr, info_ptr, PNG_INFO_pHYs);
		png_set_pHYs(png_ptr, info_ptr,
			pInfo->biXPelsPerMeter,
			pInfo->biYPelsPerMeter,
			1); //meter
TRACEUSER( "Jonathan", _T("PNG write: x,y px per cm = %d %d\n"),
	png_get_x_pixels_per_meter(png_ptr, info_ptr) / 1000,
	png_get_y_pixels_per_meter(png_ptr, info_ptr) / 1000);

		BitsPerPixel				= pInfo->biBitCount;
TRACEUSER( "Jonathan", _T("PNG write: Bitdepth = %d\n"), BitsPerPixel);
		palette		= NULL;
		num_palette	= 0;
		trans		= NULL;	// - array of transparent entries for paletted images
		num_trans	= 0;	// - number of transparent entries
TRACEUSER( "Jonathan", _T("PNG write: TransColour = %d\n"), TransparentColour);
		if ( BitsPerPixel <= 8 )
		{
			png_set_IHDR(png_ptr, info_ptr,
				Width,
				Height,
				BitsPerPixel,
				PNG_COLOR_TYPE_PALETTE,
				PNG_INTERLACE_NONE,
				PNG_COMPRESSION_TYPE_BASE,
				PNG_FILTER_TYPE_BASE);

			// set the palette if there is one
			png_set_invalid(png_ptr, info_ptr, PNG_INFO_PLTE);
			INT32 PaletteEntries = pInfo->biClrUsed;

			palette = (png_colorp)png_malloc(png_ptr, PNG_MAX_PALETTE_LENGTH * png_sizeof (png_color));
			if (palette == NULL)
				File->GotError( _R(IDS_OUT_OF_MEMORY) );

			png_set_PLTE(png_ptr, info_ptr, palette, num_palette);
			png_color_struct * pPNGPalette = palette;
			// ... set palette colors ...
	 		if (pQuadPalette && PaletteEntries > 0)
			{
				// Palette supplied in RGBQUAD form 
				for (INT32 i = 0; i < PaletteEntries; i++)
				{
					pPNGPalette->red 	= pQuadPalette->rgbRed;
					pPNGPalette->green 	= pQuadPalette->rgbGreen;
					pPNGPalette->blue 	= pQuadPalette->rgbBlue;
					// skip to the next palette entry
					pQuadPalette++;
					pPNGPalette++;
				}
			}
			else if (pPalette && PaletteEntries > 0)
			{
				// Palette supplied in LOGPALETTE form 
				for (INT32 i = 0; i < PaletteEntries; i++)
				{
					pPNGPalette->red  	= pPalette->palPalEntry[i].peRed;
					pPNGPalette->green 	= pPalette->palPalEntry[i].peGreen;
					pPNGPalette->blue 	= pPalette->palPalEntry[i].peBlue;
					pPNGPalette++;
				}
			}
			else
				File->GotError(_R(IDS_PNG_ERR_WRITE_PALETTE));
			
			// Now check to see if transparency is present or not
			if (TransparentColour >= 0 && TransparentColour <= PaletteEntries )
			{
				// Create the array of transparent entries for this palette
				// 0 is fully transparent, 255 is fully opaque, regardless of image bit depth
				// We will only create as many as we require, i.e. up to the transparent colour entry
				// rather a full palettes worth
				INT32 NumEntries = TransparentColour + 1;
				trans = (png_byte*)png_malloc(png_ptr, NumEntries * sizeof (png_byte));
				if (trans)
				{
					// Set the number of transparent entries
					num_trans			= NumEntries;
					png_byte * pTransEntry		= trans;
					png_set_invalid(png_ptr, info_ptr, PNG_INFO_tRNS);
					for (INT32 i = 0; i < TransparentColour; i++)
					{
						*pTransEntry = 255;	// set it fully opaque
						pTransEntry++;
					}
					// We should now be at the transparent entry so set it fully transparent
					*pTransEntry = 0;
				}
			}
		}
		else if (BitsPerPixel == 24) 
		{
			png_set_IHDR(png_ptr, info_ptr,
				Width,
				Height,
				8, /* bit_depth */
				PNG_COLOR_TYPE_RGB,
				PNG_INTERLACE_NONE,
				PNG_COMPRESSION_TYPE_BASE,
				PNG_FILTER_TYPE_BASE);
		}
		else if (BitsPerPixel == 32) 
		{
			png_set_IHDR(png_ptr, info_ptr,
				Width,
				Height,
				8, /* bit_depth */
				PNG_COLOR_TYPE_RGB_ALPHA,
				PNG_INTERLACE_NONE,
				PNG_COMPRESSION_TYPE_BASE,
				PNG_FILTER_TYPE_BASE);
		}
		else
			ERROR2(FALSE,"OutputPNG::OutputPNGHeader Unknown bit depth");

TRACEUSER( "Jonathan", _T("PNG write: bit_depth = %d color_type = %d\n"),
    png_get_bit_depth(png_ptr, info_ptr),
    png_get_color_type(png_ptr, info_ptr));

		// Could use:-
		// if we are dealing with a grayscale image then
		//info_ptr->sig_bit.gray = true_bit_depth;

		png_set_hIST(png_ptr, info_ptr, NULL);
		png_set_text(png_ptr, info_ptr, NULL, 0); 


		// write the file information
		png_write_info(png_ptr, info_ptr);

TRACEUSER( "Jonathan", _T("PNG write: pixel_depth %d channels %d\n"),
	png_get_bit_depth(png_ptr, info_ptr),
	png_get_channels(png_ptr, info_ptr));
TRACEUSER( "Jonathan", _T("PNG write: rowbytes %d color_type %d\n"),
	png_get_rowbytes(png_ptr, info_ptr),
	png_get_color_type(png_ptr, info_ptr));
		// Set up the transformations you want.
		// Note: that these are all optional.  Only call them if you want them

		// invert monocrome pixels
		//png_set_invert(png_ptr);

		// shift the pixels up to a legal bit depth and fill in as appropriate
		// to correctly scale the image
		//png_set_shift(png_ptr, &(info_ptr->sig_bit));

		// pack pixels into bytes
		//png_set_packing(png_ptr);

		png_set_bgr(png_ptr);

		// swap bytes of 16 bit files to most significant bit first
		png_set_swap(png_ptr);

		// Must set the exception throwing and reporting flags back to their entry states
		File->SetThrowExceptions( OldThrowingState );
		File->SetReportErrors( OldReportingState );

		// er, we seem to have finished OK so say so
		return TRUE;
	}
	
	catch (...)
	{
		// catch our form of a file exception
		TRACE( _T("OutputPNG::OutputPNGHeader CC catch handler\n"));

		// Call up function to clean up the png structures
		CleanUpPngStructures();

		// Must set the exception throwing and reporting flags back to their entry states
		File->SetThrowExceptions( OldThrowingState );
		File->SetReportErrors( OldReportingState );

		// We have finished so reset the PNG exception handling
		PNGUtil::SetCCFilePointer(NULL);

		return FALSE;
	}

	ERROR2( FALSE, "Escaped exception clause somehow" );
}	

/********************************************************************************************

>	BOOL OutputPNG::CleanUpPngStructures()

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/7/96
	Inputs:		-
	Outputs:	-
	Returns:	TRUE if worked, FALSE if failed (error will be set accordingly but not reported)
	Purpose:	Clean up those bits that may have been claimed by the PNG bits.

********************************************************************************************/

BOOL OutputPNG::CleanUpPngStructures()
{
	// If our structures are present then clean them out
	if (png_ptr)
	{
		if (info_ptr)
		{
			png_free(png_ptr, palette);
			palette=NULL;

			png_free(png_ptr, trans);
			trans=NULL;
		}

		// clean up after the write, and free any memory allocated
        png_destroy_write_struct(&png_ptr, &info_ptr);
		png_ptr = NULL;
	}

	return TRUE;
}

/********************************************************************************************

>	BOOL OutputPNG::OutputPNGBits(CCLexFile *File, LPBYTE pBlockStart, BOOL OneBlock = TRUE,
								  BaseCamelotFilter *pFilter = NULL)

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/5/96
	Inputs:		File		pointer to file to output to
				pBlockStart	actual bitmap data to write out
				OneBlock	if TRUE then have all the data so write it out in one go
							if FALSE then need to compress in strips
				pFilter		is an alternative way of handling the progress bar, assume the
							progress bar has been start and just call the IncProgressBarCount in BaseCamelotFilter
							to do the progress bar update. Defaults to NULL i.e. no progress bar.
	Outputs:	-
	Returns:	TRUE if worked, FALSE if failed (error will be set accordingly but not reported)
	Purpose:	Output the actual bits of a bitmap as compressed PNG data. Assumes that a
				header has already been output, possibly using OutputPNGHeader. Assumes that
				all the data is present.
	Errors:		Calls SetError on FALSE returns.
	SeeAlso:	OutputPNG::OutputPNGHeader; 
	SeeAlo:		OutputPNG::StartFile; OutputPNG::WriteBlock; OutputPNG::TidyUp
	Scope:		static

********************************************************************************************/

BOOL OutputPNG::OutputPNGBits(CCLexFile *File, LPBYTE pBlockStart, BOOL OneBlock,
							  BaseCamelotFilter *pFilter)
{
	ERROR2IF(File==NULL,FALSE,"OutputPNG::OutputPNGHeader File pointer is null");
	ERROR2IF(pBlockStart==NULL,FALSE,"OutputPNG::OutputPNGHeader BitmapInfo pointer is null");
	// Check we have the PNG related items claimed (NOTE: p at end means pointer and hence implied *)
	// This would then imply that OutputPNGHeader has been called
	ERROR2IF(png_ptr == NULL || info_ptr == NULL,FALSE,"OutputPNG::OutputPNGHeader PNG related items not set up");

	// Note file in our class variable as used by all the low level routines
	OutputFile = File;

	// Must set the exception throwing flag to True and force reporting of errors to False.
	// This means that the caller must report an error if the function returns False.
	// Any calls to CCFile::GotError will now throw a file exception and should fall into
	// the catch handler at the end of the function.
	// Replaces the goto's that handled this before.
	BOOL OldThrowingState = File->SetThrowExceptions( TRUE );
	BOOL OldReportingState = File->SetReportErrors( FALSE );

	try
	{
		// It is now ready to go and put that data onto the disc
		// so wait for the bitmap data to be prepared

		// turn on interlace handling if you are not using png_write_image()
		INT32 number_passes = 1;
		if (Interlace)
			number_passes = png_set_interlace_handling(png_ptr);

		// Work out how often we need to update the progress bar
		INT32 UpdateEvery = 1;
		if (pFilter == NULL)
		{
			if (number_passes > 1)
				UpdateEvery = (Height/(100*number_passes) + 1);
			else
				UpdateEvery = (Height/100 + 1);
		}
		INT32 LastProgressUpdate = 0;
		// Work out the word/byte rounded line width rather than the pixel width
		INT32 WidthOfLine = DIBUtil::ScanlineSize( Width, BitsPerPixel );
		// The pointer to the actual bitmap data
		LPBYTE pBitsData = pBlockStart;
		LPBYTE pData = pBitsData;
		BOOL JobState = TRUE;

		// Of course being DIBs we need to write the data out upside down! i.e. bottom to top
		for (INT32 pass = 0; pass < number_passes; pass++)
		{
			pBitsData = pBlockStart;
			LastProgressUpdate = 0;
			for (INT32 ypos = 0; ypos < Height; ypos++)
			{
				// Read in from bottom upwards
				pData = pBitsData + ((Height - 1 - ypos)  * WidthOfLine);
				
				// Write that row out to file
				png_write_row(png_ptr, pData);
				
				// Update the progress count, if required
				if (ypos > (LastProgressUpdate + UpdateEvery))
				{
					// Note the update point so that we know the next one  
					LastProgressUpdate = ypos;

					// Now update the progress display, started with 100, but only if pFilter is NULL
					if (pFilter == NULL)
						ContinueSlowJob( (INT32)(100 * ypos/Height * (pass + 1)/number_passes) );
					else
					{
						// Ask the pFilter to update the progress bar for us
						JobState = TRUE;
						pFilter->IncProgressBarCount(1);
					}

					// If JobState is False then the user has probably pressed escape and we should
					// immediately stop what we are doing. 
					if (!JobState)
					{
						File->GotError(_R(IDW_CANCELEXPORT));	// Expects error set on cancel
						return FALSE;
					}
				}
			}
		}

		// write the rest of the file
		png_write_end(png_ptr, info_ptr);

		// Call up function to clean up the png structures
		CleanUpPngStructures();

		// Must set the exception throwing and reporting flags back to their entry states
		File->SetThrowExceptions( OldThrowingState );
		File->SetReportErrors( OldReportingState );

		// We have finished so reset the PNG exception handling
		PNGUtil::SetCCFilePointer(NULL);

		TRACEUSER( "Jonathan", _T("PNG write: Finished\n"));

		// er, we seem to have finished OK so say so
		return TRUE;
	}

//	CATCH( CFileException, e)
	catch (...)
	{
		// catch our form of a file exception
		TRACE( _T("OutputPNG::OutputPNGBits CC catch handler\n"));

		// Call up function to clean up the png structures
		CleanUpPngStructures();

		// Must set the exception throwing and reporting flags back to their entry states
		File->SetThrowExceptions( OldThrowingState );
		File->SetReportErrors( OldReportingState );

		// We have finished so reset the PNG exception handling
		PNGUtil::SetCCFilePointer(NULL);

		return FALSE;
	}

	ERROR2( FALSE, "Escaped exception clause somehow" );
}	

/******************************************************************************************

>	LPBITMAPINFO OutputPNG::GetDestBitmapInfo ( void )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	29/6/00
	Inputs:		pPalette - Palette information that we want to copy from
	Returns:	A pointer to the bitmap information structure.
	Purpose:	Access function to DestBitmapInfo.

******************************************************************************************/

LPBITMAPINFO OutputPNG::GetDestBitmapInfo ( void )
{
	return DestBitmapInfo;
}

/******************************************************************************************

>	LPBYTE OutputPNG::GetDestBitmapBits ( void )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	29/6/00
	Inputs:		pPalette - Palette information that we want to copy from
	Returns:	A pointer to the bitmap itself.
	Purpose:	Access function to DestBitmapBytes.

******************************************************************************************/

LPBYTE OutputPNG::GetDestBitmapBits ( void )
{
	return DestBitmapBytes;
}

/********************************************************************************************

>	BOOL OutputPNG::WriteBlock( UINT32 YPos, UINT32 Height, LPBYTE BlockStart, UINT32 InputBPP = 32,
							 	INT32 ProgressOffset = 0)

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/5/96
	Inputs:		YPos		pixel co-ord of the chunk of DIB we are about to write out (0=bottom,
							increasing as it goes up).
				Height		height in pixels of this chunk
				BlockStart	the start address of the bytes of this chunk
	(optional)	InputBPP	BPP of the input image (assumed 32 by default - 8 also works)
				ProgressOffset	value to add to value passed to ContinueSlowJob (default 0).
	Returns:	TRUE if worked, FALSE if failed (error will be set accordingly but not reported)
	Purpose:	Writes a chunk of bitmap data to the device.
				Assumes a progress hourglass is required and the caller has started an hourglass
				with a size of 100 and will end it.
	Notes:		Originally this routine assumed that it was being given a 32bpp bmp, but using
				the InputBPP param it will now handle 8bpp bmps as well...
	Errors:		Calls SetError on FALSE returns.
	Scope:		Public

********************************************************************************************/

BOOL OutputPNG::WriteBlock( UINT32 YPos, UINT32 Height, LPBYTE BlockStart, UINT32 InputBPP,
							INT32 ProgressOffset)
{
	ERROR2IF(DestBitmapInfo == NULL, FALSE,"OutputPNG::WriteBlock destination bitmap info null");
	ERROR2IF(DestBitmapBytes == NULL, FALSE,"OutputPNG::WriteBlock destination bitmap bits null");
	ERROR2IF(pNextStrip == NULL, FALSE,"OutputPNG::WriteBlock next strip pointer is null");
	
	FNPTR_SCANLINE ConvertFn = NULL;
	LPBYTE Buffer = NULL;
	size_t BufSize = 0L;
	size_t ChunkHeight = 1;
	DIBConvert *DoConvert = NULL;

	// Set up the size and other information for the dib block that we require. This is
	// dependent on the export depth or bpp required.
	if ( !SetUpBlock( &BufSize, &ChunkHeight, &DoConvert, &ConvertFn ) )
		return FALSE;			// Error details already set up

	if (BufSize)
	{
		Buffer = (LPBYTE)CCMalloc( BufSize );
		if (Buffer==NULL)
			return FALSE;
	}

	if ( DoConvert )
	{
		// use new classes to do it
		// 8bpp, 4bpp and 1bpp conversion
		INT32 h = Height;
		INT32 count = 0;
		LPBYTE Data = BlockStart;
		const size_t SourceWidth = DIBUtil::ScanlineSize( BitmapInfo.biWidth, InputBPP ) * ChunkHeight;
		const size_t DestWidth   = DIBUtil::ScanlineSize( BitmapInfo.biWidth, BitmapInfo.biBitCount );

		while (h)
		{
			ENSURE(h >= 0, "bad looping");

			const size_t ThisBit = min( h, (INT32)ChunkHeight );
			if (!DoConvert->Convert( Data, Buffer, ThisBit, IsFirstStrip ))
				break;								// stop if conversion failed

			IsFirstStrip = FALSE;

			// Copy this block to our destination bitmap
			// pNextStrip should be pointing at the next place to copy the data to
			memcpy(pNextStrip, Buffer, ThisBit * DestWidth);

			Data += SourceWidth;
			h -= ThisBit;
			pNextStrip += ThisBit * DestWidth;
			
			// now update the progress display, started with CurrentExportSize
			// CurrentExport size is now the point to go from in the export
			count++;
			ContinueSlowJob( (INT32)(ProgressOffset + count) );
			//ContinueSlowJob( (INT32)(100*count/(Height)) );
		}
	}
	else if ( ConvertFn && Buffer )
	{
		// Write via conversion function
		// 24 bpp convert
		UINT32 h = Height;
		INT32 count = 0;
		LPBYTE Data = BlockStart;
		const size_t SourceWidth = DIBUtil::ScanlineSize( BitmapInfo.biWidth, InputBPP );

		while (h)
		{
			ConvertFn( BitmapInfo.biWidth, Data, Buffer );
			
			// Copy this block to our destination bitmap
			// pNextStrip should be pointing at the next place to copy the data to
			memcpy(pNextStrip, Buffer, BufSize);

			Data += SourceWidth;
			h -= ChunkHeight;
			pNextStrip += BufSize;

			// now update the progress display, started with CurrentExportSize
			// ProgressOffset size is now the point to go from in the export
			count++;
			ContinueSlowJob( (INT32)( ProgressOffset + count ));
			//ContinueSlowJob( (INT32)((CurrentExportSize * count)/Height) );
		}
	}
	else
	{
		// Write the actual bytes out to file. Used to do it in one go but we really
		// require some progress bar indication so we will do it in chunks.
		DWORD BitsSize = BitmapInfo.biSizeImage; 
		if (BitsSize > 0)
		{
			if (BitsSize < 1024)
			{
				// File very small or no progress bar required, so load in one go
				// Copy this block to our destination bitmap
				// pNextStrip should be pointing at the next place to copy the data to
				memcpy(pNextStrip, BlockStart, BitsSize);
				pNextStrip += BitsSize;
			}
			else
			{
				// Load in chunks, for present split into 100 chunks
				DWORD ChunkSize = BitsSize/100;
				DWORD Position = 0;
				LPBYTE pBitInfo = BlockStart;
				
				while (Position < BitsSize)
				{
					if ( (BitsSize - Position) > ChunkSize)
					{
						// Copy this block to our destination bitmap
						// pNextStrip should be pointing at the next place to copy the data to
						memcpy(pNextStrip, pBitInfo, ChunkSize);
					}
					else
					{
						ChunkSize = BitsSize - Position;
						// Copy this block to our destination bitmap
						// pNextStrip should be pointing at the next place to copy the data to
						memcpy(pNextStrip, pBitInfo, ChunkSize);
					}
							
					// Increment our counters/pointers
					Position+=ChunkSize;
					pBitInfo+=ChunkSize;
					pNextStrip += ChunkSize;
					// Progress bar started with height of bitmap
					ContinueSlowJob( (INT32)(ProgressOffset + (Height * Position)/BitsSize) );
					//ContinueSlowJob( (INT32)((CurrentExportSize * Position)/BitsSize) );
				}
			}
		}
	}

	// If present, get rid of our export function
	if (DoConvert)
	{
		delete DoConvert;
	 	DoConvert = NULL;
	}

	CCFree( Buffer );

	HeightWritten += Height;						// remember we wrote this lot

	return TRUE;
}

/********************************************************************************************

>	BOOL OutputDIB::TidyUp()

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/5/96
	Returns:	TRUE if worked, FALSE if failed (error will be set accordingly but not reported)
	Purpose:	When everything has been done via WriteBlock, call this to update the header
				etc. The caller is responsible for closing the file. The class CANNOT be used
				for further output until StartFile is called again.
	Errors:		Calls SetError on FALSE returns.
	Scope:		Public

********************************************************************************************/

BOOL OutputPNG::TidyUp()
{
	// Just in case we have any png related bits left around
	// Call up function to clean up the png structures
	CleanUpPngStructures();

	// Free up the DIB that we have just created
	if (DestBitmapInfo && DestBitmapBytes)
	{
		FreeDIB( DestBitmapInfo, DestBitmapBytes );
		DestBitmapInfo = NULL;
		DestBitmapBytes = NULL;	
	}

	// Call the baseclass version to do its stuff
	const BOOL ok = OutputDIB::TidyUp();

	return ok;
}


