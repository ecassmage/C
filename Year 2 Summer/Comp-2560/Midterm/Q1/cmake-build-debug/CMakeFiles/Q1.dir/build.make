# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /cygdrive/c/Users/evanm/AppData/Local/JetBrains/CLion2020.3/cygwin_cmake/bin/cmake.exe

# The command to remove a file.
RM = /cygdrive/c/Users/evanm/AppData/Local/JetBrains/CLion2020.3/cygwin_cmake/bin/cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/cygdrive/e/Github/C/Year 2 Summer/Comp-2560/Midterm/Q1"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/cygdrive/e/Github/C/Year 2 Summer/Comp-2560/Midterm/Q1/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/Q1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Q1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Q1.dir/flags.make

CMakeFiles/Q1.dir/main.c.o: CMakeFiles/Q1.dir/flags.make
CMakeFiles/Q1.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/cygdrive/e/Github/C/Year 2 Summer/Comp-2560/Midterm/Q1/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Q1.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Q1.dir/main.c.o   -c "/cygdrive/e/Github/C/Year 2 Summer/Comp-2560/Midterm/Q1/main.c"

CMakeFiles/Q1.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Q1.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/cygdrive/e/Github/C/Year 2 Summer/Comp-2560/Midterm/Q1/main.c" > CMakeFiles/Q1.dir/main.c.i

CMakeFiles/Q1.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Q1.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/cygdrive/e/Github/C/Year 2 Summer/Comp-2560/Midterm/Q1/main.c" -o CMakeFiles/Q1.dir/main.c.s

CMakeFiles/Q1.dir/Flip_Around.c.o: CMakeFiles/Q1.dir/flags.make
CMakeFiles/Q1.dir/Flip_Around.c.o: ../Flip\ Around.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/cygdrive/e/Github/C/Year 2 Summer/Comp-2560/Midterm/Q1/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/Q1.dir/Flip_Around.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Q1.dir/Flip_Around.c.o   -c "/cygdrive/e/Github/C/Year 2 Summer/Comp-2560/Midterm/Q1/Flip Around.c"

CMakeFiles/Q1.dir/Flip_Around.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Q1.dir/Flip_Around.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/cygdrive/e/Github/C/Year 2 Summer/Comp-2560/Midterm/Q1/Flip Around.c" > CMakeFiles/Q1.dir/Flip_Around.c.i

CMakeFiles/Q1.dir/Flip_Around.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Q1.dir/Flip_Around.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/cygdrive/e/Github/C/Year 2 Summer/Comp-2560/Midterm/Q1/Flip Around.c" -o CMakeFiles/Q1.dir/Flip_Around.c.s

# Object files for target Q1
Q1_OBJECTS = \
"CMakeFiles/Q1.dir/main.c.o" \
"CMakeFiles/Q1.dir/Flip_Around.c.o"

# External object files for target Q1
Q1_EXTERNAL_OBJECTS =

Q1.exe: CMakeFiles/Q1.dir/main.c.o
Q1.exe: CMakeFiles/Q1.dir/Flip_Around.c.o
Q1.exe: CMakeFiles/Q1.dir/build.make
Q1.exe: CMakeFiles/Q1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/cygdrive/e/Github/C/Year 2 Summer/Comp-2560/Midterm/Q1/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable Q1.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Q1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Q1.dir/build: Q1.exe

.PHONY : CMakeFiles/Q1.dir/build

CMakeFiles/Q1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Q1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Q1.dir/clean

CMakeFiles/Q1.dir/depend:
	cd "/cygdrive/e/Github/C/Year 2 Summer/Comp-2560/Midterm/Q1/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/cygdrive/e/Github/C/Year 2 Summer/Comp-2560/Midterm/Q1" "/cygdrive/e/Github/C/Year 2 Summer/Comp-2560/Midterm/Q1" "/cygdrive/e/Github/C/Year 2 Summer/Comp-2560/Midterm/Q1/cmake-build-debug" "/cygdrive/e/Github/C/Year 2 Summer/Comp-2560/Midterm/Q1/cmake-build-debug" "/cygdrive/e/Github/C/Year 2 Summer/Comp-2560/Midterm/Q1/cmake-build-debug/CMakeFiles/Q1.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Q1.dir/depend

