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
CMAKE_SOURCE_DIR = "/cygdrive/e/Github/C/Meh/Meh 1"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/cygdrive/e/Github/C/Meh/Meh 1/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/Meh_1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Meh_1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Meh_1.dir/flags.make

CMakeFiles/Meh_1.dir/emq2.c.o: CMakeFiles/Meh_1.dir/flags.make
CMakeFiles/Meh_1.dir/emq2.c.o: ../emq2.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/cygdrive/e/Github/C/Meh/Meh 1/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Meh_1.dir/emq2.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Meh_1.dir/emq2.c.o   -c "/cygdrive/e/Github/C/Meh/Meh 1/emq2.c"

CMakeFiles/Meh_1.dir/emq2.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Meh_1.dir/emq2.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/cygdrive/e/Github/C/Meh/Meh 1/emq2.c" > CMakeFiles/Meh_1.dir/emq2.c.i

CMakeFiles/Meh_1.dir/emq2.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Meh_1.dir/emq2.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/cygdrive/e/Github/C/Meh/Meh 1/emq2.c" -o CMakeFiles/Meh_1.dir/emq2.c.s

CMakeFiles/Meh_1.dir/client.c.o: CMakeFiles/Meh_1.dir/flags.make
CMakeFiles/Meh_1.dir/client.c.o: ../client.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/cygdrive/e/Github/C/Meh/Meh 1/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/Meh_1.dir/client.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Meh_1.dir/client.c.o   -c "/cygdrive/e/Github/C/Meh/Meh 1/client.c"

CMakeFiles/Meh_1.dir/client.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Meh_1.dir/client.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/cygdrive/e/Github/C/Meh/Meh 1/client.c" > CMakeFiles/Meh_1.dir/client.c.i

CMakeFiles/Meh_1.dir/client.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Meh_1.dir/client.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/cygdrive/e/Github/C/Meh/Meh 1/client.c" -o CMakeFiles/Meh_1.dir/client.c.s

# Object files for target Meh_1
Meh_1_OBJECTS = \
"CMakeFiles/Meh_1.dir/emq2.c.o" \
"CMakeFiles/Meh_1.dir/client.c.o"

# External object files for target Meh_1
Meh_1_EXTERNAL_OBJECTS =

Meh_1.exe: CMakeFiles/Meh_1.dir/emq2.c.o
Meh_1.exe: CMakeFiles/Meh_1.dir/client.c.o
Meh_1.exe: CMakeFiles/Meh_1.dir/build.make
Meh_1.exe: CMakeFiles/Meh_1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/cygdrive/e/Github/C/Meh/Meh 1/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable Meh_1.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Meh_1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Meh_1.dir/build: Meh_1.exe

.PHONY : CMakeFiles/Meh_1.dir/build

CMakeFiles/Meh_1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Meh_1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Meh_1.dir/clean

CMakeFiles/Meh_1.dir/depend:
	cd "/cygdrive/e/Github/C/Meh/Meh 1/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/cygdrive/e/Github/C/Meh/Meh 1" "/cygdrive/e/Github/C/Meh/Meh 1" "/cygdrive/e/Github/C/Meh/Meh 1/cmake-build-debug" "/cygdrive/e/Github/C/Meh/Meh 1/cmake-build-debug" "/cygdrive/e/Github/C/Meh/Meh 1/cmake-build-debug/CMakeFiles/Meh_1.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Meh_1.dir/depend

