/** ***************************************************************************
 * @file avg.c boxcar (moving average) digital filter
 * @author Douglas Hiranaka
 * @date   February, 2020
 * @section LICENSE
 * @copyright (c) 2020 Douglas Hiranaka
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
 * @version
 * 07.11.14 DKH initial
 *****************************************************************************/

#include <stdlib.h>

#include <stdint.h>
#include <string.h> // memset()
#include "StdAfx.h"
#include "avg.h"

/** ****************************************************************************
 * @name: init_average set up a boxcar (moving average) filter, set defaults 
 * and pick size of the delay buffer and allocate the memory for the buffer.
 * @brief
 * @param [in] avg - pointer to new data in struct
 * @param [in] circular - pointer to the circular buffer stucture
 * @retval N/A
 * @details An array must be allocated then pointed to through the movingBuffer
 *        struct passed in here:
 * movingAverage sensorBoxcar;
 * uint32_t      values[TEST_DATA_SIZE] = {0};
 * movingBuffer  sensorData;
 * sensorData.size = TEST_DATA_SIZE;
 * sensorData.values = values;
 * init_average(&sensorBoxcar, &sensorData);
 ******************************************************************************/
void init_average(movingAverage *avg,
                  movingBuffer  *circular)
{
	avg->startIndex =  0;
	avg->index      =  0;
	avg->size       =  circular->size;
	avg->sum        =  0;
	avg->average    =  0.0f;
	avg->oldValues  =  circular->values;
	memset(avg->oldValues, 0, sizeof(uint32_t) * avg->size);
}

/** ****************************************************************************
 * @name: calc_average A boxcar (moving average) filter to smooth data
 * @brief
 * @param [out] avg - data structure with the sum and delay buffer
 * @param [in] rawData - new single value in
 * @retval N/A
 ******************************************************************************/
void calc_average(movingAverage *avg,
	              uint32_t       rawData)
{
    if (avg->startIndex >= (avg->size - 1) ) {
        avg->sum -= avg->oldValues[avg->index]; ///< subtract the oldest value
    } else {
        avg->startIndex++; ///< increment until the buffer is full at start
    }
    avg->sum += rawData; ///< update with new data
    avg->oldValues[avg->index] = rawData; ///< push the new raw value over the oldest

    avg->index++; ///< circular buffer index
    avg->index %= avg->size; ///< roll over

    avg->average = (float)avg->sum / (float)avg->startIndex;
}

#if UNIT_TEST
void unitTestAvg() {
#define TEST_VALUES_SIZE 8
  movingAverage sensorBoxcar;
  uint32_t      values[TEST_DATA_SIZE] = {0}; // circular buffer - 5 test values
  movingBuffer  sensorData;
  uint32_t      testValues[TEST_VALUES_SIZE] = {7, 5, 3, 2, 6, 1, 4,};
  
  sensorData.size = TEST_DATA_SIZE;
  sensorData.values = values; // pass in the cirular buffer

  init_average(&sensorBoxcar, &sensorData);

  printf("sensorBoxcar.startIndex = %d (0)\n", sensorBoxcar.startIndex);
  printf("sensorBoxcar.index = %d (0)\n", sensorBoxcar.index);
  printf("sensorBoxcar.size = %d (%d)\n", sensorBoxcar.size, sensorData.size);
  printf("sensorBoxcar.sum = %d (0)\n", sensorBoxcar.sum);
  printf("sensorBoxcar.average = %d (0)\n", sensorBoxcar.average);
  printf("sensorBoxcar.oldValues = 0x%x (x%x)\n", sensorBoxcar.oldValues, sensorData.values);

  printf("The average of { ");
  for (int i = 0; i < TEST_VALUES_SIZE; ++i) {
    // lots of tests or checks of the incremental values can go here
    printf("%d ",testValues[i]);
    calc_average(&sensorBoxcar, testValues[i]);
  }
  printf("} is: %f (expected 3.5)\n", sensorBoxcar.average);

}
#endif
