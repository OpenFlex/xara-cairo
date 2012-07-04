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

           
#ifndef INC_DOCUMENT
#define INC_DOCUMENT

#include "listitem.h"
#include "list.h"

#include "basedoc.h"	// base class

#include "flags.h"
#include "pathname.h"    
//#include "ophist.h"
#include "colcarry.h"
#include "units.h"
#include "monotime.h"

#include "ralphint.h"


// Several mutual dependencies, so forward refs are needed:
class WorkRect;
class Document;
class DocView;
class View;
class CCamDoc;
class Path;
class Spread;
class Node;
class NodeDocument;
class NodeAttribute;
class NodeSetSentinel;
class DocComponent;
class ArrowRec;
class AttributeManager;
class InsertionNode;
class Filter;
class EPSFilter;
class EPSExportDC;
class DragInformation;
class RalphDocument;
class BitmapList;

// Horizontal gap between each chapter
const INT32 CHAPTERGAP = 5;

// Function def for ForceRedraw() parameter
typedef BOOL (*FRDocViewFunc)(DocView*);

/********************************************************************************************

<	ProcessEPSResult

	Comment:	This typedef is used when reading in EPS comments during an import.  It
				indicates whether the comment was recognised, unknown, contained an error,
				and so on.

				Possible values:

					EPSCommentUnknown
					EPSCommentSyntaxError
					EPSCommentSystemError
					EPSCommentOK

	SeeAlso:	Document::ProcessEPSComment; DocComponent::ProcessEPSComment

********************************************************************************************/ 

enum ProcessEPSResult
{
	EPSCommentUnknown,
	EPSCommentSyntaxError,
	EPSCommentSystemError,
	EPSCommentOK
};

/********************************************************************************************

>	class SafeRenderPointer : public CCObject

	Author:		Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	6/9/96
	Purpose:	A object to handle the current 'safe' rendering pointer within the document.
				This is used for 'Progressive Rendering' (see kernel\docview.h/cpp), during 
				the loading of a document.

********************************************************************************************/

class SafeRenderPointer : public CCObject
{
public:

	SafeRenderPointer();
	~SafeRenderPointer();

	void SetPointerValid();
	void SetPointerInValid();

	BOOL IsPointerValid();

	// Functions to set/get the safe render node
	BOOL UpdateLastSafeNode(Node* pNewNode);
	Node* GetLastSafeNode();

protected:

	Node* pLastSafeNodeToRender;
	BOOL m_bPointerValid;

	CC_DECLARE_DYNAMIC(SafeRenderPointer)
};



/*********************************************************************************************
>	class Document : public BaseDocument

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com> (messed about by Tim) (sorted out by JustinF)
	Created:	13/4/1993
	Purpose:	To represent a platform independent document object.
*********************************************************************************************/

class Document : public BaseDocument
{

///////////////////////////////////////////////////////////////////////////////////////
// Construction & destruction

public:

	Document(BOOL IsAHiddenDocument = FALSE);
	virtual ~Document();

	static  BOOL ReadPrefs();
	virtual BOOL Init(CCamDoc* pOilDoc);	// attaches this document to the CCamDoc,
	virtual BOOL ReInit();					// cf. BaseDocument::Init

	virtual BOOL IsNotAClipboard() const		{ return TRUE; };
	virtual BOOL IsAClipboard() const			{ return FALSE; };

protected:

	BOOL InitFailed();						// Called to tidy up on fail-exit from Init()
	BOOL InitTree(NodeDocument* RootNode);	// Called to build the basic tree structure

	//Counting the number of layers
public:
	INT32 GetNumLayers();

public:
	// Returns TRUE if the document is now "born and stable".
	BOOL IsStable() const			{ return m_fStable; }
	void SetStable(BOOL fStable)	{ m_fStable = fStable; }

private:
	BOOL m_fStable;


///////////////////////////////////////////////////////////////////////////////////////
// **RALPH** stuff should be moved into a new derived class when time will allow 

public:

	RalphDocument* GetRalphDoc()					{ return pRalphDocument; }
	BOOL IsARalphDoc(void)							{ return IsARalph; }
	void SetRalphDoc (BOOL b)						{ IsARalph = b; }

	BOOL ConnectRalphDocument(RalphDocument *pDoc)	{ pRalphDocument = pDoc; return TRUE; }

	// ralph docs can have different view modes
	//	PAGE_VIEW -		the spread is scaled to the view on every resize
	//	DOCUMENT_VIEW - normal view mode
	//	DRAWING_VIEW -	the drawing is scaled to the view at creation
	//					paper isn't rendered

	void SetRalphViewMode(ViewMode Vmode)		{Viewmode = Vmode;};

	ViewMode GetRalphViewMode()					{return Viewmode;};
	
