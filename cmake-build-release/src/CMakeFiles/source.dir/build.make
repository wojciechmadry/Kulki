# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = /home/wojtek/clion/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/wojtek/clion/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/wojtek/Desktop/Git/kulki

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/wojtek/Desktop/Git/kulki/cmake-build-release

# Include any dependencies generated for this target.
include src/CMakeFiles/source.dir/depend.make
# Include the progress variables for this target.
include src/CMakeFiles/source.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/source.dir/flags.make

# Object files for target source
source_OBJECTS =

# External object files for target source
source_EXTERNAL_OBJECTS =

src/libsource.a: src/CMakeFiles/source.dir/build.make
src/libsource.a: src/CMakeFiles/source.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/wojtek/Desktop/Git/kulki/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Linking CXX static library libsource.a"
	cd /home/wojtek/Desktop/Git/kulki/cmake-build-release/src && $(CMAKE_COMMAND) -P CMakeFiles/source.dir/cmake_clean_target.cmake
	cd /home/wojtek/Desktop/Git/kulki/cmake-build-release/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/source.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/source.dir/build: src/libsource.a
.PHONY : src/CMakeFiles/source.dir/build

src/CMakeFiles/source.dir/clean:
	cd /home/wojtek/Desktop/Git/kulki/cmake-build-release/src && $(CMAKE_COMMAND) -P CMakeFiles/source.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/source.dir/clean

src/CMakeFiles/source.dir/depend:
	cd /home/wojtek/Desktop/Git/kulki/cmake-build-release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/wojtek/Desktop/Git/kulki /home/wojtek/Desktop/Git/kulki/src /home/wojtek/Desktop/Git/kulki/cmake-build-release /home/wojtek/Desktop/Git/kulki/cmake-build-release/src /home/wojtek/Desktop/Git/kulki/cmake-build-release/src/CMakeFiles/source.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/source.dir/depend

