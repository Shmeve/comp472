cmake_minimum_required(VERSION 3.6)

project(comp472)

# Include the project cmake module directory
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Set CMake library and binary output directories to /lib and /bin
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Use C++14
set(CMAKE_CXX_STANDARD 14)

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

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

include_directories(lib ${INCLUDE_DIRS})
add_subdirectory(src)
