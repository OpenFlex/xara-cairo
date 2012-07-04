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


// Brush Attribute header

#ifndef INC_BRSHATTR
#define INC_BRSHATTR

//#include "attrval.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "cxfrech.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "nodeattr.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "brshdata.h"
#include "brpress.h"
#include "samplist.h"

class BrushPointInfo;
class FreeHandTool;
class CDistanceSampler;




#define BRUSHPOINTSCACHE
#define PRESSURE_INVALID 65536


/********************************************************************************************

>	class BrushAttrValue : public AttributeValue

	Author:		Diccon_Yamanaka (Xara Group Ltd) <camelotdev@xara.com>
	Created:	7/1/97

	Purpose:	Brush attribute value
				
	Notes:		This AttrValue just contains a pointer to a path processor which will
				apply brush path objects and attributes to the attributee, so to speak.

********************************************************************************************/

class BrushAttrValue : public AttributeValue
{
	CC_DECLARE_DYNAMIC(BrushAttrValue)

#ifdef NEWFASTBRUSHES
private:
	NodeBitmap* pCachedBitmap;
	Node* pBoundsParent;
public:
	NodeBitmap* GetCachedBitmap () { return (pCachedBitmap); }
	void SetBoundsParent (Node* parent) { pBoundsParent = parent; }
	Node* GetBoundsParent () { return (pBoundsParent); }
	void SetCachedBitmap (NodeBitmap* pBitmap) { pCachedBitmap = pBitmap; }
#endif

public:			// Construction/Initialisation
	BrushAttrValue();
	BrushAttrValue(PathProcessorBrush *pPathProcessor);
	~BrushAttrValue();

	static BOOL Init(void);
	

public:			// Overridden access methods
	virtual void Render(RenderRegion *pRegion, BOOL Temp = FALSE);
	virtual void Restore(RenderRegion *pRegion, BOOL Temp);
	virtual void GoingOutOfScope(RenderRegion *pRegion);

	virtual void SimpleCopy(AttributeValue *pValue);
	virtual NodeAttribute *MakeNode();

	virtual BOOL IsDifferent(AttributeValue *pAttr);

	virtual BrushAttrValue &operator=(BrushAttrValue &Attrib);
	virtual INT32 operator==(const BrushAttrValue &Attrib);

	virtual BOOL Blend(BlendAttrParam* pBlendParam);

	BOOL DoBecomeA(BecomeA* pBecomeA, Node* pParent);

	//Bounding box functions
	BOOL EffectsParentBounds();
	DocRect GetAttrBoundingRect(NodeRenderableInk* pParent = NULL, CCAttrMap* pAttribMap = NULL);
	static BOOL RotateBounds(double Angle, DocRect* pBounds, DocCoord* pCentre = NULL );

	void SetCachedRect(DocRect Rect);
	void TransformCachedRect(TransformBase& Trans);

public:		// interface to the path processor
	void				SetPathProcessor(PathProcessorBrush *pNewProcessor);
	PathProcessorBrush *GetPathProcessor(void)	const	{ return(m_pProcessor); };
			// Get the path processor for this Brush type (may be NULL)
	
// access to the various caches that we use
	
public: // access to the points cache
	void FlushCache();  // flushes the points cache
	void TransformCache(TransformBase& Trans);		// transform the points in the cache
	void SetCache(PointsMap* pMap);
	PointsMap* GetCache() {return m_pCachedPoints;}
	
public: // access to the timestamp cache
	TimeStampList* GetTimeStampList() { return m_pTimeStampList;}
	void SetTimeStampList(TimeStampList* pList);
	BOOL IsTimeStamping();
	
	// access to our repositioning flag
	void  SetTimeStampUpdateType(ListUpdateType Update);
	ListUpdateType GetTimeStampUpdateType();

