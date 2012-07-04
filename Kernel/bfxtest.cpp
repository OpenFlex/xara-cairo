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

// This file implents the BitmapEffect class

/*
*/

#include "camtypes.h"
//#include "errors.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "bfxtest.h"

//#include "bitmap.h" - in camtypes.h [AUTOMATICALLY REMOVED]

// for test
#include "bitmpinf.h"
#include "bfxalu.h"

// This is not compulsory, but you may as well put it in so that the correct version
// of your file can be registered in the .exe
DECLARE_SOURCE("$Revision: 1282 $");

// An implement to match the Declare in the .h file.
// If you have many classes, it is recommended to place them all together, here at the start of the file
CC_IMPLEMENT_DYNCREATE(TestBitmapEffect, BitmapEffect)

// This will get Camelot to display the filename and linenumber of any memory allocations
// that are not released at program exit
#define new CAM_DEBUG_NEW

/********************************************************************************************

>	BOOL TestBitmapEffect::Run()
					
	Author:		Alex_Bligh (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/10/94
	Inputs:		a value
	Outputs:	none
	Returns:	nothing
	Purpose:	Internal test routine
	Errors:		none
	SeeAlso:	-

A test routine

********************************************************************************************/
 
BOOL TestBitmapEffect::Run()
{

/*
	INT32 x, y, i, j;
	
	fixed16 conv[3][3];
	fixed16 convsum;

	BitmapInfo BMInfo;
	Source->ActualBitmap->GetInfo(&BMInfo);

	conv[0][0]=(fixed16)	2.0;	conv[0][1] =(fixed16)	2.0;	conv[0][2]=(fixed16)	2.0;
	conv[1][0]=(fixed16)	2.0;	conv[1][1] =(fixed16)	2.0;	conv[1][2]=(fixed16)	2.0;
	conv[2][0]=(fixed16)	2.0;	conv[2][1] =(fixed16)	2.0;	conv[2][2]=(fixed16)	2.0;

	convsum=(fixed16) 0.0;

	for (i=0; i<3; i++) for(j=0; j<3; j++) convsum+=conv[i][j];
	if (convsum!=(fixed16)0) for (i=0; i<3; i++) for(j=0; j<3; j++) conv[i][j]=conv[i][j]/convsum;

	for (y=0; y<(INT32) BMInfo.PixelHeight; y++) for (x=0; x<(INT32) BMInfo.PixelWidth; x++)
	{
		fixed16 r=0.5; //0.5 for final rounding
		fixed16 g=0.5;
		fixed16 b=0.5;
		UINT32 v;
		for (i=0; i<3; i++) for(j=0; j<3; j++)
		{
			v=Source->ReadPixel( (i+x-1<0?0:(i+x-1>=(INT32)BMInfo.PixelWidth?BMInfo.PixelWidth-1:i+x-1)),
								 (j+y-1<0?0:(j+y-1>=(INT32)BMInfo.PixelHeight?BMInfo.PixelHeight-1:j+y-1)));								 
			r+=conv[i][j]*(fixed16)((INT32)(v & 0xFF));
			g+=conv[i][j]*(fixed16)((INT32)((v & 0xFF00)>>8));
			b+=conv[i][j]*(fixed16)((INT32)((v & 0xFF0000)>>16));
		}
		if (convsum==(fixed16)0)
		{
			r+=128;
			g+=128;
			b+=128;
		}
		if (r<0) r=0;
		if (g<0) g=0;
		if (b<0) b=0;
		if (r>255) r=255;
		if (g>255) g=255;
		if (b>255) b=255;
		Destination->PlotPixel(x,y,(r.MakeLong())+((g.MakeLong())<<8)+((b.MakeLong())<<16) );
	}
	
	return TRUE;
*/
	TCHAR buf[256];
	
	clock_t Timer = clock();											// start clock

	INT32 i,j;
	INT32 ITER;
	BOOL dummybool=TRUE;
	BOOL ShiftPressed;
	KernelBitmap * Temp;
	
	ShiftPressed = ((GetAsyncKeyState( CAMKEY(SHIFT) ) & 0x8000 )!=0);


	if (ShiftPressed)
	{
		ITER=1;
	}
	else
	{
		ITER=1;
	}
	
	
//BfxALULUT LUT;
//LUT.LinearABK(0.09375,0.90625,0);
//Timer = clock() - Timer;											// stop clock
	
	for (i=1; i<=ITER; i++)
	{
		if ((Temp = ALU->NewBitmap(Source)) &&
			ALU->SetA(Temp) &&
			ALU->ZeroA() &&
			ALU->SetB(Source) &&
			ALU->SetT((DWORD) 0x00) &&
			ALU->PartTAB() &&
			TRUE)
		{	
			for (j=1; j<=10; j++)
				dummybool=(
		
			ALU->SetA(Destination) &&
			ALU->ZeroA() &&
		
			ALU->SetB(Temp) &&
			ALU->AddKAB(0x80) &&

			ALU->ZeroA() &&
		
			ALU->SetB(Temp) &&
			ALU->AddKAB(0x80) &&

			ALU->SetB(Temp,0,1) &&
			ALU->AddKAB(0x18) &&	

			ALU->SetB(Temp,0,-1) &&
			ALU->AddKAB(0x18) &&	
		
			ALU->SetB(Temp,1,0) &&
			ALU->AddKAB(0x18) &&	
		
			ALU->SetB(Temp,-1,0) &&
			ALU->AddKAB(0x18) &&

			ALU->SetB(Temp,1,1) &&
			ALU->AddKAB(0x08) &&	
		
			ALU->SetB(Temp,-1,1) &&
			ALU->AddKAB(0x08) &&	
		
			ALU->SetB(Temp,1,-1) &&
			ALU->AddKAB(0x08) &&	
		
			ALU->SetB(Temp,-1,-1) &&
			ALU->AddKAB(0x08) &&

			ALU->SetA(Temp) &&
			ALU->SetB(Destination) &&
			ALU->PartTAB() &&
		
			TRUE);

			delete Temp;
		}
	}
	Timer = clock() - Timer;											// stop clock

//ALU->SetA(Destination);
//ALU->SetB(Source,-20,20);
//ALU->PlotBLUT(&LUT);

	// as this is for our use only, it is permitted to hard-code English strings

	// this lovely line translates the clock_t value into a useful value without using
	// floats
	wsprintf( buf, "Done %d iterations. Each took %d.%03d secs",	ITER, (INT32)(Timer / (CLOCKS_PER_SEC*ITER)),
								(INT32)((Timer % (CLOCKS_PER_SEC*ITER)) * 1000 / (CLOCKS_PER_SEC*ITER)) );

	if (ShiftPressed) AfxMessageBox( buf );

	return dummybool;
	}
