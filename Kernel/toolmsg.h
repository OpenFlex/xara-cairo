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


#ifndef INC_TOOLMSG
#define INC_TOOLMSG
class Tool; 


/********************************************************************************************

>	class ToolsCurrentAttrGroupChangedMsg: public Msg

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	07/02/96
	Purpose:	This message is broadcast by the Tools whenever the Current Attribute 
				Group associated with a tool changes. This presently means that we have 
				switched to or from the Text Tool.
  SeeAlso:		CommonAttrsChangedMsg

********************************************************************************************/

class ToolsCurrentAttrGroupChangedMsg: public Msg
{
	CC_DECLARE_DYNAMIC(ToolsCurrentAttrGroupChangedMsg);
public:

	ToolsCurrentAttrGroupChangedMsg() { };
};

#endif // INC_TOOLMSG
