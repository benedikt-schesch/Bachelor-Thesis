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
CMAKE_BINARY_DIR = "/Users/benediktschesch/OneDrive - ETH Zurich/MyEnv/GNN_RL/.dacecache/dot_product_pure_float/build"

# Include any dependencies generated for this target.
include CMakeFiles/dot_product_pure_float.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/dot_product_pure_float.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/dot_product_pure_float.dir/flags.make

CMakeFiles/dot_product_pure_float.dir/Users/benediktschesch/OneDrive_-_ETH_Zurich/MyEnv/GNN_RL/.dacecache/dot_product_pure_float/src/cpu/dot_product_pure_float.cpp.o: CMakeFiles/dot_product_pure_float.dir/flags.make
CMakeFiles/dot_product_pure_float.dir/Users/benediktschesch/OneDrive_-_ETH_Zurich/MyEnv/GNN_RL/.dacecache/dot_product_pure_float/src/cpu/dot_product_pure_float.cpp.o: /Users/benediktschesch/OneDrive\ -\ ETH\ Zurich/MyEnv/GNN_RL/.dacecache/dot_product_pure_float/src/cpu/dot_product_pure_float.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/benediktschesch/OneDrive - ETH Zurich/MyEnv/GNN_RL/.dacecache/dot_product_pure_float/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/dot_product_pure_float.dir/Users/benediktschesch/OneDrive_-_ETH_Zurich/MyEnv/GNN_RL/.dacecache/dot_product_pure_float/src/cpu/dot_product_pure_float.cpp.o"
	/usr/local/bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/dot_product_pure_float.dir/Users/benediktschesch/OneDrive_-_ETH_Zurich/MyEnv/GNN_RL/.dacecache/dot_product_pure_float/src/cpu/dot_product_pure_float.cpp.o -c "/Users/benediktschesch/OneDrive - ETH Zurich/MyEnv/GNN_RL/.dacecache/dot_product_pure_float/src/cpu/dot_product_pure_float.cpp"

CMakeFiles/dot_product_pure_float.dir/Users/benediktschesch/OneDrive_-_ETH_Zurich/MyEnv/GNN_RL/.dacecache/dot_product_pure_float/src/cpu/dot_product_pure_float.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/dot_product_pure_float.dir/Users/benediktschesch/OneDrive_-_ETH_Zurich/MyEnv/GNN_RL/.dacecache/dot_product_pure_float/src/cpu/dot_product_pure_float.cpp.i"
	/usr/local/bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/benediktschesch/OneDrive - ETH Zurich/MyEnv/GNN_RL/.dacecache/dot_product_pure_float/src/cpu/dot_product_pure_float.cpp" > CMakeFiles/dot_product_pure_float.dir/Users/benediktschesch/OneDrive_-_ETH_Zurich/MyEnv/GNN_RL/.dacecache/dot_product_pure_float/src/cpu/dot_product_pure_float.cpp.i

CMakeFiles/dot_product_pure_float.dir/Users/benediktschesch/OneDrive_-_ETH_Zurich/MyEnv/GNN_RL/.dacecache/dot_product_pure_float/src/cpu/dot_product_pure_float.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/dot_product_pure_float.dir/Users/benediktschesch/OneDrive_-_ETH_Zurich/MyEnv/GNN_RL/.dacecache/dot_product_pure_float/src/cpu/dot_product_pure_float.cpp.s"
	/usr/local/bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/benediktschesch/OneDrive - ETH Zurich/MyEnv/GNN_RL/.dacecache/dot_product_pure_float/src/cpu/dot_product_pure_float.cpp" -o CMakeFiles/dot_product_pure_float.dir/Users/benediktschesch/OneDrive_-_ETH_Zurich/MyEnv/GNN_RL/.dacecache/dot_product_pure_float/src/cpu/dot_product_pure_float.cpp.s

# Object files for target dot_product_pure_float
dot_product_pure_float_OBJECTS = \
"CMakeFiles/dot_product_pure_float.dir/Users/benediktschesch/OneDrive_-_ETH_Zurich/MyEnv/GNN_RL/.dacecache/dot_product_pure_float/src/cpu/dot_product_pure_float.cpp.o"

# External object files for target dot_product_pure_float
dot_product_pure_float_EXTERNAL_OBJECTS =

libdot_product_pure_float.dylib: CMakeFiles/dot_product_pure_float.dir/Users/benediktschesch/OneDrive_-_ETH_Zurich/MyEnv/GNN_RL/.dacecache/dot_product_pure_float/src/cpu/dot_product_pure_float.cpp.o
libdot_product_pure_float.dylib: CMakeFiles/dot_product_pure_float.dir/build.make
libdot_product_pure_float.dylib: CMakeFiles/dot_product_pure_float.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/benediktschesch/OneDrive - ETH Zurich/MyEnv/GNN_RL/.dacecache/dot_product_pure_float/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library libdot_product_pure_float.dylib"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/dot_product_pure_float.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/dot_product_pure_float.dir/build: libdot_product_pure_float.dylib

.PHONY : CMakeFiles/dot_product_pure_float.dir/build

CMakeFiles/dot_product_pure_float.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/dot_product_pure_float.dir/cmake_clean.cmake
.PHONY : CMakeFiles/dot_product_pure_float.dir/clean

CMakeFiles/dot_product_pure_float.dir/depend:
	cd "/Users/benediktschesch/OneDrive - ETH Zurich/MyEnv/GNN_RL/.dacecache/dot_product_pure_float/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/benediktschesch/MyEnv/lib/python3.7/site-packages/dace/codegen /Users/benediktschesch/MyEnv/lib/python3.7/site-packages/dace/codegen "/Users/benediktschesch/OneDrive - ETH Zurich/MyEnv/GNN_RL/.dacecache/dot_product_pure_float/build" "/Users/benediktschesch/OneDrive - ETH Zurich/MyEnv/GNN_RL/.dacecache/dot_product_pure_float/build" "/Users/benediktschesch/OneDrive - ETH Zurich/MyEnv/GNN_RL/.dacecache/dot_product_pure_float/build/CMakeFiles/dot_product_pure_float.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/dot_product_pure_float.dir/depend
