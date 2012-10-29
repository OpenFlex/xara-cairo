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

#ifndef INC_FLASH_SHAPE_RECORD
#define INC_FLASH_SHAPE_RECORD


#define SWF_MAX_COLOURS				8
#define SWF_MAX_PIXEL_DIMENSION		4350		// maximum size of an object in pixels. Actually this 
												//	is 4369.6, but it's probably better to use this 
												//	value, as it should avoid rounding errors.

// Holds RGBA values for rendering to a file.
typedef struct
{
	BYTE Red;
	BYTE Green;
	BYTE Blue;
	BYTE Alpha;
} FlashColour;

/********************************************************************************************

>	class FlashShapeRecord : public CCObject

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/10/99
	Purpose:	Contains the information necessary to render a DefineShape class to a file.

********************************************************************************************/

class FlashShapeRecord : public CCObject
{
public:
	FlashShapeRecord ();
	~FlashShapeRecord ();

	// Access functions.
	FlashShapeRecord* GetNext ( void );					// Get mpNext.
	void SetNext ( FlashShapeRecord *pNext );			// Set mpNext.
	FlashShapeRecord* AddNext ( void );					// Create a new element at mpNext.

	void SetPath ( DocCoord *pPath,
				   PathVerb *pVerbs,
				   INT32 NumberCoords );

	DocCoord* GetCoords ( void );						// Get mpCoordArray.

	PathVerb* GetVerbs ( void );						// Get mpPathVerbs.

	INT32 GetNumberCoords ( void );						// Get mNumberCoords.

	void SetLineWidth ( INT32 Width );
	WORD GetLineWidth ( void );

	void SetLineColour ( DocColour *pColour,
						 UINT32 *pAlpha );
	FlashColour GetLineColour ( void );

	void SetShapeID ( WORD ShapeID );					// Sets mShapeID.
	WORD GetShapeID ( void );							// Gets mShapeID.

	void SetBitmapID ( WORD BitmapID );					// Sets mBitmapID.
	WORD GetBitmapID ( void );							// Gets mBitmapID.

	void SetBoundingBox ( const DocRect &Bounds );
	DocRect GetBoundingBox ( void );

	void SetStartPoint ( const DocCoord &Point );		// Sets mStartPoint.
	void SetEndPoint ( const DocCoord &Point );			// Sets mEndPoint.
	void SetEndPoint2 ( const DocCoord &Point );		// Sets mEndPoint2.

	DocCoord GetStartPoint ( void );					// Gets mStartPoint.
	DocCoord GetEndPoint ( void );						// Gets mEndPoint.
	DocCoord GetEndPoint2 ( void );						// Gets mEndPoint2.

	void SetColour ( DocColour *pColour,				// Sets the colour, alpha, and ratio.
					 UINT32 FillTransparency,
					 BYTE Ratio,
					 UINT32 Index );

	FlashColour GetColour ( UINT32 i );					// Gets mColours [i].
	BYTE GetRatio ( UINT32 i );							// Gets mRatios [i].
	BYTE GetNumberColours ( void );						// Gets mNumberColours.

	void SetFill ( BYTE FillType );						// Sets mFill.
	BYTE GetFill ( void );								// Gets mFill.

	void SetIsCircular ( BOOL IsCircular );				// Sets mIsCircular.
	BOOL GetIsCircular ( void );						// Gets mIsCircular.

	void SetBitmapHeight ( INT32 Height );				// Sets mBitmapHeight.
	INT32 GetBitmapHeight ( void );						// Gets mBitmapHeight.

	void SetBitmapWidth ( INT32 Width );					// Sets mBitmapWidth.
	INT32 GetBitmapWidth ( void );						// Gets mBitmapWidth.

	void RemoveLines ( void );							// Removes lines from a drawing.

	BOOL WasInvalidSizeFound ();						// gets whether an invalid size has been exported
	BOOL CheckValidExportSize (const DocRect & Bounds);	// Checks whether an object is within the
														//	maximum flash size or not.


private:

	// Member variables.
	FlashShapeRecord *mpNext;				// Pointer to next record.
	DocCoord *mpCoordArray;					// Pointer to the start of the path coordinates.
	PathVerb *mpPathVerbs;					// Array of path verbs.
	INT32 mNumberCoords;						// The number of coordinates in the path array.
	WORD mLineWidth;						// Line width.
	FlashColour mLineColour;				// Line colour.
	DocRect mBoundingBox;					// The shape's bounding box.
	INT32 mBitmapHeight;						// The height of the bitmap used as a fill.
	INT32 mBitmapWidth;						// The width of the bitmap used as a fill.
	WORD mShapeID;							// The ID value of this shape.
	WORD mBitmapID;							// The ID value for the bitmap used.
	DocCoord mStartPoint;					// The position of the start of a fill.
	DocCoord mEndPoint;						// The end point of a fill.
	DocCoord mEndPoint2;					// The second end point, for complex fills.
	FlashColour mColours [SWF_MAX_COLOURS];	// An array of colours used by the shape's fill.
	BYTE mRatios [SWF_MAX_COLOURS];			// The ratios of where the colours are placed.
	BYTE mNumberColours;					// The number of colours used.
	BYTE mFill;								// The fill's fill style.
	BOOL mIsCircular;						// Is the path circular or not.

	BOOL mInvalidSizeFound;					// has a shape with an invalid size been found ?
};

#endif
