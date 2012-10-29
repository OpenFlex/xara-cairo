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

// isetattr.h - Imagesetting attributes (Overprint line/fill, Print on all plates)

#ifndef INC_ISETATTR
#define INC_ISETATTR




/********************************************************************************************

>	class ImagesettingAttrValue : public AttributeValue

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	23/7/96

	Purpose:	Base class from which all binary imagesetting attribute values are derived

	SeeAlso:	OverprintLineAttrValue; OverprintFillAttrValue; PrintOnAllPlatesAttrValue

********************************************************************************************/

class ImagesettingAttrValue : public AttributeValue
{
	CC_DECLARE_DYNAMIC(ImagesettingAttrValue)

public:
	ImagesettingAttrValue() {};

	virtual void Restore(RenderRegion *, BOOL) = 0;
	virtual INT32 operator==(const ImagesettingAttrValue &Attrib) = 0;
};



/***********************************************************************************************

>	class AttrImagesetting : public NodeAttribute

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	23/7/96

	Purpose:	Base class from which all imagesetting attributes are derived

	SeeAlso:	AttrOverprintLine; AttrOverprintFill; AttrPrintOnAllPlates

***********************************************************************************************/

class AttrImagesetting : public NodeAttribute
{
	CC_DECLARE_DYNCREATE(AttrImagesetting)

public:		// Constructors
	AttrImagesetting();
	AttrImagesetting(Node *ContextNode,
			  		 AttachNodeDirection Direction,
		      		 BOOL Locked	= FALSE,
		      		 BOOL Mangled	= FALSE,
		      		 BOOL Marked	= FALSE,
			  		 BOOL Selected	= FALSE);

public:
	virtual void Render(RenderRegion *pRender);
	virtual void CopyNodeContents(AttrImagesetting *NodeCopy);
	virtual void PolyCopyNodeContents(NodeRenderable* pNodeCopy);
};







/********************************************************************************************

>	class OverprintLineAttrValue : public ImagesettingAttrValue

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	23/7/96
	Purpose:	Attribute value indicating if overprint-line is enabled or disabled

********************************************************************************************/

class OverprintLineAttrValue : public ImagesettingAttrValue
{
	CC_DECLARE_DYNCREATE(OverprintLineAttrValue)

public:			// Construction/Initialisation
	OverprintLineAttrValue();
	OverprintLineAttrValue(BOOL OverprintIsOn);

	static BOOL Init(void);


public:			// Overridden access methods
	virtual void Render(RenderRegion *pRegion, BOOL Temp = FALSE);
	virtual void Restore(RenderRegion *pRegion, BOOL Temp);

	virtual void SimpleCopy(AttributeValue *pValue);
	virtual NodeAttribute *MakeNode();

	virtual BOOL IsDifferent(AttributeValue *pAttr);

	virtual OverprintLineAttrValue &operator=(OverprintLineAttrValue &Attrib);
	virtual INT32 operator==(const ImagesettingAttrValue &Attrib);


public:			// Specialised interface
	BOOL IsOverprintOn(void) const		{ return(OverprintOn); };
	void SetOverprint(BOOL NewValue)	{ OverprintOn = NewValue; };


protected:		// Member variables - and no, you may not poke at them directly
	BOOL OverprintOn;
};



/***********************************************************************************************

>	class AttrOverprintLine : public AttrImagesetting

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	23/7/96
	Purpose:	Attribute indicating if overprint-line is enabled or disabled

***********************************************************************************************/

class AttrOverprintLine : public AttrImagesetting
{
	CC_DECLARE_DYNCREATE(AttrOverprintLine)

public:		// Construction/Initialisation
	AttrOverprintLine(); 
	AttrOverprintLine(Node* ContextNode,  
						AttachNodeDirection Direction,    
						BOOL Locked		= FALSE,
						BOOL Mangled	= FALSE,
						BOOL Marked		= FALSE,
						BOOL Selected	= FALSE);

public:		// Overridden access functions
	virtual UINT32 GetAttrNameID(void);
	virtual AttrIndex GetAttributeIndex () { return ATTR_OVERPRINTLINE; }
	virtual void GetDebugDetails(StringBase *Str);
    virtual UINT32 GetNodeSize() const;

