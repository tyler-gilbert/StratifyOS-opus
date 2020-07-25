cmake_minimum_required (VERSION 3.6)

#[[

cmake -P build.cmake

Options

SKIP_LIB Don't pull or build any libraries
SKIP_INSTALL Don't Install libraries (just build - not installed by default)
CLEAN_ALL Clean all projects before building
SKIP_PULL Don't pull, just build
INCLUDE_LINK Build desktop interface libraries
INCLUDE_QT Build QT based interface libraries
INCLUDE_PRIVATE Build private libraries (only available for premium subsribers)
INCLUD_APP Pull and build application samples
INCLUDE_BSP Pull and build BSP sample projects
GIT_STATUS Show status all all git repos (SKIP_PULL and SKIP_BUILD)
]]#

# Grab the SDK location
if(NOT DEFINED SOS_SDK_PATH)
	if(DEFINED ENV{SOS_SDK_PATH})
		set(SOS_SDK_PATH $ENV{SOS_SDK_PATH})
	elseif( ${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Darwin" )
		message(WARNING "default SDK locations are deprecated")
		set(SOS_SDK_PATH /Applications/StratifyLabs-SDK)
	elseif( ${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Windows" )
		message(WARNING "default SDK locations are deprecated")
		set(SOS_SDK_PATH C:/StratifyLabs-SDK)
	elseif( ${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Linux" )
		message(WARNING "default SDK locations are deprecated")
		set(SOS_SDK_PATH /StratifyLabs-SDK)
	endif()
endif()
if(NOT DEFINED SOS_SDK_PATH)
	message(FATAL_ERROR "Please set environment variable SOS_SDK_PATH to location of the StratifyLabs-SDK directory")
endif()
set(SOS_TOOLCHAIN_CMAKE_PATH ${SOS_SDK_PATH}/Tools/gcc/arm-none-eabi/cmake)

include(${SOS_TOOLCHAIN_CMAKE_PATH}/sos-sdk.cmake)

sos_sdk_clone_or_pull(${CMAKE_SOURCE_DIR}/opus https://github.com/xiph/opus.git ${CMAKE_SOURCE_DIR})

file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/build)

