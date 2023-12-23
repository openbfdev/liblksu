cmake_minimum_required(VERSION 3.9)
project(lksu VERSION "1.0" LANGUAGES C)

include(GNUInstallDirs)
include(CheckIncludeFiles)
include(CheckCXXSymbolExists)
include(CheckFunctionExists)
include(CheckCSourceCompiles)

set(LKSU_HEADERS
    ${PROJECT_SOURCE_DIR}/include/lksu.h
)

set(LKSU_SOURCES
    ${PROJECT_SOURCE_DIR}/src/lksu.c
)

set(LKSU_LIBRARY
    ${LKSU_HEADERS}
    ${LKSU_SOURCES}
)


add_library(lksu_static STATIC ${LKSU_LIBRARY})
add_library(lksu_shared SHARED ${LKSU_LIBRARY})

add_library(lksu ALIAS lksu_shared)


install(FILES
    ${PROJECT_SOURCE_DIR}/include/lksu.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
