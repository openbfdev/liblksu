# SPDX-License-Identifier: GPL-2.0-or-later
#
# Copyright(c) 2023 John Sanpe <sanpeqf@gmail.com>
#

cmake_minimum_required(VERSION 3.12)
project(liblksu VERSION 1.0.0 LANGUAGES C)

include(GNUInstallDirs)
include(CheckIncludeFiles)

file(GLOB_RECURSE LKSU_HEADERS
    ${PROJECT_SOURCE_DIR}/include/*.h
)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_BINARY_DIR}/generated)
include(${PROJECT_SOURCE_DIR}/src/build.cmake)

set(LKSU_LIBRARY
    ${LKSU_HEADERS}
    ${LKSU_SOURCES}
)

add_custom_target(
    lksu_kernel
    COMMAND bash -c \"
        install -Dpm 644
        ${PROJECT_SOURCE_DIR}/kernel/src/lksu.h
        ${PROJECT_BINARY_DIR}/generated/lksu/kernel.h
    \"
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)

add_library(lksu_object OBJECT ${LKSU_LIBRARY})
add_library(lksu ALIAS lksu_object)

add_dependencies(lksu_object lksu_kernel)
target_link_libraries(lksu_object bfdev)

if(${CMAKE_PROJECT_NAME} STREQUAL "liblksu")
    add_library(lksu_static STATIC ${LKSU_LIBRARY})
    add_library(lksu_shared SHARED ${LKSU_LIBRARY})

    add_dependencies(lksu_static lksu_kernel)
    add_dependencies(lksu_shared lksu_kernel)

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
        ${PROJECT_BINARY_DIR}/generated/lksu
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )

    install(TARGETS
        lksu_static lksu_shared
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )
endif()
