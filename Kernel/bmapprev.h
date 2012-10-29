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


#ifndef INC_BMAPPREV
#define INC_BMAPPREV

#include "bmpprefs.h"	// ExportFileType
#include "bmpalctrl.h"	// Required as BmapPrevDlg HasA BitmapExportPaletteControl

class BitmapExportPreviewDialog;
class BrowserPreviewOptions;
class ImagemapFilterOptions;
class BubbleHelpWnd;

#define OPTOKEN_GIFTABDLG _T("BmapPrevDlg")

//PORTNOTE("dialog","Removed BmapPrevDlg - derived from DialogTabOp")
//#ifndef EXCLUDE_FROM_XARALX
class BmapPrevDlg : public DialogTabOp
{         
	CC_DECLARE_DYNCREATE( BmapPrevDlg )  
	
public:		// Contructors
	BmapPrevDlg(); 
	~BmapPrevDlg();

public:		// Interface (the good bit)
	static BOOL Init();
	MsgResult Message(Msg* Message);
	void SetDontWantMouseMessage( BOOL  ) { ASSERT(FALSE); }
	void OnHelpButtonClicked();
	void UpdateCurrentTab();
	void SetPaletteSelection(INT32 index);
		// Set the selected colour in the palette control
	void SetPaletteHighlight(INT32 index);
		// Set the highlighted colour in the palette control
	BOOL DoPreview();

public:		// Interface
	// PLEASE NOTE: The following two functions have no implementation
	// and are very broken - any code that uses them should be changed
	static INT32 GetNumberOfTransparentColours();
	static INT32 GetTransparentColour( INT32 Index );

public:		// Public data (bad design)
	static BitmapExportOptions *m_pExportOptions;
	static BOOL m_bUseExistingPalette;
	static PathName m_pthExport;			// The path we are exporting the bitmap to
	static BOOL m_bSlicingImage;			// Are we doing image slicing or not?
	static BOOL m_bIsCreateBitmap;			// Are we using the Create Bitmap dialog?
	static INT32 m_NumOfColoursUserAskedFor;	// this is the value that the user has typed into no of clours field
											// or if they didn't type it is the top value defined by the max possible at this colour depth
//	static BOOL m_bNeedPaletteUpdated;
	static BOOL m_bIsOrderedDither;
	//  Did the user click on Export or not? This variable is used when the file type
	//  has changed, and so have the options.
	static BOOL m_bClickedOnExport;
	//  This is the original file type for use with the above variable
//	static ExportFileType m_OriginalFileType;
	INT32 m_FilterType;

private:	// Functions
	virtual void DoWithParam(OpDescriptor*, OpParam* pParam);
	virtual BOOL RegisterYourPagesInOrderPlease(); 

	BOOL OnCreate();
	void SetButtonsText();
	void SetPreviewButtonState(bool enabled);

	void DoBubbleHelp();
	void PrepareBubbleHelp();
	void UpdateStatusBar(UINT32 id);

	void SetPreEditedPaletteColour(INT32 r = -1, INT32 g = -1, INT32 b = -1);

	// Functions I have not deleted yet
	INT32 GetPositionOfItemInDropList( INT32 ListID, INT32 ItemID );
	BOOL SetSelectedDropListItem( INT32 ListID, INT32 ItemID );
	void RenderControl( ReDrawInfoType* pExtraInfo );

	void BrowserPreviewGetOptions(BrowserPreviewOptions *pBrowserOptions);

	void ImageMapGetOptions(ImagemapFilterOptions* pOptions);
	void ImageMapOnFileNameChanged();
	void ImageMapOnBrowseClicked();
	void ImageMapEnableExportToFileOptions(BOOL fValue);
	void ImageMapEnableOptions(BOOL fValue);
	void ImageMapOnCreate();
	void ImageMapOnCommit();
	WinRect GetExportSize(double dpi);

private:	// Data
	BitmapExportPreviewDialog *m_pPreviewDlg;			// pointer to the preview dialog
	CWindowID m_DialogWnd;								// pointer to the preview dialog window
	BaseBitmapFilter *m_pBmpFilter;
	BOOL m_bDpiSupported;								// Does the (should be) given filter support DPI?
	BOOL m_CurrentPreview;
	BOOL m_bPopularityValuesWanted;
	BitmapExportPaletteControl m_PaletteControl;
	bool m_bImageMapTabCreated;
	bool m_bBrowserPreviewTabCreated;
	enum { CLIPBOARD_NONE, CLIPBOARD_IMAGEMAP, CLIPBOARD_HTML } m_ClipBoardUsage;
	typedef enum { MODEL_INVALID, MODEL_RGBHEX, MODEL_RGBPERCENT, MODEL_RGBNUMBER, MODEL_HSV } ColourTypes;
	ColourTypes m_ColorModelType;
	bool m_MouseInsidePaletteControl;					// variable used to find out when the mouse leaves
														// the palette control
	BOOL m_LockSizeUpdates;								// when we update on sizes

