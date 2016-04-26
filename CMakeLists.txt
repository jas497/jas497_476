# define things
cmake_minimum_required(VERSION 2.8.3)
project(jas497_476)

# Gazebo compiles a bit differently from the rest of ROS
find_package(gazebo REQUIRED)

# We need to link to many external libraries.  These lines do that.
include_directories(${GAZEBO_INCLUDE_DIRS})
link_directories(${GAZEBO_LIBRARY_DIRS})
list(APPEND CMAKE_CXX_FLAGS "${GAZEBO_CXX_FLAGS}")

# Compile our code.  Note that plugins are considered libraries, not standalone
# executables.  Syntax: add_library(foo, SHARED, code.cpp) will produce
# libfoo.so from the file code.cpp (the SHARED flag means "make a shared object
# (.so) file", which is the Unix analogue of Windows DLLs).
add_library(jasGazeboGripper SHARED src/main.cpp)

# Do the linking
target_link_libraries(jasGazeboGripper ${GAZEBO_LIBRARIES})

# Needed for Gazebo v6 and higher for compatibility.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GAZEBO_CXX_FLAGS}")
