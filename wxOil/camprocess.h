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


// wxProcess derived classes for attaching to child process streams

#ifndef INC_CAMPROCESS
#define INC_CAMPROCESS

// Move these to stdwx.h once it works
#include <wx/process.h>
#include <wx/txtstrm.h>


class CamProcess : public wxProcess
{
public:
	CamProcess(CCLexFile* pInFile = NULL, CCLexFile* pOutFile = NULL);
	virtual ~CamProcess();

	virtual void OnTerminate(int /*TYPENOTE: Correct*/ pid, int /*TYPENOTE: Correct*/ status);

	// These are called to handle the various streams
	// StdIn and StdOut are only called when a file isn't being used
	virtual void ProcessStdIn();
	virtual void ProcessStdOut();
	virtual void ProcessStdErr();

	// These functions run the command optionally redirecting stdin and stdout
	INT32 Execute(const wxString& cmd);

protected:
	volatile bool m_bDead;
	volatile INT32 m_ReturnCode;
	CCLexFile* m_pInFile;
	CCLexFile* m_pOutFile;
	INT32 m_BytesIn;
	INT32 m_BytesOut;
};


/********************************************************************************************

>	class CamLaunchProcess : public wxProcess

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	19/May/2006
	Base Class:	wxProcess
	Purpose:	Launch a long-running asynchronous process
	SeeAlso:	CamProcess, wxProcess

********************************************************************************************/

class CamLaunchProcess : public wxProcess
{
public:
	CamLaunchProcess();
	virtual ~CamLaunchProcess();

	BOOL 		Execute(const wxString& cmd);
	wxKillError Terminate();
	virtual 	INT32 Disconnect();

	virtual 	void OnTerminate(int /*TYPENOTE: Correct*/ pid, int /*TYPENOTE: Correct*/ status);

protected:
	// These are called to handle the various streams
	// StdIn and StdOut are only called when a file isn't being used
	virtual 	void ProcessStdErr();

protected:
	bool		m_bDead;
	bool		m_bConnected;
	INT32 		m_ReturnCode;
	INT32 		m_pid;
};


#endif // INC_CAMPROCESS