	// functions to make sure the timestamp list is all in order
	void CalculateProportionalDistances(MILLIPOINT PathLength);
	void TransformTimeStampList(TransformBase& Trans);
	BOOL DeleteTimeStampPoints(MILLIPOINT StartDistance, MILLIPOINT EndDistance, 
								TimeStampList* pRemovedPoints = NULL);
	BOOL DeleteTimeStampPoints(MILLIPOINT StartDistance, UINT32 NumPoints, 
								TimeStampList* pRemovedPoints = NULL);
	BOOL AddTimeStampPoints(TimeStampList* pNewPoints, MILLIPOINT StartDistance);
	BOOL RecalculateTimeStampList(Path* pPath);
	BOOL RepositionPointsByProportion(Path* pPath);
	BOOL RepositionPointsByPosition(Path* pPath);
	
	TimeStampList* CopyTimeStampList();

	BOOL WriteTimeStampList(BaseCamelotFilter *pFilter);

public:	// access to the old pressure cache
	void	SetPresssureCache(CDistanceSampler* pPress);
	CDistanceSampler* GetPressureCache();
	UINT32	GetPressureValue(UINT32 Index);
	BOOL	SetPressureValue(UINT32 Index, PressureItem Value);
	
	void	CalculatePressureArrayProportions(MILLIPOINT PathLength);

public:	// access to the new pressure cache

	void	PressureSpacingChange(MILLIPOINT OldSpacing, MILLIPOINT NewSpacing);
	void	FlushPressureCache();

	INT32	GetPressureListIndexAtDistance(MILLIPOINT Distance);
	// functions to add to or remove points from our list
	BOOL DeletePressurePoints(MILLIPOINT StartDistance, MILLIPOINT EndDistance, 
								SampleArray* pRemovedPoints = NULL);
	BOOL DeletePressurePoints(UINT32 StartIndex, size_t NumPoints, 
								SampleArray* pRemovedPoints = NULL);
	BOOL AddPressurePoints(CSampleData* pNewPoints, MILLIPOINT StartDistance);
	BOOL AddPressurePoints(CSampleData* pNewPoints, UINT32 StartIndex);
	

	// access to our repositioning flag
	void  SetPressureUpdateType(ListUpdateType Update);
	ListUpdateType GetPressureUpdateType();

	CDistanceSampler* CopyPressureCache(); // makes a duplicate pressure cache

	BOOL	WritePressureData(BaseCamelotFilter *pFilter); // writes the list to a filter

protected: // pressure helper fns.
		BOOL RepositionPressureDataByPosition(Path* pPath);

public:
	// line width functions
	void				ScaleToLineWidth(MILLIPOINT Width); 
	MILLIPOINT			GetDefaultLineWidth(BOOL IgnorePressure = FALSE);

	// access to our brush definition
	BrushDefinition*	GetBrushDefinition(void);
	BrushHandle			GetBrushHandle(void);
	
protected:  // helper functions
	void InitialisePointsCache();
	void FlushTimeStampCache();  // time stamp data is too valuable to be public

	static void ShuffleArrayUp(PressureArray* pPressure, UINT32 StartIndex);
	static void ShuffleArrayDown(PressureArray* pPressure, UINT32 StartIndex);

	static UINT32 BlendUINT32(UINT32 First, UINT32 Second, double BlendRatio);
	static INT32 BlendINT32(INT32 First, INT32 Second, double BlendRatio);
	static double BlendDouble(double First, double Second, double BlendRatio);

	// timestamping helpers
	BOOL RecalculateDistances(Path* pPath); 
	BOOL RecalculateTangents(Path* pPath);
	BOOL SortTimeStampingList();
	BOOL GetRidOfCrapFromList(Path* pPath);


private:
	PathProcessorBrush *m_pProcessor;			// Pointer to the PPS we use (if any)


#ifdef BRUSHPOINTSCACHE	
	PointsMap* m_pCachedPoints;                // caches the points along the path (unless we're timestamping)
#endif   

	TimeStampList* m_pTimeStampList;            // if we are using timestamped points keep 'em here

	PressureArray* m_pPressureVals;

	CDistanceSampler* m_pPressureSampler;     // the latest incarnation of the pressure data cache
	DocRect		   m_CachedBRect;

