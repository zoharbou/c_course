# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.9

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2017.3.3\bin\cmake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2017.3.3\bin\cmake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\Users\Dell\Desktop\semester b\c course\ex2\c_course\ex2"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\Dell\Desktop\semester b\c course\ex2\c_course\ex2\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/forTest.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/forTest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/forTest.dir/flags.make

CMakeFiles/forTest.dir/fortest.c.obj: CMakeFiles/forTest.dir/flags.make
CMakeFiles/forTest.dir/fortest.c.obj: ../fortest.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\Dell\Desktop\semester b\c course\ex2\c_course\ex2\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/forTest.dir/fortest.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\forTest.dir\fortest.c.obj   -c "C:\Users\Dell\Desktop\semester b\c course\ex2\c_course\ex2\fortest.c"

CMakeFiles/forTest.dir/fortest.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/forTest.dir/fortest.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "C:\Users\Dell\Desktop\semester b\c course\ex2\c_course\ex2\fortest.c" > CMakeFiles\forTest.dir\fortest.c.i

CMakeFiles/forTest.dir/fortest.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/forTest.dir/fortest.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "C:\Users\Dell\Desktop\semester b\c course\ex2\c_course\ex2\fortest.c" -o CMakeFiles\forTest.dir\fortest.c.s

CMakeFiles/forTest.dir/fortest.c.obj.requires:

.PHONY : CMakeFiles/forTest.dir/fortest.c.obj.requires

CMakeFiles/forTest.dir/fortest.c.obj.provides: CMakeFiles/forTest.dir/fortest.c.obj.requires
	$(MAKE) -f CMakeFiles\forTest.dir\build.make CMakeFiles/forTest.dir/fortest.c.obj.provides.build
.PHONY : CMakeFiles/forTest.dir/fortest.c.obj.provides

CMakeFiles/forTest.dir/fortest.c.obj.provides.build: CMakeFiles/forTest.dir/fortest.c.obj


# Object files for target forTest
forTest_OBJECTS = \
"CMakeFiles/forTest.dir/fortest.c.obj"

# External object files for target forTest
forTest_EXTERNAL_OBJECTS =

forTest.exe: CMakeFiles/forTest.dir/fortest.c.obj
forTest.exe: CMakeFiles/forTest.dir/build.make
forTest.exe: CMakeFiles/forTest.dir/linklibs.rsp
forTest.exe: CMakeFiles/forTest.dir/objects1.rsp
forTest.exe: CMakeFiles/forTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\Users\Dell\Desktop\semester b\c course\ex2\c_course\ex2\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable forTest.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\forTest.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/forTest.dir/build: forTest.exe

.PHONY : CMakeFiles/forTest.dir/build

CMakeFiles/forTest.dir/requires: CMakeFiles/forTest.dir/fortest.c.obj.requires

.PHONY : CMakeFiles/forTest.dir/requires

CMakeFiles/forTest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\forTest.dir\cmake_clean.cmake
.PHONY : CMakeFiles/forTest.dir/clean

CMakeFiles/forTest.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\Users\Dell\Desktop\semester b\c course\ex2\c_course\ex2" "C:\Users\Dell\Desktop\semester b\c course\ex2\c_course\ex2" "C:\Users\Dell\Desktop\semester b\c course\ex2\c_course\ex2\cmake-build-debug" "C:\Users\Dell\Desktop\semester b\c course\ex2\c_course\ex2\cmake-build-debug" "C:\Users\Dell\Desktop\semester b\c course\ex2\c_course\ex2\cmake-build-debug\CMakeFiles\forTest.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/forTest.dir/depend
