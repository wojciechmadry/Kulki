# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.19

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
CMAKE_BINARY_DIR = F:\kulki\cmake-build-debug32b

# Include any dependencies generated for this target.
include CMakeFiles/Kulki.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Kulki.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Kulki.dir/flags.make

CMakeFiles/Kulki.dir/main.cpp.obj: CMakeFiles/Kulki.dir/flags.make
CMakeFiles/Kulki.dir/main.cpp.obj: CMakeFiles/Kulki.dir/includes_CXX.rsp
CMakeFiles/Kulki.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=F:\kulki\cmake-build-debug32b\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Kulki.dir/main.cpp.obj"
	C:\msys64\mingw64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Kulki.dir\main.cpp.obj -c F:\kulki\main.cpp

CMakeFiles/Kulki.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Kulki.dir/main.cpp.i"
	C:\msys64\mingw64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E F:\kulki\main.cpp > CMakeFiles\Kulki.dir\main.cpp.i

CMakeFiles/Kulki.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Kulki.dir/main.cpp.s"
	C:\msys64\mingw64\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S F:\kulki\main.cpp -o CMakeFiles\Kulki.dir\main.cpp.s

# Object files for target Kulki
Kulki_OBJECTS = \
"CMakeFiles/Kulki.dir/main.cpp.obj"

# External object files for target Kulki
Kulki_EXTERNAL_OBJECTS =

Kulki.exe: CMakeFiles/Kulki.dir/main.cpp.obj
Kulki.exe: CMakeFiles/Kulki.dir/build.make
Kulki.exe: src/libsource.a
Kulki.exe: CMakeFiles/Kulki.dir/linklibs.rsp
Kulki.exe: CMakeFiles/Kulki.dir/objects1.rsp
Kulki.exe: CMakeFiles/Kulki.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=F:\kulki\cmake-build-debug32b\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Kulki.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Kulki.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Kulki.dir/build: Kulki.exe

.PHONY : CMakeFiles/Kulki.dir/build

CMakeFiles/Kulki.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Kulki.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Kulki.dir/clean

CMakeFiles/Kulki.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" F:\kulki F:\kulki F:\kulki\cmake-build-debug32b F:\kulki\cmake-build-debug32b F:\kulki\cmake-build-debug32b\CMakeFiles\Kulki.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Kulki.dir/depend

