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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.20.2/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.20.2/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/toto/Desktop/Oasis/Oasis/vendor/glfw

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/toto/Desktop/Oasis/Oasis/vendor/glfw

# Include any dependencies generated for this target.
include tests/CMakeFiles/inputlag.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include tests/CMakeFiles/inputlag.dir/compiler_depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/inputlag.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/inputlag.dir/flags.make

tests/CMakeFiles/inputlag.dir/inputlag.c.o: tests/CMakeFiles/inputlag.dir/flags.make
tests/CMakeFiles/inputlag.dir/inputlag.c.o: tests/inputlag.c
tests/CMakeFiles/inputlag.dir/inputlag.c.o: tests/CMakeFiles/inputlag.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/toto/Desktop/Oasis/Oasis/vendor/glfw/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object tests/CMakeFiles/inputlag.dir/inputlag.c.o"
	cd /Users/toto/Desktop/Oasis/Oasis/vendor/glfw/tests && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT tests/CMakeFiles/inputlag.dir/inputlag.c.o -MF CMakeFiles/inputlag.dir/inputlag.c.o.d -o CMakeFiles/inputlag.dir/inputlag.c.o -c /Users/toto/Desktop/Oasis/Oasis/vendor/glfw/tests/inputlag.c

tests/CMakeFiles/inputlag.dir/inputlag.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/inputlag.dir/inputlag.c.i"
	cd /Users/toto/Desktop/Oasis/Oasis/vendor/glfw/tests && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/toto/Desktop/Oasis/Oasis/vendor/glfw/tests/inputlag.c > CMakeFiles/inputlag.dir/inputlag.c.i

tests/CMakeFiles/inputlag.dir/inputlag.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/inputlag.dir/inputlag.c.s"
	cd /Users/toto/Desktop/Oasis/Oasis/vendor/glfw/tests && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/toto/Desktop/Oasis/Oasis/vendor/glfw/tests/inputlag.c -o CMakeFiles/inputlag.dir/inputlag.c.s

tests/CMakeFiles/inputlag.dir/__/deps/getopt.c.o: tests/CMakeFiles/inputlag.dir/flags.make
tests/CMakeFiles/inputlag.dir/__/deps/getopt.c.o: deps/getopt.c
tests/CMakeFiles/inputlag.dir/__/deps/getopt.c.o: tests/CMakeFiles/inputlag.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/toto/Desktop/Oasis/Oasis/vendor/glfw/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object tests/CMakeFiles/inputlag.dir/__/deps/getopt.c.o"
	cd /Users/toto/Desktop/Oasis/Oasis/vendor/glfw/tests && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT tests/CMakeFiles/inputlag.dir/__/deps/getopt.c.o -MF CMakeFiles/inputlag.dir/__/deps/getopt.c.o.d -o CMakeFiles/inputlag.dir/__/deps/getopt.c.o -c /Users/toto/Desktop/Oasis/Oasis/vendor/glfw/deps/getopt.c

tests/CMakeFiles/inputlag.dir/__/deps/getopt.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/inputlag.dir/__/deps/getopt.c.i"
	cd /Users/toto/Desktop/Oasis/Oasis/vendor/glfw/tests && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/toto/Desktop/Oasis/Oasis/vendor/glfw/deps/getopt.c > CMakeFiles/inputlag.dir/__/deps/getopt.c.i

tests/CMakeFiles/inputlag.dir/__/deps/getopt.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/inputlag.dir/__/deps/getopt.c.s"
	cd /Users/toto/Desktop/Oasis/Oasis/vendor/glfw/tests && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/toto/Desktop/Oasis/Oasis/vendor/glfw/deps/getopt.c -o CMakeFiles/inputlag.dir/__/deps/getopt.c.s