	// Bubble help stuff
	BubbleHelpWnd *m_pBubbleWnd;						// pointer the the bubble help window
	UINT32 m_LastCursorOverControlID;						// the id of the last control the cursor was over
	MonotonicTime *m_pBubbleTimer;						// The timer for the bubble help

private:	// Statics
	static const UINT32 IDD;
	static const CDlgMode Mode; 
	static OpState GetState(String_256*, OpDescriptor*);	

	static bool m_MovedWindow;
		// Have we moved the main window to the correct palce?  (This needs to be static so
		// it can be used each time the dialog is created).

private:	// Init methods for each tab/control
//	void InitTabControls();

	void InitPaletteTab();
		void InitPaletteDitheringList();
		void InitPalettePaletteList();
		void InitPaletteColourDepthList();
		void InitPaletteColourModelList();
		void InitPaletteButtonStrip();
		void InitPaletteSortList();

	void InitBitmapSizeTab();
		void InitBitmapSizeDPIList();
		void InitBitmapSizeSelectionRadioGroup();
		void InitBitmapSizeAntiAlisingRadioGroup();
		void InitBitmapSizePutHTMLTick();

	void InitBitmapOptionsTab();

private:	// Message handlers for each tab/control

	// The Palette Tab
	void HandlePaletteTabMsg(DialogMsg* Msg);
		// Combo boxes & edit controls
		void HandlePaletteDitheringListChange();
		void HandlePalettePaletteListChange();
		void HandlePaletteColourDepthListChange();
		void HandlePaletteColoursUsedChange();
		void HandlePaletteColourModelListChange();
		void HandlePaletteSortListChange();
		void HandlePaletteColourEditChange(CGadgetID id);

		// Button messages
		void HandlePaletteLockedColourButtonChange();
		void HandlePaletteWebSafeColourButtonChange();
		void HandlePaletteTransparentBackgroundButtonChange();
		void HandlePaletteTransparentColourButtonChange();
		void HandlePaletteDeleteColourButtonChnage();
		void HandlePaletteRestoreColourButtonChange();
		void HandlePaletteSystemColoursButtonChnage();

	// The Bitmap Size Tab
	void HandleBitmapSizeTabMsg(DialogMsg* Msg);
		void HandleBitmapSizeDPIChange();
		void HandleBitmapSizeWidthChange();
		void HandleBitmapSizeHeightChange();
		void HandleBitmapSizeAreaToSaveChange(SelectionType type);
		void HandleBitmapSizeAntiAliasingChange(BOOL DoMinimise);
		void HandleBitmapSizePutHTMLChange();
		void HandleBitmapSizeScaleFactorChange();

	void HandleBitmapOptionsTicks(UINT32 tick);

	void HandleBrowserPreviewTabMsg(DialogMsg* Msg);

	void HandleBitmapOptionsTabMsg(DialogMsg* Msg);

	void HandleImageMapTabMsg(DialogMsg* Msg); 

//	void HandleJPEGTabMsg(DialogMsg* Msg);

//	void HandlePNGTabMsg(DialogMsg* Msg);

private:	// Refresh functions to sync the controls with the bitmap export options
	// The Palette Tab
	void RefreshPaletteOptionsTab();				// This function calls all the functions below it
		void RefreshPaletteDitheringList();
		void RefreshPalettePaletteList();
		void RefreshPaletteColourDepthList();
		void RefreshPaletteSortList();
		void RefreshPaletteLinkedControls();		// This function calls all the functions below it
			void RefreshPaletteColourModelList();
			void RefreshPaletteButtonStrip();
			void RefreshPaletteColoursUsedEdit();
			void RefreshPaletteColoursEdit();

	// The Bitmap Size Tab
	void RefreshBitmapSizeTab();
		void RefreshBitmapSizeScaleFactor();

	void RefreshBitmapOptionsTab();

	void RefreshImageMapTab();

//	void RefreshJPEGTab();

//	void RefreshPNGTab();
};
//#endif // EXCLUDE_FROM_XARALX
#endif

