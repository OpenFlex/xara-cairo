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

#if !defined(_CAMELOT_H_)
#define _CAMELOT_H_

#if !defined(EXCLUDE_FROM_XARLIB)

#include "dlgmgr.h"     

class CCamFrame;

class CCamApp : public wxApp
{
public:
	CCamApp();

	bool OnInit();
	INT32 OnExit();
	void OnAppExit();

    wxMDIChildFrame *CreateChildFrame( wxDocument *doc, wxView *view );

	// Functions required to enable/disable the systems functionality.   
	static void DisableSystem(CWindowID WindowID=NULL); 
    static void EnableSystem();
	static inline bool IsDisabled() {return s_bIsDisabled;}

    // Display our about box             
	static void DoAboutBox();
	
    // Used to access the dialog manager             
    static DialogManager *GetDlgManager();

	// Access the DocManager for templates
	wxDocManager *GetDocumentManager() const
	{
		return m_docManager.get();
	}
	
	bool OnRecentFile( INT32 RecentFileNumber );
	bool GetRecentFileText( INT32 Index, String_256* pszText );

    void OnIdle		( wxIdleEvent  &event );
	void OnTimer	( wxTimerEvent &event );

	bool HandleKeyPress( wxKeyEvent &event );

	void OnHelpIndex();

	void GiveActiveCanvasFocus();
	
	int /*TYPENOTE: Correct*/ FilterEvent( wxEvent& event );

	void OnFatalException();

	void OnFileOpen();

	void OnFilePrintSetup();

	static BOOL LaunchWebBrowser(const wxString& strUrl);

	static bool LaunchMediaApp( const wxString& strUrl );
	static bool SelectMediaApp();
	
	// Get the path to the root of the resource directory structure
	static StringBase& GetResourceDirectory();

private:
	INT32 RunFalseMainLoop();

	wxDocument* OpenDocumentFile( PCTSTR lpcszFileName );
	void AddToRecentFileList( LPCTSTR pPathName );
	BOOL MakeDocumentNative(wxDocument* pDoc, PathName* Path);

protected:
	std::auto_ptr<wxDocManager> m_docManager;
	CCamFrame			   *m_pMainFrame;

	static bool			s_bIsDisabled;

	static wxString		m_strResourcePath;		// The usually bound in resources
	static String_256	m_strResourceDirPath;	// External resources (i.e. help files)
	static String_256	m_strResourceDirPathOverride;	// Version in preference file

	static String_256	m_strMediaApplication;	// The media replay application the user chose

	wxTimer				m_Timer;

	wxSingleInstanceChecker * m_pSingleInstanceChecker;
	wxServerBase * m_pServer; // IPC server

public:
	BOOL OnSecondInstance(wxChar** argv, INT32 argc = 0);

private:
	static BOOL LaunchBrowserApp(const wxString& strAppName, wxString strCommand);

	static DialogManager m_DlgMgr; 		// The dialog manager handles all oily dialog functions

	static BOOL InInitOrDeInit;

	DECLARE_EVENT_TABLE()

public:
	// Window
	static BOOL MainWndMaximized;					// user maximized preference
	static BOOL MainWndMinimized;					// user maximized preference
	static String_256 MainWndPosString;				// user window position

	static BOOL bFirstRun;							// TRUE if this is the first time the app has been run
													// (first time with this set of preferences)
	BOOL allowRegistryWrite;						// if a copy of camelot is open, and we try do load another one,
													// and exit (we prevent this), then we don't wan't to write to
													// the registry !!!!
	static void NeedMoreIdles() { ::wxWakeUpIdle(); }
};

DECLARE_APP( CCamApp )

#endif

// Used to determine target platform at runtime.
#if defined(__WXMSW__)
extern BOOL WinArray[];
enum Winver { Winver32s=0, Winver32c=1 };
inline BOOL IsWin32s()	{	return WinArray[Winver32s];		}
inline BOOL IsWin32c()	{	return WinArray[Winver32c];		}
inline BOOL IsWin32NT()	{	return !WinArray[Winver32s];	}

inline BOOL IsWindows95() { return IsWin32s() && IsWin32c();  		}
inline BOOL IsWindows31() { return IsWin32s() && !IsWin32c(); 		}
inline BOOL IsWindowsNT() { return !IsWindows95() && !IsWindows31(); }

// Matt 16/01/2001 - Added so that we can detect NT5/Win2000
inline BOOL IsWindows2000()
{
	DWORD dwVersion = GetVersion();
	return ((dwVersion < 0x80000000) && ((DWORD)(LOBYTE(LOWORD(dwVersion))) == 5));
}

#endif



/*******************************************************************************************

>	class wxWindowDeletionWatcher : public wxObject

	Author:		Alex_Bligh <alex@alex.org.uk>
	Created:	02/07/2006
	Purpose:	A derived event to watch for the deletion of windows
	Notes:		In the OIL
	See Also:	

********************************************************************************************/

