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

// NodeBlend definition

#ifndef	INC_BLEND
#define	INC_BLEND

//#include "group.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "ops.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "blendatt.h"
//#include "biasgain.h" - in camtypes.h [AUTOMATICALLY REMOVED]

#pragma warning(disable: 4786)
#include <list>
#pragma warning(default: 4786)

class RenderRegion;
class String_32;
class NodeRect; 
class BlendPath; 
class NodeBlendPath;
class NodeBlender;

/********************************************************************************************

>	class NodeBlend: public NodeGroup

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com> M
	Created:	6/10/94
	Purpose:	The NodeBlend class

********************************************************************************************/

class NodeBlend: public NodeGroup
{
public: 
	CC_DECLARE_DYNAMIC( NodeBlend )    
	
	NodeBlend(); 
	
	NodeBlend(Node* ContextNode,  
			  AttachNodeDirection Direction,    
			  BOOL Locked=FALSE, 
			  BOOL Mangled=FALSE,  
			  BOOL Marked=FALSE, 
			  BOOL Selected=FALSE    
		     ); 
		     
	// Virtual rendering functions	     
	virtual void PreExportRender( RenderRegion* pRender ); 
	virtual BOOL ExportRender( RenderRegion* pRender ); 
	virtual void RenderBlendBlobs(RenderRegion* pRender);
	virtual void RenderObjectBlobs(RenderRegion* pRegion);

	void RenderBlendOnCurveBlobs(RenderRegion* pRegion);

	// Bounds-related funcs
	void InvalidateBlendBoundingRect();
	DocRect GetBlobBoundingRect();
	BOOL AreBoundsValid() { return IsBoundingRectValid; }
	virtual DocRect	GetBoundingRect(BOOL DontUseAttrs=FALSE, BOOL HitTest=FALSE);

	// Export-related funcs
	BOOL IsArtWorksEPSCompatible();
	INT32 GetNumInkObjects();

	// Other virtual functions
	virtual String Describe(BOOL Plural, BOOL Verbose); 
	virtual Node* SimpleCopy();  
    virtual UINT32 GetNodeSize() const; 			// Returns size of node in bytes
	virtual BOOL OnNodePopUp(Spread* pSpread, DocCoord PointerPos, ContextMenu* pMenu);
	virtual BOOL PostImport();
	virtual BOOL IsABlend () { return (TRUE); }

	// Functions to deal with messages
	virtual BOOL OnClick( DocCoord, ClickType, ClickModifiers, Spread* );
	virtual BOOL HidingNode();
	virtual BOOL ShowingNode();

	// Fuctions that allows ops and other nodes to inform this node of events on it's children
	virtual ChangeCode 	OnChildChange(ObjChangeParam* pParam);
	virtual BOOL 		AllowOp(ObjChangeParam* pParam, BOOL SetOpPermissionState = TRUE,
														BOOL DoPreTriggerEdit = TRUE);

	// Utility funcs 
	BOOL IsPointOverBlob(DocCoord* pPointerPos,
						 BlendPath** ppBlendPath,
						 INT32* pIndex,
						 BOOL* pAStart,
						 UINT32* pRemapRef);

	BOOL Remap(UINT32 RemapRef,DocCoord PosStart,DocCoord PosEnd,DocCoord* pInvPosStart, DocCoord* pInvPosEnd);
	UINT32 GetNumBlenders();
	NodeBlender* FindFirstBlender();
	NodeBlender* FindNextBlender(NodeBlender* pNodeBlender);
	NodeBlender* FindLastBlender();
	BOOL FindFirstAndLastBlenders(NodeBlender** ppFirstBlender, NodeBlender** ppLastBlender);

	// The OneToOne flag
	BOOL IsOneToOne();
	void SetOneToOne(BOOL state);

	// The NotAntialiased flag - TRUE when we don't want the blend steps to antialiased
	BOOL IsNotAntialiased();
	void SetNotAntialiased(BOOL state);

 	// Replace DoBecomeA() so that the blend node can turn itself into a group
	virtual BOOL DoBecomeA(BecomeA* pBecomeA);

	// Access functions for the num blend steps
	UINT32 GetNumBlendSteps();
	void SetNumBlendSteps(UINT32 NumSteps);

	// Access functions for the way the blend does colours
	ColourBlendType GetColourBlendType();
	void 			SetColourBlendType(ColourBlendType Type);

	//DY 27/9
	EditState GetEditState();
	void SetEditState(EditState State);
	
	BOOL Reinit(BOOL ProgressBar = TRUE);			// Calls Reinit() for all its child blenders
	void Deinit(BOOL bNodesMayBeChanged = FALSE);	// Calls Deinit() for all its child blenders

