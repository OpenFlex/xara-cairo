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

// A Limited Memory allocator

#ifndef INC_TUNEMEM
#define INC_TUNEMEM


/********************************************************************************************

>	class TunedMemory : public CC_CLASS_MEMDUMP

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	1/5/95
	Purpose:	This is a shell around the CCMalloc and CCFree memory allocator. If you
				use this class to get the memory, the total alloc'ed memory will not
				exceed the amount set in this class. This is used to allow the user to
				say how much memory they are prepared to commit to the off-screen bitmap
				used in rendering. If there is not enough, GRenderRegions will band thier
				output to use up less ram.

********************************************************************************************/

class TunedMemory : public CC_CLASS_MEMDUMP
{
	// Give my name in memory dumps
	CC_DECLARE_MEMDUMP(TunedMemory);

public:
	// construction
	TunedMemory();
	~TunedMemory();

	// Functions to get and free memory
	LPVOID LimitedCCMalloc(size_t Size);
	LPVOID LimitedCCRealloc(LPVOID buf, size_t NewSize);
	void LimitedCCFree(LPVOID buf);

	// Functions to find out how much ram is left from the amount available
	size_t GetTotalTunedMem();
	size_t GetAvailableTunedMem();

	// Functions to help comunicate with the Options Dialog
	static size_t GetLimitedMemSize();
	static size_t SetLimitedMemSize(size_t NewSize);
	
	static BOOL IsMemSizeInfinite();
	static void SetMemSizeInfinte(BOOL NewIsInfinite);

	static INT32 GetScreenMemSize();

	static BOOL IsAutomaticMemory();
	static void CalculateRecommendedMemory();

	// Function to read and write the prefs to the ini file
	static BOOL Init();

// member vars
protected:
	// The total is also saved out as a preference
	static BOOL			IsInfinite;
	static size_t		TotalRAM;
	static size_t		AvailableRAM;

	static BOOL			SmartBanding;

	static size_t		LimitRAM;
	static BOOL			RecommendInfinite;
	static INT32			RecommendRAM;
};


#endif  // INC_TUNEME


