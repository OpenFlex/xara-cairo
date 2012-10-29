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

// strkattr.h - Path stroking attributes

#ifndef INC_STRKATTR
#define INC_STRKATTR



class PathProcessorStroke;
class ValueFunction;
class BecomeA;

/********************************************************************************************

>	enum StrokeTypeID

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/1/97
	Purpose:	A unique identifier UINT32 for each predefined stroke type.
				This is used to save predefined strokes in XAR files in a minimal format

********************************************************************************************/

typedef enum
{
	StrokeType_SimpleVarWidth = 0,
} StrokeTypeID;



/********************************************************************************************

>	class StrokeTypeAttrValue : public AttributeValue

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	7/1/97

	Purpose:	StrokeType attribute value
				StrokeType attributes describe the stroking characteristics for a path

	Notes:		This AttrValue just contains a pointer to a path processor which will
				stroke paths after some given fashion. The pointer may be NULL, in which
				case new-style stroking is disabled, and old-style "lines" will be
				rendered.

********************************************************************************************/

class StrokeTypeAttrValue : public AttributeValue
{
	CC_DECLARE_DYNAMIC(StrokeTypeAttrValue)

public:			// Construction/Initialisation
	StrokeTypeAttrValue(PathProcessorStroke *pPathProcessor = NULL);
	~StrokeTypeAttrValue();

	static BOOL Init(void);


public:			// Overridden access methods
	virtual void Render(RenderRegion *pRegion, BOOL Temp = FALSE);
	virtual void Restore(RenderRegion *pRegion, BOOL Temp);
	virtual void GoingOutOfScope(RenderRegion *pRegion);

	virtual void SimpleCopy(AttributeValue *pValue);
	virtual NodeAttribute *MakeNode();

	virtual BOOL IsDifferent(AttributeValue *pAttr);

	virtual StrokeTypeAttrValue &operator=(StrokeTypeAttrValue &Attrib);
	virtual INT32 operator==(const StrokeTypeAttrValue &Attrib);


public:		// Specialised interface
	void SetPathProcessor(PathProcessorStroke *pNewProcessor);
	PathProcessorStroke *GetPathProcessor(void)	const	{ return(pProcessor); };
			// Get the path processor for this stroke type (may be NULL)

	BOOL DoBecomeA(BecomeA* pBecomeA, Node* pParent);
private:
	PathProcessorStroke *pProcessor;			// Pointer to the PPS we use (if any)
};



/***********************************************************************************************

>	class AttrStrokeType : public NodeAttribute

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	7/1/97

	Purpose:	StrokeType attribute
				StrokeType attributes are very simple, and merely contain a StrokeTypeAttrValue,
				which is the entity which holds all the info and does all the work.

***********************************************************************************************/

class AttrStrokeType : public NodeAttribute
{
	CC_DECLARE_DYNCREATE(AttrStrokeType)

public:		// Constructors
	AttrStrokeType();
	AttrStrokeType(Node *ContextNode,
			  		 AttachNodeDirection Direction,
		      		 BOOL Locked	= FALSE,
		      		 BOOL Mangled	= FALSE,
		      		 BOOL Marked	= FALSE,
			  		 BOOL Selected	= FALSE);

public:
	virtual void Render(RenderRegion *pRender);
	virtual void CopyNodeContents(AttrStrokeType *NodeCopy);
	virtual void PolyCopyNodeContents(NodeRenderable* pNodeCopy);
	virtual INT32 operator==(const NodeAttribute& NodeAttrib);
	virtual Node *SimpleCopy();
	virtual UINT32 GetAttrNameID(void);
	virtual AttrIndex GetAttributeIndex () { return ATTR_STROKETYPE; }
	virtual void GetDebugDetails(StringBase *Str);
	virtual UINT32 GetNodeSize() const;

	virtual BOOL WritePreChildrenWeb(BaseCamelotFilter *pFilter);
	virtual BOOL WritePreChildrenNative(BaseCamelotFilter *pFilter);

	virtual AttributeValue* GetAttributeValue()		{ return(&Value); };

	virtual BOOL NeedsTransparency() const;

	BOOL DoBecomeA(BecomeA* pBecomeA, Node* pParent);
	BOOL HasPathProcessor();
	PathProcessorStroke* GetPathProcessor();

protected:
	StrokeTypeAttrValue Value;
};






/********************************************************************************************

>	enum VariableWidthID

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/1/97
	Purpose:	A unique identifier UINT32 for each predefined variable width stroke function.
				This is used to save predefined varwidths in XAR files in a minimal format.

********************************************************************************************/

typedef enum
{
	VarWidth_NotPredefined = 0,		// For fns which aren't "simple" predefined ones

	VarWidth_Constant	= -1,		// All values are negative (positive values are used
	VarWidth_LinRamp	= -2,		// as references to complex function records)
	VarWidth_SRamp		= -3,
} VariableWidthID;



