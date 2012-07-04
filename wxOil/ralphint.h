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


#ifndef INC_RALPHINT
#define INC_RALPHINT

//#include <afxole.h>

#define RALPH_E_BADFILE 			((HRESULT)0x8534E102L)
#define RALPH_E_EMPTYFILE			((HRESULT)0x8534E108L)
#define RALPH_E_FILEOPENFAILED		((HRESULT)0x8534E105L)
#define RALPH_E_INVALIDID			((HRESULT)0x8534E106L)
#define RALPH_E_MISSINGFILES		((HRESULT)0x8534E104L)
#define RALPH_E_NOFILTER			((HRESULT)0x8534E100L)
#define RALPH_E_NONSUPPORTEDTYPE	((HRESULT)0x8534E101L)
#define RALPH_E_NOVIEWER 			((HRESULT)0x8534E10AL)
#define RALPH_E_OUTOFMEMORY			((HRESULT)0x8534E107L)
#define RALPH_E_PROTECTEDFILE		((HRESULT)0x8534E109L)
#define RALPH_E_UNEXPECTED			((HRESULT)0x8534E103L)

#define RALPH_E_LOADFAILED			((HRESULT)0x8534E10BL)
#define RALPH_E_INTERNAL			((HRESULT)0x8534E10CL)
#define RALPH_E_ABORTLOAD			((HRESULT)0x8534E10DL)


PORTNOTE("other","Removed IID usage")
#ifndef EXCLUDE_FROM_XARALX
// Define the interface ID's (GUIDS) for the RalphDoc's interfaces. 
// {83104620-C3B4-11cf-8898-0020AFE14B87}
static const IID IID_ICreation = 
			{ 0x27682681, 0xd299, 0x11cf, 
			{ 0xab, 0x39, 0x0, 0x20, 0xaf, 0x71, 0xe4, 0x33 } };
static const IID IID_ICommandControl = 
			{ 0x27682682, 0xd299, 0x11cf, 
			{ 0xab, 0x39, 0x0, 0x20, 0xaf, 0x71, 0xe4, 0x33 } };
static const IID IID_IViewControl = 
			{ 0x27682683, 0xd299, 0x11cf, 
			{ 0xab, 0x39, 0x0, 0x20, 0xaf, 0x71, 0xe4, 0x33 } };
static const IID IID_IInitRalph = 
			{ 0x27682684, 0xd299, 0x11cf, 
			{ 0xab, 0x39, 0x0, 0x20, 0xaf, 0x71, 0xe4, 0x33 } };
static const IID IID_IErrorCallback = 
			{ 0x27682685, 0xd299, 0x11cf, 
			{ 0xab, 0x39, 0x0, 0x20, 0xaf, 0x71, 0xe4, 0x33 } };

static const IID IID_IAsynchDownLoad = 
			{ 0x27682686, 0xd299, 0x11cf, 
			{ 0xab, 0x39, 0x0, 0x20, 0xaf, 0x71, 0xe4, 0x33 } };
#endif


// define some types for the interfaces
enum ToolMode		{NO_TOOL,ZOOM_TOOL,PUSH_TOOL}; 
enum QualityLevel	{ANTI_ALIASED,NORMAL,SIMPLE,OUTLINE};
enum DitherType		{ORDERED_DITHER,ERROR_DIFFUSE_DITHER,NO_DITHER};
enum ViewMode		{PAGE_VIEW,DRAWING_VIEW,DOCUMENT_VIEW,DEFER_SETTINGVIEW};


/********************************************************************************************

	class ICreation: public CCmdTarget

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/6/95
	Purpose:	Interface definition for the ICreation interface. 

********************************************************************************************/

class ICreation : public IUnknown
{
public:
	// Loads a Document
	STDMETHOD (LoadDocument) (TCHAR* pFileToLoad) = 0;

