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


#ifndef INC_CAMRESOURCE
#define	INC_CAMRESOURCE

// Define _R() before we include other Camelot headers
// NOTE THIS MACRO IS EXPANDABLE IN A STATIC INITIALIZER
#if 0 != wxUSE_UNICODE
#define _RESQUOTE(x) L ## #x
#else
#define _RESQUOTE(x) #x
#endif
#define _R(x) ( CamResource::GetResourceID( _RESQUOTE(x)) )

#include "xarlib/ccobject.h"

class CCLexFile;
class wxFSFile;
class wxBimtap;
class wxAdvSplashScreen;
class wxHelpProvider;

typedef UINT32 ResourceID;

// Need a type for the hash data or we get duplicate const error
typedef const TCHAR * ResourceString;

// Declare the hash map from ResourceID to String
WX_DECLARE_HASH_MAP( ResourceID, ResourceString, wxIntegerHash, wxIntegerEqual, ResIDToString );
WX_DECLARE_HASH_MAP( ResourceString, wxImage *, wxStringHash, wxStringEqual, ResourceStringToBitmap);

// Some bodgy stuff from tbbitmap which we will fix some time
extern wxImage			imageBevelTool;
extern wxImage			imageBezTool;
extern wxImage			imageBlendTool;
//extern wxImage			imagelbuttonst32_xpm );
//extern wxImage			lbuttst232_xpm );
//extern wxImage			lbutts_liveeffect_xpm );
extern wxImage			imageContourTool;
extern wxImage			imageElipTool;
extern wxImage			imageFHandTool;
extern wxImage			imageGradTool;
extern wxImage			imageLiveEffectTool;
extern wxImage			imageMouldTool;
extern wxImage			imagePenTool;
extern wxImage			imagePush;
extern wxImage			imageRectTool;
extern wxImage			imageRegShapeTool;
extern wxImage			imageSelTool;
extern wxImage			imageShadrwTool;
extern wxImage			imageSlicetool;
extern wxImage			imageTextTool;
extern wxImage			imageTransTool;
extern wxImage			imageZoomTool;

class CamResourceRemember;

/*******************************************************************************************

>	class CamResource : public CCObject

	Author:		Alex_Bligh <alex@alex.org.uk>
	Created:	02/12/2005
	Purpose:	To control the translation of resources within Camelot
	Notes:		In the OIL
	See Also:	

This is a class composed of static member functions which rapidly translates resources,
and a dynamic object which provides capabilities of loading from the disk.

String tables

The GetText() member functions look up the integer ID's passed to it in a hash map, via inline
functions, so should be pretty rapid in execution. Thus the actual mechanism of loading
the strings is effectively encapsulated.

Dialogs and other resources

The GetResourceID() member function implements the _R() macro, which allows a resource in
a dialog (or a stringtable resource) to be translated into the numeric ID's Camelot likes.

Example usage:

	ResourceID	myResource;
	myResource = _R("_R(IDS_BLOBBYSTRING)"); // Uses CamResource::GetResourceID()

	... pass around the integer value ...

	const TCHAR * myString = CamResource::GetText(myResource); // Can't fail
	... do something with the text of the entry ...

Note that the _R() macros is clevere than you think. That's because it can be used
as a static initializer (e.g. in wxWidgets event tables). What is happening here is
that the GetXRCID() hash table gets initialized at static initialization time creating
a map from the resource string (IDS_ etc.) to a unique integer value, and when the XML
resources are loaded later, they are assigned that integer value.

Note this is a static class, and thus no constructors and destructors are offered.

********************************************************************************************/


class CamResource : public CCObject
{
	CC_DECLARE_DYNCREATE( CamResource )

// The per-object bits

public:
	CamResource();
	virtual ~CamResource();

private:
	CCLexFile * pFile;
	void * pMemory;
	UINT32 Size;
	wxFSFile * pwxFSFile;
	static wxFileSystem * pwxFileSystem;
	static wxLocale * m_pLocale;
	static wxHelpProvider * m_pHelpProvider;
	static BOOL s_GenerateXRCCheck;

public:
	CCLexFile * Open ( ResourceID ID, BOOL ErrorReporting=TRUE, BOOL ExceptionThrowing=FALSE);
	CCLexFile * Open ( const TCHAR * pFileName, BOOL ErrorReporting=TRUE, BOOL ExceptionThrowing=FALSE);
	wxFSFile * OpenwxFSFile (ResourceID ID);
	wxFSFile * OpenwxFSFile (const TCHAR * pFileName);
	void Close();
	CCLexFile * Get () {return pFile;}
	wxFSFile * GetwxFSFile () {return pwxFSFile;}

// The static stuff

private:
	static void AddStringResource(const TCHAR * name, const TCHAR * text, ResourceID r=0);
	static void RememberDuringStaticInit(const TCHAR * ObjectName);
	static BOOL ReadStringTableFile();
	static void ProcessWindowAndChildren(wxWindow * pWindow);
	static void GetBinaryFileInfo (void **pPtr, UINT32 *pSize);
	static BOOL InitXmlResource();
	static BOOL Splash();
	static BOOL CheckResourcePath( const wxString &str1, const wxString &str2 );
	static const TCHAR * FixObjectName(const TCHAR * ObjectName);
	static BOOL AddBitmaps(wxString &Path);
	static BOOL LoadBitmaps();
	static void DeleteBitmapHashEntries();
	static void MakeVariantBitmaps(ResourceStringToBitmap::iterator * it=NULL);

