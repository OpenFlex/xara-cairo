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

#ifndef INC_TMPLTARG
#define INC_TMPLTARG

class WizOps;

WizOps& GetWizOps();

/**************************************************************************************

>	class WizOp : public ListItem

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com> G.Barfoot
	Created:	11/06/97

	Purpose:	The Camelot Text file format supports templating. Each argument to
				a template is processed by a WizOp. The WizOp's extracted from
				the registry, which this class represents, are then Available 
				Properties in the Wizard Properties dialog.

**************************************************************************************/
class WizOp : public ListItem
{
	// Declare the class for memory tracking
	CC_DECLARE_MEMDUMP(WizOp);

public:
	WizOp(	const StringBase& InternalName, const StringBase& UserName, 
			const StringBase& ParamHint);

	const StringBase& GetInternalName() const;
	const StringBase& GetUserName() const;
	const StringBase& GetParamHint() const;

private:
	const String_256	m_Name;
	const String_256	m_UserName;
	const String_256	m_ParamHint;
};



/**************************************************************************************

>	class WizOps : public List

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com> G.Barfoot
	Created:	11/06/97

	Purpose:	This collection of WizOps is used by the Wizard Properties dialog.

**************************************************************************************/
class WizOps : public List
{
	// Declare the class for memory tracking
	CC_DECLARE_MEMDUMP(WizOps);

public:
	~WizOps();

	BOOL InitializeFromRegistry();

	WizOp* GetFirstWizOp() const;
	WizOp* GetNextWizOp(const WizOp* const pWizOp) const;

	WizOp* FindWizOpFromInternalName(const StringBase& InternalName) const;
protected:
	BOOL AddWizOp(	const StringBase& InternalName, const StringBase& UserName,
					const StringBase& ParamHint);

	BOOL GetInternalNameFromCLSID(const CLSID& WizOpCLSID, StringBase* const pString) const;
	BOOL GetUserNameFromCLSID(const CLSID& WizOpCLSID, StringBase* const pString) const;
	BOOL GetParamHintFromCLSID(const CLSID& WizOpCLSID, StringBase* const pString) const;
private:
	// Some data / state things some day
};

#endif	// INC_TMPLTARG


