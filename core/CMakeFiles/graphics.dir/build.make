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
include core/CMakeFiles/graphics.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include core/CMakeFiles/graphics.dir/compiler_depend.make

# Include the progress variables for this target.
include core/CMakeFiles/graphics.dir/progress.make

# Include the compile flags for this target's objects.
include core/CMakeFiles/graphics.dir/flags.make

core/CMakeFiles/graphics.dir/graphics/Mesh.cpp.o: core/CMakeFiles/graphics.dir/flags.make
core/CMakeFiles/graphics.dir/graphics/Mesh.cpp.o: core/graphics/Mesh.cpp
core/CMakeFiles/graphics.dir/graphics/Mesh.cpp.o: core/CMakeFiles/graphics.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/zenneh/Documents/University/2023-2024/Computer Graphics/voxelio/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object core/CMakeFiles/graphics.dir/graphics/Mesh.cpp.o"
	cd "/Users/zenneh/Documents/University/2023-2024/Computer Graphics/voxelio/core" && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT core/CMakeFiles/graphics.dir/graphics/Mesh.cpp.o -MF CMakeFiles/graphics.dir/graphics/Mesh.cpp.o.d -o CMakeFiles/graphics.dir/graphics/Mesh.cpp.o -c "/Users/zenneh/Documents/University/2023-2024/Computer Graphics/voxelio/core/graphics/Mesh.cpp"

core/CMakeFiles/graphics.dir/graphics/Mesh.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/graphics.dir/graphics/Mesh.cpp.i"
	cd "/Users/zenneh/Documents/University/2023-2024/Computer Graphics/voxelio/core" && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/zenneh/Documents/University/2023-2024/Computer Graphics/voxelio/core/graphics/Mesh.cpp" > CMakeFiles/graphics.dir/graphics/Mesh.cpp.i

core/CMakeFiles/graphics.dir/graphics/Mesh.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/graphics.dir/graphics/Mesh.cpp.s"
	cd "/Users/zenneh/Documents/University/2023-2024/Computer Graphics/voxelio/core" && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/zenneh/Documents/University/2023-2024/Computer Graphics/voxelio/core/graphics/Mesh.cpp" -o CMakeFiles/graphics.dir/graphics/Mesh.cpp.s

core/CMakeFiles/graphics.dir/graphics/Shader.cpp.o: core/CMakeFiles/graphics.dir/flags.make
core/CMakeFiles/graphics.dir/graphics/Shader.cpp.o: core/graphics/Shader.cpp
core/CMakeFiles/graphics.dir/graphics/Shader.cpp.o: core/CMakeFiles/graphics.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/zenneh/Documents/University/2023-2024/Computer Graphics/voxelio/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object core/CMakeFiles/graphics.dir/graphics/Shader.cpp.o"
	cd "/Users/zenneh/Documents/University/2023-2024/Computer Graphics/voxelio/core" && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT core/CMakeFiles/graphics.dir/graphics/Shader.cpp.o -MF CMakeFiles/graphics.dir/graphics/Shader.cpp.o.d -o CMakeFiles/graphics.dir/graphics/Shader.cpp.o -c "/Users/zenneh/Documents/University/2023-2024/Computer Graphics/voxelio/core/graphics/Shader.cpp"

core/CMakeFiles/graphics.dir/graphics/Shader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/graphics.dir/graphics/Shader.cpp.i"
	cd "/Users/zenneh/Documents/University/2023-2024/Computer Graphics/voxelio/core" && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/zenneh/Documents/University/2023-2024/Computer Graphics/voxelio/core/graphics/Shader.cpp" > CMakeFiles/graphics.dir/graphics/Shader.cpp.i

core/CMakeFiles/graphics.dir/graphics/Shader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/graphics.dir/graphics/Shader.cpp.s"
	cd "/Users/zenneh/Documents/University/2023-2024/Computer Graphics/voxelio/core" && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/zenneh/Documents/University/2023-2024/Computer Graphics/voxelio/core/graphics/Shader.cpp" -o CMakeFiles/graphics.dir/graphics/Shader.cpp.s

core/CMakeFiles/graphics.dir/graphics/Uniform.cpp.o: core/CMakeFiles/graphics.dir/flags.make
core/CMakeFiles/graphics.dir/graphics/Uniform.cpp.o: core/graphics/Uniform.cpp
core/CMakeFiles/graphics.dir/graphics/Uniform.cpp.o: core/CMakeFiles/graphics.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/zenneh/Documents/University/2023-2024/Computer Graphics/voxelio/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object core/CMakeFiles/graphics.dir/graphics/Uniform.cpp.o"
	cd "/Users/zenneh/Documents/University/2023-2024/Computer Graphics/voxelio/core" && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT core/CMakeFiles/graphics.dir/graphics/Uniform.cpp.o -MF CMakeFiles/graphics.dir/graphics/Uniform.cpp.o.d -o CMakeFiles/graphics.dir/graphics/Uniform.cpp.o -c "/Users/zenneh/Documents/University/2023-2024/Computer Graphics/voxelio/core/graphics/Uniform.cpp"

