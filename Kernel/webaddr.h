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


#ifndef INC_WEBADDRESS
#define INC_WEBADDRESS

#include "webflags.h"	//Class WebCorrectFlags

/*********************************************************************************************

>	class WebAddress : public CCObject

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	13/9/96
	Purpose:	Represents a URL.
	
*********************************************************************************************/

class WebAddress : public CCObject
{
	CC_DECLARE_DYNAMIC(WebAddress);

protected:
	BOOL Absolute;									//TRUE if it's Absolute. FALSE if it's relative.

	String_256 Scheme;								// e.g. http:, mailto:
	String_256 NetLoc;    	                		// e.g. //www.xara.com
	String_256 Path;        	            		// e.g. /dir1/dir2/myfile.web
	String_256 Parameters;							// e.g. ; XXXX=1
	String_256 Query;								// e.g. ? XXXXX
	String_256 Fragment;							//e.g.  # XXXXX

	BOOL Parse(const String_256& InString);
	BOOL SetFlags();

public:
	WebAddress& operator=(const WebAddress&);				// Assigns one PathName onto another

	//This combines a relative URL with a base URL
	void Combine(WebAddress Relative);

	//Some constructor functions
	WebAddress();
	WebAddress(const WebAddress& InAddress);	
	WebAddress(const String_256& StringToParse, WebCorrectFlags wcfToUse=WebCorrectFlags());

	INT32 operator==(WebAddress& Other);
			
	//A function to return the whole Web Address as a string
 	String_256 GetWebAddress();			// return the full URL

	//Functions to return parts of the Web Address as strings
	const String_256& GetScheme() const		{return Scheme;}
	const String_256& GetNetLoc() const		{return NetLoc;}
	const String_256& GetPath() const		{return Path;}
	const String_256& GetParameters() const	{return Parameters;}
	const String_256& GetQuery() const		{return Query;}
	const String_256& GetFragment() const	{return Fragment;}

	const BOOL IsAbsolute()				 	{return Absolute;}

	//These functions for Olivier's work
	BOOL IsHTTP() const;
	BOOL IsValidHTTP() const;
	static BOOL IsHTTP(const String_256& strTest);

	//Functions to check if the Web Address is a local file, and
	//to get the Web Address as a PathName
	BOOL IsLocalFile() const;
	PathName GetPathName() const;

	//Functions to check whether parts of the Web Address are empty
	const BOOL SchemeIsEmpty() const		{return Scheme.IsEmpty();}
	const BOOL NetLocIsEmpty() const		{return NetLoc.IsEmpty();}
	const BOOL PathIsEmpty() const			{return Path.IsEmpty();}
	const BOOL ParametersIsEmpty() const	{return Parameters.IsEmpty();}
	const BOOL QueryIsEmpty() const			{return Query.IsEmpty();}
	const BOOL FragmentIsEmpty() const		{return Fragment.IsEmpty();}

	const BOOL IsEmpty() const	{return ((Scheme.IsEmpty())&&
										(NetLoc.IsEmpty())&&
												(Path.IsEmpty())&&
												(Parameters.IsEmpty())&&
												(Query.IsEmpty())&&
												(Fragment.IsEmpty()));}

	//And functions to set parts of the Web Address
	void SetScheme(String_256& NewScheme)		{Scheme=NewScheme; SetFlags();}
	void SetNetLoc(String_256& NewNetLoc)		{NetLoc=NewNetLoc;}
	void SetPath(String_256& NewPath)			{Path=NewPath;}
	void SetParameters(String_256& NewPara)		{Parameters=NewPara;}
	void SetQuery(String_256& NewQuery)			{Query=NewQuery;}
	void SetFragment(String_256& NewFragment)	{Fragment=NewFragment;}

	//Correction functions
protected:
	void Correct(String_256* pstrCorrect, WebCorrectFlags wcfToUse=WebCorrectFlags());

	void CorrectBackslashes(String_256* pstrCorrect);
	void CorrectLocalFilenames(String_256* pstrCorrect);
	void CorrectNetscapeFilenames(String_256* pstrCorrect);
	void CorrectFTP(String_256* pstrCorrect);
	void CorrectHTTP(String_256* pstrCorrect);
	void CorrectMailto(String_256* pstrCorrect);
	void CorrectNoSlash(String_256* pstrCorrect);
	void CorrectNoNetLoc(String_256* pstrCorrect);

	BOOL ShouldCorrectLocalFilenames(String_256* pstrCorrect);
	BOOL ShouldCorrectNetscapeFilenames(String_256* pstrCorrect);
	BOOL ShouldCorrectFTP(String_256* pstrCorrect);
	BOOL ShouldCorrectHTTP(String_256* pstrCorrect);
	BOOL ShouldCorrectMailto(String_256* pstrCorrect);
	BOOL ShouldCorrectNoSlash(String_256* pstrCorrect);
	BOOL ShouldCorrectNoNetLoc(String_256* pstrCorrect);





		
};

#endif

