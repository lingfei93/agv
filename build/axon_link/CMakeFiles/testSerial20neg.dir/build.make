# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/eee/lingfei_ws/agv/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/eee/lingfei_ws/agv/build

# Include any dependencies generated for this target.
include axon_link/CMakeFiles/testSerial20neg.dir/depend.make

# Include the progress variables for this target.
include axon_link/CMakeFiles/testSerial20neg.dir/progress.make

# Include the compile flags for this target's objects.
include axon_link/CMakeFiles/testSerial20neg.dir/flags.make

axon_link/CMakeFiles/testSerial20neg.dir/src/testSerial20neg.cpp.o: axon_link/CMakeFiles/testSerial20neg.dir/flags.make
axon_link/CMakeFiles/testSerial20neg.dir/src/testSerial20neg.cpp.o: /home/eee/lingfei_ws/agv/src/axon_link/src/testSerial20neg.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/eee/lingfei_ws/agv/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object axon_link/CMakeFiles/testSerial20neg.dir/src/testSerial20neg.cpp.o"
	cd /home/eee/lingfei_ws/agv/build/axon_link && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/testSerial20neg.dir/src/testSerial20neg.cpp.o -c /home/eee/lingfei_ws/agv/src/axon_link/src/testSerial20neg.cpp

axon_link/CMakeFiles/testSerial20neg.dir/src/testSerial20neg.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testSerial20neg.dir/src/testSerial20neg.cpp.i"
	cd /home/eee/lingfei_ws/agv/build/axon_link && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/eee/lingfei_ws/agv/src/axon_link/src/testSerial20neg.cpp > CMakeFiles/testSerial20neg.dir/src/testSerial20neg.cpp.i

axon_link/CMakeFiles/testSerial20neg.dir/src/testSerial20neg.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testSerial20neg.dir/src/testSerial20neg.cpp.s"
	cd /home/eee/lingfei_ws/agv/build/axon_link && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/eee/lingfei_ws/agv/src/axon_link/src/testSerial20neg.cpp -o CMakeFiles/testSerial20neg.dir/src/testSerial20neg.cpp.s

axon_link/CMakeFiles/testSerial20neg.dir/src/testSerial20neg.cpp.o.requires:

.PHONY : axon_link/CMakeFiles/testSerial20neg.dir/src/testSerial20neg.cpp.o.requires

axon_link/CMakeFiles/testSerial20neg.dir/src/testSerial20neg.cpp.o.provides: axon_link/CMakeFiles/testSerial20neg.dir/src/testSerial20neg.cpp.o.requires
	$(MAKE) -f axon_link/CMakeFiles/testSerial20neg.dir/build.make axon_link/CMakeFiles/testSerial20neg.dir/src/testSerial20neg.cpp.o.provides.build
.PHONY : axon_link/CMakeFiles/testSerial20neg.dir/src/testSerial20neg.cpp.o.provides

axon_link/CMakeFiles/testSerial20neg.dir/src/testSerial20neg.cpp.o.provides.build: axon_link/CMakeFiles/testSerial20neg.dir/src/testSerial20neg.cpp.o


# Object files for target testSerial20neg
testSerial20neg_OBJECTS = \
"CMakeFiles/testSerial20neg.dir/src/testSerial20neg.cpp.o"

# External object files for target testSerial20neg
testSerial20neg_EXTERNAL_OBJECTS =

