/* *****************************************************************
 *
 * Copyright 2015 Samsung Electronics All Rights Reserved.
 *
 *
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * *****************************************************************/

#ifndef SP_PROVISION_API_H
#define SP_PROVISION_API_H

#include "ocstack.h"
#include "securevirtualresourcetypes.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * Error Code.
 */
typedef enum
{
    SP_RESULT_SUCCESS = 0,
    SP_RESULT_INVALID_PARAM,
    SP_RESULT_MEM_ALLOCATION_FAIL,
    SP_RESULT_INTERNAL_ERROR,
    SP_RESULT_TIMEOUT,
    SP_RESULT_CONN_INVALID_PARAM,
    SP_RESULT_CONN_ADAPTER_NOT_ENABLED,
    SP_RESULT_CONN_SERVER_STARTED_ALREADY,
    SP_RESULT_CONN_SERVER_NOT_STARTED,
    SP_RESULT_CONN_DESTINATION_NOT_REACHABLE,
    SP_RESULT_CONN_SOCKET_OPERATION_FAILED,
    SP_RESULT_CONN_SEND_FAILED,
    SP_RESULT_CONN_RECEVIE_FAILED,
    SP_RESULT_CONN_MEMORY_ALLOC_FAILED,
    SP_RESULT_CONN_REQUEST_TIMEOUT,
    SP_RESULT_CONN_DESTINATION_DISCONNECTED,
    SP_RESULT_CONN_STATUS_FAILED,
    SP_RESULT_CONN_NOT_SUPPORTED

} SPResult;

/**
 * Connectivity types.
 */
typedef enum
{
    SP_CONN_ETHERNET = (1 << 0),
    SP_CONN_WIFI     = (1 << 1),
    SP_CONN_EDR      = (1 << 2),
    SP_CONN_LE       = (1 << 3)
} SPConnectivityType;

typedef struct SPTargetDeviceInfo SPTargetDeviceInfo_t;
typedef struct SPDevInfo SPDevInfo_t;

/**
 * Device Info structure.
 */
struct SPTargetDeviceInfo
{
    OicUuid_t deviceId;                    /**< Device ID. **/
    char ip[DEV_ADDR_SIZE_MAX];            /**< IP address in IPv4 dot-decimal notation. **/
    int port;                              /**< Remote endpoint port. **/
    SPConnectivityType connType;           /**< Connectivity type. **/
    uint16_t *oxm;                         /**< Selected owner transfer methods. **/
    int numberofOxmMethods;                /**< Number of owner transfer methods. **/
    SPTargetDeviceInfo_t *next;            /**< Next pointer. **/
};

/**
 * Owned target device info
 */
struct SPDevInfo
{
    OicUuid_t deviceId;                    /**< Device ID. **/
    char ip[DEV_ADDR_SIZE_MAX];            /**< IP address in IPv4 dot-decimal notation. **/
    int port;                              /**< Remote endpoint port. **/
    SPConnectivityType connType;           /**< Connectivity type. **/
    SPDevInfo_t *next;                     /**< Next pointer. **/
};


/**
 * The function is responsible for discovery of device is current subnet. It will list
 * all the device in subnet which are not yet owned.
 *
 * @param[in] timeout Timeout in seconds, value till which function will listen to responses from
 *                    client before returning the list of devices.
 * @param[in] connType Connectivity type.
 * @param[out] list List of provision candidate devices.
 * @return SP_SUCCESS in case of success and other value otherwise.
 */
SPResult SPProvisioningDiscovery(unsigned short timeout, SPConnectivityType connType,
                                 SPTargetDeviceInfo_t **list);

/**
 * The function is reponsible for following activities:
 * - Send post to /oic/sec/doxm resource with selected ownership transfer method
 * - Get pstat resource of target device to enumerate supported operation modes.
 * - Select and let the target device know the selected methods.
 * - Initiate anon handshake and save owner PSK
 * - Update doxm resource of target device with ownership info.
 *
 * @param[in] timeout  Timeout value in secs till which call REST request will wait before
 *                     returning error in case of 0 function will wait till success.
 * @param[in] deviceId DeviceID of the provisioning tool.
 * @param[in] selectedDeviceInfo Device information.
 * @param[out] context Provisioning context.
 * @return SP_SUCCESS in case of success and other value otherwise.
 */
SPResult SPInitProvisionContext(unsigned short timeout, OicUuid_t *deviceId,
                                const SPTargetDeviceInfo_t *selectedDeviceInfo);

/**
 * Function to send ACL information to resource.
 *
 * @param[in] timeout Timeout value in secs till which call to REST request will wait before
 *                     returning error in case of 0 function will wait till success.
 * @param[in] context Provisioning context.
 * @param[in] acl ACL to provision
 * @return  SP_SUCCESS in case of success and other value otherwise.
 */
SPResult SPProvisionACL(unsigned short timeout, const SPTargetDeviceInfo_t *selectedDeviceInfo,
                        OicSecAcl_t *acl);

/**
 * Function to send credential information to list of resources.
 *
 * @param[in] timeout Timeout value in secs till which call to REST request will wait before
 *                    returning error in case of 0 function will wait till success.
 * @param[in] type Type of credentials to be provisioned to the device.
 * @param[in] pDevList List of devices to be provisioned with the specified credential.
 *
 * @return  SP_SUCCESS in case of success and other value otherwise.
 */
SPResult SPProvisionCredentials(unsigned short timeout, OicSecCredType_t type,
                                const SPDevInfo_t *pDevList);

/**
 * Function to confirm the ACL post request to check  whether its updated at
 * resource server end properly or not.
 *
 * @param[in] timeout Timeout value in seconds till which call REST request will wait
 *                     before returning error in case of 0 function will wait till success.
 * @param[in] context Provisioning context
 * @return  SP_SUCCESS on success
 */
SPResult SPFinalizeProvisioning(unsigned short timeout,
                                const SPTargetDeviceInfo_t *selectedDeviceInfo);

/**
 * Function to end Provisioning session.
 *
 * @return  SP_SUCCESS on success
 */
SPResult SPTerminateProvisioning();

#ifdef __cplusplus
}
#endif
#endif //SP_PROVISION_API_H