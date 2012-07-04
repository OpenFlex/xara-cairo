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


#ifndef INC_COMATTRMSG
#define INC_COMATTRMSG
/********************************************************************************************

>	class CommonAttrsChangedMsg: public Msg

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	06/02/96
	
	  Purpose:	Respond to this message whenever you need to call Range::FindCommonAttribute or
				Range::FindCommonAttributes	to display up-to-date common attribute information
				to the user. Because FindCommonAttributes returns Current Attributes in some
				situations, this message is broadcast whenever any of the following msgs 
				are receved by the SelRange.

				CurrentAttrChangedMsg			The Current Attribute values have changed 
				SelChangingMsg					The selection has changed => Common attributes changed 
				ToolsCurrentAttrGroupChangedMsg	The Current Attribute Group has associated with the 
												selected tool has changed. 
								 													 			

	SeeAlso:		SelRange::FindCommonAttribute
	SeeAlso:		SelRange::FindCommonAttributes
	SeeAlso:		CurrentAttrChangedMsg
	SeeAlso:		SelChangingMsg
	SeeAlso:		ToolsCurrentAttrGroupChangedMsg

********************************************************************************************/
class CommonAttrsChangedMsg: public Msg
{
	CC_DECLARE_DYNAMIC(CommonAttrsChangedMsg);
public:
  	CommonAttrsChangedMsg() { };
};



#endif // INC_UNITS
