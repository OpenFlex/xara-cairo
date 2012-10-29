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
#include "ai8_eps.h"
#include "ai_layer.h"

//#include "tim.h"

DECLARE_SOURCE("$Revision");


#define new CAM_DEBUG_NEW


CC_IMPLEMENT_DYNAMIC(AI8EPSFilter, AI5EPSFilter)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/********************************************************************************************

>	AI8EPSFilter::~AI8EPSFilter()

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	28/03/00

	Purpose:	Default constructor, which sets the class details.

********************************************************************************************/

AI8EPSFilter::AI8EPSFilter()
{
	// Set up filter descriptions.
	FilterNameID = _R(IDT_AI8EPS_FILTERNAME);
	FilterInfoID = _R(IDT_AI8EPS_FILTERINFO);
	ImportMsgID  = _R(IDT_IMPORTMSG_AI8);

	FilterID = FILTERID_AI8EPS;

	// This filter only supports import
	Flags.CanImport = TRUE;
	Flags.CanExport = FALSE;
}

/********************************************************************************************

>	AI8EPSFilter::~AI8EPSFilter()

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	28/03/00

	Purpose:	Default destructor. Cleans up all instantiated data for the class.

********************************************************************************************/

AI8EPSFilter::~AI8EPSFilter()
{
	// Currently, nothing needs to be done.
}

/********************************************************************************************

>	BOOL AI8EPSFilter::Init()

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	28/03/00

	Purpose:	Since the constructor can't fail, it does things that the constructor can't
				do.

	Returns:	TRUE if the filter was initialised ok, FALSE otherwise.

********************************************************************************************/

