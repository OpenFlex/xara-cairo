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


// The module that controls the OIL side of import/export filters.


#include "camtypes.h"

#include "camprocess.h"



CamProcess::CamProcess(CCLexFile* pInFile, CCLexFile* pOutFile)
{
	m_bDead = true;
	m_ReturnCode = -1;
	m_pInFile = pInFile;
	m_pOutFile = pOutFile;
	m_BytesIn = 0;
	m_BytesOut = 0;
}

CamProcess::~CamProcess()
{
	if (!m_bDead)
	{
		TRACEUSER("Gerry", _T("Process not dead in ~CamProcess"));
	}
}


INT32 CamProcess::Execute(const wxString& cmd)
{
	// We're now running
	m_bDead = false;

	// Make sure redirection happens
	Redirect();

	long pid = wxExecute(cmd, wxEXEC_ASYNC, this);
	if (pid == 0)
	{
		// Report problem
		m_bDead = true;
		return 123;
	}

	BYTE ReadBuffer[4096];
	size_t ReadBytes = 0;
	BYTE* ReadPtr = NULL;
	bool bMoreInput = true;
	size_t InFileLeft = 0;
	if (m_pInFile)
	{
		InFileLeft = m_pInFile->Size();
//		TRACEUSER("Gerry", _T("InFileSize = %d"), InFileLeft);
	}

	// Loop until m_bDead is true

	while (!m_bDead)
	{
		// Call the virtual function to process any output on stderr
		ProcessStdErr();

		wxYield();

		// If we have an output file
		if (m_pOutFile)
		{
			// If there is output from the process
			if (!m_bDead && IsInputAvailable())
			{
				// Copy the data to the file

				size_t NumRead = 4096;
				BYTE Buffer[4096];

				// Read a buffer full
				GetInputStream()->Read(Buffer, 4096);

				NumRead = GetInputStream()->LastRead();

				// Write the buffer to the file
				if (NumRead > 0)
				{
//					TRACEUSER("Gerry", _T("Writing %d bytes of stdout"), NumRead);
					m_pOutFile->write(Buffer, NumRead);
				}
			}
		}
		else
		{
			// Call the virtual function to process the output
			if (!m_bDead)
				ProcessStdOut();
		}

		wxYield();

		// If we have an input file
		if (m_pInFile)
		{
			// Copy some data to the process
			// This was a while loop
			if (!m_bDead && bMoreInput)
			{
				// If there is nothing in the buffer
				if (ReadBytes == 0)
				{
					ReadBytes = 4096;
					if (ReadBytes > InFileLeft)
						ReadBytes = InFileLeft;

					if (ReadBytes > 0)
					{
						// Read a buffer full
//						TRACEUSER("Gerry", _T("Reading %d"), ReadBytes);
						m_pInFile->read(ReadBuffer, ReadBytes);

						InFileLeft -= ReadBytes;
						ReadPtr = ReadBuffer;
					}
				}

				// If there is something in the buffer
				if (ReadBytes > 0 && GetOutputStream()->IsOk())
				{
//					TRACEUSER("Gerry", _T("Buffer contains %d"), ReadBytes);
					// Try to write it to the process
					GetOutputStream()->Write(ReadPtr, ReadBytes);

					size_t Done = GetOutputStream()->LastWrite();
//					TRACEUSER("Gerry", _T("Written %d"), Done);
					// If we couldn't write it all
					if (Done < ReadBytes)
					{
						// Update the buffer pointer
						ReadPtr += Done;
					}
					// This is correct for all, part or none written
					ReadBytes -= Done;
				}
				else
				{
					// Indicate there is no more stdin
//					TRACEUSER("Gerry", _T("Buffer is empty - closing"));
					CloseOutput();
					bMoreInput = false;
				}
			}
		}
		else
		{
			// Call the virtual function to process the input
			if (!m_bDead)
				ProcessStdIn();
		}

		wxYield();
	}

//	TRACEUSER("Gerry", _T("Exiting with %d"), m_ReturnCode);
	return m_ReturnCode;
}

void CamProcess::ProcessStdIn()
{
	// Do nothing in here
}


void CamProcess::ProcessStdOut()
{
	if (IsInputAvailable())
	{
		wxTextInputStream tis(*GetInputStream());

		// This assumes that the output is always line buffered
		while (IsInputAvailable())
		{
			wxString line;
			line << tis.ReadLine();
//			TRACEUSER("Gerry", _T("(stdout):%s"), line.c_str());
		}
	}

}


void CamProcess::ProcessStdErr()
{
	if (IsErrorAvailable())
	{
		wxTextInputStream tis(*GetErrorStream());

		// This assumes that the output is always line buffered
		while (IsErrorAvailable())
		{
			wxString line;
			line << tis.ReadLine();
//			TRACEUSER("Gerry", _T("(stderr):%s"), line.c_str());
		}
	}
}


