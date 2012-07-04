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

#ifndef INC_HWMAN
#define INC_HWMAN


/*******************************************************************************
>	namespace oilHardwareManager

	Author:		Phil Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	13/12/2005
	Purpose:	Provide the kernel with an invariant API to handle differences
				in hardware (primarilly Byte ordering)
	Notes:		LE means "Little-Endian" (e.g. Intel)
				BE means "Big-Endian" (e.g. PowerPC)
				Native means whichever is the native byte ordering on the current
				platform

*******************************************************************************/

namespace oilHardwareManager
{
	// Avoid aliasing problems
	union DoubleUnion
	{
		double u_double;
		INT64 u_INT64;
	};

	union FloatUnion
	{
		float u_float;
		INT32 u_INT32;
	};

// Byte ordering functions
#if defined(WORDS_BIGENDIAN)
	// __BIG_ENDIAN__
	// Big-Endian hardware, signed
	static inline INT16 BEtoNative(INT16 n) {return n;}
	static inline INT32 BEtoNative(INT32 n) {return n;}
	static inline INT64 BEtoNative(INT64 n) {return n;}

	static inline INT16 LEtoNative(INT16 n) {return wxINT16_SWAP_ALWAYS(n);}
	static inline INT32 LEtoNative(INT32 n) {return wxINT32_SWAP_ALWAYS(n);}
	static inline INT64 LEtoNative(INT64 n) {return wxINT64_SWAP_ALWAYS(n);}

	static inline INT16 NativetoBE(INT16 n) {return n;}
	static inline INT32 NativetoBE(INT32 n) {return n;}
	static inline INT64 NativetoBE(INT64 n) {return n;}

	static inline INT16 NativetoLE(INT16 n) {return wxINT16_SWAP_ALWAYS(n);}
	static inline INT32 NativetoLE(INT32 n) {return wxINT32_SWAP_ALWAYS(n);}
	static inline INT64 NativetoLE(INT64 n) {return wxINT64_SWAP_ALWAYS(n);}

	// Big-Endian hardware, unsigned
	static inline UINT16 BEtoNative(UINT16 n) {return n;}
	static inline UINT32 BEtoNative(UINT32 n) {return n;}
	static inline UINT64 BEtoNative(UINT64 n) {return n;}

	static inline UINT16 LEtoNative(UINT16 n) {return wxUINT16_SWAP_ALWAYS(n);}
	static inline UINT32 LEtoNative(UINT32 n) {return wxUINT32_SWAP_ALWAYS(n);}
	static inline UINT64 LEtoNative(UINT64 n) {return wxUINT64_SWAP_ALWAYS(n);}

	static inline UINT16 NativetoBE(UINT16 n) {return n;}
	static inline UINT32 NativetoBE(UINT32 n) {return n;}
	static inline UINT64 NativetoBE(UINT64 n) {return n;}

	static inline UINT16 NativetoLE(UINT16 n) {return wxUINT16_SWAP_ALWAYS(n);}
	static inline UINT32 NativetoLE(UINT32 n) {return wxUINT32_SWAP_ALWAYS(n);}
	static inline UINT64 NativetoLE(UINT64 n) {return wxUINT64_SWAP_ALWAYS(n);}
	
	// Big-endian, special types
	static inline FIXED16 BEtoNative(FIXED16 n) {return n;}
	static inline FIXED16 LEtoNative(FIXED16 n) {return FIXED16::FromRawLong(wxINT32_SWAP_ALWAYS(n.GetRawLong()));}
	static inline FIXED16 NativetoBE(FIXED16 n) {return n;}
	static inline FIXED16 NativetoLE(FIXED16 n) {return FIXED16::FromRawLong(wxINT32_SWAP_ALWAYS(n.GetRawLong()));}

	static inline float BEtoNative(FloatUnion n) {return n.u_float;}
	static inline float LEtoNative(FloatUnion n) {n.u_INT32 = wxINT32_SWAP_ALWAYS(n.u_INT32); return n.u_float;}
	static inline FloatUnion NativetoBEU(float n) {FloatUnion f; f.u_float=n; return f;}
	static inline FloatUnion NativetoLEU(float n) {FloatUnion f; f.u_float=n; f.u_INT32 = wxINT32_SWAP_ALWAYS(f.u_INT32); return f;}

