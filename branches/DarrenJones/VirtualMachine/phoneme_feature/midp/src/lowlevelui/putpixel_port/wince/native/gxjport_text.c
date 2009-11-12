/*
 *   
 *
 * Copyright  1990-2008 Sun Microsystems, Inc. All Rights Reserved.
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License version
 * 2 only, as published by the Free Software Foundation.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License version 2 for more details (a copy is
 * included at /legal/license.txt).
 * 
 * You should have received a copy of the GNU General Public License
 * version 2 along with this work; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301 USA
 * 
 * Please contact Sun Microsystems, Inc., 4150 Network Circle, Santa
 * Clara, CA 95054 or visit www.sun.com if you need additional
 * information or have any questions.
 */

#include <kni.h>
#include <gxapi_constants.h>
#include <gxj_putpixel.h>
#include "font_internal.h"

/* convert color to 16bit color */
#define RGB24TORGB16(x) (((( x ) & 0x00F80000) >> 8) + \
                         ((( x ) & 0x0000FC00) >> 5) + \
                         ((( x ) & 0x000000F8) >> 3) )

/**
 * @file
 *
 * platform dependent character drawing
 */

int gxjport_draw_chars(jint pixel, const jshort *clip,
                       gxj_screen_buffer *sbuf, int dotted,
                       int face, int style, int size,
                       int x, int y, int anchor,
                       const jchar *charArray, int n) {
    if (!gfFontInit) {
        gfFontInit = 1;
        wince_init_fonts();
    }

    // #3577: UIQ, WinCE,LWUIT: fonts of the text in the body area are now green
    //
    // Davy: The green color is caused by a missing conversion from the original
    // 24-bit RGB grey Java color (being 0x676767) to a 16-bit RGB color on WinCE.
    // Make sure to convert 24-bit RGB colors to 16-bit RGB (5/6/5) before passing
    // along the color to gx_port_draw_chars (in font.c)
    pixel = RGB24TORGB16(pixel);

    gx_port_draw_chars(pixel, clip, sbuf, dotted,
        face, style, size, x, y, (TOP | LEFT), charArray, n);

    return KNI_TRUE;
}                           

int gxjport_get_font_info(int face, int style, int size,
                          int *ascent, int *descent, int *leading) {
    if (!gfFontInit) {
        gfFontInit = 1;
        wince_init_fonts();
    }

    gx_port_get_fontinfo(face, style, size, ascent, descent, leading);

    return KNI_TRUE;
}                            

int gxjport_get_chars_width(int face, int style, int size,
                            const jchar *charArray, int n) {
    if (!gfFontInit) {
        gfFontInit = 1;
        wince_init_fonts();
    }

    return gx_port_get_charswidth(face, style, size, charArray, n);
}
