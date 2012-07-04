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


#ifndef INC_PNGFUNCS
#define	INC_PNGFUNCS

// Camelot replacements for libpng functions
void  camelot_png_error(png_structp png_ptr, png_const_charp message);
void  camelot_png_warning(png_structp png_ptr, png_const_charp message);
void  camelot_png_read_data(png_structp png_ptr, png_bytep data, png_size_t length);
void  camelot_png_write_data(png_structp png_ptr, png_bytep data, png_size_t length);
void  camelot_png_flush_data(png_structp png_ptr);
void *camelot_png_malloc(png_structp png_ptr, png_size_t size);
void  camelot_png_free(png_structp png_ptr, png_voidp data);
void  camelot_png_read_row_callback
			(png_structp png_ptr, png_uint_32 row_number, INT32 pass);
void  camelot_png_write_row_callback
			(png_structp png_ptr, png_uint_32 row_number, INT32 pass);

#endif//INC_PNGFUNCS
