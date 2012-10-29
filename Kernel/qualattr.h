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


#ifndef INC_QUALATTR
#define	INC_QUALATTR


/********************************************************************************************

>	class QualityAttribute : public AttributeValue

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	26/01/94
	Purpose:	Attribute for quality of display/rendering.
	SeeAlso:	FillColourAttribute; StrokeColourAttribute;
				StartArrowAttribute; EndArrowAttribute; StartCapAttribute; EndCapAttribute;
				JoinTypeAttribute; MitreLimitAttribute; WindingRuleAttribute;
				DashPatternAttribute

********************************************************************************************/

class QualityAttribute : public AttributeValue
{
	CC_DECLARE_DYNCREATE(QualityAttribute)
public:
	QualityAttribute() {}
	QualityAttribute(Quality NewQuality) { QualityValue = NewQuality; }
	virtual void Render(RenderRegion *pRegion, BOOL Temp = FALSE);
	virtual void Restore(RenderRegion *, BOOL);
	virtual void SimpleCopy(AttributeValue *);
	virtual NodeAttribute *MakeNode();
	virtual BOOL IsDifferent(AttributeValue*);

	// The quality level.
	Quality QualityValue;

	static BOOL Init();
};

/***********************************************************************************************

>	class AttrQuality : public NodeAttribute

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	23/04/94
	Purpose:	Quality NodeAttribute class.

***********************************************************************************************/

class AttrQuality : public NodeAttribute
{
	CC_DECLARE_DYNCREATE(AttrQuality)

public:
	AttrQuality(); 
	AttrQuality(Node* ContextNode,  
				AttachNodeDirection Direction,    
				BOOL Locked=FALSE, 
				BOOL Mangled=FALSE,  
				BOOL Marked=FALSE, 
				BOOL Selected=FALSE); 

	void Render( RenderRegion* pRender );

	Node* SimpleCopy();							// Copies a node
	virtual INT32 operator==(const NodeAttribute& NodeAttrib); 
	virtual UINT32 GetAttrNameID(void); 
	virtual AttrIndex GetAttributeIndex () { return ATTR_QUALITY; }

	void ShowDebugTreeDetails() const;			// Debugging function

	void GetDebugDetails(StringBase* Str);

    virtual UINT32 GetNodeSize() const; 			// Returns size of node in bytes

	// We don't ever want to apply a quality attribute to an object directly !
	virtual BOOL CanBeAppliedToObject() { return FALSE; };

	static DocColour* GetColour() { return pCurrentColour; }

	virtual void PolyCopyNodeContents(NodeRenderable* pNodeCopy);

	// Version 2 file format functions
	virtual BOOL WritePreChildrenWeb(BaseCamelotFilter* pFilter);
	virtual BOOL WritePreChildrenNative(BaseCamelotFilter* pFilter);

private:
	void CopyNodeContents( AttrQuality* NodeCopy );

	DocColour Colour;					// colour for this AttrQuality
	static DocColour* pCurrentColour;	// Ptr to current AttrQuality colour

public:
	QualityAttribute Value;
};

#endif	//INC_QUALATTR