	// called during rendering to determine whether or not to render paper/pasteboard
	BOOL RalphDontShowPaper()					{return Viewmode == DRAWING_VIEW;};	

	// Progressive rendering
	SafeRenderPointer& GetSafeRenderPointer();

protected:

	// RALPH
	BOOL IsARalph;
	ViewMode Viewmode;
	RalphDocument* pRalphDocument;

	// Progressive rendering
	SafeRenderPointer TheSafeRenderPointer;


///////////////////////////////////////////////////////////////////////////////////////
// Titles, comments, flags, and paths.

public:

	String_256 GetTitle() const;
	String_256 GetDocName(BOOL IncludeFileType = TRUE) const;
	String_256 GetPathName(UINT32 MaxSize = 0) const;
	String_256 GetLocation(UINT32 MaxSize = 0) const;

	const String_256& GetProducer() const;

	const String_256& GetComment() const;
	void SetComment(String_256* NewComment);  

	const time_t& GetCreationTime() const;
	void SetCreationTime(time_t);

	const time_t& GetLastSaveTime() const;
	void SetLastSaveTime(time_t);
	void SetLastSaveTime();


	void MakeJustCreated();
	void SetModified(BOOL fState);		// Mark this document is "dirty"

	BOOL IsModified() const;
	BOOL IsReadOnly() const;
	BOOL IsACopy() const;

	BOOL IsLoadedAsVersion1File() const;
	BOOL SetLoadedAsVersion1File(BOOL NewState);

private:

	time_t CreationTime;
	time_t LastSaveTime;
	String_256 Producer;				// name of app that created this doc
	String_256 Comment;					// a comment on the document
										// the rest is in CCamDoc
	// Use with caution!  The value of TRUE for a signed bit-field is -1, not 1, so
	// for example:-
	//
	//			if (DocFlags.AFlag == TRUE) { /* THEN something or another */ }
	//
	// will NEVER execute the "then" clause!

	struct
	{
		BOOL SaveWithUndo    : 1;			// TRUE to save undo info in file
		BOOL LayerMultilayer : 1;			// TRUE if clicks pass through all layers
		BOOL LayerAllVisible : 1;			// TRUE if all layers are visible
	} DocFlags;

	// Flag to say that the document was loaded as a version 1 file
	// and so the user needs to be given the option of saving it in this form
	// when the document is saved
	BOOL LoadedAsVersion1File;


///////////////////////////////////////////////////////////////////////////////////////
// "Current" and "selected" document handling

public:																			  

	Spread* FindFirstSpread();
	void SetCurrent();

	static Document* GetCurrent();
	static void SetNoCurrent();
	static Document* GetSelected();
	static void SetSelectedViewAndSpread(Document *TheDocument = NULL,
											DocView *TheView = NULL,
											Spread *TheSpread = NULL);

	static void SetNoSelectedViewAndSpread(void);
	static Spread* 	GetSelectedSpread();
	static BOOL 	SpreadBelongsToDoc(Document* pDoc,Spread* pSpread);

	BOOL IsAnimated();

	// *** DEFUNCT! These now call SetSelectedViewAndSpread! DO NOT USE
//	void SetSelected();
//	static void SetNoSelected();
//	static void SetSelectedSpread(Spread* pNewSelSpread);
	// ****

private:

	Spread* pSelSpread;
	static Spread* pGlobalSelSpread;

	static Document* Current;
	static Document* Selected;


///////////////////////////////////////////////////////////////////////////////////////
// Accessing the extents etc of the document

public:

	void GetExtents(DocCoord *Lo, DocCoord *Hi, DocRect* Extent, View *pView);
	void UpdateExtents(const DocCoord& Lo, const DocCoord& Hi);

	UnitType GetDocFontUnits();

/* These functions are not used, so commented out - Markn 11/8/94
	Chapter* FindEnclosingChapter(DocCoord&);
	Spread* FindEnclosingSpread(DocCoord&);
	Layer* FindFirstEnclosingLayer(DocCoord&);
	Layer* FindNextEnclosingLayer(Layer*);
*/

///////////////////////////////////////////////////////////////////////////////////////
// All about Nodes . . .

public:

	void DeleteContents();
	void InsertNewNode(Node* NewNode, Spread *pDestSpread);
//	Node* GetFirstNode() const;
	void HandleNodeDeletion(Node* pNode);

	// Deprecated...soon to be forbidden
	static void IncCurrentNodeCount();
	static void DecCurrentNodeCount();


///////////////////////////////////////////////////////////////////////////////////////
// DocViews and OIL-ey documents.

public:

	CCamDoc* GetOilDoc() const;

	DocView* GetFirstDocView() const
				{ return (DocView*) DocViews.GetHead(); }

