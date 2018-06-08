

#Add sources to the project
include(${CMAKE_SOURCE_DIR}/sources.cmake)
file(GLOB_RECURSE HEADER_SOURCES ${CMAKE_SOURCE_DIR}/opus/include/*)
list(APPEND SOS_LIB_SOURCELIST 
    ${SILK_SOURCES} 
    ${CELT_SOURCES} 
    ${OPUS_SOURCES} 
		${HEADER_SOURCES}
		${CMAKE_SOURCE_DIR}/Opus.hpp
		${CMAKE_SOURCE_DIR}/opus_api_declaration.h
		${CMAKE_SOURCE_DIR}/opus_api.h)



set(SOS_LIB_OPTION "kernel")
set(SOS_LIB_TYPE release)
set(SOS_LIB_BUILD_FLAGS "")
include(${SOS_TOOLCHAIN_CMAKE_PATH}/sos-lib-std.cmake)

set(SOS_LIB_OPTION "")
set(SOS_LIB_TYPE release)
set(SOS_LIB_BUILD_FLAGS -mlong-calls)
include(${SOS_TOOLCHAIN_CMAKE_PATH}/sos-lib-std.cmake)
