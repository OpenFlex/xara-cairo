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

//

#ifndef DEFALLOC_H
#define DEFALLOC_H

#include <limits.h>
#include "fixmem.h"

#include "errors.h"


/*
 * the following template function is replaced by the following two functions
 * due to the fact that the Borland compiler doesn't change prediff_t type
 * to type INT32 when compile with -ml or -mh.


template <class T>
inline T* allocate(ptrdiff_t size, T*) {
    set_new_handler(0);
    T* tmp = (T*)(::operator new((size_t)(size * sizeof(T))));
    if (tmp == 0) {
	cerr << "out of memory" << endl; 
	exit(1);
    }
    return tmp;
}
*/
// Declare smart memory handling in Debug builds
#define new CAM_DEBUG_NEW

template <class T>
inline T* Allocate(INT32 size, T*)
{
    T* tmp = (T*)CCMalloc((UINT32)(size * sizeof(T)));
	ERROR2IF(tmp == 0, NULL, "Out of Memory");
    return tmp;
}

/*template <class T>
inline T* Allocate(INT32 size, T*)
{
    T* tmp = (T*)(::operator new((UINT32)(size * sizeof(T))));
	ERROR2IF(tmp == 0, NULL, "Out of Memory");
    return tmp;
} */

template <class T>
inline void Deallocate(T* buffer)
{
    ::operator delete(buffer);
}

template <class T>
inline void Destroy(T* pointer)
{
    pointer->~T();
}

inline void Destroy(char*) {}
inline void Destroy(unsigned char*) {}
inline void Destroy(short*) {}
inline void Destroy(unsigned short*) {}
inline void Destroy(INT32*) {}
inline void Destroy(UINT32*) {}
inline void Destroy(float*) {}
inline void Destroy(double*) {}
inline void Destroy(char**) {}
inline void Destroy(unsigned char**) {}
inline void Destroy(short**) {}
inline void Destroy(unsigned short**) {}
inline void Destroy(INT32**) {}
inline void Destroy(UINT32**) {}
inline void Destroy(float**) {}
inline void Destroy(double**) {}

inline void Destroy(char*, char*) {}
inline void Destroy(unsigned char*, unsigned char*) {}
inline void Destroy(short*, short*) {}
inline void Destroy(unsigned short*, unsigned short*) {}
inline void Destroy(INT32*, INT32*) {}
inline void Destroy(UINT32*, UINT32*) {}
inline void Destroy(float*, float*) {}
inline void Destroy(double*, double*) {}
inline void Destroy(char**, char**) {}
inline void Destroy(unsigned char**, unsigned char**) {}
inline void Destroy(short**, short**) {}
inline void Destroy(unsigned short**, unsigned short**) {}
inline void Destroy(INT32**, INT32**) {}
inline void Destroy(UINT32**, UINT32**) {}
inline void Destroy(float**, float**) {}
inline void Destroy(double**, double**) {}

template <class T1, class T2>
inline void Construct(T1* p, const T2& value)
{
    *p = T1(value);
}

template <class T>
class Allocator
{
public:
    typedef T			ValueType;

    typedef T*			Pointer;
    typedef const T*	ConstPointer;

    typedef T&			Reference;
    typedef const T&	ConstReference;
    
    typedef INT32		SizeType;
    typedef ptrdiff_t	DifferenceType;

    Pointer Allocate(SizeType n)
	{ 
		return ::Allocate((DifferenceType)n, (Pointer)0);
    }

    void Deallocate(Pointer p)
	{
		::Deallocate(p);
	}

    Pointer Address(Reference x)
	{
		return (Pointer)&x;
	}

    ConstPointer ConstAddress(ConstReference x)
	{ 
		return (ConstPointer)&x; 
    }

    SizeType InitPageSize()
	{ 
		return max(SizeType(1), SizeType(4096/sizeof(T))); 
    }

    SizeType MaxSize() const
	{ 
		return max(SizeType(1), SizeType(UINT_MAX/sizeof(T))); 
    }
};

template <>
class Allocator<void>
{
public:
    typedef void* Pointer;
};





#endif		// DEFALLOC_H