	virtual Node *SimpleCopy();
	virtual INT32 operator==(const NodeAttribute &NodeAttrib);

	virtual AttributeValue *GetAttributeValue()  { return(&Value); };

//	virtual void PolyCopyNodeContents(NodeRenderable* pNodeCopy);

public:		// Save/load functions
	virtual BOOL WritePreChildrenWeb(BaseCamelotFilter *pFilter);
	virtual BOOL WritePreChildrenNative(BaseCamelotFilter *pFilter);


private:
//	virtual void CopyNodeContents(AttrOverprintLine *NodeCopy);


public:
	OverprintLineAttrValue Value;
};





/********************************************************************************************

>	class OverprintFillAttrValue : public ImagesettingAttrValue

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	23/7/96
	Purpose:	Attribute value indicating if overprint-Fill is enabled or disabled

********************************************************************************************/

class OverprintFillAttrValue : public ImagesettingAttrValue
{
	CC_DECLARE_DYNCREATE(OverprintFillAttrValue)

public:			// Construction/Initialisation
	OverprintFillAttrValue();
	OverprintFillAttrValue(BOOL OverprintIsOn);

	static BOOL Init(void);


public:			// Overridden access methods
	virtual void Render(RenderRegion *pRegion, BOOL Temp = FALSE);
	virtual void Restore(RenderRegion *pRegion, BOOL Temp);

	virtual void SimpleCopy(AttributeValue *pValue);
	virtual NodeAttribute *MakeNode();

	virtual BOOL IsDifferent(AttributeValue *pAttr);

	virtual OverprintFillAttrValue &operator=(OverprintFillAttrValue &Attrib);
	virtual INT32 operator==(const ImagesettingAttrValue &Attrib);


public:			// Specialised interface
	BOOL IsOverprintOn(void) const		{ return(OverprintOn); };
	void SetOverprint(BOOL NewValue)	{ OverprintOn = NewValue; };


protected:		// Member variables - and no, you may not poke at them directly
	BOOL OverprintOn;
};





/***********************************************************************************************

>	class AttrOverprintFill : public AttrImagesetting

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	23/7/96
	Purpose:	Attribute indicating if overprint-Fill is enabled or disabled

***********************************************************************************************/

class AttrOverprintFill : public AttrImagesetting
{
	CC_DECLARE_DYNCREATE(AttrOverprintFill)

public:		// Construction/Initialisation
	AttrOverprintFill(); 
	AttrOverprintFill(Node* ContextNode,  
						AttachNodeDirection Direction,    
						BOOL Locked		= FALSE,
						BOOL Mangled	= FALSE,
						BOOL Marked		= FALSE,
						BOOL Selected	= FALSE);

public:		// Overridden access functions
	virtual UINT32 GetAttrNameID(void);
	virtual AttrIndex GetAttributeIndex () { return ATTR_OVERPRINTFILL; }
	virtual void GetDebugDetails(StringBase *Str);
    virtual UINT32 GetNodeSize() const;

	virtual Node *SimpleCopy();
	virtual INT32 operator==(const NodeAttribute &NodeAttrib);

	virtual AttributeValue *GetAttributeValue()  { return(&Value); };

//	virtual void PolyCopyNodeContents(NodeRenderable* pNodeCopy);

public:		// Save/load functions
	virtual BOOL WritePreChildrenWeb(BaseCamelotFilter *pFilter);
	virtual BOOL WritePreChildrenNative(BaseCamelotFilter *pFilter);


private:
//	void CopyNodeContents(AttrOverprintFill *NodeCopy);


public:
	OverprintFillAttrValue Value;
};





