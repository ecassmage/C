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
CMAKE_SOURCE_DIR = "/cygdrive/e/Github/C/Year 2 Summer/Comp-2560/Classes/Sockets"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/cygdrive/e/Github/C/Year 2 Summer/Comp-2560/Classes/Sockets/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/Sockets.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Sockets.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Sockets.dir/flags.make

CMakeFiles/Sockets.dir/client.c.o: CMakeFiles/Sockets.dir/flags.make
CMakeFiles/Sockets.dir/client.c.o: ../client.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/cygdrive/e/Github/C/Year 2 Summer/Comp-2560/Classes/Sockets/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Sockets.dir/client.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Sockets.dir/client.c.o   -c "/cygdrive/e/Github/C/Year 2 Summer/Comp-2560/Classes/Sockets/client.c"

CMakeFiles/Sockets.dir/client.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Sockets.dir/client.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/cygdrive/e/Github/C/Year 2 Summer/Comp-2560/Classes/Sockets/client.c" > CMakeFiles/Sockets.dir/client.c.i

CMakeFiles/Sockets.dir/client.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Sockets.dir/client.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/cygdrive/e/Github/C/Year 2 Summer/Comp-2560/Classes/Sockets/client.c" -o CMakeFiles/Sockets.dir/client.c.s

CMakeFiles/Sockets.dir/server.c.o: CMakeFiles/Sockets.dir/flags.make
CMakeFiles/Sockets.dir/server.c.o: ../server.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/cygdrive/e/Github/C/Year 2 Summer/Comp-2560/Classes/Sockets/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/Sockets.dir/server.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Sockets.dir/server.c.o   -c "/cygdrive/e/Github/C/Year 2 Summer/Comp-2560/Classes/Sockets/server.c"

CMakeFiles/Sockets.dir/server.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Sockets.dir/server.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/cygdrive/e/Github/C/Year 2 Summer/Comp-2560/Classes/Sockets/server.c" > CMakeFiles/Sockets.dir/server.c.i

CMakeFiles/Sockets.dir/server.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Sockets.dir/server.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/cygdrive/e/Github/C/Year 2 Summer/Comp-2560/Classes/Sockets/server.c" -o CMakeFiles/Sockets.dir/server.c.s

# Object files for target Sockets
Sockets_OBJECTS = \
"CMakeFiles/Sockets.dir/client.c.o" \
"CMakeFiles/Sockets.dir/server.c.o"

# External object files for target Sockets
Sockets_EXTERNAL_OBJECTS =

Sockets.exe: CMakeFiles/Sockets.dir/client.c.o
Sockets.exe: CMakeFiles/Sockets.dir/server.c.o
Sockets.exe: CMakeFiles/Sockets.dir/build.make
Sockets.exe: CMakeFiles/Sockets.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/cygdrive/e/Github/C/Year 2 Summer/Comp-2560/Classes/Sockets/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable Sockets.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Sockets.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Sockets.dir/build: Sockets.exe

.PHONY : CMakeFiles/Sockets.dir/build

CMakeFiles/Sockets.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Sockets.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Sockets.dir/clean

CMakeFiles/Sockets.dir/depend:
	cd "/cygdrive/e/Github/C/Year 2 Summer/Comp-2560/Classes/Sockets/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/cygdrive/e/Github/C/Year 2 Summer/Comp-2560/Classes/Sockets" "/cygdrive/e/Github/C/Year 2 Summer/Comp-2560/Classes/Sockets" "/cygdrive/e/Github/C/Year 2 Summer/Comp-2560/Classes/Sockets/cmake-build-debug" "/cygdrive/e/Github/C/Year 2 Summer/Comp-2560/Classes/Sockets/cmake-build-debug" "/cygdrive/e/Github/C/Year 2 Summer/Comp-2560/Classes/Sockets/cmake-build-debug/CMakeFiles/Sockets.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Sockets.dir/depend

