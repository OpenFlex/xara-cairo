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



class CXaraFileRecord;
class TextChar;

/***********************************************************************************************

>	class ImportedString : public ListItem

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/8/96
	Purpose:	Encapsulates an imported string that's come from the a v2 format file.

***********************************************************************************************/

class ImportedString : public ListItem
{
	CC_DECLARE_DYNCREATE(ImportedString);

public:
	ImportedString() { pCopyOfStringRecord = NULL; pFirstChar = NULL; }
	ImportedString(TextChar* pChar,CXaraFileRecord* pRecord);
	~ImportedString();

	CXaraFileRecord* GetRecord();
	TextChar* GetFirstChar();

private:
	CXaraFileRecord* pCopyOfStringRecord;
	TextChar*		 pFirstChar;
};


/***********************************************************************************************

>	class ImportedStringList : public List

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/8/96
	Purpose:	Used to manage a list of ImportedString objects

***********************************************************************************************/

class ImportedStringList : public List
{
	CC_DECLARE_DYNAMIC(ImportedStringList)

public:
	ImportedStringList() {}

	void AddTail(ImportedString* pItem);
	ImportedString* GetHead();
	ImportedString* GetNext(ImportedString* pItem);
};