class wxWindowDeletionWatcher;
WX_DECLARE_HASH_MAP( wxWindow *, wxWindowDeletionWatcher *, wxPointerHash, wxPointerEqual, WindowToWindowDeletionWatcher );

class wxWindowDeletionWatcher : public wxObject
{
public:
	wxWindowDeletionWatcher(wxWindow * pWatchedWindow = NULL) : m_HasBeenDeleted(FALSE), m_pWatchedWindow(pWatchedWindow), m_pNext(NULL), m_pPrev(NULL)
	{
		WindowToWindowDeletionWatcher::iterator i = GetHashEntry(m_pWatchedWindow);

		// If there is no list, create a new hash entry, and we are done
		if (i == s_UndeletedWindowHash->end() || !(i->second))
		{
			ERROR3IF(i != s_UndeletedWindowHash->end(), "wxWindowDeletionWatcher list non-empty but has NULL pointer");
			(*s_UndeletedWindowHash)[m_pWatchedWindow]=this;
		}
		else
		{
			// we are going to stick it on the front of the list
			m_pNext = i->second; // save the current list (may be NULL).
			i->second = this; // stick us on the list

			m_pPrev = NULL;
			m_pNext->m_pPrev=this;
		}
		if (m_pWatchedWindow->IsBeingDeleted())
			RegisterWindowDeletion(m_pWatchedWindow);
	}

	~wxWindowDeletionWatcher()
	{
		RemoveFromList();
	}

	void RemoveFromList()
	{
		if (m_HasBeenDeleted)
		{
			ERROR3IF(m_pNext || m_pPrev, "a deleted window appears to still be on the wxWindowDeletionWatcher list");
			return; // it's not on a list anyway
		}

		BOOL Empty = TRUE;
		if (m_pNext)
		{
			ERROR3IF(m_pNext->m_pPrev != this, "bad wxWindowDeletionWatcher next pointer");
			m_pNext->m_pPrev = m_pPrev;
			Empty = FALSE;
		}
		if (m_pPrev)
		{
			ERROR3IF(m_pPrev->m_pNext != this, "bad wxWindowDeletionWatcher prev pointer");
			m_pPrev->m_pNext = m_pNext;
			Empty = FALSE;
		}
		m_pPrev = m_pNext = NULL; // disconnect

		if (Empty)
		{
			// Delete the hash table entry
			WindowToWindowDeletionWatcher::iterator i = GetHashEntry(m_pWatchedWindow);
			if (i->second != this)
			{
				ERROR3("wxWindowWatcher list appeared to be newly emptied but I wasn't the first item on it");
			}
			if (i != s_UndeletedWindowHash->end())
				s_UndeletedWindowHash->erase(i);
			else
			{
				ERROR3("Can't find wxWindowDeletionWatcher list");
			}
		}
	}

	BOOL HasBeenDeleted() const {return m_HasBeenDeleted;}

	static void RegisterWindowDeletion(wxWindow * pWindow)
	{
		WindowToWindowDeletionWatcher::iterator i = GetHashEntry(pWindow);
		if (i != s_UndeletedWindowHash->end())
		{
			// OK, there's an entry there
			wxWindowDeletionWatcher * pWDW = i->second; // as "i" may become invalid
			ERROR3IF(!pWDW, "Empty list in wxWindowDeletionWatcher::RegisterWindowDeletion");
			while (pWDW)
			{
				ERROR3IF(pWDW->m_pWatchedWindow != pWindow, "Window on the wrong list in wxWindowDeletionWatcher::RegisterWindowDeletion");
				wxWindowDeletionWatcher * next = pWDW->m_pNext; // as removing from the list erases the next pointer
				pWDW->m_HasBeenDeleted = TRUE;
				pWDW->RemoveFromList(); // note we don't delete the WDW object
				pWDW = next;			
			}
		}
	}

	static void DeInit()
	{
		if (s_UndeletedWindowHash)
		{
			ERROR3IF(!s_UndeletedWindowHash->empty(), "wxWindowDeletionWatcher::DeInit() found hash of watched windows was non-empty; someone leaked a wxWindowDeletionWatcher");
			s_UndeletedWindowHash->clear();
			delete s_UndeletedWindowHash;
			s_UndeletedWindowHash = NULL;
		}
	}

private:
	static WindowToWindowDeletionWatcher::iterator GetHashEntry(wxWindow * pWindow) {EnsureHash(); return s_UndeletedWindowHash->find(pWindow);}

	static BOOL EnsureHash() {if (!s_UndeletedWindowHash) s_UndeletedWindowHash = new WindowToWindowDeletionWatcher; return s_UndeletedWindowHash!=NULL;}

	BOOL m_HasBeenDeleted;
	wxWindow * m_pWatchedWindow;

	// whilst the windows remain undeleted, they sit on this list
	wxWindowDeletionWatcher * m_pNext;
	wxWindowDeletionWatcher * m_pPrev;

	static WindowToWindowDeletionWatcher * s_UndeletedWindowHash;

	DECLARE_DYNAMIC_CLASS(wxWindowDeletionWatcher);
};

#endif //_CAMELOT_H_
