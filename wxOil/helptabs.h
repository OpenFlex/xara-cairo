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

/*

	helptabs.h
	
	Interface to the help system's look-up tables.
*/

#ifndef HELPTABS_H
#define HELPTABS_H

// This associates a dialog class and possibly a property-sheet page resource ID with a
// help topic identifier.
struct DialogHelpTuple
{
	LPCTSTR lpcszDialogClass;				// class-name of associated DialogOp
	UINT32	nPageResID;						// page within a tabbed dialog, or zero
	DWORD	dwTopicIndex;					// the help topic associated with this
};


// This is very similar, associating an OpDescriptor's OpToken value with a help topic ID.
struct OpHelpTuple
{
	LPCTSTR lpcszToken;						// value of the OpDescriptor's OpToken
	DWORD	dwTopicIndex;					// the associated help topic
};


// Ditto, but for message boxes.  Of course, these aren't really tuples, especially as many
// message ID's are associated with one help topic, but for consistency . . .
typedef DWORD MsgHelpTuple;


// And these are the tables.
extern DialogHelpTuple  atplDialogTopics[];
extern OpHelpTuple		atplOpTopics[];
extern MsgHelpTuple		atplMsgTopics[];

#endif	// !HELPTABS_H