tests/CMakeFiles/inputlag.dir/__/deps/glad_gl.c.o: tests/CMakeFiles/inputlag.dir/flags.make
tests/CMakeFiles/inputlag.dir/__/deps/glad_gl.c.o: deps/glad_gl.c
tests/CMakeFiles/inputlag.dir/__/deps/glad_gl.c.o: tests/CMakeFiles/inputlag.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/toto/Desktop/Oasis/Oasis/vendor/glfw/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object tests/CMakeFiles/inputlag.dir/__/deps/glad_gl.c.o"
	cd /Users/toto/Desktop/Oasis/Oasis/vendor/glfw/tests && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT tests/CMakeFiles/inputlag.dir/__/deps/glad_gl.c.o -MF CMakeFiles/inputlag.dir/__/deps/glad_gl.c.o.d -o CMakeFiles/inputlag.dir/__/deps/glad_gl.c.o -c /Users/toto/Desktop/Oasis/Oasis/vendor/glfw/deps/glad_gl.c

tests/CMakeFiles/inputlag.dir/__/deps/glad_gl.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/inputlag.dir/__/deps/glad_gl.c.i"
	cd /Users/toto/Desktop/Oasis/Oasis/vendor/glfw/tests && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/toto/Desktop/Oasis/Oasis/vendor/glfw/deps/glad_gl.c > CMakeFiles/inputlag.dir/__/deps/glad_gl.c.i

tests/CMakeFiles/inputlag.dir/__/deps/glad_gl.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/inputlag.dir/__/deps/glad_gl.c.s"
	cd /Users/toto/Desktop/Oasis/Oasis/vendor/glfw/tests && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/toto/Desktop/Oasis/Oasis/vendor/glfw/deps/glad_gl.c -o CMakeFiles/inputlag.dir/__/deps/glad_gl.c.s

# Object files for target inputlag
inputlag_OBJECTS = \
"CMakeFiles/inputlag.dir/inputlag.c.o" \
"CMakeFiles/inputlag.dir/__/deps/getopt.c.o" \
"CMakeFiles/inputlag.dir/__/deps/glad_gl.c.o"

# External object files for target inputlag
inputlag_EXTERNAL_OBJECTS =

tests/inputlag.app/Contents/MacOS/inputlag: tests/CMakeFiles/inputlag.dir/inputlag.c.o
tests/inputlag.app/Contents/MacOS/inputlag: tests/CMakeFiles/inputlag.dir/__/deps/getopt.c.o
tests/inputlag.app/Contents/MacOS/inputlag: tests/CMakeFiles/inputlag.dir/__/deps/glad_gl.c.o
tests/inputlag.app/Contents/MacOS/inputlag: tests/CMakeFiles/inputlag.dir/build.make
tests/inputlag.app/Contents/MacOS/inputlag: src/libglfw3.a
tests/inputlag.app/Contents/MacOS/inputlag: tests/CMakeFiles/inputlag.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/toto/Desktop/Oasis/Oasis/vendor/glfw/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable inputlag.app/Contents/MacOS/inputlag"
	cd /Users/toto/Desktop/Oasis/Oasis/vendor/glfw/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/inputlag.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/inputlag.dir/build: tests/inputlag.app/Contents/MacOS/inputlag
.PHONY : tests/CMakeFiles/inputlag.dir/build

tests/CMakeFiles/inputlag.dir/clean:
	cd /Users/toto/Desktop/Oasis/Oasis/vendor/glfw/tests && $(CMAKE_COMMAND) -P CMakeFiles/inputlag.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/inputlag.dir/clean

tests/CMakeFiles/inputlag.dir/depend:
	cd /Users/toto/Desktop/Oasis/Oasis/vendor/glfw && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/toto/Desktop/Oasis/Oasis/vendor/glfw /Users/toto/Desktop/Oasis/Oasis/vendor/glfw/tests /Users/toto/Desktop/Oasis/Oasis/vendor/glfw /Users/toto/Desktop/Oasis/Oasis/vendor/glfw/tests /Users/toto/Desktop/Oasis/Oasis/vendor/glfw/tests/CMakeFiles/inputlag.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/inputlag.dir/depend

