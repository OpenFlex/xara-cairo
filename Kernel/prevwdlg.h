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


// A preview dialog box for previwing items like animated GIFs

#ifndef INC_PREVIEWDLG
#define INC_PREVIEWDLG

// Find out about the DialogOp Class
//#include "dialogop.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "list.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "listitem.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "ktimer.h"
//#include "impexpop.h"
#include "frameops.h"

class KernelBitmap;
class RenderRegion;
class DialogColourInfo;

/********************************************************************************************

>	class AnimatedBitmapItem : public ListItem

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/4/97
	Purpose:	Saves out the list of bitmaps currently in the animation sequence.
	
********************************************************************************************/

class AnimatedBitmapItem : public ListItem
{
	CC_DECLARE_DYNCREATE( AnimatedBitmapItem )

public:
	AnimatedBitmapItem();
	~AnimatedBitmapItem();

	AnimatedBitmapItem(KernelBitmap * pEntry, Layer * pLayer = NULL);

	KernelBitmap * GetBitmap() { return m_pBitmap; }
	Layer * GetLayer() { return m_pLayer; }

protected:
	KernelBitmap * m_pBitmap;
	Layer * m_pLayer;
};

/********************************************************************************************

>	class PreviewDialog : public DialogOp

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/4/97
	Purpose:	A preview dialog box for previwing items like animated GIFs
	SeeAlso:	PreviewDialog

********************************************************************************************/

#define OPTOKEN_PREVIEWDIALOG _T("PreviewDialog")

class PreviewDialog : public DialogOp
{
	// Give my name in memory dumps
	CC_DECLARE_DYNCREATE(PreviewDialog);

public:
	// Construction etc
	PreviewDialog();
	~PreviewDialog();

	static	BOOL Init();

	// Called when the dialog is to be displayed
	virtual void DoWithParam(OpDescriptor* pOpDesc,OpParam* pParam);
	virtual	MsgResult Message(Msg* Message);

	virtual BOOL OnIdleEvent(void);		// Overriden idle event processing method.
	void	UpdateBubbleHelp(void);		// Get Bubble help for the current pointer position.	

	static	BOOL GetStatusLineText(String_256 *Result);	// Get status line help text for the current pointer position.
			
	// Find out about the state of the dlg
	static	OpState			GetState(String_256*, OpDescriptor*);
	static	BOOL			GetAnimationPropertiesChanged()						{ return m_AnimationPropertiesChanged; }
	static	void			SetAnimationPropertiesChanged(const BOOL Val)		{ m_pPreviewDialog->m_AnimationPropertiesChanged = Val; }		
			BOOL			SetBitmapList(BitmapExportParam* pParam, BOOL SetSlider = TRUE);
			BOOL			SetRegeneratedBitmapInList(GIFAnimationExportParam* pParam);
			BOOL			SetBitmapToListTail(GIFAnimationExportParam* pParam);

	// Access to our static preview dialog ptr.
	static	PreviewDialog*	GetPreviewDialog()	{ return m_pPreviewDialog; }												

	// Acess functions.
	BOOL	GetPlayAnimation()					{ return m_PlayAnimation;	}
	void	SetPlayAnimation(BOOL Value)		{ m_PlayAnimation = Value;	} 
	INT32		GetBitmapListSize()					{ return  m_BitmapListSize;	}
	void	SetDlgState(BOOL State)				{ m_SetPreviewDlgToIdleState = State;	}		
	BOOL	GetDlgState()						{ return m_SetPreviewDlgToIdleState;	}
	void	SetDocumentAboutToDie(BOOL Val)		{ m_DocumentAboutToDie = Val;			}
	void	SetGeneratedFrameLayers(BOOL Val)	{ m_GeneratedFrameLayers = Val;			}
	BOOL	GetGeneratedFrameLayers()			{ return m_GeneratedFrameLayers;		}				
	void	SetCurrentItem(INT32 Num)				{ m_CurrentItem = Num;					}
	INT32		GetCurrentItem()					{ return m_CurrentItem;					}
	INT32		GetSliderPosition()					{ return m_SliderPosition;				}
	void	SetSliderPosition(INT32 Position);
	void	SelectCurrentBitmap(UINT32 Position);
	
public:
	// Re-start the timer.
	void RestartTimer();

