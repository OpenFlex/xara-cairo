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

// Trace dialog

#ifndef INC_TRACECTL
#define INC_TRACECTL

#include "bfxbase.h"

class KernelBitmap;
class TraceRegion;
class LinearFillAttribute;
class NodePath;
class Node;
class KernelStatistics;				
class BfxErrorRegionList;
class BfxPixelOp;

#define NUM_TRACECTL_DEBUG_BITMAPS 7

enum TraceMethod { 	TRACEMETHOD_MONO = 0,
					TRACEMETHOD_GREYSCALE,
					TRACEMETHOD_256COL,
					TRACEMETHOD_TRUECOL,

					// the end
					TRACEMETHOD_ILLEGAL,
					NUM_TRACEMETHOD=TRACEMETHOD_ILLEGAL};


/********************************************************************************************

>	class TraceControl : public CCObject

	Author:		Alex_Bligh (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/12/94
	Purpose:	Dialog for tracer

********************************************************************************************/

class TraceControl : public BitmapEffectBase
{
	// Give my name in memory dumps
	CC_DECLARE_DYNCREATE(TraceControl);

public:
	// Construction etc
	TraceControl();
	virtual ~TraceControl();

	virtual BOOL InitBitmap(KernelBitmap * theOriginal = NULL);
	virtual BOOL GetBitmaps( KernelBitmap * * theOriginal = NULL,
							 KernelBitmap * * theProposed = NULL,
							 KernelBitmap * * theUndithered = NULL	);

	virtual BOOL Trace(BOOL * Done);

	virtual BOOL SetPath(NodePath * pNodePath);
	virtual Node * GetPaths();
	virtual BOOL RemoveTree(BOOL DeleteIt = TRUE);

	virtual BOOL GetParams(
		TraceMethod * pMethod = NULL,
		INT32 * pMinimumArea = NULL,
		double * pMaximumInitialAreaErrorThreshold = NULL,
		double * pMinimumInitialAreaErrorThreshold = NULL,
		double * pInitialAreaErrorRatio = NULL,
		double * pMinGradFillError = NULL,
		double * pGradFillErrorRatio = NULL,
		double * pMinPixelError = NULL,
		double * pMaxPixelError = NULL,
		double * pPixelErrorRatio = NULL,
		double * pQuantColours = NULL,
		double * pBlur = NULL,
		double * pSmooth = NULL
		);

	virtual BOOL SetParams(
		TraceMethod * pMethod = NULL,
		INT32 * pMinimumArea = NULL,
		double * pMaximumInitialAreaErrorThreshold = NULL,
		double * pMinimumInitialAreaErrorThreshold = NULL,
		double * pInitialAreaErrorRatio = NULL,
		double * pMinGradFillError = NULL,
		double * pGradFillErrorRatio = NULL,
		double * pMinPixelError = NULL,
		double * pMaxPixelError = NULL,
		double * pPixelErrorRatio = NULL,
		double * pQuantColours = NULL,
		double * pBlur = NULL,
		double * pSmooth = NULL
);

	virtual BOOL GetProgress(INT32 * pPercent = NULL,
							 INT32 * pNumPaths = NULL,
							 INT32 * pNumCusps = NULL,
							 INT32 * pNumPoints = NULL,
							 BOOL * pProgressDone = NULL);
	
protected:

	virtual BOOL MarkInitialArea();
//	virtual BOOL MarkPositiveArea();

//	virtual BOOL FindInitialPoint();

	virtual BOOL TracePath(BfxPixelOp * pBfxPixelOp);
	virtual BOOL CalculateStatistics();
	virtual BOOL FormGradFill();

	virtual BOOL PlotGradFill(BOOL ToProposed, BOOL UsePath=TRUE);

//	virtual BOOL SwapTempAndProposed();

	virtual BOOL CheckMinimumArea(BfxPixelOp * pBfxPixelOp);

	KernelBitmap * pOriginal;
	KernelBitmap * pProposed;
	KernelBitmap * pUndithered;

#ifdef _DEBUG
public:
	KernelBitmap * pDebug[NUM_TRACECTL_DEBUG_BITMAPS];
	BOOL DebugSwitch[NUM_TRACECTL_DEBUG_BITMAPS];
	BOOL DebugInvalid[NUM_TRACECTL_DEBUG_BITMAPS];
protected:
#endif

	NodePath * pCurrentPath;
	LinearFillAttribute * pFill;

	Node * pTree;
	Node * pJoinNode;

	TraceRegion * pTraceRegion;
	BfxErrorRegionList * pErrorRegionList;

	KernelStatistics * pStats;

	BfxPixelOp * pThresholdPixelOp;
	BfxPixelOp * pColourThresholdPixelOp;
	BfxPixelOp * pPositivePixelOp;

	double InitialAreaErrorThreshold;
	double MaximumInitialAreaErrorThreshold;
	double MinimumInitialAreaErrorThreshold;
	double InitialAreaErrorRatio;

	double GradFillError;
	double NewGradFillError;
	double MinGradFillError;
	double GradFillErrorRatio;

	double PixelError;
	double MinPixelError;
	double MaxPixelError;
	double PixelErrorRatio;
	double QuantColours;

	double Blur;
	double Smooth;

	TraceMethod Method;
	INT32 Log2BPP;

	INT32 MinimumArea;

	// For progrss indicator only
	INT32 TotalPasses;
	INT32 NumPasses;
	INT32 NumPaths;
	INT32 NumCusps;
	INT32 NumPoints;
	BOOL ProgressDone;

	BOOL HavePath;
	BOOL FirstShape;
	BOOL ShapeFreePass;

	BOOL FoundRegion;
	INT32 InitialX;
	INT32 InitialY;
	INT32 RegionArea;

	INT32 ScanPointX;
	INT32 ScanPointY;
	DWORD ScanPointColour;
	
	INT32 XSize;
	INT32 YSize;

	INT32 GFStartX;
	INT32 GFStartY;
	INT32 GFEndX;
	INT32 GFEndY;
	DWORD GFStartC;
	DWORD GFEndC;

};

#endif  // INC_TRACECTL


