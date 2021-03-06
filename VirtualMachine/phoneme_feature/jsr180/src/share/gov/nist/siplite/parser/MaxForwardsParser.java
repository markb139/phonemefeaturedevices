/*
 * Portions Copyright  2000-2008 Sun Microsystems, Inc. All Rights
 * Reserved.  Use is subject to license terms.
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
package gov.nist.siplite.parser;

import gov.nist.core.*;
import gov.nist.siplite.header.*;
/**
 * Parser for Max Forwards Header.
 *
 * @version JAIN-SIP-1.1
 *
 *
 * <a href="{@docRoot}/uncopyright.html">This code is in the public domain.</a>
 *
 * @version 1.0
 */
public class MaxForwardsParser extends HeaderParser {
    /** Default constructor. */
    MaxForwardsParser() {}
    
    /**
     * Constructor with initial content length header string.
     * @param contentLength initial contentlength header
     */
    public MaxForwardsParser(String contentLength) {
        super(contentLength);
    }
    
    /**
     * Constructor with initial lexer engine.
     * @param lexer initial lexer engine
     */
    protected MaxForwardsParser(Lexer lexer) {
        super(lexer);
    }
    
    /**
     * Invokes parser for maximum forwards header field.
     * @return the parsed maximum forwards header
     * @exception ParseException if a parsing error occurs
     */
    public Header parse() throws ParseException {
        if (debug) dbg_enter("MaxForwardsParser.enter");
        try {
            MaxForwardsHeader maxForwards = new MaxForwardsHeader();
            headerName(TokenTypes.MAX_FORWARDS);
            String number = this.lexer.number();
            maxForwards.setMaxForwards(Integer.parseInt(number));
            this.lexer.SPorHT();
            this.lexer.match('\n');
            return maxForwards;
        } catch (IllegalArgumentException ex) {
            throw createParseException(ex.getMessage());
        } finally {
            if (debug) dbg_leave("MaxForwardsParser.leave");
        }
    }
}
