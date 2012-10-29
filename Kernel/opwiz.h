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
 * */

/*
<THIS_FILE>  The name of the file (In capitals)
<OPNAME>	 The name of the operation (eg. OpPrint)
<OPTOKEN>	 The name of the operation without the Op prefix. eg. the OpToken for OpPrint
			 could be "print" 
<YOURNAME>	 The name you put in your function and class header blocks
<TODAY>		 Todays date
<?>			 Other information required 
*/

#ifndef INC_<THIS_FILE>
#define	INC_<THIS_FILE>


#define	 OPTOKEN_<OPTOKEN> "<OPTOKEN>"

/********************************************************************************************

>	class <OPNAME> : public Operation

	Author:		<YOURNAME>
	Created:	<TODAY>
	Purpose:	<?>
	SeeAlso:	Operation

********************************************************************************************/

class <OPNAME> : public Operation
{
	CC_DECLARE_DYNCREATE( <OPNAME> )
	
public:

	<OPNAME>();	                                    
	static BOOL Init();                       	
	static OpState GetState(String_256*, OpDescriptor*);
	void Do(OpDescriptor*);                    		
};


#endif