	DocView* GetNextDocView(const DocView* pView) const
				{ return (DocView*) DocViews.GetNext((const ListItem*) pView); }

	DocView* GetTopmostView() const;

	DocView* GetNewDocView();
	DocView* GetSpareDocView();

	void OnDocViewDying(DocView* pdv);

	void ShowViewScrollers(BOOL fIsVisible);
	void ShowViewRulers(BOOL fIsVisible);

	BOOL CreateDragTargets(DragInformation * DragInfo);

	void ForceRedraw(FRDocViewFunc = NULL);
	void ForceRedraw(WorkRect& forceRect);
	void ForceRedraw(Spread* pSpread,
					 DocRect SpreadRect,
					 BOOL Accumulate = FALSE,
					 Node* pInvalidNode = NULL,
					 BOOL bAutoRelease = TRUE);
	void FlushRedraw();

protected:

	CCamDoc* OilDoc;		// the attached CCamDoc, if any
	List DocViews;


///////////////////////////////////////////////////////////////////////////////////////
// Serial numbers

public:

	UINT32 GetCreatorSerialNo();			// all unimplemented?
	UINT32 GetLastSerialNo();
	void SetLastEditorSerialNo(UINT32 sn);

private:

	UINT32 CreatorSerialNo;				// serial no of creator
	UINT32 LastSerialNo;					// serial no of last editor


///////////////////////////////////////////////////////////////////////////////////////
// Attributes

public:
	// Layer stuff.
	BOOL IsMultilayer();
	BOOL IsAllVisible();
	void SetMultilayer(BOOL state);
	void SetAllVisible(BOOL state);

	// Tree initialisation.
	AttributeManager& GetAttributeMgr() const;
	NodeSetSentinel* GetSetSentinel() const;
	NodeAttribute* GetDefaultAttr(CCRuntimeClass* RequiredAttr);

	// Pasteboard.
	MILLIPOINT GetBleedOffset() const;	// Get the bleed offset for this document
	BOOL SetBleedOffset(MILLIPOINT);	// Set the bleed offset for this document

private:
	// Data.
	AttributeManager* AttributeMgr;
	NodeSetSentinel* m_pSetSentinel;	// cached pointer to the tree's set attributes sentinel

	MILLIPOINT PasteBoardOffsetWidth;	// width of pasteboard outside spread (doc-coords)
	MILLIPOINT PasteBoardOffsetHeight;	// height of pasteboard outside spread (ditto)
	MILLIPOINT BleedOffset;				// Distance outside page which is rendered during printing


///////////////////////////////////////////////////////////////////////////////////////
// Operation history management

public:

	OperationHistory& GetOpHistory();	// finds this docs op. history

	// Function to get rid of everything in the operation history
	BOOL EmptyOperationHistory();

protected:
	OperationHistory* OpHistory; 		// Documents operation history. 
							 			// This has to be a pointer because the
							 			// destructor of the  Operation history MUST
							 			// get called before the tree is destroyed.


///////////////////////////////////////////////////////////////////////////////////////
// Document lists

public:
	BitmapList*		GetBitmapList();
	DocUnitList*	GetDocUnitList()			{ return pDocUnitList; }

private:
	DocUnitList*	pDocUnitList;

///////////////////////////////////////////////////////////////////////////////////////
// CGS (30/8/2000):  Nudge is now stored within the document ....
// Andy Hills (07-11-00): So is the 'smooth bitmaps when scaled up' flag

	UINT32 m_docNudge;
	BOOL m_bSmoothBitmaps;
	DocCoord m_DuplicationOffset;

public:
	UINT32 GetDocNudge() { return (m_docNudge); }
	BOOL SetDocNudge(UINT32 newVal);

	BOOL GetBitmapSmoothing() { return (m_bSmoothBitmaps); }
	void SetBitmapSmoothing(BOOL newVal) { m_bSmoothBitmaps = newVal; }

	DocCoord GetDuplicationOffset() { return (m_DuplicationOffset); }
	void SetDuplicationOffset(DocCoord newOffset) { m_DuplicationOffset = newOffset; }


///////////////////////////////////////////////////////////////////////////////////////
// EPS stuff:-

public:

	virtual BOOL EPSStartImport(EPSFilter *);
	virtual void EPSEndImport(EPSFilter *, BOOL);
	virtual BOOL EPSStartExport(EPSFilter *);
	virtual void EPSEndExport(EPSFilter *);

	virtual BOOL WriteEPSResources(EPSFilter *);
	virtual BOOL WriteEPSProlog(EPSFilter *);
	virtual BOOL WriteEPSSetup(EPSFilter *);
	virtual BOOL WriteEPSFonts(EPSFilter *);
	virtual BOOL WriteEPSComments(EPSFilter *);
	virtual BOOL WriteEPSTrailer(EPSFilter *);
	virtual ProcessEPSResult ProcessEPSComment(EPSFilter *, const TCHAR *);
	virtual void EndOfEPSComment(EPSFilter *);

