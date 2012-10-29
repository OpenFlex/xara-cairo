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


// Declaration of the Corel EPS filters.

#ifndef INC_CORELEPS
#define INC_CORELEPS


/********************************************************************************************

>	class CorelEPSFilter : public EPSFilter

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	08/03/94
	Purpose:	A base class filter that implements the core functionality required for
				a Corel EPS import filter.  Other filters are derived from this - this
				class is never instantiated as it is incomplete.
	SeeAlso:	Corel3EPSFilter; Corel4EPSFilter; EPSFilter

********************************************************************************************/

class CorelEPSFilter : public EPSFilter
{
	CC_DECLARE_DYNAMIC(CorelEPSFilter);
	
public:
	CorelEPSFilter();
	BOOL Init();
	char *GetEPSCommand(EPSCommand Cmd);

protected:
	virtual void LookUpToken();
	virtual BOOL ProcessToken();

	BOOL DecodeCorelGradFill();
	BOOL DecodeLinearGradFill();
	BOOL DecodeRadialGradFill();
	BOOL DecodeConicalGradFill();
	BOOL AddAttributes(NodeRenderableBounded *pNode, BOOL Stroked, BOOL Filled);

	// The array of keyword names
	static CommandMap CorelCommands[];
	
	// The parameters for the current graduated fill.
	struct CCAPI
	{
		INT32 RotateX;
		INT32 RotateY;
		INT32 EdgePad;
		INT32 FillType;
		INT32 Angle;
	} GradFillInfo;

	// Flag to indicate whether a grad fill is the current fill style
	BOOL GradFill;

	// Used to decode grad fills
	DocColour StartColour, EndColour;
};

/********************************************************************************************

>	class Corel3EPSFilter : public CorelEPSFilter

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	08/03/94
	Purpose:	An import filter to import EPS files as saved by Corel Draw! 3.x
	SeeAlso:	Corel4EPSFilter; CorelEPSFilter

********************************************************************************************/

class Corel3EPSFilter : public CorelEPSFilter
{
	CC_DECLARE_DYNAMIC(Corel3EPSFilter);
	
public:
	Corel3EPSFilter();
	BOOL Init();
	char *GetEPSCommand(EPSCommand Cmd);

protected:
	virtual void LookUpToken();
	virtual BOOL ProcessToken();
	INT32 EPSHeaderIsOk(ADDR pFileHeader, UINT32 HeaderSize);

	// The array of keyword names
	static CommandMap Corel3Commands[];
};

/********************************************************************************************

>	class Corel4EPSFilter : public CorelEPSFilter

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	08/03/94
	Purpose:	An import filter to import EPS files as saved by Corel Draw! 4.0
	SeeAlso:	Corel3EPSFilter; CorelEPSFilter

********************************************************************************************/

class Corel4EPSFilter : public CorelEPSFilter
{
	CC_DECLARE_DYNAMIC(Corel4EPSFilter);
	
public:
	Corel4EPSFilter();
	BOOL Init();
	char *GetEPSCommand(EPSCommand Cmd);

protected:
	virtual void LookUpToken();
	virtual BOOL ProcessToken();
	INT32 EPSHeaderIsOk(ADDR pFileHeader, UINT32 HeaderSize);

	// The array of keyword names
	static CommandMap Corel4Commands[];
};



#endif  // INC_CORELEPS

