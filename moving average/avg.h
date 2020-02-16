/** ***************************************************************************
 * @file avg.h boxcar (moving average) digital filter
 * @author Douglas Hiranaka
 * @date   Februarry, 2020
 * @copyright (c) 2020 All Rights Reserved.
 * @section LICENSE
 * Copyright 2020 Douglas Hiranaka
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this  
 * software and associated documentation files (the "Software"), to deal in the Software 
 * without restriction, including without limitation the rights to use, copy, modify,  
 * merge, publish, distribute, sublicense, and/or sell copies of the Software, and to 
 * permit persons to whom the Software is furnished to do so, subject to the following 
 * conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies 
 * or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,  
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT  
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF 
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR 
 * THE USE OR OTHER DEALINGS IN THE SOFTWARE. 
 * @brief 02.15.120 intial DKH
 *****************************************************************************/

#ifndef _AVG_H
#define _AVG_H

//#include <cctype>
#include <string>
#include <cstdlib>
#include <stdint.h>

#define UNIT_TEST 1

/** @brief Rolling avereage "boxcar" filter
  moving average structure including pointer to the circular buffer
  its size, the running sum and current average. The function pushes on a
  new value poping off the oldest in a circular buffer summing the rawData
  subtracting off the last value before it is popped off providing a window
  the size of the circular buffer for the running average.
*/

#define TEST_DATA_SIZE 5 ///< this can be any value or name. 

typedef struct {
	uint32_t size;       ///< length of the circular buffer
	uint32_t *oldValues; ///< raw data to be avereraged
	uint32_t index;      ///< head/tail pointer for new data
	uint32_t startIndex; ///< index for loading the first time
	uint32_t sum;        ///< running total of the contents of the buffer
	float    average;    ///< running average of the contents of the buffer
} movingAverage;

/**
  @brief standardized rolling buffer, similar to a circular buffer but does not have or
  need a tail pointer. The oldest value is over written deleting the value replacing it
  with the new value.
*/
typedef struct {
	uint32_t size;    ///< number of items in the buffer
	uint32_t *values; ///< pointer to the payload array
} movingBuffer;

void init_average(movingAverage *avg,  movingBuffer *circular);
void calc_average(movingAverage *avg,
				  uint32_t      rawData);

#if UNIT_TEST  
  void unitTestAvg();
#endif

#endif /* _AVG_H */