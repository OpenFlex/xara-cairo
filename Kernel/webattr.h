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


// Definition of the new Web Address attribute

#ifndef INC_WEBATTR
#define INC_WEBATTR

//#include "nodeattr.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "attr.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "attrval.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "rndrgn.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "hotlink.h"
#include "webaddr.h" //Class WebAddress

class BlendAttrParam;
class BaseCamelotFilter;
class TextChar;
class CamelotFileRecord;

/********************************************************************************************

>	class WebAddressAttribute : public AttributeValue

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>

	Created:	18/3/97

	Purpose:	The new Web Address attribute. It's distinct from the old Web
				Address attribute, which was a type of UserAttribute.

				It stores three member variables:

				m_url		A WebAddress object:
							The URL to fetch when the object to which the
							attribute is applied is clicked on

				m_fBounding	Whether the clickable area of the object to which
							the attribute is applied is the bounding box or
							the actual shape of the object

				m_pcFrame	(Optional)
							The name of a frame into which to fetch the URL

				It also stores the following rectangle:

				m_rectClickableInRendering

				This member variable is an oddity and it works as follows.

				When this WebAddressAttribute is contained in an AttrWebAddress in 
				the Camelot tree, then the clickable rectangle of the Web
				Address Attribute is easily obtained from the parent of the 
				AttrWebAddress in the tree.

				But when this WebAddressAttribute is set into a RenderRegion,
				there is no way of finding out the clickable rectangle of the
				Web Address attribute. But at the same time the WebAddressAttribute
				*must* know its clickable rectangle.

				So, this is what happens. When the AttrWebAddress is called to
				render the WebAddressAttribute, it does the following:
				
				a. Makes a copy of the WebAddressAttribute
				b. Finds out the clickable rectangle
				c. Stores the clickable rectangle in the WebAddressAttribute
				d. Sets the WebAddressAttribute into the RenderRegion.

				The moral of the story is: to find the clickable rectangle when the
				attribute is stored in the tree, use AttrWebAddress::GetClickableRectangle.
				Don't call AttrWebAddress::GetClickableRectangleInRendering.
							
********************************************************************************************/

class WebAddressAttribute : public AttributeValue
{
	CC_DECLARE_DYNCREATE(WebAddressAttribute)

	//Constructors and initialiser
public:
	WebAddressAttribute();

	WebAddressAttribute(WebAddress url, 
							BOOL fBounding=FALSE, 
							TCHAR*  pcFrame=NULL);

	WebAddressAttribute(TCHAR* pcURL, 
							BOOL fBounding=FALSE, 
							TCHAR*  pcFrame=NULL);

	



	static BOOL Init();

	//Destructor, copy constructor and assignment operator
public:
	~WebAddressAttribute();
	WebAddressAttribute(const WebAddressAttribute& waaCopy);
	WebAddressAttribute& operator=(const WebAddressAttribute& waaCopy);

	
	//Operations
public:
	virtual void Render(RenderRegion* pRegion, BOOL Temp = FALSE);
	virtual void Restore(RenderRegion* pRegion, BOOL Temp);

	virtual void SimpleCopy(AttributeValue *);
	virtual NodeAttribute *MakeNode();
	BOOL IsDifferent(AttributeValue *pAttr);

	virtual BOOL Blend(BlendAttrParam* pBlendParam);

	//Access functions
public:
	void SetClickableRectangleInRendering(DocRect rectNew)
	{
		m_rectClickableInRendering=rectNew;
	}

	DocRect GetClickableRectangleInRendering()
	{
		return m_rectClickableInRendering;
	}

	BOOL HasURL()
	{
		return (!m_url.IsEmpty());
	}

	BOOL UseBoundingRectangle()
	{
		return m_fBounding;
	}

	//Toolkit functions
public:
	static void CopyString(TCHAR** ppcCopyTo, const TCHAR* pcCopyFrom);
	static BOOL AreStringsEqual(TCHAR* pcFirst, TCHAR* pcSecond);
	
	//Member variables. See comments above for a description
public:
	WebAddress m_url;
	BOOL m_fBounding;
	TCHAR* m_pcFrame;

	DocRect m_rectClickableInRendering;
};


/***********************************************************************************************

>	class AttrWebAddress : public NodeAttribute

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/3/97
	Purpose:	The new Web Address attribute. This is distinct from the old
				Web Address attribute from CorelXARA 1.5, which was a type of
				AttrUser.

***********************************************************************************************/

