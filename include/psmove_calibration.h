
 /**
 * PS Move API - An interface for the PS Move Motion Controller
 * Copyright (c) 2012 Thomas Perl <m@thp.io>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *    1. Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *
 *    2. Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 **/


#ifndef PSMOVE_CALIBRATION_H
#define PSMOVE_CALIBRATION_H

#ifdef __cplusplus
extern "C" {
#endif

#include "psmove.h"


struct _PSMoveCalibration;
typedef struct _PSMoveCalibration PSMoveCalibration;


/**
 * Create a new calibration object for a given controller
 *
 * move ... a valid PSMove * instance.
 *
 * The calibration will be read from disk if possible. If not (and if the
 * controller is connected via USB), the calibration will be fetched from
 * the controller and saved on-disk for future loading).
 **/
ADDAPI PSMoveCalibration *
ADDCALL psmove_calibration_new(PSMove *move);

/**
 * Check if a calibration object has the necessary calibration data.
 *
 * calibration ... a valid PSMoveCalibration * instance.
 *
 * Returns nonzero if calibration is supported, zero otherwise (and on error).
 **/
ADDAPI int
ADDCALL psmove_calibration_supported(PSMoveCalibration *calibration);

/**
 * Map raw sensor values to calibrated values.
 *
 * calibration ... a valid PSMoveCalibration * instance.
 * input ... pointer to a n-array containing raw values.
 * output ... pointer to a n-array to store output values.
 * n ... 3 (accel only), 6 (accel+gyro) or 9 (accel+gyro+magnetometer)
 *
 * Returns nonzero if calibration was successful, zero if no calibration
 * data is available (pair via USB to load calibration data).
 **/
ADDAPI int
ADDCALL psmove_calibration_map(PSMoveCalibration *calibration,
        int *input, float *output, size_t n);

/**
 * Dump calibration information to stdout.
 *
 * This ist mostly used for debugging. Don't rely on this function to
 * be available in the future - it might be removed.
 **/
ADDAPI void
ADDCALL psmove_calibration_dump(PSMoveCalibration *calibration);

/**
 * Destroy a PSMoveCalibration * instance and free() associated memory.
 **/
ADDAPI void
ADDCALL psmove_calibration_free(PSMoveCalibration *calibration);


#ifdef __cplusplus
}
#endif

#endif