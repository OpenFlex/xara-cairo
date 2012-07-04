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

//

#ifndef INC_JPGPRGRES
#define INC_JPGPRGRES

/**************************************************************************************

>	class JPEGProgressMonitor : public jpeg_progress_mgr

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/08/96
	Purpose:	Provides progress update callback for the IJG library JPEG Filters

**************************************************************************************/
class JPEGProgressMonitor : public libJPEG::jpeg_progress_mgr 
{
	// Declare the class for memory tracking
	//CC_DECLARE_MEMDUMP(JPEGProgressMonitor);
public:
	// Overridden 'C' function
	static void Update(libJPEG::j_common_ptr cinfo);

	BOOL UserAborted() const	{	return !m_bContinueOp;	}

	virtual ~JPEGProgressMonitor() = 0;

protected:

	BOOL				m_bContinueOp;
	libJPEG::j_decompress_ptr	m_pcinfo;

protected:
	// Support functions
	JPEGProgressMonitor(libJPEG::j_decompress_ptr cinfo);

	// Overridable functions

	virtual void	OnUpdate() = 0;
};


/**************************************************************************************

>	class JPEGProgressBySelf : public JPEGProgressMonitor

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/08/96
	Purpose:	Provides progress update callback for the IJG library JPEG Filters
				using a self-contained Progress object.

**************************************************************************************/
class JPEGProgressBySelf : public JPEGProgressMonitor
{
	// Declare the class for memory tracking
	//CC_DECLARE_MEMDUMP(JPEGProgressBySelf);
public:

	JPEGProgressBySelf(libJPEG::j_decompress_ptr cinfo, const StringBase& BarString);

	~JPEGProgressBySelf();

protected:
	String_64		m_BarString;
	Progress*		m_pProgressBar;
	UINT32			m_uLastPercentDone;

protected:
	// Overridden functions
	virtual void	OnUpdate();

};


/**************************************************************************************

>	class JPEGProgressFilter : public JPEGProgressMonitor

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/08/96
	Purpose:	Provides progress update callback for the IJG library JPEG Filters
				using the Update member of the Filter class

**************************************************************************************/
class JPEGProgressByFilter : public JPEGProgressMonitor
{
	// Declare the class for memory tracking
	//CC_DECLARE_MEMDUMP(JPEGProgressByFilter);
public:

	JPEGProgressByFilter(libJPEG::j_decompress_ptr cinfo, Filter* pFilterToUse,
		UINT32 ImportSize);

protected:
	Filter*			m_pFilterForUpdate;
	UINT32			m_uLastScanLineDone;
	UINT32			m_uImportSize;

protected:
	// Overridden functions
	virtual void	OnUpdate();
};

#endif	// INC_JPGPRGRES


