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

// The header file for the hot key system

#ifndef INC_HOTKEYS
#define INC_HOTKEYS

//#include "listitem.h" - in camtypes.h [AUTOMATICALLY REMOVED]

class KeyPress;
class OpDescriptor;
class CCLexFile;
class String_256;
class String_32;

/********************************************************************************************

>	class HotKey : public ListItem

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	31/8/94
	Purpose:	Encapsulates hot keys in camelot

********************************************************************************************/

class HotKey : public ListItem
{
CC_DECLARE_MEMDUMP(HotKey)

public:
	static BOOL Init();
	static void Deinit();

	static BOOL 	AddHotKey(KeyPress* pKeyPress,TCHAR* pOpToken,String_32* pTextDesc,BOOL CheckUnicode);
	static BOOL 	OnKeyPress(KeyPress* pKeyPress);
	static HotKey* 	FindHotKey(OpDescriptor* pThisOpDesc);

	void GetTextDesc(String_256* pStr);

private:
	static BOOL DoesHotKeyMatchKeyPress(HotKey* pHotKey,KeyPress* pKeyPress);

	static BOOL ReadHotKeys();
	static BOOL ReadHotKeysFromDisk();
	static BOOL ReadHotKeysFromRes();
	static BOOL ReadHotKeysFromFile(CCLexFile& file);
	static BOOL ReadHotKey(CCLexFile& file);
	static BOOL ReadToolSwitch(CCLexFile& file);

	static BOOL ReadKeyDef(CCLexFile& file,KeyPress** ppKeyPress,String_256* pOpToken,String_32** ppTextDesc,BOOL *pCheckUnicode);

	HotKey();			// Private default constructor
	~HotKey();			// Private default destructor

	BOOL IsEnabled();	// Tests to see if hot key's op can be invoked. Also updates the status bar

	KeyPress* 		pKeyPress;
	OpDescriptor* 	pOpDesc;
	String_32*		pTextDesc;
	BOOL			CheckUnicode;
};


#endif	// INC_HOTKEYS
