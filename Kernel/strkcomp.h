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

// Stroke Doc-component classes.
// These store brush-stroke definitions as clipart subtrees

#ifndef INC_STRKCOMP
#define INC_STRKCOMP

//#include "doccomp.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "linecomp.h"
#include "linedef.h"
//#include "camfiltr.h" - in camtypes.h [AUTOMATICALLY REMOVED]

class BaseCamelotFilter;
class CXaraFileRecord;
class CamelotRecordHandler;
class Node;


/* NOTE: Diccon - 13/12/99.
In the implementation of the new brush objects it was decided that they should be stored and
retrieved in the same way as strokes.  Therefore a new superclass has been createed from which 
these classes are now derived as well as the brushcomponent and brushdefintion classes.
See other notes in linecomp.h for more info
*/

/********************************************************************************************

>	typedef UINT32 StrokeHandle;

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	28/2/97

	Purpose:	A StrokeHandle is a unique reference to a vector stroke in the
				StrokeComponent. All references to strokes are done via StrokeHandles,
				which allows us to delete & relocate strokes without worrying about
				leaving lots of pointers to them lying about and causing havoc.

				The special handle StrokeHandle_NoStroke is used for illegal handles
				and returning error states.

	SeeAlso:	StrokeComponent; StrokeDefinition

********************************************************************************************/

typedef UINT32 StrokeHandle;

const StrokeHandle StrokeHandle_NoStroke = 0xffffffff;



/********************************************************************************************

>	class StrokeDefinition : public LineDefinition

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	28/2/97

	Purpose:	Stores a vector stroke definition
				A static list of these items is held in the StrokeComponent.

	SeeAlso:	StrokeComponent

********************************************************************************************/

class StrokeDefinition : public LineDefinition
{
CC_DECLARE_DYNAMIC(StrokeDefinition)

public:
	StrokeDefinition()	{ ERROR3("Don't use this constructor"); };
	StrokeDefinition(Node *pStrokeTree, BOOL repeating = FALSE, INT32 repeats = 0);
//	StrokeDefinition(Node *pStrokeTree, MILLIPOINT StartCap, MILLIPOINT EndCap);

	~StrokeDefinition();

	void SetStrokeName(StringBase *pName);
	void SetStrokeRepeating(BOOL Repeating);
	void SetNumStrokeRepeats(INT32 NumRepeats);
	void SetOverrideFill(BOOL Override)		{ OverridesFill  = Override; };
	void SetOverrideTrans(BOOL Override)	{ OverridesTrans = Override; };

public:
	virtual BOOL IsDifferent(LineDefinition *pOther);
			// Returns TRUE if these stroke definitions are not the same

	inline Node *GetStrokeTree(void)		{ return(pStroke); };
			// Get at the stroke clipart tree

 	inline String_32 *GetStrokeName(void)	{ return(&Name); };

	inline BOOL IsRepeating(void) const		{ return(Repeating); };
			// Determine if this stroke should repeat or stretch onto the destination path

	inline INT32 NumRepeats(void) const		{ return(Repeats); };
			// Determine if this stroke should repeat or stretch onto the destination path

	inline BOOL OverrideFill(void) const	{ return(OverridesFill); };
	inline BOOL OverrideTrans(void) const	{ return(OverridesTrans); };
			// Determine if this stroke overrides the fill/transparency geometry with its own ones

	BOOL NeedsTransparency(void) const;
			// Determine if this stroke needs transparency to render correctly

	inline void  SetIOStore(UINT32 NewValue)		{ IOStore = NewValue; };
	inline UINT32 ReadIOStore(void) const		{ return(IOStore); };

private:
	Node *pStroke;				// A clipart subtree which defines the stroke

	String_32 Name;				// The name of this stroke (as shown in stroke gallery)

	INT32 Repeats;				// Number of times a brush should repeat along the stroke, or zero for optimal
	BOOL Repeating;				// TRUE if the stroke should repeat along the path, FALSE if it should stretch
	BOOL OverridesFill;			// TRUE if the stroke uses its own fills rather than the current fill colour
	BOOL OverridesTrans;		// TRUE if the stroke uses its own transparencies rather than the current one

	BOOL NeedsTrans;			// TRUE if the stroke needs transparency in order to render

	UINT32 IOStore;				// Used during export to indicate whether this definition has been saved
								// Used during import to store the handle associated with this stroke
								// in the file, so we can re-map handles into our array on import.
};



/********************************************************************************************

>	class StrokeComponentClass : public DocComponentClass

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/2/97
	Purpose:	The class that gets a Stroke doc component going on start up
				We need to register our class as a document component and this is where
				we do it all.
	SeeAlso:	DocComponentClass

********************************************************************************************/

class StrokeComponentClass : public DocComponentClass
{
CC_DECLARE_DYNAMIC(StrokeComponentClass)

public:
	static BOOL Init();
	static void DeInit();

public:
	BOOL AddComponent(BaseDocument *pDoc);
};



/********************************************************************************************

>	class StrokeComponent : public DocComponent

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/2/97

	Purpose:	A document component for handling Stroke definitions.

				StrokeComponents share a global cache of available stroke types.
				Individual instances serve as managers for the list, mainly providing
				import/export facilities for stroke definitions.

	SeeAlso:	DocComponent

********************************************************************************************/

class StrokeComponent : public DocComponent
{
friend class StrokeComponentClass;
friend class StrokeDefinition;

CC_DECLARE_DYNAMIC(StrokeComponent)

public:
	StrokeComponent();
	virtual ~StrokeComponent();


protected:		// Internal functions for friend classes
	static void DeleteStrokeList(void);
				// One-time deinitialisation, called on exit

public:
	static StrokeHandle AddNewStroke(StrokeDefinition *pStroke);
				// Add a new stroke definition to the global list

	static StrokeDefinition *FindStroke(StrokeHandle Handle);
				// Finds the definition of a given stroke

public:			// External V2 native file import/export handlers
	virtual BOOL StartImport(BaseCamelotFilter *pFilter);
	virtual BOOL EndImport(BaseCamelotFilter *pFilter, BOOL Success);
	virtual BOOL StartExport(BaseCamelotFilter *pFilter);
	virtual BOOL EndExport(BaseCamelotFilter *pFilter, BOOL Success);


public:			// Internal file format handlers - called from our RecordHandler in strkattr.cpp
	static BOOL StartImportStroke(CamelotRecordHandler *pHandler, CXaraFileRecord *pRecord);
	static BOOL EndImportStroke(CamelotRecordHandler *pHandler);
				// Starts and completes import of the Atomic stroke definition

	static StrokeHandle FindImportedStroke(UINT32 ImportedHandle);
				// Finds the internal handle of the stroke definition with the given imported handle

	static BOOL ExportStroke(BaseCamelotFilter *pFilter, StrokeHandle Handle);
				// Exports a stroke definition (if necessary)


private:			// Global Stroke list & management functions
	static BOOL ExpandArray(void);

private:
	static StrokeDefinition **pStrokeList;	// Global array of available stroke definitions
	static UINT32 CurrentSize;				// Number of entries allocated to the array
	static UINT32 Used;						// Number of entries used in the array (index of 1st free slot)

private:			// Import records
	static UINT32 ImportHandle;				// Record the data associated with the record currently 
	static UINT32 ImportFlags;				// being imported
	static UINT32 ImportData1;
	static UINT32 ImportData2;
	static InsertTreeContext *pImportPreviousContext;
	static Node  *pImportNewBrush;
	static String_32 ImportedName;
};



#endif
