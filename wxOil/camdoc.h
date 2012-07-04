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
	camdoc.h : interface of the CCamDoc class
*/

#ifndef INC_CAMDOC_H
#define INC_CAMDOC_H

// Forward references.
class Document;
class DocRect;
class PathName;
class CCamApp;
class CCLexFile;

/**********************************************************************************
>	class CCamDoc : public COleServerDoc (MFC 2.5)

	Author:		Luke_Hart (Xara Group Ltd) <camelotdev@xara.com> (originally from samples\docvwmdi) with mods.
	Created:	01/07/05
	
	Purpose:	This is the wxWidgets class for a document type object in the OIL (it was
				originally part of wxWidgets example app. docvwmdi).  It is very simple - 
				its main use is getting hold of the relevant Document object from the kernel
				layer.  wxWidgets calls various member functions when processing commands
				from the File menu.  This class calls down into the kernel to do
				the actual work.
	
	SeeAlso:	Document
***********************************************************************************/

class CCamDoc :
	public wxDocument
{
public:
	CCamDoc( Document *pKernelDoc = NULL );
	~CCamDoc();

	// Returns a pointer to the kernel document associated with this.
	Document *GetKernelDoc() const;

	// Serialization support
	virtual bool OnNewDocument();
	virtual bool OnSaveDocument(const wxString& filename);
	virtual bool OnOpenDocument(const wxString& filename);

	// override wxDocument::SaveAs
	virtual bool SaveAs();

	// Some CDocument emulation stuff
	void SetModifiedFlag( BOOL fMod = TRUE ) { Modify( FALSE != fMod ); }

	// Framwwork titles, paths, & filenames.
	virtual void SetTitle(LPCTSTR lpszTitle);
	virtual void SetPathName(LPCTSTR lpszPathName, BOOL bAddToMRU = TRUE);
	void SetPathNameEmpty();
	void SetDocName(LPCTSTR lpszTitle);

	// Kernel titles, paths, and filenames.
	String_256 GetKernelTitle();
	String_256 GetKernelPathName(UINT32 MaxSize = 0);
	String_256 GetKernelDocName(BOOL IncludeFileType = TRUE);
	String_256 GetKernelLocation(UINT32 MaxSize = 0);

	// The original file that this Camelot doc was based on, if they still correspond.
	String_256 GetOriginalPath() const;
	void SetOriginalPath(const String_256& strPath);

	// Sets or clears the document's flags.
	void SetModified(bool fState);
	void SetReadOnly(bool fState);
	void SetCopy(bool fState);

	// Test the above flags (note that MFC defines the IsModified() function).
	bool IsReadOnly() const;
	bool IsACopy() const;
	bool IsUntouched() const;
	bool IsModifiable() const;

	// Call this to set the document flags MFC uses to decide if a save is Save, Save As,
	// or Save Copy As.
	void SetSaveFlags(BOOL fSameAsLoad, BOOL fRememberName)
	{
	#if (_OLE_VER >= 0x200)
		m_bSameAsLoad = fSameAsLoad; m_bRemember = fRememberName;
	#endif
	}

	// This returns the file-name of the template document for this kind of
	// document (normally 'template.xar', for embedded documents it's 'embedded.xar'
	//virtual void GetTemplateFilename(String_256* pstr) const;

	//Graham 21/10/97: New template stuff
public:
	PathName GetTemplate() const;
	void SetTemplate( const PathName &pathToSet = PathName() );

	static PathName GetNextTemplateToUse();
	static void SetNextTemplateToUse(const PathName& pathToSet=PathName());
	
protected:
	PathName m_pathTemplate;
	static PathName ms_pathNextTemplateToUse;

protected:
	// This creates a CCOleStream or a CCDiskFile for OnOpenDocument and
	// OnSaveDocument, according to their role (server doc or normal doc).
	virtual CCLexFile* CreateCCFile(LPCTSTR lpcszPath, INT32 nOpenMode);

	// Useful helper functions.
	// Functions to help with the opening of documents
	virtual bool DefaultDocumentRequired(CCLexFile* pFile, UINT32 nPrefFilter);
	virtual bool LoadDefaultDocument();
	virtual bool GeneralOpenDocument(CCLexFile* pFile, UINT32 nPrefFilter);
	virtual bool OnSaveModified();
	virtual bool DoSave(LPCTSTR lpszPathName, BOOL bReplace = TRUE);
	virtual bool DeleteContents();

	BOOL RemoveExistingDocs();

	// These perform the actual loading and saving of the document, without
	// touching the doc's flags etc.
	virtual bool DoNewDocument();
	virtual bool DoOpenDocument( const wxString &strFilename );
	virtual bool DoSaveDocument( const wxString &strFilename );

////////////////////////////////////////////////////////////////////////////////
// Implementation.

public:

	// Public so that Document can get at it (?)
	static BOOL s_RemoveExistingOnNewDoc;

	// Don't want or need a stinking wxCommandProcessor, we do our own undo\redo handling
	virtual wxCommandProcessor *OnCreateCommandProcessor() { return NULL; }

	static BOOL EnableRemoveUntouchedDocs();
//	static BOOL RemoveUntouchedDocs();
//	static BOOL IdleDocumentProcess();
//	static BOOL MarkAllDocsUntouched(CWinApp* pApp);

private:
	// Helpers.
	void UpdateTitle();
//	BOOL AnotherIsMaximised();			// TRUE is a view onto another doc is maximised.

	// Data members.
	Document		  *m_pKernelDoc;			// points to this object's alter-ego
	bool				m_fIsReadOnly;			// "is modified" flag and functions.
	bool				m_fIsACopy;
	bool				m_fIsUntouched;			// ...by human hand.
	String_256			m_TitlePrefix;			// essentially the document name
	String_256			m_strOriginalPath;		// the file that this doc was loaded from if
												// it wasn't from a .ART file or the default document,
												// empty if this doc is new or no longer corresponds
	bool				m_bIsModifiable;		// Is this doc modifiable?
	LPTSTR				m_lpszInitialZoomOp;	// the initial zoom Op to perform, if any
	bool				m_fDoneNewDoc;			// bodge-flag to stop OLE calling OnNewDoc twice (??)

//	static BOOL			s_fRunIdleProcessing;	// Do some Document work on next idle event
	static Document	   *s_pForceDocument;

public:
	// Originaly OLE related, hardcoded to true now
	bool IsVisible() const	{ return true; }

private:
	DECLARE_DYNAMIC_CLASS(CCamDoc)
};

#endif
