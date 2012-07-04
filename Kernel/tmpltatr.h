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


#ifndef INC_TMPLTATR
#define INC_TMPLTATR

#define ENSURE_NOT_NULL(Pointer)		ERROR2IF(Pointer == NULL, 0, "NULL Args")


extern const String_8 NullString;


class WizOp;
class WizOpStyles;
/***********************************************************************************************

>	class TemplateAttribute : public AttrUser

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	21/06/97

	Purpose:	This represents a TemplateOp/Argument/user-changable from the template file
				attribute.
				It will probably be superceded, but for now it's derived from AttrUser with a 
				value of the form <InternalName>[/<Param>][;<Question>]
				Bring on the plug-in attributes I say.

***********************************************************************************************/
class TemplateAttribute : public AttrUser
{
	CC_DECLARE_DYNAMIC(TemplateAttribute)
public:
	TemplateAttribute(	const StringBase& ArgumentName = NullString, 
						const StringBase& Question = NullString,
						const StringBase& Param = NullString); 



// Overridden
	virtual Node* SimpleCopy();
	void CopyNodeContents(TemplateAttribute* pAttr);
	virtual void PolyCopyNodeContents(NodeRenderable* pNodeCopy);
	virtual UINT32 GetAttrNameID();
	virtual BOOL IsAnObjectName() const;
	virtual BOOL WritePreChildrenWeb(BaseCamelotFilter* pFilter);
	virtual AttributeIdentifier	GetAttributeClassID() const;
	virtual VisibleAttribute* CreateVisibleAttribute() const;

// Data Access
	String_256 GetQuestion() const;
	String_256 GetInternalName() const;
	String_256 GetParam() const;
	StringBase&	GetUserName() const;

	BOOL SetWizOpNameAndParam(const StringBase& Name, const StringBase& Param);

protected:
	BOOL m_fIsAnObjectName;
	static const TCHAR s_ParamDelimiter;
	static const String_8 s_TemplateKey;
};


// Shorthand - we use these a lot in the Name gallery.
#define TA_CLASS	(CC_RUNTIME_CLASS(TemplateAttribute))
#define	TA_NAME		(String(TEXT("ObjectName")))



/***********************************************************************************************

>	class TemplateAttrRecordHandler : public CamelotRecordHandler

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	27/06/97

	Purpose:	Handles the reading of WizOp records in the v2 file format

***********************************************************************************************/
class TemplateAttrRecordHandler : public CamelotRecordHandler
{
	// Give my name in memory dumps
	CC_DECLARE_DYNAMIC(TemplateAttrRecordHandler);

public:
	// functions that must be implemented.
	virtual UINT32*	GetTagList();
	virtual BOOL	HandleRecord(CXaraFileRecord* pCXaraFileRecord);

#ifdef XAR_TREE_DIALOG
	virtual void GetRecordDescriptionText(CXaraFileRecord* pCXaraFileRecord,StringBase* Str);
	virtual void GetTagText(UINT32 Tag,String_256& Str);
#endif

private:
	// nothing here but us mice
};

class WizOpStyle;
/***********************************************************************************************

>	class StyleReferenceAttribute : public TemplateAttribute

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	21/06/97

	Purpose:	This represents a TemplateOp/Argument/user-changable from the template file
				attribute.
				It will probably be superceded, but for now it's derived from AttrUser with a 
				value of the form <InternalName>[/<Param>][;<Question>]
				Bring on the plug-in attributes I say.

***********************************************************************************************/
class StyleReferenceAttribute : public TemplateAttribute
{
	CC_DECLARE_MEMDUMP(StyleReferenceAttribute)
public:
	StyleReferenceAttribute(const WizOpStyle& Style);

// Overridden
	virtual Node* SimpleCopy();
	virtual UINT32 GetAttrNameID(void); 
	virtual BOOL WritePreChildrenWeb(BaseCamelotFilter* pFilter);
	virtual BOOL CopyComponentData(BaseDocument* SrcDoc,  BaseDocument* NodesDoc);

	virtual VisibleAttribute* CreateVisibleAttribute() const;

	const StringBase& GetStyleName() const;

protected:
	// Implementation
	BOOL SetStyle(const Style& StyleToReference);

	WizOpStyles* GetStylesForFilter(BaseCamelotFilter& Filter) const;
	WizOpStyles* GetStylesForDoc(BaseDocument& Doc) const;
//	WizOpStyles* GetStyles() const;
};



/***********************************************************************************************

>	class WizOpStyleRefRecordHandler : public CamelotRecordHandler

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	27/06/97

	Purpose:	Handles the reading of WizOpStyleRef records in the v2 file format

***********************************************************************************************/
class WizOpStyleRefRecordHandler : public CamelotRecordHandler
{
	// Give my name in memory dumps
	CC_DECLARE_DYNAMIC(WizOpStyleRefRecordHandler);

public:
	WizOpStyleRefRecordHandler() : m_pStyleComponent(NULL) {}
	BOOL Init(BaseCamelotFilter* pFilter);

	// functions that must be implemented.
	virtual UINT32*	GetTagList();
	virtual BOOL	HandleRecord(CXaraFileRecord* pCXaraFileRecord);

#ifdef XAR_TREE_DIALOG
	virtual void GetRecordDescriptionText(CXaraFileRecord* pCXaraFileRecord,StringBase* Str);
	virtual void GetTagText(UINT32 Tag,String_256& Str);
#endif

protected:
	WizOpStyles&	GetImportedStyles() const;

private:
	WizOpStyles*	m_pStyleComponent;
};

#endif //ifdef INC_USERATTR
