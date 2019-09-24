

#Add sources to the project
include(${CMAKE_SOURCE_DIR}/sources.cmake)
file(GLOB_RECURSE HEADER_SOURCES ${CMAKE_SOURCE_DIR}/opus/include/*)

list(APPEND SOS_SOURCELIST
	${CMAKE_SOURCE_DIR}/Opus.hpp
	${CMAKE_SOURCE_DIR}/Opus.cpp
	${CMAKE_SOURCE_DIR}/opus_api_declaration.h
	${CMAKE_SOURCE_DIR}/opus_api.h)

set(SOS_OPTION "api")
set(SOS_CONFIG release)
set(SOS_BUILD_FLAGS -mlong-calls)
include(${SOS_TOOLCHAIN_CMAKE_PATH}/sos-lib-std.cmake)

list(APPEND SOS_SOURCELIST
    ${SILK_SOURCES} 
    ${CELT_SOURCES} 
    ${OPUS_SOURCES} 
		${HEADER_SOURCES})

set(SOS_OPTION "kernel")
set(SOS_CONFIG release)
set(SOS_BUILD_FLAGS "")
include(${SOS_TOOLCHAIN_CMAKE_PATH}/sos-lib-std.cmake)

set(SOS_OPTION "")
set(SOS_CONFIG release)
set(SOS_BUILD_FLAGS -mlong-calls)
include(${SOS_TOOLCHAIN_CMAKE_PATH}/sos-lib-std.cmake)
