# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.17

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

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "F:\CLion\CLion 2020.2.4\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "F:\CLion\CLion 2020.2.4\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = F:\kulki

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = F:\kulki\cmake-build-debug64b

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
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=F:\kulki\cmake-build-debug64b\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Linking CXX static library libsource.a"
	cd /d F:\kulki\cmake-build-debug64b\src && $(CMAKE_COMMAND) -P CMakeFiles\source.dir\cmake_clean_target.cmake
	cd /d F:\kulki\cmake-build-debug64b\src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\source.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/source.dir/build: src/libsource.a

.PHONY : src/CMakeFiles/source.dir/build

src/CMakeFiles/source.dir/clean:
	cd /d F:\kulki\cmake-build-debug64b\src && $(CMAKE_COMMAND) -P CMakeFiles\source.dir\cmake_clean.cmake
.PHONY : src/CMakeFiles/source.dir/clean

src/CMakeFiles/source.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" F:\kulki F:\kulki\src F:\kulki\cmake-build-debug64b F:\kulki\cmake-build-debug64b\src F:\kulki\cmake-build-debug64b\src\CMakeFiles\source.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/source.dir/depend