BOOL AI8EPSFilter::Init()
{
	// Get the OILFilter object
	pOILFilter = new AI8EPSOILFilter(this);
	if (pOILFilter == NULL)
		return FALSE;

	// Load the description strings
	FilterName.Load(FilterNameID);
	FilterInfo.Load(FilterInfoID);

	// All ok
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// I M P O R T ////////////////////////////////////////////
//
//	Note: All import responsibility is delegated to the parent class
//
/////////////////////////////////////////////////////////////////////////////////////////////

/********************************************************************************************

>	virtual INT32 AI8EPSFilter::EPSHeaderIsOk(ADDR pFileHeader, UINT32 HeaderSize)

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	28/03/00

	Purpose:	Checks to see if the EPS comment headers specify that this is an AI
				generated EPS file, as required.

	Returns:	TRUE if the header is ok and import should proceed, FALSE if not.

	The header for AI8.0 begins....

		%!PS-Adobe-3.0 
		%%Creator: Adobe Illustrator(R) 8.0
		%%AI8_CreatorVersion: 8

********************************************************************************************/

INT32 AI8EPSFilter::EPSHeaderIsOk(ADDR pFileHeader, UINT32 HeaderSize)
{
	UINT32	Lines	= 0;
	TCHAR	*Buffer	= NULL;

	// !PS-Adobe line is ok - check creator line...
	CCMemTextFile HeaderFile ( reinterpret_cast<char *> ( pFileHeader ), HeaderSize );

	if( HeaderFile.IsMemFileInited () == FALSE || HeaderFile.InitLexer () == FALSE )
	{
		HeaderFile.close();
		return 0;
	}

	// Graeme (28/6/00) - Adobe have changed their file format, and so the first line can
	// now be a %PDF directive. Therefore look for this directive in the first twenty
	// lines.
	while ( ( Lines < 100 ) && !HeaderFile.eof () )
	{
		// Get the current line from the file.
		HeaderFile.GetLineToken();
		Buffer = const_cast<TCHAR *> ( HeaderFile.GetTokenBuf () );

		// Ensure that it's OK.
		ERROR2IF(Buffer == 0, 0, "Returned buffer from lex file == 0");

		// Increment the line counter.
		Lines++;

		if (camStrncmp(Buffer, _T("%!PS-Adobe"), 10) == 0)
		{
			// Now find the %%Creator string.
			while ((Lines < 100) && !HeaderFile.eof())
			{
				HeaderFile.GetLineToken();
				Buffer = const_cast<TCHAR *> ( HeaderFile.GetTokenBuf() );
				ERROR2IF(Buffer == 0, 0, "Returned buffer from lex file == 0");
				Lines++;

				// Return TRUE if this file was created by Illustrator, or has been exported in 
				// Illustrator format.
				if (camStrncmp(Buffer, _T("%%Creator: Adobe Illustrator(R) 8"), 33) == 0)
				{
					// We definitely want this.
					HeaderFile.close();
					return 10;
				}

				// Check to see if it's from Illustrator 9. If you're writing a dedicated AI9
				// filter, then you really should remove this code.
				else if (camStrncmp(Buffer, _T("%%Creator: Adobe Illustrator(R) 9"), 33) == 0)
				{
					// We probably want this. Note: I'm returning 9 because a native AI9
					// filter would return 10, and if this code is left in, it will be
					// ignored.
					HeaderFile.close();
					return 9;
				}

				if (camStrncmp(Buffer, _T("%%Creator:"), 10) == 0)
				{
					// Found the creator line - does it contain the word Illustrator?
					if (camStrstr( (const TCHAR*)Buffer, _T("Illustrator(R) 8")) != NULL)
					{
						HeaderFile.close();
						return 10;
					}
					
					// Try to see if it's Illustrator 9. Again, remove this code when you're
					// writing a dedicated AI9 filter.
					else if (camStrstr( (const TCHAR*)Buffer, _T("Illustrator(R) 9")) != NULL)
					{
						HeaderFile.close();
						return 9;
					}

					// Not an AI file.
					else
					{
						break;
					}
				}

				// If we find the compression token then stop the search as we don't want to
				// start looking in the compressed data!
				if (camStrncmp(Buffer, _T("%%Compression:"), 14)==0)
					break;
			}

			// Remember to close the file before returning.
			HeaderFile.close();

			// Didn't find a suitable Creator line, but the EPS line was ok, so return
			// that we're interested, but not sure.
			return 5;
		}

		// If we find the compression token then stop the search as we don't want to start
		// looking in the compressed data!
		if (camStrncmp(Buffer, _T("%%Compression:"), 14)==0)
			break;
	}

	// Remember to close the file before returning.
	HeaderFile.close();
	
	// This file type isn't suitable.
	return 0;
}

/********************************************************************************************

>	void AI8EPSFilter::LookUpToken()

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	28/03/00

	Purpose:	Compare the current token against the AI keywords to see if it is
				one of them.

				Currently 8.0 checks only for its version of the layer operator which differs
				from previous versions.

********************************************************************************************/

void AI8EPSFilter::LookUpToken()
{
	// Currently I do not have documentation for the AI 8 tokens, and so am passing the
	// token directly to the base class.
	AI5EPSFilter::LookUpToken();
}

/********************************************************************************************

>	BOOL AI5EPSFilter::ProcessToken()

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	28/03/00

	Purpose:	Checks if we're looking at the version 8.0 layer token otherwise delegates
				to the base class.

********************************************************************************************/

BOOL AI8EPSFilter::ProcessToken()
{
	// Graeme (8/5/00) - The only AI8 token that we're handling at the moment is Lb,
	// which is a modified version of the AI5 Lb token. As such, all responsibility
	// for token processing is being passed to the base class.
	return AI5EPSFilter::ProcessToken();
}

/********************************************************************************************

>	BOOL AI8EPSFilter::DecodeLayer ( void )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	8/5/00
	Inputs:		-  
	Returns:	TRUE	- The command was processed.
				FALSE	- It wasn't used by this filter.
	Purpose:	Inserts a layer into the tree.

********************************************************************************************/

BOOL AI8EPSFilter::DecodeLayer ( void )
{
	// If there's still an active layer, the LB token has been missed out, so throw an EPS
	// error message.
	if ( mpLayerProc != NULL )
	{
		return FALSE;
	}

	// Create the new layer processor.
	mpLayerProc = new AILayerProcessor;

	ERROR2IF( mpLayerProc == NULL, FALSE, "Insufficient memory to create layer processor.");

	// Insert the layer into the tree.
	return mpLayerProc->DecodeAI8Lb ( *this );
}