	ListUpdateType m_TimeStampUpdateType;  // indicates what kind of update we have to perform on 
												// the timestamping list following an edit
	ListUpdateType  m_PressureUpdateType; 

};




/***********************************************************************************************

>	class AttrBrushType : public NodeAttribute

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	7/1/97

	Purpose:	BrushType attribute
				BrushType attributes are very simple, and merely contain a BrushTypeAttrValue,
				which is the entity which holds all the info and does all the work.

***********************************************************************************************/

class AttrBrushType : public NodeAttribute
{
	CC_DECLARE_DYNCREATE(AttrBrushType)

public:		// Constructors
	AttrBrushType();
	AttrBrushType(Node *ContextNode,
			  		 AttachNodeDirection Direction,
		      		 BOOL Locked	= FALSE,
		      		 BOOL Mangled	= FALSE,
		      		 BOOL Marked	= FALSE,
			  		 BOOL Selected	= FALSE);
	~AttrBrushType();

public: // regular attribute virtual fns.
	virtual void Render(RenderRegion *pRender);
	virtual void CopyNodeContents(AttrBrushType *NodeCopy);
	virtual INT32 operator==(const NodeAttribute& NodeAttrib);
	virtual Node *SimpleCopy();
	virtual UINT32 GetAttrNameID(void);
	virtual void GetDebugDetails(StringBase *Str);
	virtual UINT32 GetNodeSize() const;
	virtual void Transform( TransformBase& );
	virtual BOOL WritePreChildrenWeb(BaseCamelotFilter *pFilter);
	virtual BOOL WritePreChildrenNative(BaseCamelotFilter *pFilter);

	virtual AttributeValue* GetAttributeValue()		{ return(&m_Value); };

	virtual BOOL NeedsTransparency() const;

	virtual BOOL Blend(BlendAttrParam* pBlendParam);

	virtual SubtreeRenderState RenderSubtree(RenderRegion *pRender, Node** ppNextNode = NULL, BOOL bClip = TRUE);

	BOOL DoBecomeA(BecomeA* pBecomeA, Node* pParent);
	virtual void PolyCopyNodeContents(NodeRenderable* pNodeCopy);

	//Bounding box functions
	virtual BOOL EffectsParentBounds();
	virtual DocRect GetAttrBoundingRect(NodeRenderableInk* pParent = NULL, CCAttrMap* pAttribMap = NULL);

	virtual BOOL IsABrush() const;
	virtual BOOL ShouldBeOptimized() { return TRUE;}

	void NodePathUpdated(Path* pPath);

	BOOL OnReplaceAttribute(AttrBrushType* pOther);
		// call when this attribute is being used to replace pOther

public:  // access functions - these are actually an interface to the path processor 
		 // of m_Value
		String_32 GetBrushName();
		BOOL SetSpacing(MILLIPOINT NewSpacing);
		BOOL SetScaling(double NewScale);
		BOOL SetPathOffsetType(PathOffset NewOffsetType);
		BOOL SetPathOffsetValue(MILLIPOINT NewOffsetValue);
		BOOL SetTiled(BOOL Tiled);
		BOOL SetRotated(BOOL Rotated);
		BOOL SetRotateAngle(double NewAngle);
		PathProcessorBrush* GetPathProcessor();
		BrushDefinition* GetBrushDefinition();
		BrushHandle      GetBrushHandle(void);
		MILLIPOINT GetSpacing();
		MILLIPOINT GetDefaultLineWidth(BOOL IgnorePressure = FALSE);
		
		void SetUseLocalTransp(BOOL UseTransp);
public:
		// Cache access functions
		void FlushCache();
		void SetCache(PointsMap* pMap);
		PointsMap* GetCache();
		
		// timestamping access fns.
		TimeStampList* GetTimeStampList();
		BOOL IsTimeStamping();

		// pressure access fns.
		void SetPressureCache(CDistanceSampler* pSamp);
		CDistanceSampler* GetPressureCache();
		BOOL ContainsPressureCache();
	
