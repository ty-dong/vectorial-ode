# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/jiahuawu/Desktop/ODE_Solver

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/jiahuawu/Desktop/ODE_Solver/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/superlib.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/superlib.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/superlib.dir/flags.make

CMakeFiles/superlib.dir/test.o: CMakeFiles/superlib.dir/flags.make
CMakeFiles/superlib.dir/test.o: ../test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jiahuawu/Desktop/ODE_Solver/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/superlib.dir/test.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/superlib.dir/test.o -c /Users/jiahuawu/Desktop/ODE_Solver/test.cpp

CMakeFiles/superlib.dir/test.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/superlib.dir/test.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/jiahuawu/Desktop/ODE_Solver/test.cpp > CMakeFiles/superlib.dir/test.i

CMakeFiles/superlib.dir/test.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/superlib.dir/test.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/jiahuawu/Desktop/ODE_Solver/test.cpp -o CMakeFiles/superlib.dir/test.s

CMakeFiles/superlib.dir/ODE_System.o: CMakeFiles/superlib.dir/flags.make
CMakeFiles/superlib.dir/ODE_System.o: ../ODE_System.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jiahuawu/Desktop/ODE_Solver/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/superlib.dir/ODE_System.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/superlib.dir/ODE_System.o -c /Users/jiahuawu/Desktop/ODE_Solver/ODE_System.cpp

CMakeFiles/superlib.dir/ODE_System.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/superlib.dir/ODE_System.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/jiahuawu/Desktop/ODE_Solver/ODE_System.cpp > CMakeFiles/superlib.dir/ODE_System.i

CMakeFiles/superlib.dir/ODE_System.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/superlib.dir/ODE_System.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/jiahuawu/Desktop/ODE_Solver/ODE_System.cpp -o CMakeFiles/superlib.dir/ODE_System.s

CMakeFiles/superlib.dir/ODE_solver.o: CMakeFiles/superlib.dir/flags.make
CMakeFiles/superlib.dir/ODE_solver.o: ../ODE_solver.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jiahuawu/Desktop/ODE_Solver/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/superlib.dir/ODE_solver.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/superlib.dir/ODE_solver.o -c /Users/jiahuawu/Desktop/ODE_Solver/ODE_solver.cpp

CMakeFiles/superlib.dir/ODE_solver.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/superlib.dir/ODE_solver.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/jiahuawu/Desktop/ODE_Solver/ODE_solver.cpp > CMakeFiles/superlib.dir/ODE_solver.i

CMakeFiles/superlib.dir/ODE_solver.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/superlib.dir/ODE_solver.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/jiahuawu/Desktop/ODE_Solver/ODE_solver.cpp -o CMakeFiles/superlib.dir/ODE_solver.s

# Object files for target superlib
superlib_OBJECTS = \
"CMakeFiles/superlib.dir/test.o" \
"CMakeFiles/superlib.dir/ODE_System.o" \
"CMakeFiles/superlib.dir/ODE_solver.o"

# External object files for target superlib
superlib_EXTERNAL_OBJECTS =

superlib: CMakeFiles/superlib.dir/test.o
superlib: CMakeFiles/superlib.dir/ODE_System.o
superlib: CMakeFiles/superlib.dir/ODE_solver.o
superlib: CMakeFiles/superlib.dir/build.make
superlib: CMakeFiles/superlib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/jiahuawu/Desktop/ODE_Solver/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable superlib"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/superlib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/superlib.dir/build: superlib

.PHONY : CMakeFiles/superlib.dir/build

CMakeFiles/superlib.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/superlib.dir/cmake_clean.cmake
.PHONY : CMakeFiles/superlib.dir/clean

CMakeFiles/superlib.dir/depend:
	cd /Users/jiahuawu/Desktop/ODE_Solver/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/jiahuawu/Desktop/ODE_Solver /Users/jiahuawu/Desktop/ODE_Solver /Users/jiahuawu/Desktop/ODE_Solver/cmake-build-debug /Users/jiahuawu/Desktop/ODE_Solver/cmake-build-debug /Users/jiahuawu/Desktop/ODE_Solver/cmake-build-debug/CMakeFiles/superlib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/superlib.dir/depend
