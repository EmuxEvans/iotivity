# root path of each PC.
ROOT_DIR=/home/choi/tmp/test/upload/Iotivity-Candidate

# oic-service folder path.
FD_SSM=${ROOT_DIR}/oic-service/SoftSensorManager
FD_SAMPLEAPP=${FD_SSM}/SampleApp
FD_BUILD=${FD_SSM}/build

# outputs directory path.
OUTPUTS_DIR=${FD_BUILD}/arduino/release

# ioc-resource folder path.
# IOT_BASE=${FD_SAMPLEAPP}/arduino/oic-resource_a
IOT_BASE=${ROOT_DIR}/oic-resource
IOT_MAKE_PATH=${IOT_BASE}
IOT_RELEASE=${IOT_BASE}/release/obj
IOT_CSDK_RELEASE=${IOT_BASE}/csdk/release

# SoftSensorManager makefile path
MAKE_01=${FD_SAMPLEAPP}/arduino/THSensorApp/build

MAKE_LIST=${MAKE_01}
