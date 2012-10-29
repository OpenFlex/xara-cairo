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

/*
 *  */ 

#ifndef INC_SENTRYOP
#define INC_SENTRYOP        



/********************************************************************************************

>	class SentryOperation: public Operation

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/2/94

	Purpose:	A SentryOperation is a non-undoable operation which hangs around on 
				the live operations list (receiving message broadcasts) for the lifetime of 
				the system.  

				Its a background, system helper sort of animal.  
				
				It will never be directly  invokable by the user, so there is no need to 
				declare an Init, GetState, or Do function for it. 

				An instance of the SentryOp class is created in the Application object.
				When it receives a message indicating a change in the system, it informs
				all subsystems that need to know about the change. 
				

	SeeAlso:	Operation

********************************************************************************************/

class CCAPI SentryOperation: public Operation
{
	CC_DECLARE_DYNCREATE( SentryOperation )   

public: 
  	SentryOperation(); 
	virtual ~SentryOperation(); 

};							  
 
#endif 


