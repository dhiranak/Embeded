/** ***************************************************************************
 * @file static_queue.h static memory generic circular queue 
 * @author Douglas Hiranaka
 * @date   Februarry, 2020
 * @section LICENSE
 * @Copyright 2020 Douglas Hiranaka
 *
 * Permission is hereby granted, free of charge, to any person obtaining a 
 * copy of this software and associated documentation files (the "Software"), 
 * to deal in the Software without restriction, including without limitation 
 * the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 * and/or sell copies of the Software, and to permit persons to whom the 
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included 
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL 
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS 
 * IN THE SOFTWARE.
 *
 * @brief circular queue to avoid dynamic allocation memory issues in an embedded
 *        system. Since the queue is sized at compilation there should be no 
 *        issuse with overflow. The queue is used in comm buffers and for 
 *        memory management for statically defined algorithms.
 * @version 
 * 02.17.120 intial DKH
 *****************************************************************************/
#ifndef _EMBEDDED_H
#define _EMBEDDED_H

#ifndef true
  #define true 1
  #define false !true
#endif

#define SUCCESS 0
#define EMPTY -1

#endif // _EMBEDDED_H