	// Create a view window onto the document. If the ParentWnd parameter is
	// supplied then the window is created as a child of this window. If ParentWnd is 
	// NULL then the window is created as a popup (possible).
	// Initially we will probably allow a document to have only a single view associated with it. 
	STDMETHOD (CreateViewWindow)   (wxWindow * ParentWnd,
									ViewMode Viewmode,
									BOOL ShowScrollers,
									BOOL ShowWindow,
									BOOL HasBorder,
									wxWindow * * ViewWindow) =0;
	STDMETHOD (GetVerNum)	(TCHAR * pVerNum) =0;
	
	// This is intended mainly for printing
	STDMETHOD (RenderToDC)	(wxDC *TheDC, DWORD X, DWORD Y, DWORD Width, DWORD Height, DWORD DPI) =0;

};



/*******************************************************************************************

	class ICommandControl: public CCmdTarget

	Author:		Chris_Snook (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/6/95
	Purpose:	Interface definition for the ICommandControl interface. This will be supported
				by a RalphDocument. 

********************************************************************************************/

class ICommandControl : public IUnknown
{
public:
	// set ralph toolmode - currently supports NO_TOOL, PUSH_TOOL and ZOOM_TOOL
	STDMETHOD(SetToolMode)		(ToolMode toolmode) = 0;
	// just do a normal PreviousZoom op
	STDMETHOD(PreviousZoom)		() = 0;
	// do a ZoomToDrawing op
	STDMETHOD(ZoomToDrawing) 	() = 0;
	// Zoom To 100%
	STDMETHOD(ZoomToFullScale) 	() = 0;
 	// set the render for this document (ANTI_ALIASED,NORMAL,SIMPLE,OUTLINE)
	STDMETHOD(SetQuality)		(QualityLevel Quality) = 0;
	// set the dither type for this document (ORDERED_DITHER,ERROR_DIFFUSE_DITHER,NO_DITHER)
	STDMETHOD(SetDitherType)	(DitherType Dither) = 0;
	// set the palette mode to foreground / background
	STDMETHOD(SetPaletteMode)	(BOOL Foreground) = 0;
	// Is there a previous zoom ? - this allows us to update the UI in the harness's
	STDMETHOD(HasPreviousZoom)	() = 0;
	// set the render for this document (ANTI_ALIASED,NORMAL,SIMPLE,OUTLINE)
	STDMETHOD(SetURL)			(wxString InURL) = 0;


};

class IViewControl : public IUnknown
{
public:

	STDMETHOD (ShowScrollers) (BOOL State) = 0;
	STDMETHOD (SetViewMode) (ViewMode Viewmode) = 0;
};


class IErrorCallback : public IUnknown
{
public:
	STDMETHOD(InformError) (HRESULT ErrCode)=0;
 
 };

/*******************************************************************************************

	class IEventCallback

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20/07/96
	Purpose:	Interface definition for the IEventCallback interface. This interface will 
				be implemented by a Harness that needs to respond to events sent from a 
				RalphDocument. The interface is registered with a RalphDocument thru a 
				call to IInitRalph::SetEventCallback. Note that it is not derived from 
				IUnknown as there is no reason for it to have AddRef, Release, QueryInterface 
				methods. 

********************************************************************************************/

class IEventCallback : public IUnknown
{
public:
	// WebAddressSelected is called by a RalphDocument whenever the user selects a Web address
	STDMETHOD(WebAddressSelected) (wxString& WebAddress )=0;
	STDMETHOD(SetStatusBar) (wxString& StringToPass)=0;
};


 
class IInitRalph : public IUnknown
{
public:
	STDMETHOD(SetErrorCallback) (IErrorCallback* pCallbackInterface)=0;

 };



class IAsynchDownLoad : public IUnknown
{
public:
	STDMETHOD(StartAsynchDownLoad) ()=0;
	STDMETHOD(OnDataAvailable) (unsigned char* pReadBuffer,DWORD BytesRead)=0;
	STDMETHOD(EndAsynchDownLoad) (HRESULT Status)=0;

};

#endif
