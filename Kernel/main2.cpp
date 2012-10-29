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

// Contains general initialisation of the kernel, after Tool::InitTools() is called

/*
*/

#include "camtypes.h"
//#include "bars.h"
#include "ophist.h"
#include "blobby.h"
#include "groupops.h"
#include "zordops.h"
#include "mkshapes.h"
#include "cutop.h"
#include "menuops.h"
#include "attrappl.h"
#include "aboutdlg.h"
//#include "tooldlg.h"
#include "layermgr.h"
#include "sginit.h"
#include "bfxdlg.h"
#include "dbugtree.h"
#include "printing.h"
#include "filedlgs.h"
#include "nativeop.h"
#include "filelist.h"
#include "exceptio.h"
#include "infobar.h"
#include "speedtst.h"
#include "snapops.h"
#include "oppull.h"
#include "pathedit.h"
#include "textops.h"
#include "shapeops.h"
#include "pathops.h"
#include "opsmpshp.h"
#include "qualops.h"
//#include "clipext.h"
#include "opdragbx.h"
#include "optsprin.h"
#include "guides.h"
#include "snapops.h"
#include "opwhat.h"
#include "impexpop.h"
//#include "xaracms.h"
#include "tipsdlg.h"
//#include "oleprefs.h"
#include "pen.h"
#include "valfunc.h"
#include "mkstroke.h"
#include "bmpsdlg.h"
#include "urlimp.h"
#include "urldlg.h"
#include "aprps.h"
#include "crthumb.h"
#include "bmapprev.h"
#include "opbevel.h"
#include "lattrops.h" // for OpChangeArrowExtendsDesc
#include "opshadow.h"
//#include "slice.h"
#include "biasdlg.h"
#include "opcntr.h" // Contouring operations
#include "barcreationdlg.h"
#include "opbarcreation.h"
#include "opdupbar.h"
//#include "extendsetsdlg.h"	// for ExtendSetsDlg
#include "opdrbrsh.h"
#include "opfeathr.h"
#include "opclip.h"			// for ClipView operations
#include "brushdlg.h"		// for CBrushEditDlg
#include "brushop.h"
#include "brshname.h"
#include "zoomops.h"
//#include "helpdownload.h"
//#include "opliveeffects.h"
#include "nodeliveeffect.h"
#include "stdbars.h"
#include "rendwnd.h"
#include "backgrnd.h"
#include "blndtool.h"
#include "helpuser.h"
#ifdef XAR_TREE_DIALOG
#include "cxftree.h"
#endif

#if _DEBUG
#include "debugdlg.h"
//#include "cmxtree.h"
#endif

#ifdef RALPH

// Ralph only
BOOL InitPostTools1()
{
	return (
			OILBitmap::Init() &&				// read default fill bitmap
			GlobalBitmapList::Init() &&			// Setup the global bitmap list
			GlobalFractalList::Init() &&		// Setup the fractal list
			OpToggleScroll::Init() &&			// Register Toggle proport scrolbar Operation
			OpMenuLoad::Init() &&				// Register Load operation
			OpException::Init() &&
			NodeRenderableInk::Init() &&
			NodeRenderableBounded::Init() &&	// Declare the magnetic radii options
			Filter::InitFilters() &&			// Init filters (must be after ExternalClipboard)
			OpDragBox::Init() &&				// drag operation base-class
			OpQuality::Init() 					// init the OpQuality operations
			);
}

#else

