# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /mnt/c/Users/louis/Documents/uni/repos/202122_INFOF209_5/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/louis/Documents/uni/repos/202122_INFOF209_5/src/cmake-build-debug

# Include any dependencies generated for this target.
include client/CMakeFiles/client.dir/depend.make

# Include the progress variables for this target.
include client/CMakeFiles/client.dir/progress.make

# Include the compile flags for this target's objects.
include client/CMakeFiles/client.dir/flags.make

client/CMakeFiles/client.dir/main.cpp.o: client/CMakeFiles/client.dir/flags.make
client/CMakeFiles/client.dir/main.cpp.o: ../client/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/louis/Documents/uni/repos/202122_INFOF209_5/src/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object client/CMakeFiles/client.dir/main.cpp.o"
	cd /mnt/c/Users/louis/Documents/uni/repos/202122_INFOF209_5/src/cmake-build-debug/client && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/client.dir/main.cpp.o -c /mnt/c/Users/louis/Documents/uni/repos/202122_INFOF209_5/src/client/main.cpp

client/CMakeFiles/client.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client.dir/main.cpp.i"
	cd /mnt/c/Users/louis/Documents/uni/repos/202122_INFOF209_5/src/cmake-build-debug/client && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/louis/Documents/uni/repos/202122_INFOF209_5/src/client/main.cpp > CMakeFiles/client.dir/main.cpp.i

client/CMakeFiles/client.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client.dir/main.cpp.s"
	cd /mnt/c/Users/louis/Documents/uni/repos/202122_INFOF209_5/src/cmake-build-debug/client && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/louis/Documents/uni/repos/202122_INFOF209_5/src/client/main.cpp -o CMakeFiles/client.dir/main.cpp.s

# Object files for target client
client_OBJECTS = \
"CMakeFiles/client.dir/main.cpp.o"

# External object files for target client
client_EXTERNAL_OBJECTS =

client/client: client/CMakeFiles/client.dir/main.cpp.o
client/client: client/CMakeFiles/client.dir/build.make
client/client: _deps/ftxui-build/ftxui-screen.a
client/client: _deps/ftxui-build/ftxui-dom.a
client/client: _deps/ftxui-build/ftxui-component.a
client/client: client/libquoridor_client.a
client/client: _deps/ftxui-build/ftxui-dom.a
client/client: _deps/ftxui-build/ftxui-screen.a
client/client: client/CMakeFiles/client.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/louis/Documents/uni/repos/202122_INFOF209_5/src/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable client"
	cd /mnt/c/Users/louis/Documents/uni/repos/202122_INFOF209_5/src/cmake-build-debug/client && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/client.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
client/CMakeFiles/client.dir/build: client/client

.PHONY : client/CMakeFiles/client.dir/build

client/CMakeFiles/client.dir/clean:
	cd /mnt/c/Users/louis/Documents/uni/repos/202122_INFOF209_5/src/cmake-build-debug/client && $(CMAKE_COMMAND) -P CMakeFiles/client.dir/cmake_clean.cmake
.PHONY : client/CMakeFiles/client.dir/clean

client/CMakeFiles/client.dir/depend:
	cd /mnt/c/Users/louis/Documents/uni/repos/202122_INFOF209_5/src/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/louis/Documents/uni/repos/202122_INFOF209_5/src /mnt/c/Users/louis/Documents/uni/repos/202122_INFOF209_5/src/client /mnt/c/Users/louis/Documents/uni/repos/202122_INFOF209_5/src/cmake-build-debug /mnt/c/Users/louis/Documents/uni/repos/202122_INFOF209_5/src/cmake-build-debug/client /mnt/c/Users/louis/Documents/uni/repos/202122_INFOF209_5/src/cmake-build-debug/client/CMakeFiles/client.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : client/CMakeFiles/client.dir/depend

