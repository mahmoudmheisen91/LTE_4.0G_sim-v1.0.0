/*-------------------------------------------------------------------------*/
/**
  @file     statics.c
  @author   Mahmoud Mheisen
  @date     Feb 2015
  @version  $Revision: 1.0 $
  @brief    Contain simple statics function which defined in resource.h

  LTE Simulator Project: Undergraduate project for simulation the physical
  layer of fourth generation wirless communication standerd (LTE).
*/
/*--------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/
#include "resources.h"


/*---------------------------------------------------------------------------
                            Function codes
 ---------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/**
  @brief    find minimum value in double pointer array
  @param    data double array input
  @param    length length of array
  @return   minimum value in array

  Examples:

  @code
  double value = min(data, 23);
  @endcode

 */
/*--------------------------------------------------------------------------*/

double min(double *data, int length) {
    // first value in the array:
    double result = data[0];

    // search for minimum:
    int i;
    for(i = 0; i < length; i++) {
        if(data[i] < result)
            result = data[i];
    }

    // return
    return result;
}

/*-------------------------------------------------------------------------*/
/**
  @brief    find maximum value in double pointer array
  @param    data double array input
  @param    length length of array
  @return   maximum value in array

  Examples:

  @code
  double value = max(data, 23);
  @endcode

 */
/*--------------------------------------------------------------------------*/

double max(double *data, int length) {
    // first value in the array:
    double result = data[0];

    // search for maximum:
    int i;
    for(i = 0; i < length; i++) {
        if(data[i] > result)
            result = data[i];
    }

    // return:
    return result;
}

/*-------------------------------------------------------------------------*/
/**
  @brief    find mean value of double pointer array
  @param    data double array input
  @param    length length of array
  @return   mean value of array

  Examples:

  @code
  double value = mean(data, 23);
  @endcode

 */
/*--------------------------------------------------------------------------*/

double mean(double *data, int length) {
    // initial sum:
    double result = 0.0;

    // summation:
    int i;
    for(i = 0; i < length; i++)
        result += data[i];

    // return:
    return result / length;
}

/*-------------------------------------------------------------------------*/
/**
  @brief    find variance value of double pointer array
  @param    data double array input
  @param    length length of array
  @return   variance of array

  Examples:

  @code
  double value = variance(data, 23);
  @endcode

 */
/*--------------------------------------------------------------------------*/

double variance(double *data, int length) {
    // inital sum:
    double result = 0;

    // fin mean of array:
    double data_mean = mean(data, length);

    // variance math:
    int i;
    for(i = 0; i < length; i++)
        result += pow((data[i] - data_mean), 2);

    // return:
    return result / (length - 1);
}