void CamProcess::OnTerminate(int /*TYPENOTE: Correct*/ pid, int /*TYPENOTE: Correct*/ status)
{
//	TRACEUSER("Gerry", _T("CamProcess::OnTerminate pid = %d  status = %d"), pid, status);
	m_bDead = true;
	m_ReturnCode = status;

	// Process anything remaining on stderr and stdout
	// If we have an output file
	if (m_pOutFile)
	{
		// If there is output from the process
		if (IsInputAvailable())
		{
			// Copy the data to the file
			size_t NumRead = 4096;
			BYTE Buffer[4096];

			while (NumRead > 0)
			{
				// Read a buffer full
				GetInputStream()->Read(Buffer, 4096);

				NumRead = GetInputStream()->LastRead();

				// Write the buffer to the file
				if (NumRead > 0)
				{
					m_pOutFile->write(Buffer, NumRead);
				}
			}
		}
	}
	else
	{
		// Call the virtual function to process the output
		ProcessStdOut();
	}

	ProcessStdErr();
}




/*****************************************************************************************

	class CamLaunchProcess implementation

*****************************************************************************************/

/********************************************************************************************

>	CamLaunchProcess::CamLaunchProcess()

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	19/May/2006
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	CamLaunchProcess constructor

********************************************************************************************/
CamLaunchProcess::CamLaunchProcess()
{
	m_pid = 0;
	m_bDead = true;
	m_ReturnCode = -1;
	m_bConnected = false;
}


/********************************************************************************************

>	CamLaunchProcess::~CamLaunchProcess()

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	19/May/2006
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	CamLaunchProcess destructor

********************************************************************************************/
CamLaunchProcess::~CamLaunchProcess()
{
	if (m_bConnected)
	{
		TRACEUSER("Phil", _T("Process still connected in ~CamLaunchProcess"));
		Disconnect();
	}
}


/********************************************************************************************

>	virtual BOOL CamLaunchProcess::Execute(const wxString& cmd)

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	19/May/2006
	Inputs:		cmd - The command string including parameters
	Outputs:	-
	Returns:	TRUE if the command was launched successfully
				FALSE otherwise
	Purpose:	Execute a command which should launch a long-running process

********************************************************************************************/
BOOL CamLaunchProcess::Execute(const wxString& cmd)
{
	m_ReturnCode = 0;		// Assume success until we find otherwise

	// Make sure redirection happens
	Redirect();

	TRACEUSER("Phil", _T("Executing %s\n"), (LPCTSTR) cmd);
	m_pid = wxExecute(cmd, wxEXEC_ASYNC, this);
	if (m_pid==0)
	{
		// Couldn't even create a process for the command!
		m_bDead = true;
		return FALSE;
	}

	// We're now running
	m_bDead = false;
	m_bConnected = true;

	// Give the command 100 milliseconds to return an error condition or die...
	// After that we will either use the return code it passed back to OnTerminate
	// or assume it is running successfully...
	MonotonicTime graceperiod;
	while (!m_bDead && m_ReturnCode==0 && !graceperiod.Elapsed(100))
	{
		ProcessStdErr();		// Process any output on stderr
		wxMilliSleep(1);
		wxYield();
	}

	TRACEUSER("Phil", _T("Exiting with %d\n"), m_ReturnCode);
	return (m_ReturnCode==0);
}


/********************************************************************************************

>	UINT32 CamLaunchProcess::Disconnect()

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	19/May/2006
	Inputs:		-
	Outputs:	-
	Returns:	ProcessID of the process we have just allowed to live
	Purpose:	Allow a process to continue to run after this object is destroyed

********************************************************************************************/
INT32 CamLaunchProcess::Disconnect()
{
	INT32 pid = m_pid;

	m_pid = 0;
	m_bConnected = false;
	Detach();

	return pid;
}


/********************************************************************************************

>	wxKillError CamLaunchProcess::Terminate()

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	19/May/2006
	Inputs:		-
	Outputs:	-
	Returns:	wxKillError enum giving result of termination
	Purpose:	Kill the process

********************************************************************************************/
wxKillError CamLaunchProcess::Terminate()
{
	if (!m_bDead)
		return Kill(m_pid, wxSIGTERM);

	return wxKILL_OK;
}


/********************************************************************************************

>	void CamLaunchProcess::ProcessStdErr()

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
				Gerry_Iles (Xara Group Ltd) <camelotdev@xara.com>
	Created:	19/May/2006
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	Process anything the process writes to the error stream

********************************************************************************************/
void CamLaunchProcess::ProcessStdErr()
{
	if (IsErrorAvailable())
	{
		wxTextInputStream tis(*GetErrorStream());

		// This assumes that the output is always line buffered
		while (!GetErrorStream()->Eof())
		{
			wxString line;
			line << tis.ReadLine();
			TRACEUSER("Phil", _T("(stderr):%s\n"), line.c_str());
		}

		m_ReturnCode = 42;		// Signal failure
	}
}


/********************************************************************************************

>	void CamLaunchProcess::OnTerminate(int TYPENOTE: Correct pid, int TYPENOTE: Correct status)

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	19/May/2006
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	Process anything the process writes to the error stream

********************************************************************************************/
void CamLaunchProcess::OnTerminate(int /*TYPENOTE: Correct*/ pid, int /*TYPENOTE: Correct*/ status)
{
	ProcessStdErr();

	TRACEUSER("Phil", _T("CamProcess::OnTerminate pid = %d  status = %d\n"), pid, status);
	m_bDead = true;
	m_ReturnCode = status;
	m_bConnected = false;
}