	static inline double BEtoNative(DoubleUnion n) {return n.u_double;}
	static inline double LEtoNative(DoubleUnion n) {n.u_INT64 = wxINT64_SWAP_ALWAYS(n.u_INT64); return n.u_double;}
	static inline DoubleUnion NativetoBEU(double n) {DoubleUnion f; f.u_double=n; return f;}
	static inline DoubleUnion NativetoLEU(double n) {DoubleUnion f; f.u_double=n; f.u_INT64 = wxINT64_SWAP_ALWAYS(f.u_INT64); return f;}

#else
	// __LITTLE_ENDIAN__
	// Little-Endian, signed
	static inline INT16 BEtoNative(INT16 n) {return wxINT16_SWAP_ALWAYS(n);}
	static inline INT32 BEtoNative(INT32 n) {return wxINT32_SWAP_ALWAYS(n);}
	static inline INT64 BEtoNative(INT64 n) {return wxINT64_SWAP_ALWAYS(n);}

	static inline INT16 LEtoNative(INT16 n) {return n;}
	static inline INT32 LEtoNative(INT32 n) {return n;}
	static inline INT64 LEtoNative(INT64 n) {return n;}

	static inline INT16 NativetoBE(INT16 n) {return wxINT16_SWAP_ALWAYS(n);}
	static inline INT32 NativetoBE(INT32 n) {return wxINT32_SWAP_ALWAYS(n);}
	static inline INT64 NativetoBE(INT64 n) {return wxINT64_SWAP_ALWAYS(n);}

	static inline INT16 NativetoLE(INT16 n) {return n;}
	static inline INT32 NativetoLE(INT32 n) {return n;}
	static inline INT64 NativetoLE(INT64 n) {return n;}

	// Little-Endian, unsigned
	static inline UINT16 BEtoNative(UINT16 n) {return wxUINT16_SWAP_ALWAYS(n);}
	static inline UINT32 BEtoNative(UINT32 n) {return wxUINT32_SWAP_ALWAYS(n);}
	static inline UINT64 BEtoNative(UINT64 n) {return wxUINT64_SWAP_ALWAYS(n);}

	static inline UINT16 LEtoNative(UINT16 n) {return n;}
	static inline UINT32 LEtoNative(UINT32 n) {return n;}
	static inline UINT64 LEtoNative(UINT64 n) {return n;}

	static inline UINT16 NativetoBE(UINT16 n) {return wxUINT16_SWAP_ALWAYS(n);}
	static inline UINT32 NativetoBE(UINT32 n) {return wxUINT32_SWAP_ALWAYS(n);}
	static inline UINT64 NativetoBE(UINT64 n) {return wxUINT64_SWAP_ALWAYS(n);}

	static inline UINT16 NativetoLE(UINT16 n) {return n;}
	static inline UINT32 NativetoLE(UINT32 n) {return n;}
	static inline UINT64 NativetoLE(UINT64 n) {return n;}

	// Little-endian, special types
	static inline FIXED16 BEtoNative(FIXED16 n) {return FIXED16::FromRawLong(wxINT32_SWAP_ALWAYS(n.GetRawLong()));}
	static inline FIXED16 LEtoNative(FIXED16 n) {return n;}
	static inline FIXED16 NativetoBE(FIXED16 n) {return FIXED16::FromRawLong(wxINT32_SWAP_ALWAYS(n.GetRawLong()));}
	static inline FIXED16 NativetoLE(FIXED16 n) {return n;}

	static inline float BEtoNative(FloatUnion n) {n.u_INT32 = wxINT32_SWAP_ALWAYS(n.u_INT32); return n.u_float;}
	static inline float LEtoNative(FloatUnion n) {return n.u_float;}
	static inline FloatUnion NativetoBEU(float n) {FloatUnion f; f.u_float=n; f.u_INT32 = wxINT32_SWAP_ALWAYS(f.u_INT32); return f;}
	static inline FloatUnion NativetoLEU(float n) {FloatUnion f; f.u_float=n; return f;}

	static inline double BEtoNative(DoubleUnion n) {n.u_INT64 = wxINT64_SWAP_ALWAYS(n.u_INT64); return n.u_double;}
	static inline double LEtoNative(DoubleUnion n) {return n.u_double;}
	static inline DoubleUnion NativetoBEU(double n) {DoubleUnion f; f.u_double=n; f.u_INT64 = wxINT64_SWAP_ALWAYS(f.u_INT64); return f;}
	static inline DoubleUnion NativetoLEU(double n) {DoubleUnion f; f.u_double=n; return f;}
#endif

// -------------------------------------------------------------------------------
// Native Unicode character width handling (XAR files always use UTF16)
// Useful reference: http://en.wikipedia.org/wiki/Comparison_of_Unicode_encodings
//
PORTNOTE("WCHARSize", "Check conversion from UTF32 to UTF16 and vice-versa");
	static inline WCHAR NativeToUTF16(WCHAR n) {return n;}		// Just truncate at the moment
	static inline WCHAR UTF16ToNative(WCHAR n) {return n;}		// Just truncate at the moment

};

#endif	// INC_HWMAN