		BOOL ReversePressureCache();  // reverse list belonging to this attribute

		
		BOOL CanUsePointsCache();

		// assorted other access fns.
		MILLIPOINT GetAppliedLineWidth();
		void	   SetValueToScaleTo(MILLIPOINT LineWidth);
		DocColour  GetLocalStrokeColour();
		void	   SetBlendedStrokeColour(DocColour* pCol);
		
		UINT32	   GetLocalTranspValue();
		UINT32	   GetLocalTranspType();

		static BOOL RotateBounds(double Angle, DocRect* pBounds) ;
		void ClearCachedRect();

		void SetFreeHandTool(FreeHandTool* pTool); 
public:		// BrushData functions	
		void InitialiseBrushData();
		BrushData GetBrushData();
		void SetBrushData(BrushData NewData);

public: // other
		void GetMaxScalingFromDefinition();
		BOOL IsParentSelected();

protected:
		void FindNearestStrokeColour();  // looks for the nearest applied stroke colour and caches it
		void FindNearestStrokeTransp();
		
protected:
		BrushAttrValue m_Value;

		DocColour*      m_pLocalStrokeColour; // the nearest stroke colour
		DocColour*      m_pBlendedStrokeColour;  // the current stroke colour if we are in a blend
		BrushData		m_BrushData;

		FreeHandTool*  m_pFreeTool;
			
		UINT32		    m_LocalTranspValue; // stores the applied stroke transparency
		UINT32			m_LocalTranspType;
};


/***********************************************************************************************

>	class BrushAttrRecordHandler : public CamelotRecordHandler

	Author:		Diccon_Yamanaka (Xara Group Ltd) <camelotdev@xara.com>
	Created:	7/1/97
	Purpose:	Handles the reading of all brush attribute records
				
***********************************************************************************************/

class CXaraFileRecord;

class BrushAttrRecordHandler : public CamelotRecordHandler
{
	CC_DECLARE_DYNAMIC(BrushAttrRecordHandler);

public:
	BrushAttrRecordHandler() : CamelotRecordHandler() { m_pLastAttribute = NULL;}
	~BrushAttrRecordHandler() {}

	// functions that must be implemented.
	virtual UINT32 *GetTagList();
	virtual BOOL HandleRecord(CXaraFileRecord *pCXaraFileRecord);

	// handling of atomic TAG_STROKEDEFINITION tags
	virtual BOOL BeginSubtree(UINT32 Tag);
	virtual BOOL EndSubtree(UINT32 Tag);



protected: //helper functions
	BOOL HandleBrushAttributeRecord(CXaraFileRecord* pRecord);
	BOOL HandleBrushDataRecord(CXaraFileRecord* pRecord);
	BOOL HandleMoreBrushDataRecord(CXaraFileRecord* pRecord);
	BOOL HandleMoreBrushAttrRecord(CXaraFileRecord* pRecord);
	BOOL HandleEvenMoreBrushData(CXaraFileRecord* pRecord);
	BOOL HandleEvenMoreBrushAttr(CXaraFileRecord* pRecord);
	BOOL HandleTimeStampData(CXaraFileRecord* pRecord);
	BOOL HandlePressureInfo(CXaraFileRecord* pRecord);
	BOOL HandleAttrPressureInfo(CXaraFileRecord* pRecord);
	BOOL HandlePressureData(CXaraFileRecord* pRecord);
	BOOL HandlePressureSampleData(CXaraFileRecord* pRecord);
	BOOL HandleAttrFillFlags(CXaraFileRecord* pRecord);
	BOOL HandleTranspInfo(CXaraFileRecord* pRecord);
	BOOL HandleAttrTranspInfo(CXaraFileRecord* pRecord);


#ifdef XAR_TREE_DIALOG
	virtual void GetRecordDescriptionText(CXaraFileRecord* pRecord, StringBase* pStr);
#endif

protected:
	// keeps track of the last brush attribute we imported
	static AttrBrushType* m_pLastAttribute;

};

#endif
