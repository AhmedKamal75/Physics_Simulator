# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ak/Projects/cpp_projects/Physics_Simulator

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ak/Projects/cpp_projects/Physics_Simulator/build

# Include any dependencies generated for this target.
include CMakeFiles/PhysicsSimulator.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/PhysicsSimulator.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/PhysicsSimulator.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/PhysicsSimulator.dir/flags.make

CMakeFiles/PhysicsSimulator.dir/main.cpp.o: CMakeFiles/PhysicsSimulator.dir/flags.make
CMakeFiles/PhysicsSimulator.dir/main.cpp.o: /home/ak/Projects/cpp_projects/Physics_Simulator/main.cpp
CMakeFiles/PhysicsSimulator.dir/main.cpp.o: CMakeFiles/PhysicsSimulator.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/ak/Projects/cpp_projects/Physics_Simulator/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/PhysicsSimulator.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/PhysicsSimulator.dir/main.cpp.o -MF CMakeFiles/PhysicsSimulator.dir/main.cpp.o.d -o CMakeFiles/PhysicsSimulator.dir/main.cpp.o -c /home/ak/Projects/cpp_projects/Physics_Simulator/main.cpp

CMakeFiles/PhysicsSimulator.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/PhysicsSimulator.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ak/Projects/cpp_projects/Physics_Simulator/main.cpp > CMakeFiles/PhysicsSimulator.dir/main.cpp.i

CMakeFiles/PhysicsSimulator.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/PhysicsSimulator.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ak/Projects/cpp_projects/Physics_Simulator/main.cpp -o CMakeFiles/PhysicsSimulator.dir/main.cpp.s

# Object files for target PhysicsSimulator
PhysicsSimulator_OBJECTS = \
"CMakeFiles/PhysicsSimulator.dir/main.cpp.o"

# External object files for target PhysicsSimulator
PhysicsSimulator_EXTERNAL_OBJECTS =

PhysicsSimulator: CMakeFiles/PhysicsSimulator.dir/main.cpp.o
PhysicsSimulator: CMakeFiles/PhysicsSimulator.dir/build.make
PhysicsSimulator: /usr/lib/x86_64-linux-gnu/libsfml-graphics.so.2.6.1
PhysicsSimulator: /usr/lib/x86_64-linux-gnu/libsfml-window.so.2.6.1
PhysicsSimulator: /usr/lib/x86_64-linux-gnu/libsfml-system.so.2.6.1
PhysicsSimulator: CMakeFiles/PhysicsSimulator.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/ak/Projects/cpp_projects/Physics_Simulator/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable PhysicsSimulator"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/PhysicsSimulator.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/PhysicsSimulator.dir/build: PhysicsSimulator
.PHONY : CMakeFiles/PhysicsSimulator.dir/build

CMakeFiles/PhysicsSimulator.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/PhysicsSimulator.dir/cmake_clean.cmake
.PHONY : CMakeFiles/PhysicsSimulator.dir/clean

CMakeFiles/PhysicsSimulator.dir/depend:
	cd /home/ak/Projects/cpp_projects/Physics_Simulator/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ak/Projects/cpp_projects/Physics_Simulator /home/ak/Projects/cpp_projects/Physics_Simulator /home/ak/Projects/cpp_projects/Physics_Simulator/build /home/ak/Projects/cpp_projects/Physics_Simulator/build /home/ak/Projects/cpp_projects/Physics_Simulator/build/CMakeFiles/PhysicsSimulator.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/PhysicsSimulator.dir/depend