class AttrWebAddress : public NodeAttribute
{
	CC_DECLARE_DYNCREATE(AttrWebAddress)

	//Constructors
public:
	AttrWebAddress(); 
	AttrWebAddress(Node* ContextNode,  
					  AttachNodeDirection Direction,    
				      BOOL Locked=FALSE, 
				      BOOL Mangled=FALSE,  
				      BOOL Marked=FALSE, 
					  BOOL Selected=FALSE); 
	AttrWebAddress(WebAddress url, BOOL fBounding=FALSE, TCHAR* pcFrame=NULL);
	AttrWebAddress(TCHAR* pcURL, BOOL fBounding=FALSE, TCHAR* pcFrame=NULL);
	virtual AttrIndex GetAttributeIndex () { return ATTR_WEBADDRESS; }

	//Overloaded operators
public:
	virtual INT32 operator==(const NodeAttribute& NodeAttrib); 

	
	//Operations
public:
	void Render( RenderRegion* pRender );
	virtual BOOL Blend(BlendAttrParam* pBlendParam);

	virtual BOOL WritePreChildrenWeb(BaseCamelotFilter* pFilter);
	virtual BOOL WritePreChildrenNative(BaseCamelotFilter* pFilter);
	
	Node* SimpleCopy();		

	//Information functions
public:
	virtual UINT32 GetAttrNameID(void)
	{
		return (_R(IDS_WEBADDRESSATTRIBUTE_ID)); 
	}

    virtual UINT32 GetNodeSize() const
	{
		return sizeof(AttrWebAddress);
	}

	virtual AttributeValue* GetAttributeValue() 
	{ 
		return &Value; 
	}
	
	virtual CCRuntimeClass* GetAttributeType() 
	{ 
		return CC_RUNTIME_CLASS(AttrWebAddress);
	}

	BOOL ShouldBecomeCurrent()
	{
		return FALSE;
	}


	DocRect GetClickableRectangle();

	virtual void PolyCopyNodeContents(NodeRenderable* pNodeCopy);

	//Debug functions
public:
	void GetDebugDetails(StringBase* Str);
	void ShowDebugTreeDetails() const;
	
	//Toolkit functions
private:
	BOOL WriteString(CamelotFileRecord* pcfrRecord, TCHAR* pcWrite);
	void CopyNodeContents( AttrWebAddress* NodeCopy );
	
	//Member variables
public:
	WebAddressAttribute Value;
};


/********************************************************************************************

>	virtual UINT32 AttrWebAddress::GetAttrNameID(void)  

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com> from Simon
	Created:	22/2/94
	Inputs:		-
	Outputs:	-
	Returns:	Attribute description ID
	Purpose:	Returns back a string resource ID describing the attribute

	Errors:		-
	SeeAlso:	-

********************************************************************************************/
/********************************************************************************************

>	virtual UINT32 AttrWebAddress::GetNodeSize() const

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com> from Simon
	Created:	6/10/93
	Inputs:		-
	Outputs:	-
	Returns:	The size of the node in bytes
	Purpose:	For finding the size of the node 
				
	SeeAlso:	Node::GetSubtreeSize

********************************************************************************************/
/********************************************************************************************

>	BOOL AttrUser::ShouldBecomeCurrent()

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	23/3/97
	Returns:	TRUE if this attribute should become current.

				FALSE if the user must deliberately apply this attribute to an object
				every time he wants to use it.

	Purpose:	The attribute manager calls this function before making an attribute current.

				There are some attributes - like this WebAddress attribute I'm about
				to put in - that the user probably won't want to become current.
				For example, if a user puts a HotLink on an object and happens to have
				the Give Other Objects Most Recent Attributes option on, all his new objects are
				going to have HotLinks. That's not good.

				So those attributes will override this function and return FALSE.

********************************************************************************************/

/********************************************************************************************

>	BOOL WebAddressAttribute::HasURL()

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	16/4/97
	Returns:	TRUE if this WebAddressAttribute has a non-empty URL
				FALSE if this WebAddressAttribute has an empty URL

	Purpose:	The definitive test to find whether this attribute
				contains a link to a Web Address. Used to decide
				whether to let this WebAddressAttribute specify
				a region in an imagemap.

				The test to find whether the URL is empty is:
				a. EITHER m_pcURL is NULL
				b. OR m_pcURL points to a NULL character

********************************************************************************************/


#endif //ifdef INC_WEBATTR
