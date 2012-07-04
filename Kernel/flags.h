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


// Header file for generic flag operations etc.

#ifndef INC_FLAGS
#define INC_FLAGS

/********************************************************************************************

<	FlagState

	Comment:	Standard enum which can be used to change/read a flag (assuming a routine
				exists that uses this enum).

				Possible values:

					Disable		- Set flag to be off/disabled/FALSE etc.
					Enable		- Set flag to be on/enabled/TRUE etc.
					Toggle		- Toggle the flags value
					NoChange	- Don't change - just return the current value of the
								  flag (i.e. either Disable or Enable)
					Fail		- Failure/error of some kind.

********************************************************************************************/ 

enum FlagState { Disable, Enable, Toggle, NoChange, Fail };


#endif  // INC_FLAGS


