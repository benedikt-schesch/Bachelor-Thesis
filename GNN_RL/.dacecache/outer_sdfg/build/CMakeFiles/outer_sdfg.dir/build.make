# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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
CMAKE_COMMAND = "/Users/benediktschesch/OneDrive - ETH Zurich/MyEnv/lib/python3.7/site-packages/cmake/data/CMake.app/Contents/bin/cmake"

# The command to remove a file.
RM = "/Users/benediktschesch/OneDrive - ETH Zurich/MyEnv/lib/python3.7/site-packages/cmake/data/CMake.app/Contents/bin/cmake" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/benediktschesch/MyEnv/lib/python3.7/site-packages/dace/codegen

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/benediktschesch/OneDrive - ETH Zurich/MyEnv/GNN_RL/.dacecache/outer_sdfg/build"

# Include any dependencies generated for this target.
include CMakeFiles/outer_sdfg.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/outer_sdfg.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/outer_sdfg.dir/flags.make

CMakeFiles/outer_sdfg.dir/Users/benediktschesch/OneDrive_-_ETH_Zurich/MyEnv/GNN_RL/.dacecache/outer_sdfg/src/cpu/outer_sdfg.cpp.o: CMakeFiles/outer_sdfg.dir/flags.make
CMakeFiles/outer_sdfg.dir/Users/benediktschesch/OneDrive_-_ETH_Zurich/MyEnv/GNN_RL/.dacecache/outer_sdfg/src/cpu/outer_sdfg.cpp.o: /Users/benediktschesch/OneDrive\ -\ ETH\ Zurich/MyEnv/GNN_RL/.dacecache/outer_sdfg/src/cpu/outer_sdfg.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/benediktschesch/OneDrive - ETH Zurich/MyEnv/GNN_RL/.dacecache/outer_sdfg/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/outer_sdfg.dir/Users/benediktschesch/OneDrive_-_ETH_Zurich/MyEnv/GNN_RL/.dacecache/outer_sdfg/src/cpu/outer_sdfg.cpp.o"
	/usr/local/bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/outer_sdfg.dir/Users/benediktschesch/OneDrive_-_ETH_Zurich/MyEnv/GNN_RL/.dacecache/outer_sdfg/src/cpu/outer_sdfg.cpp.o -c "/Users/benediktschesch/OneDrive - ETH Zurich/MyEnv/GNN_RL/.dacecache/outer_sdfg/src/cpu/outer_sdfg.cpp"

CMakeFiles/outer_sdfg.dir/Users/benediktschesch/OneDrive_-_ETH_Zurich/MyEnv/GNN_RL/.dacecache/outer_sdfg/src/cpu/outer_sdfg.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/outer_sdfg.dir/Users/benediktschesch/OneDrive_-_ETH_Zurich/MyEnv/GNN_RL/.dacecache/outer_sdfg/src/cpu/outer_sdfg.cpp.i"
	/usr/local/bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/benediktschesch/OneDrive - ETH Zurich/MyEnv/GNN_RL/.dacecache/outer_sdfg/src/cpu/outer_sdfg.cpp" > CMakeFiles/outer_sdfg.dir/Users/benediktschesch/OneDrive_-_ETH_Zurich/MyEnv/GNN_RL/.dacecache/outer_sdfg/src/cpu/outer_sdfg.cpp.i

CMakeFiles/outer_sdfg.dir/Users/benediktschesch/OneDrive_-_ETH_Zurich/MyEnv/GNN_RL/.dacecache/outer_sdfg/src/cpu/outer_sdfg.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/outer_sdfg.dir/Users/benediktschesch/OneDrive_-_ETH_Zurich/MyEnv/GNN_RL/.dacecache/outer_sdfg/src/cpu/outer_sdfg.cpp.s"
	/usr/local/bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/benediktschesch/OneDrive - ETH Zurich/MyEnv/GNN_RL/.dacecache/outer_sdfg/src/cpu/outer_sdfg.cpp" -o CMakeFiles/outer_sdfg.dir/Users/benediktschesch/OneDrive_-_ETH_Zurich/MyEnv/GNN_RL/.dacecache/outer_sdfg/src/cpu/outer_sdfg.cpp.s

# Object files for target outer_sdfg
outer_sdfg_OBJECTS = \
"CMakeFiles/outer_sdfg.dir/Users/benediktschesch/OneDrive_-_ETH_Zurich/MyEnv/GNN_RL/.dacecache/outer_sdfg/src/cpu/outer_sdfg.cpp.o"

# External object files for target outer_sdfg
outer_sdfg_EXTERNAL_OBJECTS =

libouter_sdfg.dylib: CMakeFiles/outer_sdfg.dir/Users/benediktschesch/OneDrive_-_ETH_Zurich/MyEnv/GNN_RL/.dacecache/outer_sdfg/src/cpu/outer_sdfg.cpp.o
libouter_sdfg.dylib: CMakeFiles/outer_sdfg.dir/build.make
libouter_sdfg.dylib: CMakeFiles/outer_sdfg.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/benediktschesch/OneDrive - ETH Zurich/MyEnv/GNN_RL/.dacecache/outer_sdfg/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library libouter_sdfg.dylib"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/outer_sdfg.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/outer_sdfg.dir/build: libouter_sdfg.dylib

.PHONY : CMakeFiles/outer_sdfg.dir/build

CMakeFiles/outer_sdfg.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/outer_sdfg.dir/cmake_clean.cmake
.PHONY : CMakeFiles/outer_sdfg.dir/clean

CMakeFiles/outer_sdfg.dir/depend:
	cd "/Users/benediktschesch/OneDrive - ETH Zurich/MyEnv/GNN_RL/.dacecache/outer_sdfg/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/benediktschesch/MyEnv/lib/python3.7/site-packages/dace/codegen /Users/benediktschesch/MyEnv/lib/python3.7/site-packages/dace/codegen "/Users/benediktschesch/OneDrive - ETH Zurich/MyEnv/GNN_RL/.dacecache/outer_sdfg/build" "/Users/benediktschesch/OneDrive - ETH Zurich/MyEnv/GNN_RL/.dacecache/outer_sdfg/build" "/Users/benediktschesch/OneDrive - ETH Zurich/MyEnv/GNN_RL/.dacecache/outer_sdfg/build/CMakeFiles/outer_sdfg.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/outer_sdfg.dir/depend
