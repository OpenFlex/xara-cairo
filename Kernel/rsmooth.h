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

// Contains class definitions for retrosmoothing functions

/*
*/

#ifndef INC_RETSMOOTH
#define INC_RETSMOOTH

//#include "selop.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "doccoord.h" - in camtypes.h [AUTOMATICALLY REMOVED]

#define SMOOTH_MAX (2000*2000)
#define SMOOTH_MIN (256*256)

#define OPTOKEN_RETROSMOOTH _T("RetroSmooth")


//	define a region type to hold region start, end values

struct Set {
	INT32 first;
	BOOL Finclusive;
	INT32 last;
	BOOL Linclusive;
};

#define ITEM_TYPE Set

class NodePath;

/******************************************************************************

	class DynArray

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created: 	16/11/94
	Purpose: 	A temporary class to control a dynamic array of doccoords.
				This will be replaced by a template class whenever we can
				use the template directive.
	
******************************************************************************/

class DynArray {

	public:
		DynArray();
		~DynArray();
        BOOL		Initialise(INT32 inititems, INT32 newitems);
        ITEM_TYPE*	GetFirstItem();
        INT32		NumItems() { return UsedSlots; };
        BOOL		AddItem(ITEM_TYPE&);
		void		DeleteItems(INT32 firstitem, INT32 numitems);
        void    	Empty(BOOL compress=TRUE);
        ITEM_TYPE&	operator[](const INT32 i);
		void 		Compact();
		BOOL 		CloneFrom(DynArray* SourceArray);

	private:
        BOOL	MakeSpaceInList(const INT32 numitems);

	private:
		MHANDLE BlockHandle;

		INT32	UsedSlots;
        INT32	UnusedSlots;
        INT32	SlotInitSize;
        INT32	SlotAllocSize;

};


/******************************************************************************

> class RetroSmooth

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created: 	11/11/94
	Purpose: 	A new class to control retro smoothing of path regions.

******************************************************************************/

class RetroSmooth
{
	public:
    	RetroSmooth();
		BOOL	Initialise();
		void 	Changing(NodePath* pNodePath, Spread* pSpread, double smooth);
		void 	Finished();
		void	Invalidate();
		double	ReturnCachedAccuracy(Path* pPath);

		// non-undoable version of finished. does not launch an operation
		BOOL	FinishedNoUndo(NodePath* pNodePath);
		void	SetRenderFlag(BOOL Render);
	private:
		BOOL 	Starting(NodePath* pDocNodePath);
		void	Update();
		BOOL 	RenderRegions();
		BOOL	NewPathToSmooth(NodePath* pNodePath);
		BOOL 	MatchRegions(NodePath* pNodePath);
		BOOL 	RecordPathRegions(Path* pPath);
		void	AlterRegion(INT32 index, INT32 newstart, INT32 newend);
		INT32	FindMasterRegion();
		void	TranslateRetroData(Path* pPath);

	private:
		BOOL		RetroSmoothing;
		NodePath* 	pRetroNode;				// a pointer to the current 'retro' node
		Spread*		pRetroSpread;
		Path		RetroPath;				// the original path points we need
		Path		RetroEorPath;			// the current path points after smoothing
		DynArray	RetroEorRegion;			// the working path regions
		double		RetroSmoothPercent;		// the current cached percentage
		double		RetroSmoothAcc;			// the current retro smoothing accurary
		INT32		RetroPathCRC;			// cyclic reduncancy for the EorPath
		INT32		RetroSelCRC;			// cyclic redundancy for the Selected points

		BOOL		m_bRender;				// flag to say whether or not we should do EOR rendering
};


/********************************************************************************************

>	class OpRetroSmooth : public SelOperation

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	7/10/94
	Purpose:	

********************************************************************************************/

class OpRetroSmooth : public SelOperation
{

CC_DECLARE_DYNCREATE(OpRetroSmooth)

public:
	OpRetroSmooth();
	static BOOL		Init();				
	static OpState	GetState(String_256*, OpDescriptor*);		
	void			GetOpName(String_256* OpName);
	void			DoRetroSmooth(NodePath* pNode, Path* pPath, double smoothacc);
};


#endif