// Normal exe's and standalones
BOOL InitPostTools1()
{
	return
PORTNOTE("other","Removed DialogBarOp usage")
#ifndef EXCLUDE_FROM_XARALX
			DialogBarOp::Init() &&
#endif
PORTNOTE("other","Removed SystemBarOp usage")
#ifndef EXCLUDE_FROM_XARALX
			SystemBarOp::Init() &&				// Register system bars
#endif
			OILBitmap::Init() &&				// read default fill bitmap
PORTNOTE("other","Removed Lots of init functions")
#ifndef EXCLUDE_FROM_XARALX
			GlobalBitmapList::Init() &&			// Setup the global bitmap list
			GlobalFractalList::Init() &&		// Setup the fractal list
#endif
	 		OpUndo::Init() &&					// Register Undo Operation
			OpRedo::Init() &&					// Register Redo Operation
			OpToggleFore::Init() &&				// Register Toggle fore/back render Operation
			OpToggleDoubleBuffer::Init() &&		// Register Toggle double buffer operation
			OpToggleSolidDrag::Init() &&		// Register Toggle solid drag operation
			OpCut::Init() &&					// Register Cut operation
			OpCopy::Init() &&					// Register Copy operation
			OpPaste::Init() &&					// Register Paste operation
			OpPasteAttributes::Init() &&		// Register Paste Attributes operation
			OpDelete::Init() &&					// Register Delete operation
			OpDuplicate::Init() &&				// Register Duplicate operation
			OpClone::Init() &&					// Register Clone operation
			OpCopyAndTransform::Init() &&		// Register the operation for dropping copies
			OpExit::Init() &&					// Register Exit Operation
	        BlobbyOp::Init() &&					// Temp ******
			OpGroup::Init() &&                 	// Register group operation  
	        OpUngroup::Init() &&               	// Register Ungroup operation  
	        OpUngroupSpecial::Init() &&        	// Register Ungroup Special operation  
	        OpBringToFront::Init() &&          	// Register BringToFront operation
	        OpPutToBack::Init() &&             	// Register PutToBack operation 
	        OpMoveForwards::Init() && 			// Register MoveForwards operation
	        OpMoveBackwards::Init() &&         	// Register MoveBackwards operation
			OpMoveToLyrInFront::Init() &&		// Register Move to layer in front operation
			OpMoveToLyrBehind::Init() &&		// Register Move to layer behind operation
			OpApplyAttribToSelected::Init() && 	// Register OpApplyAttribToSelected	Operation
			OpApplyAttribsToSelected::Init() && // Register OpApplyAttribsToSelected Operation
			OpApplyAttribToNode::Init() && 		// Register OpApplyAttribToNode	Operation

			OpReplaceAttributes::Init() && 		// Register OpReplaceAttributes	Operation
	        DocOps::Init() &&					// Register Doc Operations
	        MenuPopupOps::Init() &&				// Register Menu Popup Operations
			OpChangeBlendDistance::Declare() && // Register the change blend steps distance op

#ifndef EXCLUDE_FROM_XARALX
			OpToggleScroll::Init() &&			// Register Toggle proport scrolbar Operation
#endif
			OpChangeFeatherSize::Init() &&		// Register feather size change operation
			OpChangeFeatherProfile::Init() &&	// Register feather profile change operation
			OpMakeShapes::Init() &&				// Register MakeShapes operation
// Neville 5/8/97 remove Stroking code
#ifdef VECTOR_STROKING
			OpMakeStroke::Init() &&				// Register MakeStroke operation
#endif // VECTOR_STROKING
			AboutDlg::Init() &&					// Register "About Camelot" Dialog
#ifndef EXCLUDE_FROM_XARALX
			OpUpdate::Init() &&					// Register Update Operation
			OpRegister::Init() &&				// Register Register Operation
			TipsDlg::Init() &&					// Register "Tip of the Day" Dialog
			OpSlice::Init() &&					// Register Image Slicing
			BarStatesDlg::Init() &&				// Register the Bar States Creation Dlg
			BarRedefineStateDlg::Init() &&		// Register the Redefine Bar State Dlg
			BarCreationDlg::Init() &&			// Register the Bar Creation Dlg
			OpBarCreation::Init() &&			// Register the Bar Creation Op
			OpDuplicateBar::Init() &&			// Register the Bar Duplication Op
			OpShortenBar::Init() &&				// Register the Bar Reducing Op
			OpDelBar::Init() &&					// Register the Bar State Deleting Op
			OpShowState::Init() &&				// Register the Show State-Layer Op
			OpMoveToLayer::Init() &&			// Register the op that moves the selection between layers
			ExtendSetsDlg::Init() &&			// Register the Extend Sets Dialog
#endif
			OpMakeNodesShapes::Init() &&		// Register the OpMakeNodesShapes operation
			OpChangeBrush::Declare() &&         // Register the change brush operation

			OpApplyClipView::Init() &&			// Register the Apply ClipView operation
			OpRemoveClipView::Init() &&			// Register the Remove ClipView operation
// Neville 5/8/97 remove Stroking code
#ifdef VECTOR_STROKING
			ValueFunction::Init() &&			// Init all value function classes
#endif // VECTOR_STROKING
//			LayerDlg::Init() &&					// Register Layer dialog (No longer used)
#ifndef EXCLUDE_FROM_XARALX
#ifndef STANDALONE
			ToolbarDlg::Init() &&				// Register "Toolbar..." dialogs
#endif // STANDALONE
#endif //EXCLUDE_FROM_XARALX

// WEBSTER - markn 15/1/97
// Removed these ops as they are not used
#ifndef WEBSTER
			OpLayerChange::Init() &&			// Register layer change Op
#endif //WEBSTER

#ifndef EXCLUDE_GALS
			SGInit::Init() &&					// Init/Register all the supergallery related Ops
#endif //EXCLUDE_GALS
			BmapPrevDlg::Init() &&				// Bitmap Preview Dialog Box - Dbug Builds for the moment [MartinD]

// Moved this here from inside ColourSGallery::Init
			OpBackground::Init() &&

// WEBSTER - markn 15/1/97
// Removed these ops as they are not used
#ifndef WEBSTER
			OpGuideline::Init() &&				// Register the guideline op
			OpSnapToGuides::Init() &&			// Register the snap-to-guides menu op
			OpShowGuides::Init() &&				// Register the show-guides menu op
#endif //WEBSTER

	        BlobbyDlg::Init() &&				// Temp ******
	        BlobbyBar::Init() &&				// Temp ******
			StandardBar::Init() &&

#if DEBUG_TREE
			DebugTreeDlg::Init() &&				// Temp ******
#endif //DEBUG_TREE

#if _DEBUG
			DebugDlg::Init() &&					// Debug command dialogue - in debug builds only
#endif //_DEBUG

			BlobbyTabDlg::Init() &&				// Temp ******
#ifndef EXCLUDE_FROM_XARALX
#if _DEBUG
			OpCreateFontThumbnails::Init() &&	// Debug only
			OpConvertFileFormats::Init() &&		// Debug only
#endif //_DEBUG

//#ifndef EXCLUDE_BFX
//#ifndef STANDALONE
//#ifndef WEBSTER
//			BfxDlg::Init() &&					// Register bitmap effects dialog
//#endif //WEBSTER
//#endif
//#endif

#if DEBUG_TREE
PORTNOTE("other","Removed CMXTreeDlg usage")
//			CMXTreeDlg::Init() &&				// Temp ******
#endif //DEBUG_TREE
#endif //EXCLUDE_FROM_XARALX

#ifdef XAR_TREE_DIALOG
			CXFTreeDlg::Init() &&				// The Xar format debug tree dialog
#endif //XAR_TREE_DIALOG

#ifndef EXCLUDE_FROM_XARALX
			OpWhatsThis::Init() &&				// Register the "What's This?" help mode Operation
#endif //EXCLUDE_FROM_XARALX
			ViewOps::Init() &&					// Register View Operations
			WindowOps::Init() &&				// Register Window Operations
//WEBSTER-ranbirr-12/11/96
#ifndef WEBSTER
#ifndef STANDALONE
// no printing on Viewer version 
			OpPrint::Init() &&					// Register Print operations
#endif //STANDALONE
#endif //webster

			HelpOps::Init() &&					// Register Help Operations

			OpMenuImport::Init() &&				// Register import operations
			OpMenuExport::Init() &&				// Register export operations

#ifndef EXCLUDE_FROM_XARALX
			OpURLImport::Init() &&				// Register internet import operations
			URLImportDlg::Init() &&				// Register internet import operations
			HelpDownloadOp::Init() &&			// Register help and support download operations
#ifndef STANDALONE
#endif // STANDALONE
#endif //EXCLUDE_FROM_XARALX
			OpDroppedFile::Init() &&			// Register drag'n'drop import operations
			BaseFileDialog::Init() &&			// Declare the open and save default paths
			DummyOp::Init() &&					// Register dummy ops for unimplemented menu items
			OpMenuLoad::Init() &&				// Register Load operation
#ifndef STANDALONE
			OpMenuSave::Init() &&				// Register Save operation
#endif
			OpException::Init() &&
#ifndef EXCLUDE_FROM_XARALX
			InfoBarOp::Init() &&
			InfoBarViewOp::Init() &&
			ExternalClipboard::Init() &&		// Create the application's external clipboard manager
#endif
			FileListOp::Init() &&				// Init the Recent File List Operation
			NodeRenderableInk::Init() &&
			NodeRenderableBounded::Init() &&	// Declare the magnetic radii options
			Filter::InitFilters() &&			// Init filters (must be after ExternalClipboard)
			OpTimeDraw::Init() &&
			OpShowGrid::Init() &&				// op for toggling "show grid" in a view
			OpSnapToGrid::Init() &&				// op for toggling "snap to grid" in a view
// WEBSTER - markn 15/1/97
// Removed these ops as they are not used
#ifndef WEBSTER
			OpSnapToObjects::Init() &&			// op for toggling "snap to objects" in a view
#endif
			OpPullOntoGrid::Init() &&			// Op for pulling selection onto the grid

PORTNOTE("other","Removed OLEPrefs usage")
#ifndef EXCLUDE_FROM_XARALX
			OLEPrefs::Init() &&					// Initialise any OLE related prefs
#endif

PORTNOTE("other","Removed various bevel usage")
#ifdef BUILDSHADOWS
#ifndef EXCLUDE_FROM_XARALX
			OpBevel::Init()	&&					// bevelling operator
#endif
			OpCreateBevel::Declare() && 
			OpRemoveBevel::Declare() &&
			OpChangeBevelLightAngle::Declare() &&
			OpSelectBevel::Declare() &&
			OpApplyAttribForShadows::Init() &&
#endif 
			// Contouring ops
			OpCreateContour::Declare() &&
			OpRemoveContour::Declare() &&
			OpChangeContourWidth::Declare() &&

#ifdef ARROWHEADS
			OpChangeStartArrowExtendsDesc::Declare()) && // makes arrows sit on the line instead
												   // of extending the line
			OpChangeEndArrowExtendsDesc::Declare()) &&
