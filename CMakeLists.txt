cmake_minimum_required (VERSION 3.6)

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

include(${SOS_TOOLCHAIN_CMAKE_PATH}/sos-variables.cmake)

if( ${SOS_BUILD_CONFIG} STREQUAL arm )
  message(STATUS "Load SOS Lib Toolchain for arm: " ${SOS_TOOLCHAIN_CMAKE_PATH})
  set(CMAKE_TOOLCHAIN_FILE ${SOS_TOOLCHAIN_CMAKE_PATH}/sos-lib-toolchain.cmake)
elseif( ${SOS_BUILD_CONFIG} STREQUAL link )
  set(CMAKE_TOOLCHAIN_FILE ${SOS_TOOLCHAIN_CMAKE_PATH}/link-toolchain.cmake)
endif()

set(SOS_NAME opus)
project(${SOS_NAME} CXX C ASM)

install(DIRECTORY opus/include/ DESTINATION include)
install(FILES
	${CMAKE_SOURCE_DIR}/opus_api.h
	${CMAKE_SOURCE_DIR}/opus_api_declaration.h
	${CMAKE_SOURCE_DIR}/Opus.hpp DESTINATION
	include)

set(SOS_INCLUDE_DIRECTORIES
	opus/include
	opus/celt
	opus/silk/float
	opus/silk
	opus/silk/fixed)

set(SOS_DEFINES OPUS_BUILD)

include( ${CMAKE_SOURCE_DIR}/${SOS_BUILD_CONFIG}.cmake )
