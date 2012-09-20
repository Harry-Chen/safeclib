/*------------------------------------------------------------------
 * strisalphanumeric_s.c
 *
 * November 2008, Bo Berry
 *
 * Copyright (c) 2008-2011 by Cisco Systems, Inc
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT.  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *------------------------------------------------------------------
 */

#include "safe_str_lib.h"
#include "safeclib_private.h"
#include "safe_str_constraint.h"


/**
 * NAME
 *    strisalphanumeric_s
 *
 * SYNOPSIS
 *    #include "safe_dest_lib.h"
 *    boolean_t
 *    strisalphanumeric_s(const char *dest, rsize_t dmax)
 *
 * DESCRIPTION
 *    This function checks if the entire string contains
 *    alphanumerics.  The scanning stops at the first null
 *    or after dmax characters.
 *
 * EXTENSION TO
 *    ISO/IEC TR 24731, Programming languages, environments
 *    and system software interfaces, Extensions to the C Library,
 *    Part I: Bounds-checking interfaces
 *
 * INPUT PARAMETERS
 *    dest         pointer to string
 *
 *    dmax         maximum length of string
 *
 * OUTPUT PARAMETERS
 *    none
 *
 * Runtime-condestaints
 *    dest shall not be a null pointer.
 *    dmax shall not equal zero.
 *    dmax shall not be greater than RSIZE_MAX_STR.
 *
 * RETURN VALUE
 *    TRUE      dest is alphanumeric
 *    FALSE     dest is not alphanumeric or an error occurred
 *
 * ALSO SEE
 *    strisascii_s(), strisdigit_s(), strishex_s(), strislowercase_s(),
 *    strismixedcase_s(), strisuppercase_s()
 *
 */
boolean_t
strisalphanumeric_s (const char *dest, rsize_t dmax)
{
    if (!dest) {
        invoke_safe_str_constraint_handler("strisalphanumeric_s: "
                   "dest is null",
                   NULL, ESNULLP);
        return (FALSE);
    }

    if (dmax == 0) {
        invoke_safe_str_constraint_handler("strisalphanumeric_s: "
                   "dmax is 0",
                   NULL, ESZEROL);
        return (FALSE);
    }

    if (dmax > RSIZE_MAX_STR) {
        invoke_safe_str_constraint_handler("strisalphanumeric_s: "
                   "dmax exceeds max",
                   NULL, ESLEMAX);
        return (FALSE);
    }

    if (*dest == '\0') {
        return (FALSE);
    }

    while (*dest && dmax) {

        if (( (*dest >= '0') && (*dest <= '9') )  ||
            ( (*dest >= 'a') && (*dest <= 'z') )  ||
            ( (*dest >= 'A') && (*dest <= 'Z') )) {
            dest++;
            dmax--;
        } else {
            return (FALSE);
        }
    }

    return (TRUE);
}