#endif

#ifndef STANDALONE
			OpNodePathEditBlob::Init() &&		// Node path editing itself operation
			OpNodePathEditControlBlob::Init() &&	// Node path editing its control points operation
			OpFitTextToCurve::Init() &&			// Fit text line to path
			OpTextKern::Init() &&				// Apply kern op
			OpTextAutoKern::Init() &&			// Apply kern op
			OpJoinShapes::Init() &&				// Join shapes operation
			OpBreakShapes::Init() &&			// Break shapes operation
			OpNodePathAddEndpoint::Init() &&	// op to add a curve or line at the end of a path
			OpCloseNodePaths::Init() &&			// op to auto-close paths
			OpReshapeOrAddPoint::Init() &&		// op to reform or add a point to a path
			OpNewPath::Init() &&				// Adds a new path and starts editing it
			OpEditRegularShape::Init() &&		// Changing a regular shape
			OpDragRegularShape::Init() &&		// Changing a regular shape	via dragging
			OpReformShapeEdge::Init() &&		// Reforming the edges of a regular shape
			OpToggleSmooth::Init() &&			// Toggles between smooth and cusp point
			OpMakeSegmentsCurves::Init() &&		// Make path segments curved
			OpMakeSegmentsLines::Init() &&		// Make path segments lines
			OpReversePath::Init() &&			// Reverse the path(s)
			OpMovePathPoint::Init() &&			// Move a path point operation
