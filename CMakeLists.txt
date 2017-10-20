cmake_minimum_required(VERSION 3.2)

project(comp472)

# Include the project cmake module directory
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Set CMake library and binary output directories to /lib and /bin
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Use C++11
set(CMAKE_CXX_STANDARD 11)

# Find Curses library
if (WIN32 AND NOT CYGWIN)
    # Win32
    set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} ${CMAKE_SOURCE_DIR}/lib/pdcurses)
    set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} ${CMAKE_SOURCE_DIR}/lib/pdcurses)
    find_package(PDCurses REQUIRED)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
else ()
    # UNIX
    find_package(Curses REQUIRED)
endif (WIN32 AND NOT CYGWIN)

if (PDCURSES_FOUND)
    set(INCLUDE_DIRS ${INCLUDE_DIRS} ${PDCURSES_INCLUDE_DIR})
    set(LIBRARIES ${LIBRARIES} ${PDCURSES_LIBRARIES})
elseif (CURSES_FOUND)
    set(INCLUDE_DIRS ${INCLUDE_DIRS} ${CURSES_INCLUDE_DIRS})
    set(LIBRARIES ${LIBRARIES} ${CURSES_LIBRARIES})
else ()
    message(SEND_ERROR "Could not find Curses library")
endif (PDCURSES_FOUND)

include_directories(${INCLUDE_DIRS})

# Catch library
set(CATCH_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/catch)
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})
enable_testing()

add_subdirectory(src)
add_subdirectory(test)