	static BOOL GetDefaultAntialias() { return !s_DefaultNotAntialiased; }

	// Version 2 file format functions
	virtual BOOL WritePreChildrenWeb(BaseCamelotFilter* pFilter);
	virtual BOOL WritePreChildrenNative(BaseCamelotFilter* pFilter);
	virtual BOOL WritePreChildren(BaseCamelotFilter* pFilter);
	virtual BOOL CanWriteChildrenWeb(BaseCamelotFilter* pFilter);
	virtual BOOL CanWriteChildrenNative(BaseCamelotFilter* pFilter);

	// Blend path functions
	NodeBlendPath*	GetNodeBlendPath(UINT32 Index);
	BOOL			BlendAlongThisPath(NodePath* pPath,CCAttrMap* pAttrMap,UndoableOperation* pUndoOp, BOOL BlendPathOnTop);    //DY added last parameter 16/9/99
	virtual Node* 	HasEditableChild(CCRuntimeClass *ChildClass, Node* pPrevEditable);
	BOOL			TransformBlendEndObjects(UndoableOperation* pUndoOp);
	BOOL			RotateBlendEndObjectsBack(UndoableOperation* pUndoOp);
	BOOL			TransformNodeToPoint(NodeRenderableInk* pNode,DocCoord* pPoint,UndoableOperation* pUndoOp,double Angle);
	BOOL			InitBlenderPathProportions(UndoableOperation* pUndoOp);
	BOOL			DetachNodeBlendPath(Node* pContextNode, AttachNodeDirection AttDir,UndoableOperation* pUndoOp);
	BOOL			IsTangential();
	void			SetTangential(BOOL Tangential);
	BOOL			IsOnACurve();
	void			SetBlendedOnCurve(BOOL State);
	
	// Profile blending functions
	CProfileBiasGain* GetObjectProfile()	{ return &m_ObjectProfile; }
	CProfileBiasGain* GetAttrProfile()		{ return &m_AttrProfile; } 
	CProfileBiasGain* GetPositionProfile()	{ return &m_PositionProfile; }

	// DY 26/9/99
	BOOL GetBlendDistance(BOOL GetFullDistance, double* Distance);  // returns the length of a blend in MP
	
	// works out how many steps would be required to achieve distance between steps of StepDistance 
	BOOL GetNumStepsFromDistance(double StepDistance, UINT32* NumSteps); 

	double GetStepDistance(); // returns the distance between steps in the blend
	void UpdateStepDistance();  // updates the actual distance between steps member variable
	double GetDistanceEntered(); 
	void SetDistanceEntered(double Distance);

	EndObject GetLastEdited();
	void SetLastEdited(EndObject ObjectEdited);
	BOOL GetStartAndEndProportions(double* StartProp, double* EndProp);
	BOOL GetStartAndEndNodes(Node** ppStart, Node** ppEnd);
	BOOL IsChildOfGroup();
	BOOL HitOnEndDragBlob(DocCoord Point, Node** ppHitNode);

	// if the blend is part of a bevel, shadow, or contour, this returns the controller node
	NodeCompound* GetParentController() const;

	// access functions to deal with multiple nodeblendpaths
	UINT32 GetNumNodeBlendPaths();
	void SetNumNodeBlendPathsInc(BOOL Increase);
	void SetNumNodeBlendPaths(INT32 Index);
	BOOL HitOnDragBlob(NodeRenderableInk* pInk, DocCoord PointerPos);
	
	// function to find out which blender a given node belongs to, the first is now  
	// obsolete and should not be used
	NodeBlender* NodeIsPartOfBlender(Node* pNode, BOOL First);
	
	// Function to find out which other blender in a blend uses pNode, given that it is als
	// used by pBlender
	NodeBlender* NodeIsPartOfBlender(Node* pNode, NodeBlender* pBlender, BOOL* First);

	// returns whether or not the blend currently has a non-linear object profile
	BOOL NonLinearObjectProfile();

	BOOL ContainsBrushedNode();

	// CGS (27/7/2000):  special profiling functions ....
	// these functions provide access to the new features described within blndattr.h
	
	void RequestObjectProfileProcessing (BOOL newVal) { objectProfileProcessing = newVal; }
	BOOL GetObjectProfileProcessing () { return (objectProfileProcessing); }

	virtual INT32 EstimateNodeComplexity (OpParam* details);

	// CGS:  NOTE the use of RequestObjectProfileProcessing may appear to be incorrect.
	// For example, when the user changes the object profile I call this function with TRUE
	// (thereby requesting object processing).  However, I also do exactly the same when the user
	// changes the attribute profile.  The reason for this is THAT when changing the attribute
	// profile, we MUST blend position data (e.g.  fill control points) with respect to the object
	// profile AND not of the attribute profile!  As can be seen, this approach works well.

