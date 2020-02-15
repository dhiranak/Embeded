/** ***************************************************************************
 * @file avg.h boxcar (moving average) digital filter
 * @author Douglas Hiranaka
 * @date   Februarry, 2020
 * @copyright (c) 2020 All Rights Reserved.
 * @section LICENSE
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 * @brief 02.15.120 intial DKH
 *****************************************************************************/

// avg.h : moving buffer and moving average

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