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


// CSampleList and CSampleItem header file

#ifndef INC_SAMPLIST
#define INC_SAMPLIST

class CCObject;
class DocCoord;
class CXaraFileRecord;

/********************************************************************************************

>	class CSampleItem : public CCObject

	Author:		Diccon_Yamanaka (Xara Group Ltd) <camelotdev@xara.com>
	Created:	31/5/2000

	Purpose:	Brush sample data item class, records position, distance along the path and 
				pressure at the point when it is recorded.
				
	Notes:		
********************************************************************************************/

class CSampleItem : public CCObject
{
	CC_DECLARE_DYNAMIC(CSampleItem)

public:
	CSampleItem();
	CSampleItem(DocCoord Coord, MILLIPOINT Distance, UINT32 Pressure);
	CSampleItem(const CSampleItem& Other);
	~CSampleItem() {};

public: // operator overrides
	CSampleItem operator=(const CSampleItem& Other);
	BOOL		operator==(const CSampleItem& Other);

public: // other
	CSampleItem InterpolateItems(CSampleItem& Other, double Proportion);
	
	BOOL WriteNative(CXaraFileRecord* pRecord);

public: // data - bit naughty but I'm in a hurry
	DocCoord	m_Coord;
	MILLIPOINT	m_Distance;
	UINT32		m_Pressure;

	// Special note - we only ever actually use the pressure data, so ignore the distance and position
};


typedef std::vector< CSampleItem >	SampleArray;

/********************************************************************************************

>	class CSampleData : public CCObject

	Author:		Diccon_Yamanaka (Xara Group Ltd) <camelotdev@xara.com>
	Created:	31/5/2000

	Purpose:	Base class to hold an array of CSampleItems.  
				
	Notes:		
********************************************************************************************/

class CSampleData : public CCObject
{
	CC_DECLARE_DYNAMIC(CSampleData)
public:
	CSampleData();
	~CSampleData();

public:  // overridables
	CSampleData* MakeCopy();
	virtual BOOL InitialiseData(size_t Size = 1000, UINT32 GrowBy = 50);  // initialises the list member, you need to do this.
	virtual BOOL CollectData(DocCoord Coord, UINT32 Pressure); 
	void FinishSampling();
public: // access fns.
	BOOL	SetCollectionSampleRate(double Rate);
	double	GetCollectionSampleRate();
	BOOL	SetRetrievalSampleRate(double Rate);
	double	GetRetrievalSampleRate();

	void	SetSampleArray(SampleArray* pArray);
	SampleArray* GetSampleArray() { return m_pSampleData;}
	size_t	GetNumItems() {return m_NumItems;}

	UINT32	GetMaxPressure();
	void	SetMaxPressure(UINT32 Max);
public: // manipulation functions
	BOOL ReverseData();

public: // writes this data object to a record
	BOOL WriteNative(CXaraFileRecord* pRecord);

	void SetNumItemsFromArraySize(); // sets the number of items member
	BOOL ClipArray(size_t Size);       // sets the size of the data array - use with care!

public: // array access fns.
	void Add(CSampleItem& Item);
	BOOL SetAt(UINT32 Index, CSampleItem& Item);
	BOOL InsertAt(UINT32 Index, CSampleItem& Item);
	BOOL SetNext(CSampleItem& Item, BOOL Grow = FALSE);
	BOOL SetPrev(CSampleItem& Item);
	BOOL RemoveAt(UINT32 Index);
	
	BOOL GetAt(UINT32 Index, CSampleItem* pItem);
	BOOL GetAtPos(double Index, CSampleItem* pItem);
	BOOL GetNext(CSampleItem* pItem);
	BOOL GetPrev(CSampleItem* pItem);
	
