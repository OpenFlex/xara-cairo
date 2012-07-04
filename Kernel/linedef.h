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


// The line definition class header.  An abstract base class from which to
// derive the definitions of things like strokes, brushes.


#ifndef INC_LINEDEF
#define INC_LINEDEF


/********************************************************************************************

>	class LineDefinition : public CCObject

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	28/2/97

	Purpose:	Stores a vector Line definition
				A static list of these items is held in the LineComponent.

	SeeAlso:	LineComponent

********************************************************************************************/

class LineDefinition : public CCObject
{
CC_DECLARE_DYNAMIC(LineDefinition);

public:
	LineDefinition();
	LineDefinition(Node *pLineTree);

	~LineDefinition();

	void SetLineName(StringBase *pName);
	
	/* StrokeDefinition functions - not sure yet if we want to keep them
	in the base class
	void SetLineRepeating(BOOL Repeating);
	void SetNumLineRepeats(INT32 NumRepeats);
	*/
	void SetOverrideFill(BOOL Override)		{ m_bOverridesFill  = Override; };
	void SetOverrideTrans(BOOL Override)	{ m_bOverridesTrans = Override; };

	static void ConvertIndexedColours(Spread* pSpread);

public:
	virtual BOOL IsDifferent(LineDefinition *pOther) = 0;
			// Returns TRUE if these Line definitions are not the same

	inline Node *GetLineTree(void)		{ return(m_pTree); };
			// Get at the Line clipart tree

	inline String_32 *GetLineName(void)	{ return(&m_Name); };
	
	/*
	inline BOOL IsRepeating(void) const		{ return(Repeating); };
			// Determine if this Line should repeat or stretch onto the destination path

	inline INT32 NumRepeats(void) const		{ return(Repeats); };
			// Determine if this Line should repeat or stretch onto the destination path
	*/
	inline BOOL OverrideFill(void) const	{ return(m_bOverridesFill); };
	inline BOOL OverrideTrans(void) const	{ return(m_bOverridesTrans); };
			// Determine if this Line overrides the fill/transparency geometry with its own ones
	
	BOOL NeedsTransparency(void) const;
			// Determine if this Line needs transparency to render correctly

	inline void  SetIOStore(UINT32 NewValue)		{ IOStore = NewValue; };
	inline UINT32 ReadIOStore(void) const		{ return(IOStore); };

protected:
	Node *m_pTree;				// A clipart subtree which defines the Line

	String_32 m_Name;				// The name of this Line (as shown in Line gallery)
	
	/*
	INT32 Repeats;				// Number of times a brush should repeat along the Line, or zero for optimal
	BOOL Repeating;				// TRUE if the Line should repeat along the path, FALSE if it should stretch
	*/
	BOOL m_bOverridesFill;			// TRUE if the Line uses its own fills rather than the current fill colour
	BOOL m_bOverridesTrans;		// TRUE if the Line uses its own transparencies rather than the current one

	BOOL m_bNeedsTrans;			// TRUE if the Line needs transparency in order to render

	UINT32 IOStore;				// Used during export to indicate whether this definition has been saved
								// Used during import to store the handle associated with this Line
								// in the file, so we can re-map handles into our array on import.
};


#endif
