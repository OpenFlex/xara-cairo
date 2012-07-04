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


// Declaration of the Document Component objects

#ifndef INC_DOCCOMP
#define INC_DOCCOMP

#include "listitem.h"
#include "document.h"

class BaseDocument;
class EPSFilter;
class BaseCamelotFilter;

/********************************************************************************************

>	class DocComponentClass : public ListItem

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	01/08/94
	Purpose:	This provides a class of objects which implement an interface to a particular 
				kind of	document component - for example a colour table, or a list of
				arrowheads.
				Each kind of object should register with the application on startup, and
				then when a document is created, each of these objects is asked to add
				an instance of a DocumentComponent object to it.  The DocumentComponent
				objects are the actual implemtations of the components.  For example, they
				contain the colours for a colour list, and so on.  This class, the
				DocumentComponentClass, is merely for registering the existence of a new
				kind of document component, and providing a mechanism for inserting them
				into new documents.
	SeeAlso:	DocumentComponent

********************************************************************************************/

class DocComponentClass : public ListItem
{
	CC_DECLARE_DYNAMIC(DocComponentClass)

public:
	virtual BOOL AddComponent(BaseDocument *) = 0;
};



/********************************************************************************************

>	class DocComponent : public ListItem

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	01/08/94
	Purpose:	An implementation of an instance of a document component, such as a colour
				table, or a list of arrowheads.  These are the objects that are 
				instantiated for each Document object that exists, and are held in a list
				in each Document object.
	SeeAlso:	DocumentComponentClass

********************************************************************************************/

class DocComponent : public ListItem
{
	CC_DECLARE_DYNAMIC(DocComponent)

public:
	// These are the Camelot Version 2 Web and Native file related functions
	virtual BOOL StartImport(BaseCamelotFilter *pFilter);
	virtual BOOL EndImport(BaseCamelotFilter *pFilter, BOOL Success);

	virtual BOOL StartExport(BaseCamelotFilter *pFilter);				// Set up export data structures
	virtual BOOL StartExportBeforeComp(BaseCamelotFilter *pFilter);
	virtual BOOL EndExport(BaseCamelotFilter *pFilter, BOOL Success);	// Write out pending data
	virtual void CleanUpAfterExport(BOOL Success);						// Destroy export data structures

	// -------------------------------
	
	// These are the EPS related functions - covers from simple EPS to the old native EPS formats
	virtual BOOL EPSStartImport(EPSFilter *);
	virtual void EPSEndImport(EPSFilter *, BOOL);
	virtual BOOL EPSStartExport(EPSFilter *);
	virtual void EPSEndExport(EPSFilter *);

	virtual BOOL WriteEPSProlog(EPSFilter *);
	virtual BOOL WriteEPSSetup(EPSFilter *);
	virtual BOOL WriteEPSComments(EPSFilter *);
	virtual BOOL WriteScript(EPSFilter*);

	virtual ProcessEPSResult ProcessEPSComment(EPSFilter *, const TCHAR *);
	virtual void EndOfEPSComment(EPSFilter *);

	// More general function to control progress display.
	virtual INT32 GetSizeOfExport(Filter*);

	// Methods called before and after a tree copy
	virtual BOOL StartComponentCopy();
	virtual BOOL EndComponentCopy(); 
	virtual void AbortComponentCopy();  
};



#endif  // INC_DOCCOMP