	// Called when the dialog box is already open
	BOOL ReInitDialog();

	BOOL StopPreviewing();

	BOOL SetDialogToIdleState();

	BOOL SelectCurrentFrame(const UINT32 Position);

	static void ToggleViaBitmapGallery (BOOL val);

	void SetDelay (UINT32 newDelay) { m_Delay = newDelay; }

protected:
	void RenderControl(ReDrawInfoType* pExtraInfo);

	void GridLockRect(DocRect *TheRect, INT32 GridSize);
	inline INT32 HalfGridLock(INT32 Position, INT32 GridSize);

	// Useful set up functions
			BOOL	InitDialog();
			BOOL	SetUpCallBack();
	static	TCHAR*	HelpCallbackHandler(wxWindow * Window, UINT32 Item, void *UserData);
	static	BOOL	GetStatusLineText(PreviewDialog *pPrvDlg, UINT32 GadgetID,String_256 *Result);
			BOOL	DoRegenerateFrames();
			void	SetPreviewDialogToIdleState(ReDrawInfoType* pExtraInfo);
	
public:
	// Static Vars
	static const UINT32 IDD;
	static const CDlgMode Mode;

protected:
	// Useful helper functions
	KernelBitmap * GetBitmapItem(INT32 Index);
	KernelBitmap * GetCurrentBitmap(BOOL GetDetails = TRUE);
	
	Layer * GetLayerItem(INT32 Index);
	Layer * GetCurrentLayer();

	void	IncrementCurrentBitmap();
	void	DecrementCurrentBitmap();
	UINT32	GetDelayForCurrentBitmap();
	void	SelectFirstBitmap();
	void	SelectLastBitmap();
	BOOL	SetDlgStateAfterDocChange();
	BOOL	SetDlgStateAfterRefresh();
	void	PreviewDlgPlay();
	void	PreviewDlgStop();
	void	PreviewNextFrame();
	void	PreviewPreviousFrame();
	void	SetSliderPosition();

	BOOL	ResizeDialogToFitAnimation();

	BOOL	RedrawBitmap(KernelBitmap * pBitmapToUse, DocRect * pVirtualSize);
	BOOL	RedrawCross(DocRect * pVirtualSize, DialogColourInfo * pRedrawColours,
						INT32 PixelSize);
	
protected:
	// The list of bitmaps that we need to animate
	List m_BitmapList;
	INT32 m_BitmapListSize;

	// The number of the current bitmap that we are displaying
	INT32 m_CurrentItem;
	
	// The render region that we are using for redraws
	RenderRegion * m_pRender;

	INT32	 m_SliderPosition;				// The position on the slider.	
	BOOL m_PlayAnimation;				// Should the animation be played?
	BOOL m_DisplayNextFrame;			// Should we display the next frame?
	BOOL m_DisplayPreviousFrame;		// Should we display the prvious frame?
	BOOL m_DocumentAboutToDie;			// Is the document about to be closed.			
	BOOL m_SetPreviewDlgToIdleState;	// If the document has changed, then set the dlg to its idle state.
	BOOL m_GeneratedFrameLayers;		// Have the gif animation frame layers been generated.

	GIFDisposalMethod m_DisposalMethod;	// The GIF disposal method for the previous frame
	GIFDisposalMethod m_CurrentDisposalMethod;	// The GIF disposal method for the current frame

	DocRect m_AnimationRect;			// Bounding box of the animation

	INT32 m_CurrentLoopCount;				// The loop that we are currently on
	INT32 m_RequiredLoopCount;			// The loop count that we must reach

	static BOOL viaBitmapGallery;

protected:
	// the call back statics that we require
//	static BOOL TimerProc(HiResTimer* pTimer, INT32 nElapsed, void* pvData);

	void OnTimer();

	class PreviewTimer : public KernelTimer
	{
	public:
		PreviewTimer(PreviewDialog * pOwner) : m_pOwner(pOwner) {}
		virtual void Notify() {m_pOwner->OnTimer();}
		PreviewDialog * m_pOwner;
	};
	PreviewTimer m_Timer;


	static UINT32 m_Delay; 
	static BOOL m_AnimationPropertiesChanged;	// While the dialog is open, has the user changed any properties?
	static PreviewDialog* m_pPreviewDialog;
};

#endif  // INC_PREVIEWDLG
