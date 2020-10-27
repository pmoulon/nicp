cmake_minimum_required(VERSION 3.5)

project(nicp CXX)

# Optionally compiling part.
option(BUILD_NICP_VIEWER "enables NICP viewer" false)
option(BUILD_NICP_TEST "enables NICP test" false)

# The library prefix.
set(LIB_PREFIX nicp)

set(nicp_C_FLAGS)
set(nicp_CXX_FLAGS)

# Default built type.
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif(NOT CMAKE_BUILD_TYPE)

# Postfix, based on type.
set(CMAKE_DEBUG_POSTFIX "_d" CACHE STRING "postfix applied to debug build of libraries")
set(CMAKE_RELEASE_POSTFIX "" CACHE STRING "postfix applied to release build of libraries")
set(CMAKE_RELWITHDEBINFO_POSTFIX "_rd" CACHE STRING "postfix applied to release-with-debug-information libraries")
set(CMAKE_MINSIZEREL_POSTFIX "_s" CACHE STRING "postfix applied to minimium-size-build libraries")

# Work out the postfix; required where we use OUTPUT_NAME.
if(CMAKE_BUILD_TYPE MATCHES Release)
  set(EXE_POSTFIX)
  set(CMAKE_CXX_FLAGS_RELEASE "")
elseif(CMAKE_BUILD_TYPE MATCHES Debug)
  set(EXE_POSTFIX ${CMAKE_DEBUG_POSTFIX})
elseif(CMAKE_BUILD_TYPE MATCHES RelWithDebInfo)
  set(EXE_POSTFIX ${CMAKE_RELWITHDEBINFO_POSTFIX})
elseif(CMAKE_BUILD_TYPE MATCHES MinSizeRel)
  set(EXE_POSTFIX ${CMAKE_MINSIZEREL_POSTFIX})
endif(CMAKE_BUILD_TYPE MATCHES Release)

# Set the output directory for the build executables and libraries.
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${nicp_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${nicp_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${nicp_SOURCE_DIR}/bin)

# Set search directory for looking for our custom CMake scripts to look for Eigen3.
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${nicp_SOURCE_DIR}/cmake_modules)

add_definitions(-DUNIX)
message(STATUS "Compiling on Unix")

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -msse4.2 -fopenmp -std=gnu++17")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3 -msse4.2 -fopenmp")
set(nicp_C_FLAGS "${nicp_C_FLAGS} -Wall -W")
set(nicp_CXX_FLAGS "${nicp_CXX_FLAGS} -Wall -W")

# Specifying compiler flags.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${nicp_CXX_FLAGS}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${nicp_C_FLAGS}")

# Find Eigen3.
find_package(Eigen3 3.2.0 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

# Find Flann.
find_package(Flann REQUIRED)
include_directories(${FLANN_INCLUDE_DIR})
link_directories(${FLANN_LIBRARY})

# Find OpenMP.
find_package(OpenMP)
if(OPENMP_FOUND)
 set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
 set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS} -D_NICP_USE_OPENMP_ -DEIGEN_DONT_PARALLELIZE")
 set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif(OPENMP_FOUND)

# Find OpenCV.
find_package(OpenCV 3.2.0 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# Set up the top-level include directories.
include_directories(${nicp_SOURCE_DIR})

if(BUILD_NICP_VIEWER)
  # OpenGL is used in the draw actions for the different types, as well as for creating the GUI itself.
  find_package(OpenGL REQUIRED)
  include_directories(${OPENGL_INCLUDE})
  message(STATUS "Compiling with OpenGL support")

  # Find Qt5.
  find_package(Qt5 COMPONENTS Core Xml OpenGL Gui Widgets REQUIRED)
  include_directories(
    ${Qt5Core_INCLUDE_DIRS} ${Qt5Xml_INCLUDE_DIRS} ${Qt5Gui_INCLUDE_DIRS}
    ${Qt5Widgets_INCLUDE_DIRS} ${Qt5OpenGL_INCLUDE_DIRS}
  )
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

  # For building the GUI.
  find_package(QGLViewer REQUIRED)
  include_directories(${QGLVIEWER_INCLUDE_DIR})
endif(BUILD_NICP_VIEWER)

# Include the subdirectories.
add_subdirectory(core)
