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

if( ${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Darwin" )
set(SOS_TOOLCHAIN_CMAKE_PATH /Applications/StratifyLabs-SDK/Tools/gcc/arm-none-eabi/cmake)
endif()
if( ${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Windows" )
  set(SOS_TOOLCHAIN_CMAKE_PATH C:/StratifyLabs-SDK/Tools/gcc/arm-none-eabi/cmake)
endif()

include(${SOS_TOOLCHAIN_CMAKE_PATH}/sos-sdk.cmake)

sos_sdk_clone_or_pull(${CMAKE_SOURCE_DIR}/opus https://github.com/xiph/opus.git ${CMAKE_SOURCE_DIR})

file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/build)

