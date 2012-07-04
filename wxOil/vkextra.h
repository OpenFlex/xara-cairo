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


#ifndef INC_VKEXTRA
#define INC_VKEXTRA

/* WXK_0 thru WXK_9 are the same as ASCII '0' thru '9' (0x30 - 0x39) */

#define WXK_0 0x30
#define WXK_1 0x31
#define WXK_2 0x32
#define WXK_3 0x33
#define WXK_4 0x34
#define WXK_5 0x35
#define WXK_6 0x36
#define WXK_7 0x37
#define WXK_8 0x38
#define WXK_9 0x39

/* WXK_A thru WXK_Z are the same as ASCII 'A' thru 'Z' (0x41 - 0x5A) */

#define WXK_A 0x41
#define WXK_B 0x42
#define WXK_C 0x43
#define WXK_D 0x44
#define WXK_E 0x45
#define WXK_F 0x46
#define WXK_G 0x47
#define WXK_H 0x48
#define WXK_I 0x49
#define WXK_J 0x4A
#define WXK_K 0x4B
#define WXK_L 0x4C
#define WXK_M 0x4D
#define WXK_N 0x4E
#define WXK_O 0x4F
#define WXK_P 0x50
#define WXK_Q 0x51
#define WXK_R 0x52
#define WXK_S 0x53
#define WXK_T 0x54
#define WXK_U 0x55
#define WXK_V 0x56
#define WXK_W 0x57
#define WXK_X 0x58
#define WXK_Y 0x59
#define WXK_Z 0x5A

#define WXK_LESS 0xBC
#define WXK_GREATER 0xBE

#define WXK_ADD 0x6B
#define WXK_EQUALS 0xBB
#define WXK_COMMA 0xBC
#define WXK_MINUS 0xBD
#define WXK_PERIOD 0xBE
#define WXK_HASH 0xDE

//--------------------------------------------------------------------------------------------------------------
// The following codes have been made up by CC so could possibly clash with future definitions from Microsoft.
// To make this highly unlikely, all CC virtual key codes will be defined with the prefix WXK_CC_

// The actual numbers that are given to new WXK_CC_ bindings should be big.  It is suggested that
// they all be 32 bit values, with the top byte being &8C, i.e. &8C000000 being the first code

//---

// Special virtual key code we have defined that should be impossible to generate
// from any keyboard in the world.
#define WXK_CC_NONE 0xffffffff

// Define which actual virtual key codes will represent our modifier keys
#define WXK_CC_MOD_ADJUST 			WXK_SHIFT
#define WXK_CC_MOD_CONSTRAIN 		WXK_CONTROL
#define WXK_CC_MOD_ALTERNATIVE 		WXK_ALT
#define WXK_CC_MOD_OPTION			WXK_CC_NONE

// Define the left and right versions of the modifiers, if we can
#define WXK_CC_MOD_ADJUST_LEFT		WXK_LSHIFT
#define WXK_CC_MOD_ADJUST_RIGHT		WXK_RSHIFT
#define WXK_CC_MOD_CONSTRAIN_LEFT	WXK_LCONTROL
#define WXK_CC_MOD_CONSTRAIN_RIGHT	WXK_RCONTROL
#define WXK_CC_MOD_ALTERNATIVE_LEFT	WXK_LALT
#define WXK_CC_MOD_ALTERNATIVE_RIGHT	WXK_RALT

#endif  // INC_VKEXTRA
