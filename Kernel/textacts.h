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

// Actions used by text operations

#ifndef INC_TEXTACTS
#define INC_TEXTACTS

//#include "ops.h" - in camtypes.h [AUTOMATICALLY REMOVED]

class TextStory;
class TextChar;
class KernCode;

/********************************************************************************************

>	class BaseTextAction : public Action

	Author:		Peter_Arnold (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/5/95
	Purpose:	Base class of all text actions

********************************************************************************************/

class BaseTextAction : public Action
{
	CC_DECLARE_DYNCREATE(BaseTextAction);

	BaseTextAction();

protected:
	TextStory* pStory;

};



/********************************************************************************************

>	class StoreCharCodeAction : public BaseTextAction

	Author:		Peter_Arnold (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/5/95
	Purpose:	This action is used to restore a character's UniCode value on undo.  Using
				this an op can chage the character code of a TextChar without having to 
				hide the old char and create a new one.
	SeeAlso:	BaseTextAction

********************************************************************************************/

class StoreCharCodeAction : public BaseTextAction
{

CC_DECLARE_DYNCREATE(StoreCharCodeAction)

public:
	StoreCharCodeAction();
	~StoreCharCodeAction();
	virtual ActionCode Execute();
	static ActionCode Init( Operation*, ActionList*, TextStory*, TextChar*);
	static BOOL DoStoreCharacterCode( Operation* pOp, ActionList*, TextChar*);

protected:
	TextChar* pChar;
	WCHAR CharCode;
}; 



/********************************************************************************************

>	class StoreKernCodeAction : public BaseTextAction

	Author:		Peter_Arnold (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/5/95
	Purpose:	This action is used to restore a kern value on undo.  Using this an op can
				change the kern value without having to hide the old KernCode and create a
				new one.
	SeeAlso:	BaseTextAction

********************************************************************************************/

class StoreKernCodeAction : public BaseTextAction
{

CC_DECLARE_DYNCREATE(StoreKernCodeAction)

public:
	StoreKernCodeAction();
	~StoreKernCodeAction();
	virtual ActionCode Execute();
	static ActionCode Init( Operation*, ActionList*, TextStory*, KernCode*);
	static BOOL DoStoreKernValue( Operation* pOp, ActionList*, KernCode*);

	// Access functions used when op merging
	KernCode* GetKernCode() const {return pKernCode;}
	DocCoord GetKernValue() const {return KernValue;}
	void SetKernCode(DocCoord NewValue) {KernValue = NewValue;}

protected:
	KernCode* pKernCode;
	DocCoord KernValue;
}; 



/********************************************************************************************

>	class ReversePathAction : public BaseTextAction

	Author:		Peter_Arnold (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/5/95
	Purpose:	This action is used to reverse (change direction of) the path inside a TextStory
	SeeAlso:	BaseTextAction

********************************************************************************************/

class ReversePathAction : public BaseTextAction
{

CC_DECLARE_DYNCREATE(ReversePathAction)

public:
	ReversePathAction();
	~ReversePathAction();
	virtual ActionCode Execute();
	static ActionCode Init( Operation*, ActionList*, TextStory*);
	static BOOL DoReversePath( Operation* pOp, ActionList*, TextStory*);
}; 



/********************************************************************************************

>	class MatrixFitToPathAction : public BaseTextAction

	Author:		Peter_Arnold (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/5/95
	Purpose:	This action is used when fitting a TextStory on a path in order to undo 
				matrix changes
	SeeAlso:	BaseTextAction

********************************************************************************************/

class MatrixFitToPathAction : public BaseTextAction
{

CC_DECLARE_DYNCREATE(MatrixFitToPathAction)

public:
	MatrixFitToPathAction();
	~MatrixFitToPathAction();
	virtual ActionCode Execute();
	static ActionCode Init( Operation*, ActionList*, TextStory*);
	static BOOL DoMatrixRemoveFromPath( Operation* pOp, ActionList*, TextStory*);
}; 



/********************************************************************************************

>	class MatrixRemoveFromPathAction : public BaseTextAction

	Author:		Peter_Arnold (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/5/95
	Purpose:	This action is used when fitting a TextStory on a path in order to undo 
				matrix changes
	SeeAlso:	BaseTextAction

********************************************************************************************/

class MatrixRemoveFromPathAction : public BaseTextAction
{

CC_DECLARE_DYNCREATE(MatrixRemoveFromPathAction)

public:
	MatrixRemoveFromPathAction();
	~MatrixRemoveFromPathAction();
	virtual ActionCode Execute();
	static ActionCode Init( Operation*, ActionList*, TextStory*);
	static BOOL DoMatrixFitToPath( Operation* pOp, ActionList*, TextStory*);
}; 


#endif  // INC_TEXTACTS


