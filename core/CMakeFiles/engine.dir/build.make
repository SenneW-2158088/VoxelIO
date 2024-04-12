# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.27.4/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.27.4/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/zenneh/Documents/University/2023-2024/Computer Graphics/voxelio"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/zenneh/Documents/University/2023-2024/Computer Graphics/voxelio"

# Include any dependencies generated for this target.
include core/CMakeFiles/engine.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include core/CMakeFiles/engine.dir/compiler_depend.make

# Include the progress variables for this target.
include core/CMakeFiles/engine.dir/progress.make

# Include the compile flags for this target's objects.
include core/CMakeFiles/engine.dir/flags.make

core/CMakeFiles/engine.dir/engine/GameEngine.cpp.o: core/CMakeFiles/engine.dir/flags.make
core/CMakeFiles/engine.dir/engine/GameEngine.cpp.o: core/engine/GameEngine.cpp
core/CMakeFiles/engine.dir/engine/GameEngine.cpp.o: core/CMakeFiles/engine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/zenneh/Documents/University/2023-2024/Computer Graphics/voxelio/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object core/CMakeFiles/engine.dir/engine/GameEngine.cpp.o"
	cd "/Users/zenneh/Documents/University/2023-2024/Computer Graphics/voxelio/core" && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT core/CMakeFiles/engine.dir/engine/GameEngine.cpp.o -MF CMakeFiles/engine.dir/engine/GameEngine.cpp.o.d -o CMakeFiles/engine.dir/engine/GameEngine.cpp.o -c "/Users/zenneh/Documents/University/2023-2024/Computer Graphics/voxelio/core/engine/GameEngine.cpp"

core/CMakeFiles/engine.dir/engine/GameEngine.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/engine.dir/engine/GameEngine.cpp.i"
	cd "/Users/zenneh/Documents/University/2023-2024/Computer Graphics/voxelio/core" && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/zenneh/Documents/University/2023-2024/Computer Graphics/voxelio/core/engine/GameEngine.cpp" > CMakeFiles/engine.dir/engine/GameEngine.cpp.i

core/CMakeFiles/engine.dir/engine/GameEngine.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/engine.dir/engine/GameEngine.cpp.s"
	cd "/Users/zenneh/Documents/University/2023-2024/Computer Graphics/voxelio/core" && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/zenneh/Documents/University/2023-2024/Computer Graphics/voxelio/core/engine/GameEngine.cpp" -o CMakeFiles/engine.dir/engine/GameEngine.cpp.s

# Object files for target engine
engine_OBJECTS = \
"CMakeFiles/engine.dir/engine/GameEngine.cpp.o"

# External object files for target engine
engine_EXTERNAL_OBJECTS =

core/libengine.a: core/CMakeFiles/engine.dir/engine/GameEngine.cpp.o
core/libengine.a: core/CMakeFiles/engine.dir/build.make
core/libengine.a: core/CMakeFiles/engine.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir="/Users/zenneh/Documents/University/2023-2024/Computer Graphics/voxelio/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libengine.a"
	cd "/Users/zenneh/Documents/University/2023-2024/Computer Graphics/voxelio/core" && $(CMAKE_COMMAND) -P CMakeFiles/engine.dir/cmake_clean_target.cmake
	cd "/Users/zenneh/Documents/University/2023-2024/Computer Graphics/voxelio/core" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/engine.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
core/CMakeFiles/engine.dir/build: core/libengine.a
.PHONY : core/CMakeFiles/engine.dir/build

core/CMakeFiles/engine.dir/clean:
	cd "/Users/zenneh/Documents/University/2023-2024/Computer Graphics/voxelio/core" && $(CMAKE_COMMAND) -P CMakeFiles/engine.dir/cmake_clean.cmake
.PHONY : core/CMakeFiles/engine.dir/clean

core/CMakeFiles/engine.dir/depend:
	cd "/Users/zenneh/Documents/University/2023-2024/Computer Graphics/voxelio" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/zenneh/Documents/University/2023-2024/Computer Graphics/voxelio" "/Users/zenneh/Documents/University/2023-2024/Computer Graphics/voxelio/core" "/Users/zenneh/Documents/University/2023-2024/Computer Graphics/voxelio" "/Users/zenneh/Documents/University/2023-2024/Computer Graphics/voxelio/core" "/Users/zenneh/Documents/University/2023-2024/Computer Graphics/voxelio/core/CMakeFiles/engine.dir/DependInfo.cmake" "--color=$(COLOR)"
.PHONY : core/CMakeFiles/engine.dir/depend

