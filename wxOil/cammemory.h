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


// This is the Camelot Memory Manager


/********************************************************************************************

< Memory Manager
< Dynamic Heap

Comment:

\b Overview \b0

The dynamic heap or dynamic memory manager is used in Camelot to manage a shifting set
of memory blocks.  These memory blocks are used to hold objects which are either very
large (e.g. bitmaps) or which frequently change size (e.g. paths/curves etc.).  The blocks
of memory are physically moved around by the memory manager to achieve the best use of the
memory available.


\b Access Restrictions \b0

In order for a client to access the block, a handle must be used, which is translated into
a physical address when access to the block is needed.  This handle is valid only as long
as the block it relates to is in existence.  More importantly, the physical address
associated with a given handle may change across calls to the memory manager.  In particular,
the following memory manager functions may cause the mapping from a handle to a physical
address to change:
MonoOn
		ClaimBlock()
		ReleaseBlock()
		SplitBlock()
		RemoveBlockGaps()
		TidyMemory()
MonoOff
Any other functions will not change the physical address associated with a handle, so it
is safe to call them, and still use the same physical address to access the block.  The
client should be aware that the event processing structure of Camelot means that it is not
safe to assume that physical addresses remain valid across calls to Windows message
processing functions, as Camelot will call the TidyMemory() function on idle events, which
will cause block addresses to change.

These restrictions are also relevant when using the handle manager directly to point into
arbitrary positions in dynamic heap blocks.  Using the handle manager, a client can obtain
a handle which points to any part of their dynamic heap block.  While obtaining this handle,
the client must follow the same constraints as when using a physical address obtained via a
block handle.


\b General Use \b0

The ClaimBlock() function should be used when allocating a block of memory from the dynamic
heap.  This will return a handle for this block, which can be converted to a physical address
using DescribeBlock().  The client can then access the contents of the block using this
address.  It is also possible to use the Handle Manager to obtain extra handles which
refer to arbitrary areas within blocks - such handles are automatically deallocated when the
block itself is deallocated.  This is because the Memory Manager is itself a client of the
Handle Manager, and when deallocating blocks, it instructs the Handle Manager to release any
handles which point into the block in question.

To deallocate a block, use the ReleaseBlock() function, passing the handle of the block
you wish to deallocate. Clients should \i not \i0 pass in a handle that has been allocated
by the Handle Manager directly - the Memory Manager will not deallocate the correct block,
and an error will usually occur.

The remaining function for manipulation of blocks is SplitBlock().  This is a general
purpose function which can remove or insert memory at an arbitrary point within a block.
The heap block is resized to accomodate the increase or reduction in the size of the block
as a result.  This will usually cause heap blocks to move, as mentioned above, and any
physical addresses obtained from handles should be considered invalid, and new versions
should be obtained with DescribeBlock() (or DescribeHandle() if the handle has been obtained
directly from the Handle Manager rather than via the Memory Manager).


\b Debugging \b0

There are two debugging functions (which are only present in the DEBUG build of Camelot).
The first is CheckMemory(), which walks the heap and examines special debugging information
to ensure that the heap structure has not been corrupted.  If the heap has been corrupted,
an assertion failure will occur, with the usual consequences.  The other function is
DumpMemory() which outputs to the debugging stream (DBWIN) the overall structure of the
heap - how many blocks, what size they are, whether they are in use or designated as 'holes',
and how much free memory is available at the time.


SeeAlso:	InitMemory;DeinitMemory;ClaimBlock;DescribeBlock;ReleaseBlock
SeeAlso:	SplitBlock;RemoveBlockGaps;TidyMemory;DumpMemory;CheckMemory
SeeAlso:	Handle Manager


********************************************************************************************/

#ifndef INC_MEMORY
#define INC_MEMORY

#include "handles.h"

extern BOOL 	InitMemory();
extern void 	DeinitMemory();
extern MHANDLE 	ClaimBlock(size_t Size, BOOL Heavy = FALSE);
extern BOOL 	DescribeBlock(MHANDLE Handle, ADDR *Address, size_t *Size);
extern BOOL 	ReleaseBlock(MHANDLE Handle);
extern BOOL 	SplitBlock(MHANDLE Handle, INT32 SplitSize, UINT32 Offset);
extern BOOL 	IncreaseBlock(MHANDLE Handle, UINT32 NumBytes);
extern BOOL 	DecreaseBlock(MHANDLE Handle, UINT32 NumBytes);
extern BOOL 	InsertMemory(MHANDLE Handle, UINT32 Offset, UINT32 NumBytes);
extern BOOL 	RemoveMemory(MHANDLE Handle, UINT32 Offset, UINT32 NumBytes);
extern BOOL 	TidyMemory();
extern void		GetMemoryStatus(UINT64* pPhysRam = NULL, UINT32* pLoadPercent = NULL);

#ifdef _DEBUG
extern void DumpMemory();
extern void SetMemoryFailFlag(BOOL DenyRequests);

#else
#define DumpMemory()
#define SetMemoryFailFlag(x)

#endif // _DEBUG

#endif // INC_MEMORY