/home/eee/lingfei_ws/agv/devel/lib/axon_link/testSerial20neg: axon_link/CMakeFiles/testSerial20neg.dir/src/testSerial20neg.cpp.o
/home/eee/lingfei_ws/agv/devel/lib/axon_link/testSerial20neg: axon_link/CMakeFiles/testSerial20neg.dir/build.make
/home/eee/lingfei_ws/agv/devel/lib/axon_link/testSerial20neg: /home/eee/lingfei_ws/agv/devel/lib/libcereal_port.so
/home/eee/lingfei_ws/agv/devel/lib/axon_link/testSerial20neg: /opt/ros/kinetic/lib/libtf.so
/home/eee/lingfei_ws/agv/devel/lib/axon_link/testSerial20neg: /opt/ros/kinetic/lib/libtf2_ros.so
/home/eee/lingfei_ws/agv/devel/lib/axon_link/testSerial20neg: /opt/ros/kinetic/lib/libactionlib.so
/home/eee/lingfei_ws/agv/devel/lib/axon_link/testSerial20neg: /opt/ros/kinetic/lib/libmessage_filters.so
/home/eee/lingfei_ws/agv/devel/lib/axon_link/testSerial20neg: /opt/ros/kinetic/lib/libroscpp.so
/home/eee/lingfei_ws/agv/devel/lib/axon_link/testSerial20neg: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
/home/eee/lingfei_ws/agv/devel/lib/axon_link/testSerial20neg: /usr/lib/x86_64-linux-gnu/libboost_signals.so
/home/eee/lingfei_ws/agv/devel/lib/axon_link/testSerial20neg: /opt/ros/kinetic/lib/libxmlrpcpp.so
/home/eee/lingfei_ws/agv/devel/lib/axon_link/testSerial20neg: /opt/ros/kinetic/lib/libtf2.so
/home/eee/lingfei_ws/agv/devel/lib/axon_link/testSerial20neg: /opt/ros/kinetic/lib/libroscpp_serialization.so
/home/eee/lingfei_ws/agv/devel/lib/axon_link/testSerial20neg: /opt/ros/kinetic/lib/librosconsole.so
/home/eee/lingfei_ws/agv/devel/lib/axon_link/testSerial20neg: /opt/ros/kinetic/lib/librosconsole_log4cxx.so
/home/eee/lingfei_ws/agv/devel/lib/axon_link/testSerial20neg: /opt/ros/kinetic/lib/librosconsole_backend_interface.so
/home/eee/lingfei_ws/agv/devel/lib/axon_link/testSerial20neg: /usr/lib/x86_64-linux-gnu/liblog4cxx.so
/home/eee/lingfei_ws/agv/devel/lib/axon_link/testSerial20neg: /usr/lib/x86_64-linux-gnu/libboost_regex.so
/home/eee/lingfei_ws/agv/devel/lib/axon_link/testSerial20neg: /opt/ros/kinetic/lib/librostime.so
/home/eee/lingfei_ws/agv/devel/lib/axon_link/testSerial20neg: /opt/ros/kinetic/lib/libcpp_common.so
/home/eee/lingfei_ws/agv/devel/lib/axon_link/testSerial20neg: /usr/lib/x86_64-linux-gnu/libboost_system.so
/home/eee/lingfei_ws/agv/devel/lib/axon_link/testSerial20neg: /usr/lib/x86_64-linux-gnu/libboost_thread.so
/home/eee/lingfei_ws/agv/devel/lib/axon_link/testSerial20neg: /usr/lib/x86_64-linux-gnu/libboost_chrono.so
/home/eee/lingfei_ws/agv/devel/lib/axon_link/testSerial20neg: /usr/lib/x86_64-linux-gnu/libboost_date_time.so
/home/eee/lingfei_ws/agv/devel/lib/axon_link/testSerial20neg: /usr/lib/x86_64-linux-gnu/libboost_atomic.so
/home/eee/lingfei_ws/agv/devel/lib/axon_link/testSerial20neg: /usr/lib/x86_64-linux-gnu/libpthread.so
/home/eee/lingfei_ws/agv/devel/lib/axon_link/testSerial20neg: /usr/lib/x86_64-linux-gnu/libconsole_bridge.so
/home/eee/lingfei_ws/agv/devel/lib/axon_link/testSerial20neg: axon_link/CMakeFiles/testSerial20neg.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/eee/lingfei_ws/agv/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable /home/eee/lingfei_ws/agv/devel/lib/axon_link/testSerial20neg"
	cd /home/eee/lingfei_ws/agv/build/axon_link && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/testSerial20neg.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
axon_link/CMakeFiles/testSerial20neg.dir/build: /home/eee/lingfei_ws/agv/devel/lib/axon_link/testSerial20neg

.PHONY : axon_link/CMakeFiles/testSerial20neg.dir/build

axon_link/CMakeFiles/testSerial20neg.dir/requires: axon_link/CMakeFiles/testSerial20neg.dir/src/testSerial20neg.cpp.o.requires

.PHONY : axon_link/CMakeFiles/testSerial20neg.dir/requires

axon_link/CMakeFiles/testSerial20neg.dir/clean:
	cd /home/eee/lingfei_ws/agv/build/axon_link && $(CMAKE_COMMAND) -P CMakeFiles/testSerial20neg.dir/cmake_clean.cmake
.PHONY : axon_link/CMakeFiles/testSerial20neg.dir/clean

axon_link/CMakeFiles/testSerial20neg.dir/depend:
	cd /home/eee/lingfei_ws/agv/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/eee/lingfei_ws/agv/src /home/eee/lingfei_ws/agv/src/axon_link /home/eee/lingfei_ws/agv/build /home/eee/lingfei_ws/agv/build/axon_link /home/eee/lingfei_ws/agv/build/axon_link/CMakeFiles/testSerial20neg.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : axon_link/CMakeFiles/testSerial20neg.dir/depend