//			OpEditEllipse::Init() &&			// Editing of a (old style) node ellipse
			OpEditRectangle::Init() &&			// Editing of a (old style) node rectangle
//			DialogBarOp::Init() &&				// init the DialogBarOp descriptors
//#endif
			OpDragBox::Init() &&				// drag operation base-class
			OpQuality::Init() &&				// init the OpQuality operations
			BmpDlg::Init() &&					// Register Bitmap Properties Dialog
			GIFAnimationPropertyTabsDlg::Init() &&	// Register the GIF animation tabs dialog
			AnimExOptns::Init() &&					// Register the Animation Export Options tabs dialog	
			OpConvertPathToShapes::Declare() &&		// convert path to shapes operation
			OpChangeBrushDefinition::Declare() &&
#ifndef EXCLUDE_FROM_XARALX
// WEBSTER-ranbirr-13/11/96
#ifndef WEBSTER
			SepsDlg::Init() &&					// Init the separation properties dialog
			OpShowPrintBorders::Init() &&		// init the Show Print Borders operation
#endif	//webster

// Neville 2/10/97 remove Stroking code
#ifdef VECTOR_STROKING
			OpTogglePressure::Init() &&			// Register the pen pressure On/Off operation
#endif // VECTOR_STROKING

			XaraCMS::InitPrefs() &&  			// Init Xara CMS Colour manager settings
#endif
#else
#ifndef EXCLUDE_FROM_XARALX
			OpDragBox::Init() &&				// drag operation base-class
#endif
			OpQuality::Init() &&  				// init the OpQuality operations
#endif
			CBiasGainDlg::Init() &&
			CBrushEditDlg::Init () &&
			OpSelectBrush::Declare() &&
			CNameBrushDlg::Init() &&
			CInitBrushNameDlg::Init() &&
			OpDeactivateBrush::Declare() &&

			OpZoomIn::Init() &&
			OpZoomOut::Init() &&
#ifndef EXCLUDE_FROM_XARALX
			OpLiveEffect::Init() &&				// Register the liveeffects ops (now done by LiveEffecttool)
			&& NodeBitmapEffect::Init() &&
#endif
			InitUserHelp() &&
			TRUE;
}

#endif

