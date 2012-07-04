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
//#include "app.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "bmanip.h"

/******************************************************************************************

>	BOOL CBitmapManip::ApplyGaussianFilter(BYTE * bits, INT32 wid, INT32 hei, INT32 matrix[3][3],
			INT32 index)


	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	1-10-98

	Inputs:		The source bitmap bits, its width and height and the matrix to apply

	Returns:	-

	Purpose:	Applies a 3x3 matrix to the bitmap's alpha channel

	Notes:		Remember DIB's are held upside-down in memory

******************************************************************************************/
BOOL CBitmapManip::ApplyGaussianFilter(BYTE * bits, INT32 wid, INT32 hei, INT32 matrix[3][3], 
									   BOOL bIgnoreBlankPixels)
{
	// we need a temporary bitmap
	INT32 ksize = (wid) * (hei) * 4;

	BYTE * tmpBits = new BYTE[ksize];

	if (!tmpBits)
		return FALSE;

	memcpy(tmpBits, bits, ksize);

	INT32 size = wid * hei;
	size -= wid * 2;
	size -= 2;

	COLORREF *srcPtr = ((COLORREF *)bits);
	COLORREF *destPtr = ((COLORREF *)tmpBits) + wid + 1;

	UINT32 srcAlpha = 0;
	UINT32 destAlpha = 0;

	INT32 incBy1 = wid*4;

	INT32 sum = 0;

	INT32 posX = 0;
	INT32 posY = 1;

	COLORREF Area[3][3];

	INT32 i = 0;
	INT32 j = 0;

	BYTE R = 0;
	BYTE A = 0;

	INT32 SumR;
	INT32 SumA;

	while (posY < hei - 1)
	{
		// transfer colour
		for (i = 0 ; i < 3; i++)
		{
			for (j = 0 ; j < 3; j++)
			{
				Area[i][j] = *(srcPtr + i * wid + j);
			}
		}

		// now, ignore transparent areas
		if (((Area[1][1] & 0xff000000) >> 24) != 0xff || !bIgnoreBlankPixels)
		{
			SumR = 0;
			SumA = 0;
			sum = 0;

			for (i = 0 ; i < 3; i++)
			{
				for (j = 0 ; j < 3; j++)
				{
					A = (BYTE)(Area[i][j] & 0xff000000) >> 24;
					R = (BYTE)(Area[i][j] & 0xff);
					
					if (A != 0xff || !bIgnoreBlankPixels)
					{
						SumR += ((INT32)R) * matrix[i][j];
						SumA += ((INT32)A) * matrix[i][j];
						sum += matrix[i][j];
					}
				}
			}

			SumR /= sum;
			SumA /= sum;
			
			*destPtr = SumR + (SumR << 8) + (SumR << 16) + (SumA << 24);
		}

		// increment of pointers
		posX ++;
		
		destPtr ++;
		srcPtr ++;

		if (posX >= wid - 3)
		{
			destPtr += 3;
			srcPtr += 3;
			posX = 0;
			posY ++;
		}	
	}

	memcpy(bits, tmpBits, wid * hei * 4);

	delete [] tmpBits;

	return TRUE;
}