	static ResIDToString * pHash;
	static ResIDToString * pObjectNameHash;
	static TCHAR * DefaultString;
	static TCHAR * DefaultObjectName;
	static wxString * pResourcePath;
	static BOOL HaveCheckedResourcePath;
	static CamResourceRemember * pFirstRemember;

	static wxBitmap * pSplashBitmap;
	static wxAdvSplashScreen * pSplashScreen;

	static ResourceStringToBitmap * pBitmapHash;

public:
	static BOOL LoadwxImage (wxImage & rImage, const TCHAR * pFileName, BOOL Grey=FALSE);
	static BOOL LoadwxBitmap (wxBitmap & rBitmap, const TCHAR * pFileName, BOOL Grey=FALSE);

	static wxImage* GetCachedBitmap(const TCHAR * pName);

	static void MakeGreyImage (wxImage & rImage);
	static void MakeHotImage (wxImage & rImage);

	static inline ResourceID GetResourceID(const TCHAR * ObjectName) // Implement the _R macro
	{
		const TCHAR * fObjectName=FixObjectName(ObjectName);
		ResourceID Resource = wxXmlResource::GetXRCID(fObjectName);
		// need to record it in the hash that goes the other way lest we be asked. Note this will always
		// work as the caller to GetObjectName can't have a ResourceID without _R()'ing it (or at least
		// cannot legally have one).
		if (pObjectNameHash)	// skip on static initialization phase or we'll be dead
		{
			ResIDToString::iterator i=pObjectNameHash->find(Resource);
			if (i==pObjectNameHash->end()) (*pObjectNameHash)[Resource]=camStrdup(fObjectName);
		}
		else RememberDuringStaticInit(fObjectName); // add it to the hash later
		return Resource;
	} 	
	static inline const TCHAR * GetTextFail(ResourceID Resource)
	{
		if (!pHash) return NULL;
		ResIDToString::iterator i=pHash->find(Resource);
		return (const TCHAR *)((i==pHash->end())?NULL:i->second);
	};
	static inline const TCHAR * GetText(ResourceID Resource)
	{
		if (!pHash) return DefaultString;
		ResIDToString::iterator i=pHash->find(Resource);
		const TCHAR * text = (const TCHAR *)((i==pHash->end())?NULL:i->second);
		return text?text:DefaultString;
	};
	static inline const TCHAR * GetObjectNameFail(ResourceID Resource)
	{
		if (!pObjectNameHash) return NULL;
		ResIDToString::iterator i=pObjectNameHash->find(Resource);
		return (const TCHAR *)((i==pObjectNameHash->end())?NULL:i->second);
	};
	static inline const TCHAR * GetObjectName(ResourceID Resource)
	{
		if (!pObjectNameHash) return DefaultString;
		ResIDToString::iterator i=pObjectNameHash->find(Resource);
		const TCHAR * text = (const TCHAR *)((i==pObjectNameHash->end())?NULL:i->second);
		return text?text:DefaultString;
	};

	static wxString GetResourceFilePath( const wxString &str, BOOL AllowOverride=TRUE );
	static void SetResourceFilePath( const wxString &str );

	// String manipulation functions for bitmaps
	static BOOL IsBitmapName(const wxString &str);
	static wxString GetBitmapExtension(const wxString &str);
	static wxString GetBitmapBaseName(const wxString &str);
	static wxString GetBitmapFlagString(const wxString & str);
	static wxString MakeBitmapString(const wxString base, const wxString flags, const wxString ext)
	{
		if (flags.IsEmpty())
			return base+wxString(_T("."))+ext;
		else
			return base+wxString(_T("-"))+flags+wxString(_T("."))+ext;
	}

	static BOOL Init();
	static BOOL DeInit();

	static wxLocale * GetLocale() {return m_pLocale;}

	static wxArrayString BitmapExtensions;

	static void SetGenerateXRCCheck(BOOL flag) {s_GenerateXRCCheck=flag;}
	static void * LoadFile( const wxString &str1, UINT32 * pSize );
};


class CamResourceRemember
{
	friend class CamResource;

private:
	CamResourceRemember * next;
	TCHAR * text;
};



#endif

