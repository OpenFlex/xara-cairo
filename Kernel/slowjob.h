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


#ifndef	INC_SLOWJOB
#define	INC_SLOWJOB

/********************************************************************************************

<	SlowJobResult

	Comment:	This enum is used to indicate the outcome of a 'slow job'.  It is used by the
				printing and EPS export code.  It has the following values:

					SLOWJOB_SUCCESS:	Job finished successfully
					SLOWJOB_FAILURE:	An error occured during the job.
					SLOWJOB_USERABORT:	The user aborted the job.

	SeeAlso:	RenderViewResult

********************************************************************************************/ 

enum SlowJobResult		
{ 
	SLOWJOB_SUCCESS, 
	SLOWJOB_FAILURE, 
	SLOWJOB_USERABORT 
};

#endif //INC_SLOWJOB
