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

#ifndef INC_OPWHAT
#define INC_OPWHAT 

//class NodeGroup;

//#include "ops.h" - in camtypes.h [AUTOMATICALLY REMOVED]

#define OPTOKEN_WHATSTHIS _T("WhatsThis")
   

/********************************************************************************************

>	class OpWhatsThis : public Operation

	Author:		Ollie_Cornes (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/11/95
	Purpose:	This class represents the global "What's This?" operation.
	SeeAlso:	
	Documentation:  Docs\Help\*.*

********************************************************************************************/

class CCAPI OpWhatsThis: public Operation
{         

	CC_DECLARE_DYNCREATE( OpWhatsThis )    

public:
	OpWhatsThis();								
	static BOOL		Init();				
	static OpState	GetState(String_256*, OpDescriptor*);		
	void			Do(OpDescriptor*);	
protected:	  
};        


#endif // IC_OPWHAT
