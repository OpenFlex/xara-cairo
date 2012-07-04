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

#ifndef _STL_H_
#define _STL_H_

#ifndef _WINDOWS
#error  STL probably won't compile on this platform (adrian 22/05/97)
#endif

#ifndef __AFX_H__
#error MFC headers should be included before STL
#endif

#if _MFC_VER  > 0x0420 // VC5 STL- this may have to be fixed, I don't have it installed and can't check if the headers names are correct

#define STL_SINGLETHREADED // the multihreaded version doesn't link yet
namespace stl 
{ 
#include "algo.h"
#include "stdalloc.h"
#include "stlfunc.h"
#include "hash_map.h"
#include "hash_set.h"
#include "heap.h"
#include "iteratr.h"
#include "map.h"
#include "multimap.h"
#include "multiset.h"
#include "pair.h"
#include "set.h"
#include "tstack.h"
#include "tempbuf.h"
#include "bvector.h"
#include "deque.h"
#include "hashtable.h"
#include "tlist.h"
#include "tree.h"
#include "vector.h"
}
#define STL stl

#else // VC4.1/4.2

#define STL_SINGLETHREADED // the multihreaded version doesn't link yet
namespace stl 
{ 
#include "algo.h"
#include "stdalloc.h"
#include "function.h"
#include "hash_map.h"
#include "hash_set.h"
#include "heap.h"
#include "iteratr.h"
#include "map.h"
#include "multimap.h"
#include "multiset.h"
#include "pair.h"
#include "set.h"
#include "tstack.h"
#include "tempbuf.h"
#include "bvector.h"
#include "deque.h"
#include "hashtable.h"
#include "tlist.h"
#include "tree.h"
#include "vector.h"
}
#define STL stl

#endif // _MFC_VER  > 0x0410
#endif // _STL_H_
