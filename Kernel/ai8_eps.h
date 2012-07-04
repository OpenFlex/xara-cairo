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


#if !defined(AFX_AI8_EPS_H__DF935500_009B_11D4_8364_006008484641__INCLUDED_)
#define AFX_AI8_EPS_H__DF935500_009B_11D4_8364_006008484641__INCLUDED_

#include "ai_eps.h"
#include "ai5_eps.h"

/********************************************************************************************

>	class AI8EPSFilter

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	28/03/00
	Purpose:	Allows us to import Adobe Illustrator 8.0 files.
				(at the time of writing only the version 7.0 documentation was available
				so some omissions are inevitable).

********************************************************************************************/

class AI8EPSFilter : public AI5EPSFilter  
{
	CC_DECLARE_DYNAMIC(AI8EPSFilter);

public:
	AI8EPSFilter();
	virtual ~AI8EPSFilter();

	virtual BOOL Init();

	virtual INT32 EPSHeaderIsOk(ADDR pFileHeader, UINT32 HeaderSize);
	virtual void LookUpToken();
	virtual BOOL ProcessToken();

protected:
	virtual BOOL DecodeLayer ( void );
};

#endif // !defined(AFX_AI8_EPS_H__DF935500_009B_11D4_8364_006008484641__INCLUDED_)
