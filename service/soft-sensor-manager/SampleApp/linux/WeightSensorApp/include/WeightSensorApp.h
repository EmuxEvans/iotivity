/******************************************************************
 *
 * Copyright 2015 Samsung Electronics All Rights Reserved.
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
/*
 * WeightSensorApp.h
 */

#ifndef WEIGHTSENSORAPP_H_
#define WEIGHTSENSORAPP_H_

#include <functional>
#include <pthread.h>
#include "OCPlatform.h"
#include "OCApi.h"

using namespace OC;
using namespace std;

#include <string>
#include <cstdlib>

#define COAP_IP                 "0.0.0.0"
#define COAP_PORT               0
#define COAP_MODE               ModeType::Server
#define COAP_SRVTYPE        ServiceType::InProc

#define COAP_TYPE_NAME          "SSManager.Sensor"

//  testing case
#define INTERVAL_FOR_CHECK          14   // seconds
#define INTERVAL_FOR_MEASUREMENT    3   // seconds
#define INIT_VAL                    33   // default value
#define DIFF_VAL                    0.01   // default value



// Forward declaring the entityHandler

class WeightResource
{
    public:
        /// Access this property from a TB client
//        int m_humid;
//        int m_temp;
        double m_weight;
        std::string m_resourceUri;
        std::vector<std::string> m_resourceTypes;
        std::vector<std::string> m_resourceInterfaces;
        OCResourceHandle m_resourceHandle;
        OCRepresentation m_resourceRep;
        ObservationIds m_interestedObservers;

    public:
        /// Constructor
        WeightResource() :
            m_weight(0), m_resourceHandle(0)
        {
            m_resourceUri = "/Thing_WeightSensor";
            m_resourceTypes.push_back(COAP_TYPE_NAME);
            m_resourceInterfaces.push_back(DEFAULT_INTERFACE);

            printf("Running thing as %s\n", m_resourceUri.c_str());
            m_resourceRep.setUri(m_resourceUri);
            m_resourceRep.setResourceTypes(m_resourceTypes);
            m_resourceRep.setResourceInterfaces(m_resourceInterfaces);
        }

        ~WeightResource()
        {
        }

        void registerResource();

        OCResourceHandle getHandle();

        void setResourceRepresentation(OCRepresentation &rep);

        OCRepresentation getResourceRepresentation();
};

#endif /* THINGRESOURCESERVER_H_ */