	BOOL ReinitialiseOnChildChanged(UndoableOperation* pOp, NodeRenderableInk* pOldChild,
															NodeRenderableInk* pNewChild);

	virtual void PolyCopyNodeContents(NodeRenderable* pNodeCopy);

	// Karim MacDonald 26/11/1999
	// Extend functions.
	// Note that if a sub-class returns TRUE from IsTypeExtendible, it must
	// also provide complete implementations of ValidateExtend and Extend,
	// which should usually check/extend its children.
public:
	virtual BOOL IsTypeExtendible() const { return TRUE; }
	virtual DocRect ValidateExtend(const ExtendParams& ExtParams);
	virtual void Extend(const ExtendParams& ExtParams);
protected:
	void FindExtendingChildren(std::list<NodeRenderableInk*>&, std::list<NodeBlendPath*>&);

private:
	void CopyNodeContents(NodeBlend* pCopyOfNode);
	void ResetVars();

	BOOL objectProfileProcessing;		// do we want object profile processing capability?

	String_32 m_BlendName; // The name of the blend 

	// Number of blend steps all child blenders will render.
	// E.g if 1, then 1 intermediate step will be rendered. If 0, just the end objecs get rendered
	UINT32 m_NumBlendSteps;

	
	// DY 27/9/99
	double m_StepDistance; // distance between steps of the blend
	double m_DistanceEntered; //the last distance requested by the user
	EndObject m_LastEdited;  // 

	// These vars are used during exporting to ArtWorks EPS. They determine whether the whole blend is
	// AWEPS compatible, and whether this info is cached for this blend (for when blenders ask their 
	// parent for the info)
	BOOL m_AWEPSCompatible;
	BOOL m_AWEPSCompatibleCache;

	// The OneToOne flag is TRUE if the blend should be be done using a one-to-one node mapping
	BOOL m_OneToOne;

	// This flags is TRUE if we should NOT render blend steps antialiased
	BOOL m_NotAntialiased;

	// This specifies how the blend will blend colours (either fade, rainbow, or alt rainbow)
	ColourBlendType m_ColBlendType;

	// This is true if the blend should fit the objects on a curve tangentially
	BOOL m_Tangential;
	
	// is this blend currently on a curve?
	BOOL m_BlendedOnCurve;

	// when the blend is on a curve and we wish to edit the path do we keep the 
	EditState m_Edit;   // number of steps constant (or the distance between steps)

	CProfileBiasGain m_ObjectProfile;
	CProfileBiasGain m_AttrProfile;
	CProfileBiasGain m_PositionProfile;

	static BOOL s_DefaultNotAntialiased;

	UINT32 m_NumNodeBlendPaths;
};


/********************************************************************************************

>	class InitBlendAction : public Action

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	21/11/94
	Purpose:	An action which deinits or reinits a blend
	SeeAlso:	-

********************************************************************************************/

enum InitBlendActionType { IBAT_INVALID, IBAT_INIT, IBAT_INITONBLENDER };

class InitBlendAction : public Action
{

CC_DECLARE_DYNCREATE(InitBlendAction)

public:
	InitBlendAction();
	~InitBlendAction();
	virtual ActionCode Execute();
	static ActionCode Init( UndoableOperation* pOp,
							ActionList* pActionList,
							NodeBlend* pThisNodeBlend,
							BOOL StoreStartAndEndNodes=FALSE, // DMc change so that the action							
															  // can restore the blends start & end points
							BOOL bReverse = FALSE,			  // Instead of adding this action to the head of the action list
															  // add it to the tail
							BOOL bNodesMayBeChanged = FALSE
							);

	// CGS (14/7/2000)
	// allows us to initialise undo information based upon blenders (so that we store the CORRECT nodes)
	// this should only be called when we replace the geometry that starts/ends the blends (e.g.
	// remove the contour of a blends start node).
	static ActionCode InitOnBlender( UndoableOperation* pOp,
							ActionList* pActionList,
							NodeBlender* pThisNodeBlender,
							BOOL StoreStartAndEndNodes=FALSE, // DMc change so that the action							
															  // can restore the blends start & end points
							BOOL bReverse = FALSE);			  // Instead of adding this action to the head of the action list
															  // add it to the tail

protected:
	NodeBlend* m_pNodeBlend;
	NodeBlender* m_pNodeBlender;
	Node * m_pStartNode;
	Node * m_pEndNode;
	BOOL m_bReverse;
	BOOL m_bStoreStartAndEndNodes;
	InitBlendActionType m_enInitType;
	BOOL m_bNodesMayBeChanged;
};

#endif