core/CMakeFiles/graphics.dir/graphics/Uniform.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/graphics.dir/graphics/Uniform.cpp.i"
	cd "/Users/zenneh/Documents/University/2023-2024/Computer Graphics/voxelio/core" && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/zenneh/Documents/University/2023-2024/Computer Graphics/voxelio/core/graphics/Uniform.cpp" > CMakeFiles/graphics.dir/graphics/Uniform.cpp.i

core/CMakeFiles/graphics.dir/graphics/Uniform.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/graphics.dir/graphics/Uniform.cpp.s"
	cd "/Users/zenneh/Documents/University/2023-2024/Computer Graphics/voxelio/core" && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/zenneh/Documents/University/2023-2024/Computer Graphics/voxelio/core/graphics/Uniform.cpp" -o CMakeFiles/graphics.dir/graphics/Uniform.cpp.s

core/CMakeFiles/graphics.dir/graphics/Texture.cpp.o: core/CMakeFiles/graphics.dir/flags.make
core/CMakeFiles/graphics.dir/graphics/Texture.cpp.o: core/graphics/Texture.cpp
core/CMakeFiles/graphics.dir/graphics/Texture.cpp.o: core/CMakeFiles/graphics.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/zenneh/Documents/University/2023-2024/Computer Graphics/voxelio/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object core/CMakeFiles/graphics.dir/graphics/Texture.cpp.o"
	cd "/Users/zenneh/Documents/University/2023-2024/Computer Graphics/voxelio/core" && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT core/CMakeFiles/graphics.dir/graphics/Texture.cpp.o -MF CMakeFiles/graphics.dir/graphics/Texture.cpp.o.d -o CMakeFiles/graphics.dir/graphics/Texture.cpp.o -c "/Users/zenneh/Documents/University/2023-2024/Computer Graphics/voxelio/core/graphics/Texture.cpp"

core/CMakeFiles/graphics.dir/graphics/Texture.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/graphics.dir/graphics/Texture.cpp.i"
	cd "/Users/zenneh/Documents/University/2023-2024/Computer Graphics/voxelio/core" && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/zenneh/Documents/University/2023-2024/Computer Graphics/voxelio/core/graphics/Texture.cpp" > CMakeFiles/graphics.dir/graphics/Texture.cpp.i

core/CMakeFiles/graphics.dir/graphics/Texture.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/graphics.dir/graphics/Texture.cpp.s"
	cd "/Users/zenneh/Documents/University/2023-2024/Computer Graphics/voxelio/core" && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/zenneh/Documents/University/2023-2024/Computer Graphics/voxelio/core/graphics/Texture.cpp" -o CMakeFiles/graphics.dir/graphics/Texture.cpp.s

# Object files for target graphics
graphics_OBJECTS = \
"CMakeFiles/graphics.dir/graphics/Mesh.cpp.o" \
"CMakeFiles/graphics.dir/graphics/Shader.cpp.o" \
"CMakeFiles/graphics.dir/graphics/Uniform.cpp.o" \
"CMakeFiles/graphics.dir/graphics/Texture.cpp.o"

# External object files for target graphics
graphics_EXTERNAL_OBJECTS =

core/libgraphics.a: core/CMakeFiles/graphics.dir/graphics/Mesh.cpp.o
core/libgraphics.a: core/CMakeFiles/graphics.dir/graphics/Shader.cpp.o
core/libgraphics.a: core/CMakeFiles/graphics.dir/graphics/Uniform.cpp.o
core/libgraphics.a: core/CMakeFiles/graphics.dir/graphics/Texture.cpp.o
core/libgraphics.a: core/CMakeFiles/graphics.dir/build.make
core/libgraphics.a: core/CMakeFiles/graphics.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir="/Users/zenneh/Documents/University/2023-2024/Computer Graphics/voxelio/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX static library libgraphics.a"
	cd "/Users/zenneh/Documents/University/2023-2024/Computer Graphics/voxelio/core" && $(CMAKE_COMMAND) -P CMakeFiles/graphics.dir/cmake_clean_target.cmake
	cd "/Users/zenneh/Documents/University/2023-2024/Computer Graphics/voxelio/core" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/graphics.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
core/CMakeFiles/graphics.dir/build: core/libgraphics.a
.PHONY : core/CMakeFiles/graphics.dir/build

core/CMakeFiles/graphics.dir/clean:
	cd "/Users/zenneh/Documents/University/2023-2024/Computer Graphics/voxelio/core" && $(CMAKE_COMMAND) -P CMakeFiles/graphics.dir/cmake_clean.cmake
.PHONY : core/CMakeFiles/graphics.dir/clean

core/CMakeFiles/graphics.dir/depend:
	cd "/Users/zenneh/Documents/University/2023-2024/Computer Graphics/voxelio" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/zenneh/Documents/University/2023-2024/Computer Graphics/voxelio" "/Users/zenneh/Documents/University/2023-2024/Computer Graphics/voxelio/core" "/Users/zenneh/Documents/University/2023-2024/Computer Graphics/voxelio" "/Users/zenneh/Documents/University/2023-2024/Computer Graphics/voxelio/core" "/Users/zenneh/Documents/University/2023-2024/Computer Graphics/voxelio/core/CMakeFiles/graphics.dir/DependInfo.cmake" "--color=$(COLOR)"
.PHONY : core/CMakeFiles/graphics.dir/depend

