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

// Aldus FreeHand EPS filter

#ifndef INC_FREEEPS
#define INC_FREEEPS

//#include "epsfiltr.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "impcol.h"


#define FHEF_COLOURARRAY_INITIALSIZE	32
#define FHEF_COLOURARRAY_CHUNK			16


/********************************************************************************************

>	class FreeHandEPSFilter : public EPSFilter

	Author:		Ben_Summers (Xara Group Ltd) <camelotdev@xara.com>
	Created:	31/05/95
	Purpose:	Aldus FreeHand 3.0 filter

********************************************************************************************/

class FreeHandEPSFilter : public EPSFilter
{
	CC_DECLARE_DYNAMIC(FreeHandEPSFilter);
	
public:
	FreeHandEPSFilter();
	BOOL Init();

protected:
	BOOL PrepareToImport();
	INT32 EPSHeaderIsOk(ADDR pFileHeader, UINT32 HeaderSize);
	void LookUpToken();
	BOOL ProcessToken();
	void CleanUpAfterImport(BOOL Successful);
	BOOL ValidateGroup(Node *pGroup);
	BOOL MaskedGroupEnding();
	virtual BOOL AddNewNode(Node *pNewNode);

private:
	static CommandMap FHCommands[];
	BOOL PopColour(DocColour *Col);
	BOOL PopNamedColour(DocColour *Col);
	BOOL DiscardFillSubType();
	BOOL SaveCurrentFill();
	BOOL RestoreCurrentFill();
	BOOL RemoveLastSubPathIfNotUnique(Path *pPath);

private:
	BOOL HadhToken;
	BOOL DoingGradFill;
	AttributeValue *OldFill;
	BOOL InColours;
	BOOL InText;
	ImportedColours *pNewColours;
	IndexedColour **ColourArray;
	INT32 ColourArrayEntries;
	INT32 ColourArraySize;
	BOOL ComplexPathMode;
	BOOL HadFirstOfComplexPath;
	NodePath *pLastPathSeen;
};


#endif  // INC_FREEEPS
