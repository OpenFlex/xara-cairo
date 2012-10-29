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
// Declaration of PathBecomeA.
//

#ifndef INC_PBECOMEA
#define INC_PBECOMEA




/********************************************************************************************

>	class PathBecomeA : public BecomeA

	Author:		Karim_MacDonald (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10 February 2000
	Purpose:	Converts nodes to paths.

	Notes:		Karim 31/10/2000
				Moved into its own source files from nodeclip.h/.cpp, as it really isn't
				related to NodeClipView et al.

********************************************************************************************/
class PathBecomeA : public BecomeA
{
// runtime class info.
CC_DECLARE_MEMDUMP(PathBecomeA)

public:

enum OutlineRules
{
	STRIP_OUTLINES,		//	remove areas covered by outline from the final path.
	ADD_OUTLINES,		//	add areas covered by outline to the final path.
	IGNORE_OUTLINES		//	don't worry about outlines at all.
};

	// constructor/destructor.
	PathBecomeA(	BecomeAReason baReason, CCRuntimeClass* pClass,
					UndoableOperation* pUndoOp, BOOL bSel, Path* pResultPath,
					enum OutlineRules OutlineRule = IGNORE_OUTLINES );
	~PathBecomeA();

	// the passback method to be called by Node::DoBecomeA when Reason == BECOMEA_PASSBACK.
	virtual BOOL PassBack(	NodeRenderableInk* pNewNode,
							NodeRenderableInk* pCreatedByNode,
							CCAttrMap* pAttrMap = NULL );

protected:
	// the accumulated path of all passed-back objects.
	Path* m_pResultPath;

private:
	Path* ExtractOutlineAsPath(NodePath* pSrcNodePath, CCAttrMap* pAttrMap);

	// whether to strip off, add on, or just not worry about object outlines.
	enum OutlineRules m_OutlineRule;

	// this rule is set in our constructor, depending on m_OutlineRules;
	// the value within tells ClipPathToPath what to do with our outlines - strip or add.
	UINT32 m_ClipPathRule;
};



//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------



/********************************************************************************************

>	class ContourBecomeA2 : public PathBecomeA

	Author:		Karim_MacDonald (Xara Group Ltd) <camelotdev@xara.com>
	Created:	21/11/2000
	Inputs:		
	Outputs:	
	Returns:	
	Purpose:	ContourBecomeA2 class provides a greener alternative to ContourBecomeA.

				Reasons to use us:
				It deals with all lines correctly, because it doesn't simulate line width by
				contouring out from lines (like ContourBecomeA), but actually strokes them,
				and contours outwards from the result.

				Reasons not to use us:
				1.	We don't currently deal with brush strokes correctly.
				2.	We currently only do rounded contours - no bevelled or mitred contours.

				Example usage:
					Path ContourPath;
					ContourPath.Initialise();
					ContourBecomeA2 baContour(NULL, MillipointWidth, &ContourPath)
					BOOL Success = pSourceNode->DoBecomeA(&baContour);

					( source node not included :o] )

********************************************************************************************/
class ContourBecomeA2 : public PathBecomeA
{
CC_DECLARE_MEMDUMP(ContourBecomeA2);

public:
	// constructor/destructor.
	ContourBecomeA2(	UndoableOperation* pUndoOp,
						MILLIPOINT Width, Path* pResultPath );

	// the passback method to be called by Node::DoBecomeA when Reason == BECOMEA_PASSBACK.
	virtual BOOL PassBack(	NodeRenderableInk* pNewNode,
							NodeRenderableInk* pCreatedByNode,
							CCAttrMap* pAttrMap = NULL );

protected:
	MILLIPOINT m_Width;
};



#endif	// INC_PBECOMEA
