# SPDX-License-Identifier: GPL-2.0-or-later
#
# Copyright(c) 2023 John Sanpe <sanpeqf@gmail.com>
#

cmake_minimum_required(VERSION 3.12)
project(lksu VERSION 1.0.0 LANGUAGES C)

include(GNUInstallDirs)
include(CheckIncludeFiles)

file(GLOB_RECURSE LKSU_HEADERS
    ${PROJECT_SOURCE_DIR}/include/*.h
)

include_directories(${PROJECT_SOURCE_DIR}/include)
include(${PROJECT_SOURCE_DIR}/src/build.cmake)

set(LKSU_LIBRARY
    ${LKSU_HEADERS}
    ${LKSU_SOURCES}
)

add_library(lksu_object OBJECT ${LKSU_LIBRARY})
target_link_libraries(lksu_object bfdev)
add_library(lksu ALIAS lksu_object)

if(${CMAKE_PROJECT_NAME} STREQUAL "lksu")
    add_library(lksu_static STATIC ${LKSU_LIBRARY})
    add_library(lksu_shared SHARED ${LKSU_LIBRARY})

    target_link_libraries(lksu_static bfdev)
    target_link_libraries(lksu_shared bfdev)

    set_target_properties(lksu_static
        PROPERTIES
        OUTPUT_NAME ${PROJECT_NAME}
        LINKER_LANGUAGE C
    )

    set_target_properties(lksu_shared
        PROPERTIES
        OUTPUT_NAME ${PROJECT_NAME}
        VERSION ${PROJECT_VERSION}
        SOVERSION ${PROJECT_VERSION_MAJOR}
        LINKER_LANGUAGE C
        MACOSX_RPATH ON
    )

    install(DIRECTORY
        ${PROJECT_SOURCE_DIR}/include/lksu
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )

    install(TARGETS
        lksu_static lksu_shared
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )
endif()
