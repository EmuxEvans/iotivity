/* ****************************************************************
 *
 * Copyright 2014 Samsung Electronics All Rights Reserved.
 *
 *
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ******************************************************************/

/**
 * @file
 *
 * This file contains common utility function for handling message ques.
 */

#ifndef CA_QUEUEINGTHREAD_H_
#define CA_QUEUEINGTHREAD_H_

#include <stdint.h>

#include "cathreadpool.h"
#include "camutex.h"
#include "uqueue.h"
#include "cacommon.h"
#ifdef __cplusplus
extern "C"
{
#endif

/**Thread function to be invoked**/
typedef void (*CAThreadTask)(void *threadData);

/**Data destroy function**/
typedef void (*CADataDestroyFunction)(void *data, uint32_t size);

typedef struct
{
    /** Thread pool of the thread started **/
    ca_thread_pool_t threadPool;
    /** mutex for synchrnoization **/
    ca_mutex threadMutex;
    /** conditional mutex for synchrnoization **/
    ca_cond threadCond;
    /**Thread function to be invoked**/
    CAThreadTask threadTask;
    /**Data destroy function**/
    CADataDestroyFunction destroy;
    /** Variable to inform the thread to stop **/
    bool isStop;
    /** Que on which the thread is operating. **/
    u_queue_t *dataQueue;
} CAQueueingThread_t;

/**
 * @brief   Initializes the queing thread
 * @param   thread      [IN] thread data for each thread
 * @param   handle      [IN] thread pool handle created
 * @param   task        [IN] function to be called for each data
 * @param   destroy     [IN] function to data destroy
 * @return  CA_STATUS_OK or ERROR CODES ( CAResult_t error codes in cacommon.h)
 */
CAResult_t CAQueueingThreadInitialize(CAQueueingThread_t *thread, ca_thread_pool_t handle,
                                      CAThreadTask task, CADataDestroyFunction destroy);

/**
 * @brief   Starting the queueing thread
 * @param   thread       [IN] thread data that needs to be started
 * @return  CA_STATUS_OK or ERROR CODES ( CAResult_t error codes in cacommon.h)
 */
CAResult_t CAQueueingThreadStart(CAQueueingThread_t *thread);

/**
 * @brief   Add queueing thread data for new thread
 * @param   thread      [IN] thread data for new thread control
 * @param   data        [IN] data that needs to be given for each thread
 * @param   size        [IN] length of the data
 * @return  CA_STATUS_OK or ERROR CODES ( CAResult_t error codes in cacommon.h)
 */
CAResult_t CAQueueingThreadAddData(CAQueueingThread_t *thread, void *data, uint32_t size);

/**
 * @brief   Stopping the queueing thread
 * @param   thread      [IN] thread data that needs to be started
 * @return  CA_STATUS_OK or ERROR CODES ( CAResult_t error codes in cacommon.h)
 */

CAResult_t CAQueueingThreadStop(CAQueueingThread_t *thread);

/**
 * @brief   Terminating  the queing thread
 * @param   thread      [IN] thread data for each thread
 * @return  CA_STATUS_OK or ERROR CODES ( CAResult_t error codes in cacommon.h)
 */

CAResult_t CAQueueingThreadDestroy(CAQueueingThread_t *thread);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif  // CA_QUEUEINGTHREAD_H_

