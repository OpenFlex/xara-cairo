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

// Definition of the processpath classes

#ifndef INC_PATHPROC
#define INC_PATHPROC


#define PROC_CACHE_SIZE 0x1000


/******************************************************************************************

> 	class ProcessFlags

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	25/10/94
	Purpose:	

******************************************************************************************/

class ProcessFlags
{
public:
	ProcessFlags(BOOL flatten = TRUE, BOOL quantise = FALSE, BOOL quantiseall = FALSE);

	BYTE FlattenCurves : 1;
	BYTE QuantiseLines : 1;
	BYTE QuantiseAll : 1;
};



/******************************************************************************************

> 	class ProcessPath

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	25/10/94
	Purpose:	

******************************************************************************************/

class ProcessPath : public CCObject
{
	CC_DECLARE_DYNAMIC(ProcessPath);

	public:
		ProcessPath(const double flat);
		~ProcessPath();

		BOOL 	Init(Path* pSource);
		BOOL	Process(const ProcessFlags& PFlags);
		
		virtual void OpenElement(PathVerb Verb, INT32 index);
		virtual BOOL NewPoint(PathVerb Verb, DocCoord* pCoord) = 0;
		virtual BOOL CloseElement(BOOL ok, PathVerb Verb, INT32 index);
		virtual void CloseFigure(void);
		
	protected:
		BOOL	FlattenCurve(INT32 Px0,INT32 Py0, INT32 Px1,INT32 Py1,
							 INT32 Px2,INT32 Py2, INT32 Px3,INT32 Py3, BOOL QuantiseAll=FALSE);
		BOOL	FlattenSplit(INT32 Px0,INT32 Py0, INT32 Px1,INT32 Py1,
							 INT32 Px2,INT32 Py2, INT32 Px3,INT32 Py3, BOOL QuantiseAll=FALSE);
		virtual BOOL InsertQuantisedLineTo(DocCoord * pEnd, DocCoord * pStart);

	protected:
		Path*		ProcSource;
		INT32* 		ProcCache;				// Cache pointer for flattening
		INT32		ProcNumCached;			// Number of entries in cache
		BOOL		ProcFirstPoint;			// True if first point not processed yet
		double		ProcFlatness;			// <0 then dont flatten curves, approx 64 is good

		DocCoord	ProcPreviousEl;			// coord of previous element point
		
};


/******************************************************************************************

> 	class FlattenPath

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	25/10/94
	Purpose:	Flattens a path to the user specified output buffer using a 
				given flatness

******************************************************************************************/

class ProcessFlatten : public ProcessPath
{
	public:
		ProcessFlatten(const double flat);
		BOOL FlattenPath(const ProcessFlags& PFlags, Path* pSource, Path* pDestin);
		virtual BOOL NewPoint(PathVerb Verb, DocCoord* pCoord);

	private:
		Path*	FlattenOutput;

};



/******************************************************************************************

> 	class ProcessLength

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	25/10/94
	Purpose:	Calculates the length of a path

******************************************************************************************/

class ProcessLength : public ProcessPath
{
	public:
		ProcessLength(const double flat);
		BOOL PathLength(Path* Input, double* Length, INT32 Index = -1);
		virtual void OpenElement(PathVerb Verb, INT32 index);
		virtual BOOL NewPoint(PathVerb Verb, DocCoord* pCoord);
		virtual BOOL CloseElement(BOOL ok, PathVerb Verb, INT32 index);

	private:
		DocCoord PrevCoord;
		double	 ElementLength;
		double   CurrLength;
		INT32	 UserIndex;
};



/******************************************************************************************

> 	class ProcessDistance

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	25/10/94
	Purpose:	If a platonic piece of string whose length l and endpoints (p0,p1) is laid 
				along a path [e0,e1,e2,....en], this class calculates the index of the 
				element ei, which contains p1 and the parameter mu (0<=mu<1) which can be 
				used to calculate the actual coordinate value of p1.
				
******************************************************************************************/

class ProcessDistance : public ProcessPath
{
	public:
		ProcessDistance(const double flat);
		double PathDistance(const double dist, Path* Input, INT32* index);
		virtual void OpenElement(PathVerb Verb, INT32 index);
		virtual BOOL NewPoint(PathVerb Verb, DocCoord* pCoord);
		virtual BOOL CloseElement(BOOL ok, PathVerb Verb, INT32 index);

	private:
		double		Distance;
		INT32		ElementIndex;
		double		ElementLength;
		double		ElementParam;
		DocCoord 	PrevCoord;
};


/******************************************************************************************
> 	class ProcessPathDistance : ProcessPath

	Author:		Ed_Cornes (Xara Group Ltd) <camelotdev@xara.com>
	Created:	9/4/95
	Purpose:	Process path to find Coord and Tangent at specified distance along path

	Additional: Diccon 2/12/99 - I have made some additions to this class with the intention
				of making it so that you can instantiate a PPD object and use it repeatedly
				to find points on a path without always traversing the path form the beginning.
				Unfortunately time pressure means that at the moment it is not finished except 
				for its particular application to the Brush.  If I get time I will 
				endeavour to make it generalised, but for now use with care.
	
******************************************************************************************/

class ProcessPathDistance : public ProcessPath
{
	public:
		ProcessPathDistance(const double flat);
		BOOL GetCoordAndTangent(DocCoord* pCoord, double* pTangent, BOOL* pFound,
								double dist, Path* pPath, UINT32* pPressure = NULL);
		

		// version called by the nodebrushpath where previous results are cached
		INT32 GetCoordAndTangentWithCache(DocCoord* pCoord, double* pTangent, BOOL* pFound,
									double dist, Path* pPath, UINT32* pPressure = NULL);

		//INT32 GetCoordTangentAndPressure(DocCoord* pCoord, double* pTangent, UINT32* pPressure,
		//								BOOL* pFound, double Dist, Path* pPath);
		virtual BOOL NewPoint(PathVerb Verb, DocCoord* pCoord);
		BOOL NewPointA(PathVerb Verb, DocCoord* pCoord, UINT32* pPressure = NULL);
		
		// the cached version of process
		INT32	Process(const ProcessFlags& PFlags, INT32 AlreadyProcessed);
	private:
		double   DesiredDist;
		double   CurrentDist;
		double   TangentAtDist;
		DocCoord CoordAtDist;
		UINT32	 PressureAtDist;
		BOOL     Found;
		DocCoord PrevCoord;
		UINT32     m_PrevPressure;

		// members used to cache previous results
		INT32	 m_LastFoundIndex;
		BOOL	 m_bDrawingBrush;
		double	 m_LastFoundDistance;

};

#endif

