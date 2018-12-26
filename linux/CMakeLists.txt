cmake_minimum_required(VERSION 2.8)
project(Spider-Man)

#add_definitions("-DBOOST_LOG_DYN_LINK")

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -finstrument-functions -fPIC")

if (${ARCH} STREQUAL "x86_64")
    add_definitions(-DARCH_X86_64)
    set(PATH_THIRD_PARTY ${PROJECT_SOURCE_DIR}/../third_party/x86)
    set(PATH_MOBVOI_LIB ${PROJECT_SOURCE_DIR}/libs/x86)
elseif(${ARCH} STREQUAL "aarch64")
    add_definitions(-DARCH_AARCH64)
    set(PATH_THIRD_PARTY ${PROJECT_SOURCE_DIR}/../third_party/aarch64)
    set(PATH_MOBVOI_LIB ${PROJECT_SOURCE_DIR}/libs/aarch64)
endif()

set(PATH_UTILS ${PROJECT_SOURCE_DIR}/utils)
set(PATH_PLATFORM ${PROJECT_SOURCE_DIR}/platform)
set(PATH_LINK_SCRIPT ${PROJECT_SOURCE_DIR}/link_script)
set(INC_DIR
    ${PROJECT_SOURCE_DIR}/.
    ${PROJECT_SOURCE_DIR}/src
    ${PATH_THIRD_PARTY}/include/
    ${PATH_UTILS}/.
    )
include_directories(${INC_DIR})

link_directories(${PATH_THIRD_PARTY}/lib ${PATH_MOBVOI_LIB})

# fake jpcc audio lib
set(PATH_MIB3_AUDIOLIB_DIR ${PATH_PLATFORM}/jpcc/src)

add_library(jpcc.sds.audiostream SHARED ${PATH_MIB3_AUDIOLIB_DIR}/fake_mib3audio_lib.cc)
target_link_libraries(jpcc.sds.audiostream)

set(UTILS_SRCS
    ${PATH_UTILS}/log/blog/blog.cc
    ${PATH_UTILS}/log/log_impl/log_impl.cc
    ${PATH_UTILS}/config/speech_config.cc
    )
add_library(utils SHARED ${UTILS_SRCS})
target_link_libraries(utils boost_log boost_program_options)

# network recorder
set(NETWORK_RECORDER_SRCS
    ${PROJECT_SOURCE_DIR}/src/recorder/recorder.cc
    ${PROJECT_SOURCE_DIR}/src/recorder/events.cc
    ${PROJECT_SOURCE_DIR}/src/ecnr/ecnr.cc
    )
add_library(network_recorder SHARED ${NETWORK_RECORDER_SRCS})
target_link_libraries(network_recorder utils boost_filesystem mobvoidsp mobvoisdk jpcc.sds.audiostream)

set(CNS_HU_RECORDER_SRCS
    ${PROJECT_SOURCE_DIR}/src/main.cc
    )
add_executable(Spider-Man ${CNS_HU_RECORDER_SRCS})
set_target_properties(Spider-Man PROPERTIES LINK_FLAGS -Wl,--version-script=${PATH_LINK_SCRIPT}/Spider_Man.map)
target_link_libraries(Spider-Man utils boost_system network_recorder boost_log pthread)


# install executable files

INSTALL (TARGETS Spider-Man RUNTIME DESTINATION ./)

# install library

if (${OS} STREQUAL "embedded_linux")
    INSTALL (TARGETS "jpcc.sds.audiostream" LIBRARY DESTINATION ./)
endif()

INSTALL (FILES ${PATH_MOBVOI_LIB}/libmobvoidsp.so DESTINATION ./)
INSTALL (FILES ${PATH_MOBVOI_LIB}/libmobvoisdk.so DESTINATION ./)
INSTALL (DIRECTORY ${PATH_UTILS}/dsp_config DESTINATION ./simulator)
INSTALL (FILES ${PATH_UTILS}/config/parameter_config.conf DESTINATION ./simulator)

set(INSTALL_LIBS
    utils
    network_recorder
    )

INSTALL (TARGETS ${INSTALL_LIBS} LIBRARY DESTINATION ./)