/********************************************************************************************

>	class PrintOnAllPlatesAttrValue : public ImagesettingAttrValue

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	23/7/96
	Purpose:	Attribute value indicating if "print on all plates" is enabled or disabled

********************************************************************************************/

class PrintOnAllPlatesAttrValue : public ImagesettingAttrValue
{
	CC_DECLARE_DYNCREATE(PrintOnAllPlatesAttrValue)

public:			// Construction/Initialisation
	PrintOnAllPlatesAttrValue();
	PrintOnAllPlatesAttrValue(BOOL PrintOnAllPlatesIsOn);

	static BOOL Init(void);


public:			// Overridden access methods
	virtual void Render(RenderRegion *pRegion, BOOL Temp = FALSE);
	virtual void Restore(RenderRegion *pRegion, BOOL Temp);

	virtual void SimpleCopy(AttributeValue *pValue);
	virtual NodeAttribute *MakeNode();

	virtual BOOL IsDifferent(AttributeValue *pAttr);

	virtual PrintOnAllPlatesAttrValue &operator=(PrintOnAllPlatesAttrValue &Attrib);
	virtual INT32 operator==(const ImagesettingAttrValue &Attrib);


public:			// Specialised interface
	BOOL IsPrintOnAllPlatesOn(void) const		{ return(PrintOnAllPlates); };
	void SetPrintOnAllPlates(BOOL NewValue)		{ PrintOnAllPlates = NewValue; };


protected:		// Member variables - and no, you may not poke at them directly
	BOOL PrintOnAllPlates;
};



/***********************************************************************************************

>	class AttrPrintOnAllPlates : public AttrImagesetting

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	23/7/96
	Purpose:	Attribute indicating if "print on all plates" is enabled or disabled

***********************************************************************************************/

class AttrPrintOnAllPlates : public AttrImagesetting
{
	CC_DECLARE_DYNCREATE(AttrPrintOnAllPlates)

public:		// Construction/Initialisation
	AttrPrintOnAllPlates(); 
	AttrPrintOnAllPlates(Node* ContextNode,  
						AttachNodeDirection Direction,    
						BOOL Locked		= FALSE,
						BOOL Mangled	= FALSE,
						BOOL Marked		= FALSE,
						BOOL Selected	= FALSE);

public:		// Overridden access functions
	virtual UINT32 GetAttrNameID(void);
	virtual AttrIndex GetAttributeIndex () { return ATTR_PRINTONALLPLATES; }
	virtual void GetDebugDetails(StringBase *Str);
    virtual UINT32 GetNodeSize() const;

	virtual Node *SimpleCopy();
	virtual INT32 operator==(const NodeAttribute &NodeAttrib);

	virtual AttributeValue *GetAttributeValue()  { return(&Value); };

//	virtual void PolyCopyNodeContents(NodeRenderable* pNodeCopy);

public:		// Save/load functions
	virtual BOOL WritePreChildrenWeb(BaseCamelotFilter *pFilter);
	virtual BOOL WritePreChildrenNative(BaseCamelotFilter *pFilter);


private:
//	void CopyNodeContents(AttrPrintOnAllPlates *NodeCopy);


public:
	PrintOnAllPlatesAttrValue Value;
};







/***********************************************************************************************

>	class ImagesettingAttrRecordHandler : public CamelotRecordHandler

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	26/7/96
	Purpose:	Handles the reading of all imagesetting attribute records in the v2 file format

***********************************************************************************************/

class CXaraFileRecord;

class ImagesettingAttrRecordHandler : public CamelotRecordHandler
{
	CC_DECLARE_DYNAMIC(ImagesettingAttrRecordHandler);

public:
	ImagesettingAttrRecordHandler() : CamelotRecordHandler() {}
	~ImagesettingAttrRecordHandler() {}

	// functions that must be implemented.
	virtual UINT32 *GetTagList();
	virtual BOOL HandleRecord(CXaraFileRecord *pCXaraFileRecord);
};


#endif