/********************************************************************************************

>	class VariableWidthAttrValue : public AttributeValue

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	7/1/97

	Purpose:	VariableWidth attribute value
				VariableWidth attributes describe the width characteristics for a path

********************************************************************************************/

class VariableWidthAttrValue : public AttributeValue
{
	CC_DECLARE_DYNAMIC(VariableWidthAttrValue)

public:			// Construction/Initialisation
	VariableWidthAttrValue(ValueFunction *pValueFunction = NULL);
	~VariableWidthAttrValue();

	static BOOL Init(void);


public:			// Overridden access methods
	virtual void Render(RenderRegion *pRegion, BOOL Temp = FALSE);
	virtual void Restore(RenderRegion *pRegion, BOOL Temp);

	virtual void SimpleCopy(AttributeValue *pValue);
	virtual NodeAttribute *MakeNode();

	virtual BOOL IsDifferent(AttributeValue *pAttr);

	virtual VariableWidthAttrValue &operator=(VariableWidthAttrValue &Attrib);
	virtual INT32 operator==(const VariableWidthAttrValue &Attrib);


public:			// Specialised methods
	void SetWidthFunction(VariableWidthID PredefinedFuncID);
	void SetWidthFunction(ValueFunction *pNewFunction);

	ValueFunction *GetWidthFunction(void)		{ return(WidthFunction); };
	VariableWidthID GetWidthFunctionID(void)	{ return(PredefinedFunctionID); };

private:
	VariableWidthID	PredefinedFunctionID;
	ValueFunction	*WidthFunction;
};



/***********************************************************************************************

>	class AttrVariableWidth : public NodeAttribute

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	7/1/97

	Purpose:	VariableWidth attribute
				VariableWidth attributes are very simple, and merely contain a VariableWidthAttrValue,
				which is the entity which holds all the info and does all the work.

***********************************************************************************************/

class AttrVariableWidth : public NodeAttribute
{
	CC_DECLARE_DYNCREATE(AttrVariableWidth)

// the stroke path-processor needs access to our value.
friend class PathProcessorStroke;

public:		// Constructors
	AttrVariableWidth();
	AttrVariableWidth(Node *ContextNode,
			  		 AttachNodeDirection Direction,
		      		 BOOL Locked	= FALSE,
		      		 BOOL Mangled	= FALSE,
		      		 BOOL Marked	= FALSE,
			  		 BOOL Selected	= FALSE);
public:
	virtual void Render(RenderRegion *pRender);
	virtual void CopyNodeContents(AttrVariableWidth *NodeCopy);
	virtual void PolyCopyNodeContents(NodeRenderable* pNodeCopy);
	virtual INT32 operator==(const NodeAttribute& NodeAttrib);
	virtual Node *SimpleCopy();
	virtual UINT32 GetAttrNameID(void);
	virtual AttrIndex GetAttributeIndex () { return ATTR_VARWIDTH; }
	virtual void GetDebugDetails(StringBase *Str);
	virtual UINT32 GetNodeSize() const;

	virtual BOOL WritePreChildrenWeb(BaseCamelotFilter *pFilter);
	virtual BOOL WritePreChildrenNative(BaseCamelotFilter *pFilter);

	virtual AttributeValue* GetAttributeValue()				{ return(&Value); };

	BOOL DoBecomeA(BecomeA* pBecomeA, Node* pParent);

	BOOL HasActiveValueFunction();
protected:
	VariableWidthAttrValue Value;
};








/***********************************************************************************************

>	class StrokeAttrRecordHandler : public CamelotRecordHandler

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	7/1/97
	Purpose:	Handles the reading of all Stroke attribute records in the v2 file format
				This includes StrokeType Attributes and VariableWidth attributes

***********************************************************************************************/

class CXaraFileRecord;

class StrokeAttrRecordHandler : public CamelotRecordHandler
{
	CC_DECLARE_DYNAMIC(StrokeAttrRecordHandler);

public:
	StrokeAttrRecordHandler() : CamelotRecordHandler() {}
	~StrokeAttrRecordHandler() {}

	// functions that must be implemented.
	virtual UINT32 *GetTagList();
	virtual BOOL HandleRecord(CXaraFileRecord *pCXaraFileRecord);

	// handling of atomic TAG_STROKEDEFINITION tags
	virtual BOOL BeginSubtree(UINT32 Tag);
	virtual BOOL EndSubtree(UINT32 Tag);

#ifdef XAR_TREE_DIALOG
	virtual void GetRecordDescriptionText(CXaraFileRecord* pRecord, StringBase* pStr);
#endif
};

#endif

