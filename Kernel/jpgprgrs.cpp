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


#include "camtypes.h"
//#include "filters.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "progress.h"

#include "jinclude.h"
#include "jpeglib.h"
#include "jpgprgrs.h"



// Place any IMPLEMENT type statements here
//CC_IMPLEMENT_MEMDUMP(CCWobJob, CC_CLASS_MEMDUMP)


// We want better memory tracking
#define new CAM_DEBUG_NEW


// Functions follow


/********************************************************************************************

>	JPEGProgressMonitor::JPEGProgressMonitor(j_decompress_ptr cinfo)

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	02/08/96
	Inputs:		cinfo : the structure provided by the IJG library
	Purpose:	Derived classes should call this prior to their own construction to construct
				a safe base class.
	Scope:		protected

********************************************************************************************/
JPEGProgressMonitor::JPEGProgressMonitor(j_decompress_ptr cinfo)
{
	// Set "base class" member...
	progress_monitor = Update;

	m_pcinfo			= cinfo;
	m_bContinueOp		= TRUE;
}


/********************************************************************************************

>	JPEGProgressMonitor::~JPEGProgressMonitor()

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	02/08/96
	Purpose:	Provides bizarre pure implementation for derived class destructors
	Scope:		protected

********************************************************************************************/
JPEGProgressMonitor::~JPEGProgressMonitor()
{
}


/********************************************************************************************

>	void JPEGProgressMonitor::Update(j_common_ptr cinfo)

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	02/08/96
	Inputs:		cinfo : data provided by the IJG Library
	Purpose:	Callback function for the IJG library.
				It updates the Camelot Progress bar
	Scope:		static
	Notes:		This member is static because the IJG library is written in C, so requiring
				classless pointers to functions

********************************************************************************************/
void JPEGProgressMonitor::Update(j_common_ptr cinfo)
{
	JPEGProgressMonitor* pThis = (JPEGProgressMonitor*) cinfo->progress;
	pThis->OnUpdate();
}





/********************************************************************************************

>	JPEGProgressBySelf::JPEGProgressBySelf(j_decompress_ptr cinfo, 
											const StringBase& BarString)

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	02/08/96
	Inputs:		BarString: a reference to the string to be used on the progress bar during
				the time-consuming operation
	Purpose:	Constructor for a class providing a progress callback to the IJG Library
				JPEG filter.
	Notes:		A progress bar will be constructed via this constructor.
	See Also:	JPEGProgressByFilter

********************************************************************************************/
JPEGProgressBySelf::JPEGProgressBySelf(j_decompress_ptr cinfo, const StringBase& BarString)
	: JPEGProgressMonitor(cinfo)
{
	m_BarString			= BarString;
	m_uLastPercentDone	= 0;

	// Create a new progress bar. Actually not that bothered if it doesn't construct
	m_pProgressBar		= new Progress(&m_BarString, 100);
}


/********************************************************************************************

>	JPEGProgressBySelf::~JPEGProgressBySelf()

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	02/08/96
	Purpose:	Destructor - stops the progress bar
	Notes:		Derived classes should call this subsequent to any specialized destruction
				code of their own.

********************************************************************************************/
JPEGProgressBySelf::~JPEGProgressBySelf()
{
	// If started, then stop then progress bar
	if (m_pProgressBar != NULL)
	{
		delete m_pProgressBar;
		m_pProgressBar = NULL;
	}
}


/********************************************************************************************

>	virtual void JPEGProgressBySelf::OnUpdate()

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	02/08/96
	Purpose:	Called by JPEGProgressMonitor::Update() to provide feedback on the filter
				progress. Derived classes should provide an implementation for this.
				JPEGProgressBySelf calls the contained Progress::Update member with the
				percentage done.

********************************************************************************************/
void JPEGProgressBySelf::OnUpdate()
{
	/*
		Fraction done =

			completed_passes + (pass_counter/pass_limit)
			--------------------------------------------
						total_passes
	*/
	UINT32 PercentDone = (UINT32) (100L * completed_passes + (100L * pass_counter) / pass_limit)
							/ total_passes;

	// Update the progress count, if required
	// but don't bother if the user aborted
	if (PercentDone != m_uLastPercentDone && m_bContinueOp)
	{
		m_bContinueOp = m_pProgressBar->Update(PercentDone);
		m_uLastPercentDone = PercentDone;
	}
}





/********************************************************************************************

>	JPEGProgressByFilter::JPEGProgressByFilter(j_decompress_ptr cinfo, Filter* pFilterToUse,
												UINT32 Increment);

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	02/08/96
	Inputs:		cinfo : the structure provided by the IJG library
				pFilterToUse : a pointer to a Filter with an IncProgressBarCount(UINT32 ...) 
				member, which will be called with an update of the percentage progress made.
				ImportSize : the size of the file we are importing

	Purpose:	Constructor for a class providing a progress callback to the IJG Library
				JPEG filter.
	Notes:		No progress bar will be constructed via this constructor. The given filter
				is expected to provide one.
	See Also:	JPEGProgressBySelf

********************************************************************************************/
JPEGProgressByFilter::JPEGProgressByFilter(j_decompress_ptr cinfo, Filter* pFilterToUse,
						UINT32 ImportSize)
	: JPEGProgressMonitor(cinfo)
{
	m_pFilterForUpdate	= pFilterToUse;
	m_uLastScanLineDone	= 0;
	m_uImportSize = ImportSize;
}


/********************************************************************************************

>	virtual void JPEGProgressByFilter::OnUpdate()

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	02/08/96
	Purpose:	Called by JPEGProgressMonitor::Update() to provide feedback on the filter
				progress. Derived classes should provide an implementation for this.
				JPEGProgressByFilter calls the contained Filter's Update member with the
				number of scanlines processed.

********************************************************************************************/
void JPEGProgressByFilter::OnUpdate()
{
	INT32 Difference = m_pcinfo->output_scanline - m_uLastScanLineDone;
	if (Difference > 0)
	{
		UINT32 PerLineIncrement = m_uImportSize / m_pcinfo->output_height;
		m_pFilterForUpdate->IncProgressBarCount(Difference * PerLineIncrement);
		m_uLastScanLineDone += Difference;
	}
}
