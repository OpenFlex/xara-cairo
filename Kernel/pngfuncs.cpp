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

// Replacements for some libpng functions (pointers to these functions
// are passed to libpng)

#include "camtypes.h"
#include "png.h"
#include "pngprgrs.h"
#include "pngutil.h"

/******************************************************************* 

>       void camelot_png_error(png_structp png_ptr,
										png_const_charp message)

        Author:		Jonathan_Payne (Xara Group Ltd) <camelotdev@xara.com>
        Created:	29/8/2000
        Inputs:		png_ptr, error message
        Outputs:	Error message
        Returns:	void
        Purpose:	Pointer to this function given to libpng to be
					called in case of error.
*******************************************************************/

void camelot_png_error(png_structp png_ptr, png_const_charp message)
{
	TRACEUSER( "Gavin", _T("PNG: libpng error: %s\n"), message);
	
	// Use the error handler in the PNG util function which assumes TRY CATCH block in
	// operation and CCFile present, in which case it will use the CCFile GotError function
	//	PNGUtil::DefaultErrorHandler(MessageID, message);
	PNGUtil::DefaultErrorHandler();
}

/******************************************************************* 

>       void camelot_png_warning(png_structp png_ptr,
								png_const_charp message)

        Author:		Jonathan_Payne (Xara Group Ltd) <camelotdev@xara.com>
        Created:	29/8/2000
        Inputs:		png_ptr, warning message
        Outputs:	Nothing (except a trace message)
        Returns:	void
        Purpose:	Pointer to this function given to libpng to be
					called in case of warning.
*******************************************************************/

void camelot_png_warning(png_structp png_ptr, png_const_charp message)
{
	if (!png_ptr)
		return;
	
	TRACEUSER( "Gavin", _T("PNG: libpng warning: %s\n"), message);
}

/******************************************************************* 

>       void camelot_png_read_data(png_structp png_ptr, 
								png_bytep data, png_size_t length)

        Author:		Jonathan_Payne (Xara Group Ltd) <camelotdev@xara.com>
        Created:	29/8/2000
        Inputs:		png_ptr, amount to be read
        Outputs:	'data' set to data from file
        Returns:	void
        Purpose:	Pointer to this function given to libpng to be
					called for reading data.
*******************************************************************/

void camelot_png_read_data(png_structp png_ptr, png_bytep data, png_size_t length)
{
	iostream *fp = (iostream *)png_get_io_ptr(png_ptr);
	png_uint_32 check = png_uint_32(length);
	
	if (fp)
		fp->read((char *) data, check );
	else
		png_error(png_ptr, "Read Error");
	
	if (check != length)
	{
		png_error(png_ptr, "Read Error");
	}
}

/******************************************************************* 

>       void camelot_png_write_data(png_structp png_ptr, 
								png_bytep data, png_size_t length)

        Author:		Jonathan_Payne (Xara Group Ltd) <camelotdev@xara.com>
        Created:	29/8/2000
        Inputs:		png_ptr, amount to be written, data
        Outputs:	Data in file
        Returns:	void
        Purpose:	Pointer to this function given to libpng to be
					called for writting data.
*******************************************************************/

void camelot_png_write_data(png_structp png_ptr, png_bytep data, png_size_t length)
{
	iostream *fp = (iostream *)png_get_io_ptr(png_ptr);
	png_uint_32 check = png_uint_32(length);

	if (fp)
		fp->write((const char*)data, check);
	else
		png_error(png_ptr, "Write Error");

	if (check != length)
	{
		png_error(png_ptr, "Write Error");
	}
}

/******************************************************************* 

>       void camelot_png_flush_data(png_structp png_ptr)

        Author:		Jonathan_Payne (Xara Group Ltd) <camelotdev@xara.com>
        Created:	29/8/2000
        Inputs:		png_ptr
        Outputs:	Output stream flushed
        Returns:	void
        Purpose:	Pointer to this function given to libpng to be
					called for flushing output stream on write.
*******************************************************************/

void camelot_png_flush_data(png_structp png_ptr)
{
	iostream *fp = (iostream *)png_get_io_ptr(png_ptr);

	if (fp)
		fp->flush();
}

/******************************************************************* 

>       void camelot_png_malloc(png_structp png_ptr, png_size_t size)

        Author:		Jonathan_Payne (Xara Group Ltd) <camelotdev@xara.com>
        Created:	29/8/2000
        Inputs:		png_ptr, size of memory
        Outputs:	Memory block
        Returns:	void * to memory
        Purpose:	Pointer to this function given to libpng to be
					called for allocing memory.
*******************************************************************/

void *camelot_png_malloc(png_structp png_ptr, png_size_t size)
{
	return (CCMalloc(size));
}

/******************************************************************* 

>       void camelot_png_free(png_structp png_ptr, png_voidp data)

        Author:		Jonathan_Payne (Xara Group Ltd) <camelotdev@xara.com>
        Created:	29/8/2000
        Inputs:		png_ptr, &data
        Returns:	void
        Purpose:	Pointer to this function given to libpng to be
					called for freeing data.
*******************************************************************/

void camelot_png_free(png_structp png_ptr, png_voidp data)
{
	CCFree(data);
}

/******************************************************************* 

>       void camelot_png_write_row_callback
			(png_structp png_ptr, png_uint_32 row_number, INT32 pass)

        Author:		Jonathan_Payne (Xara Group Ltd) <camelotdev@xara.com>
        Created:	29/8/2000
        Inputs:		png_ptr, row, pass
        Outputs:	Status bar update
        Returns:	void
        Purpose:	Pointer to this function given to libpng to be
					called when a row has been read.

					IMPORTANT NOTE: This function is not used, I have
					just included it for completness (the write code does
					its own status bar updates).
*******************************************************************/

void camelot_png_write_row_callback
			(png_structp png_ptr, png_uint_32 row_number, INT32 pass)
{
}