	// More general function to control progress display.
	virtual INT32 GetSizeOfExport( Filter * );

	// Function to see if this document is loading or importing a file
	BOOL IsImporting();
	void SetIsImporting(BOOL NewIsImporting);

	// Function to see if this document is a default or template document being loaded
	BOOL IsTemplateLoading();
	void SetTemplateLoading(BOOL NewTemplateLoading);

	static BOOL GetRestoreViewOnImport()	{ return fRestoreViewOnImport; }
	static void ShouldRestoreViewOnImport(BOOL fNewState);

	// Graeme (24/3/00) - Made this public, so that it can be accessed by other classes.
	BOOL AIExportExtras(EPSExportDC *pDC);

protected:

	// Functions to help save out the Document Info and load it back in again
	BOOL ExportPageInfo(EPSExportDC *pDC);
	BOOL ExportDocumentComment(EPSExportDC *pDC);
	BOOL ExportViewInfo(EPSExportDC *pDC);
	BOOL ExportStateInfo(EPSExportDC *pDC);
	BOOL ExportQualityInfo(EPSExportDC *pDC);
	BOOL ExportGridInfo(EPSExportDC *pDC);
	BOOL ExportFlagInfo(EPSExportDC *pDC);
	BOOL ExportUnitInfo(EPSExportDC *pDC);
	BOOL ExportDateInfo(EPSExportDC *pDC);
	BOOL ExportTextSetup(EPSFilter *pFilter);
	BOOL ExportTextTrailer(EPSFilter *pFilter);

	BOOL ExportRulerState(EPSExportDC *pFilter);
	BOOL ExportUndoInfo(EPSExportDC *pDC);
	BOOL ExportDefaultUnitsInfo(EPSExportDC *pDC);
	BOOL ExportOriginInfo(EPSExportDC *pDC);

	// Functions to explicitly export Illustrator format tokens
	BOOL AIExportResources(EPSExportDC *pDC, BOOL);
	BOOL AIExportProlog(EPSExportDC *pDC);
	BOOL AIExportCharEncoding(EPSExportDC *pDC);
	BOOL AIExportFontEncoding(EPSExportDC *pDC);
	BOOL AIExportFontEncoding(EPSExportDC *pDC, String_64& FontName, INT32 Style);
	BOOL AIExportTrailer(EPSExportDC *pDC);

	// Functions to Import stuff again
	ProcessEPSResult ImportPageInfo(TCHAR* Comment);
	ProcessEPSResult ImportDocumentComment(TCHAR* Comment);
	ProcessEPSResult ImportViewInfo(TCHAR* Comment);
	ProcessEPSResult ImportRulerState(TCHAR* Comment);
	ProcessEPSResult ImportStateInfo(TCHAR* Comment);
	ProcessEPSResult ImportQualityInfo(TCHAR* Comment);
	ProcessEPSResult ImportGridInfo(TCHAR* Comment);
	ProcessEPSResult ImportFlagInfo(TCHAR* Comment);
	ProcessEPSResult ImportUnitInfo(TCHAR* Comment);
	ProcessEPSResult ImportDateInfo(TCHAR* Comment);
	ProcessEPSResult ImportUndoInfo(TCHAR* Comment);
	ProcessEPSResult ImportDefaultUnitsInfo(TCHAR* Comment);
	ProcessEPSResult ImportOriginInfo(TCHAR* Comment);

	// Data members.
	BOOL DocIsImporting;
	BOOL DocTemplateLoading;
	static BOOL fRestoreViewOnImport;		// if TRUE will set the view onto this new doc

private:

	// Implementation.
	BOOL InitDefaultAttributeNodes();

	// The point in camelot where we insert new objects
	InsertionNode* InsertPos;

	CC_DECLARE_DYNAMIC(Document);

public:

	// Only for test purposes:-
	InsertionNode* GetInsertionPosition();
	void ResetInsertionPosition();
	void InsertionNodeDying()		{ InsertPos = 0; }		// Called by ~InsertionNode
};



/********************************************************************************************
>	class TranspModeMsg : public Msg

	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com>
	Created:	5/1/95
	Purpose:	A "transparency mode-change" message class.
	SeeAlso:	-
********************************************************************************************/

class TranspModeMsg : public Msg
{
public:

	TranspModeMsg(BOOL fInTranspMode);
	BOOL InTransparencyMode() const;

private:

	BOOL	m_fInTranspMode;
	CC_DECLARE_DYNAMIC(TranspModeMsg)
};

#endif	// !INC_DOCUMENT