	INT32 GetCount();
	void FreeExtra();

public: // array manipulation functions
	BOOL InsertNewData(UINT32 Index, CSampleData* pData);
	BOOL RemoveData(UINT32 StartIndex, UINT32 EndIndex, SampleArray* pArray = NULL);

protected: // helper functions
	BOOL	SetInternalCollectionIndex(UINT32 IndexRequested);
	BOOL	SetInternalRetrievalIndex(UINT32 IndexRequested);
	BOOL	IncrementInternalIndex(double* CurrentIndex);
	BOOL	DecrementInternalIndex(double* CurrentIndex);

	BOOL	GetItemAtInternalIndex(double Index, CSampleItem* pItem);

protected:  // resampling helper functins
	BOOL	ReSampleArray(SampleArray** ppArray, UINT32 NewNumItems);
	BOOL	InsertControlPoints(UINT32 Frequency, SampleArray* pOriginal, SampleArray* pNew);
	BOOL	RemoveControlPoints(UINT32 Frequency, SampleArray* pOriginal, SampleArray* pNew);
	BOOL	InterpolateItems(UINT32 StartIndex, UINT32 EndIndex, SampleArray* pArray);
	BOOL	GetArraySection(UINT32 StartIndex, UINT32 EndIndex, SampleArray* pArraySection);

protected: // data
	SampleArray* m_pSampleData;  // the actual array

	double		 m_CollectionInternalIndex;  // index into the array that we use for collection
	double		 m_RetrievalInternalIndex;	 // index into the array that we use for retrieval

	double		 m_CollectionSampleRate; // determines the rate at which we set data
	double		 m_RetrievalSampleRate;  // the rate at which we retrieve data

	UINT32		 m_ElementSize; // size of each item in the array

	size_t		 m_NumItems;

	UINT32		 m_MaxPressure; // the maximum possible value allowed by the pressure device
									// during collection
	double		 m_ScalePressure; // the value that will scale the local pressure value to the
								  // globally defined range
	
};

/********************************************************************************************

>	class CDistanceSampler : public CSampleData

	Author:		Diccon_Yamanaka (Xara Group Ltd) <camelotdev@xara.com>
	Created:	31/5/2000

	Purpose:	Derived class which has a method to sample data over distances.  Basically
				what you want to do is initialise the object, set the sample distances, then 
				pass in data to the CollectData method and this object will sample at the
				appropriate rate
				
	Notes:		
********************************************************************************************/

class CDistanceSampler : public CSampleData
{
	CC_DECLARE_DYNAMIC(CDistanceSampler)

public:
	CDistanceSampler();
	~CDistanceSampler();

public: // overridables
	CDistanceSampler* MakeCopy();
	virtual BOOL CollectData(DocCoord Coord, UINT32 Pressure);

public: 
	BOOL SetSampleDistance(MILLIPOINT Distance);
	MILLIPOINT GetSampleDistance();

	BOOL SetSampleRateFromSpacing(MILLIPOINT Spacing);
				// sets the retrieval sample rate from a given brush spacing			

	INT32 GetInternalIndexFromDistance(MILLIPOINT Distance);
				// gets the internal index at the given distance			

	BOOL GetDataSection(MILLIPOINT Start, MILLIPOINT End, CDistanceSampler* pSection);
				// retrieves a section of data and wraps it up for us			

	BOOL ReSample(MILLIPOINT NewLength);  
				// stretches or shrinks our data to fit a new length

	UINT32 m_ItemsInserted;

	double	GetDistanceRep () { return ((double) m_DistanceSoFar); }
	void SetDistanceSoFar (double val) { m_DistanceSoFar = (MILLIPOINT) val; }
protected: // data
	MILLIPOINT	m_SampleDistance;  // the distance at which we want to take each sample
	
	CSampleItem m_LastItemStored;        // the last item we inserted
	CSampleItem m_LastItem;				 // the last item we receieved
	DocCoord	m_LastCoord;       // the last coordinate we received
	MILLIPOINT	m_DistanceSinceLastSample;  // pretty much what you might expect, given the name
	MILLIPOINT	m_DistanceSoFar;

	double		m_ItemRemainder;

	MILLIPOINT	m_TotalDistance;
	MILLIPOINT	m_DistanceSinceLastData;

};

#endif
