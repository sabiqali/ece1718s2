# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /homes/c/chaud482/workspace/design2_piped/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /homes/c/chaud482/workspace/design2_piped/src/build

# Include any dependencies generated for this target.
include src/CMakeFiles/design2_piped.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/design2_piped.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/design2_piped.dir/flags.make

src/CMakeFiles/design2_piped.dir/design2_piped.c.o: src/CMakeFiles/design2_piped.dir/flags.make
src/CMakeFiles/design2_piped.dir/design2_piped.c.o: ../src/design2_piped.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/homes/c/chaud482/workspace/design2_piped/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/CMakeFiles/design2_piped.dir/design2_piped.c.o"
	cd /homes/c/chaud482/workspace/design2_piped/src/build/src && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/design2_piped.dir/design2_piped.c.o   -c /homes/c/chaud482/workspace/design2_piped/src/src/design2_piped.c

src/CMakeFiles/design2_piped.dir/design2_piped.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/design2_piped.dir/design2_piped.c.i"
	cd /homes/c/chaud482/workspace/design2_piped/src/build/src && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /homes/c/chaud482/workspace/design2_piped/src/src/design2_piped.c > CMakeFiles/design2_piped.dir/design2_piped.c.i

src/CMakeFiles/design2_piped.dir/design2_piped.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/design2_piped.dir/design2_piped.c.s"
	cd /homes/c/chaud482/workspace/design2_piped/src/build/src && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /homes/c/chaud482/workspace/design2_piped/src/src/design2_piped.c -o CMakeFiles/design2_piped.dir/design2_piped.c.s

src/CMakeFiles/design2_piped.dir/design2_piped.c.o.requires:

.PHONY : src/CMakeFiles/design2_piped.dir/design2_piped.c.o.requires

src/CMakeFiles/design2_piped.dir/design2_piped.c.o.provides: src/CMakeFiles/design2_piped.dir/design2_piped.c.o.requires
	$(MAKE) -f src/CMakeFiles/design2_piped.dir/build.make src/CMakeFiles/design2_piped.dir/design2_piped.c.o.provides.build
.PHONY : src/CMakeFiles/design2_piped.dir/design2_piped.c.o.provides

src/CMakeFiles/design2_piped.dir/design2_piped.c.o.provides.build: src/CMakeFiles/design2_piped.dir/design2_piped.c.o


src/CMakeFiles/design2_piped.dir/Source.c.o: src/CMakeFiles/design2_piped.dir/flags.make
src/CMakeFiles/design2_piped.dir/Source.c.o: ../src/Source.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/homes/c/chaud482/workspace/design2_piped/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object src/CMakeFiles/design2_piped.dir/Source.c.o"
	cd /homes/c/chaud482/workspace/design2_piped/src/build/src && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/design2_piped.dir/Source.c.o   -c /homes/c/chaud482/workspace/design2_piped/src/src/Source.c

src/CMakeFiles/design2_piped.dir/Source.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/design2_piped.dir/Source.c.i"
	cd /homes/c/chaud482/workspace/design2_piped/src/build/src && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /homes/c/chaud482/workspace/design2_piped/src/src/Source.c > CMakeFiles/design2_piped.dir/Source.c.i

src/CMakeFiles/design2_piped.dir/Source.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/design2_piped.dir/Source.c.s"
	cd /homes/c/chaud482/workspace/design2_piped/src/build/src && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /homes/c/chaud482/workspace/design2_piped/src/src/Source.c -o CMakeFiles/design2_piped.dir/Source.c.s

src/CMakeFiles/design2_piped.dir/Source.c.o.requires:

.PHONY : src/CMakeFiles/design2_piped.dir/Source.c.o.requires

src/CMakeFiles/design2_piped.dir/Source.c.o.provides: src/CMakeFiles/design2_piped.dir/Source.c.o.requires
	$(MAKE) -f src/CMakeFiles/design2_piped.dir/build.make src/CMakeFiles/design2_piped.dir/Source.c.o.provides.build
.PHONY : src/CMakeFiles/design2_piped.dir/Source.c.o.provides

src/CMakeFiles/design2_piped.dir/Source.c.o.provides.build: src/CMakeFiles/design2_piped.dir/Source.c.o


src/CMakeFiles/design2_piped.dir/Duplicate.c.o: src/CMakeFiles/design2_piped.dir/flags.make
src/CMakeFiles/design2_piped.dir/Duplicate.c.o: ../src/Duplicate.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/homes/c/chaud482/workspace/design2_piped/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object src/CMakeFiles/design2_piped.dir/Duplicate.c.o"
	cd /homes/c/chaud482/workspace/design2_piped/src/build/src && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/design2_piped.dir/Duplicate.c.o   -c /homes/c/chaud482/workspace/design2_piped/src/src/Duplicate.c

src/CMakeFiles/design2_piped.dir/Duplicate.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/design2_piped.dir/Duplicate.c.i"
	cd /homes/c/chaud482/workspace/design2_piped/src/build/src && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /homes/c/chaud482/workspace/design2_piped/src/src/Duplicate.c > CMakeFiles/design2_piped.dir/Duplicate.c.i

src/CMakeFiles/design2_piped.dir/Duplicate.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/design2_piped.dir/Duplicate.c.s"
	cd /homes/c/chaud482/workspace/design2_piped/src/build/src && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /homes/c/chaud482/workspace/design2_piped/src/src/Duplicate.c -o CMakeFiles/design2_piped.dir/Duplicate.c.s

src/CMakeFiles/design2_piped.dir/Duplicate.c.o.requires:

.PHONY : src/CMakeFiles/design2_piped.dir/Duplicate.c.o.requires

src/CMakeFiles/design2_piped.dir/Duplicate.c.o.provides: src/CMakeFiles/design2_piped.dir/Duplicate.c.o.requires
	$(MAKE) -f src/CMakeFiles/design2_piped.dir/build.make src/CMakeFiles/design2_piped.dir/Duplicate.c.o.provides.build
.PHONY : src/CMakeFiles/design2_piped.dir/Duplicate.c.o.provides

src/CMakeFiles/design2_piped.dir/Duplicate.c.o.provides.build: src/CMakeFiles/design2_piped.dir/Duplicate.c.o


src/CMakeFiles/design2_piped.dir/Approx.c.o: src/CMakeFiles/design2_piped.dir/flags.make
src/CMakeFiles/design2_piped.dir/Approx.c.o: ../src/Approx.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/homes/c/chaud482/workspace/design2_piped/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object src/CMakeFiles/design2_piped.dir/Approx.c.o"
	cd /homes/c/chaud482/workspace/design2_piped/src/build/src && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/design2_piped.dir/Approx.c.o   -c /homes/c/chaud482/workspace/design2_piped/src/src/Approx.c

src/CMakeFiles/design2_piped.dir/Approx.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/design2_piped.dir/Approx.c.i"
	cd /homes/c/chaud482/workspace/design2_piped/src/build/src && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /homes/c/chaud482/workspace/design2_piped/src/src/Approx.c > CMakeFiles/design2_piped.dir/Approx.c.i

src/CMakeFiles/design2_piped.dir/Approx.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/design2_piped.dir/Approx.c.s"
	cd /homes/c/chaud482/workspace/design2_piped/src/build/src && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /homes/c/chaud482/workspace/design2_piped/src/src/Approx.c -o CMakeFiles/design2_piped.dir/Approx.c.s

src/CMakeFiles/design2_piped.dir/Approx.c.o.requires:

.PHONY : src/CMakeFiles/design2_piped.dir/Approx.c.o.requires

src/CMakeFiles/design2_piped.dir/Approx.c.o.provides: src/CMakeFiles/design2_piped.dir/Approx.c.o.requires
	$(MAKE) -f src/CMakeFiles/design2_piped.dir/build.make src/CMakeFiles/design2_piped.dir/Approx.c.o.provides.build
.PHONY : src/CMakeFiles/design2_piped.dir/Approx.c.o.provides

src/CMakeFiles/design2_piped.dir/Approx.c.o.provides.build: src/CMakeFiles/design2_piped.dir/Approx.c.o


src/CMakeFiles/design2_piped.dir/Abs_Diff.c.o: src/CMakeFiles/design2_piped.dir/flags.make
src/CMakeFiles/design2_piped.dir/Abs_Diff.c.o: ../src/Abs_Diff.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/homes/c/chaud482/workspace/design2_piped/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object src/CMakeFiles/design2_piped.dir/Abs_Diff.c.o"
	cd /homes/c/chaud482/workspace/design2_piped/src/build/src && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/design2_piped.dir/Abs_Diff.c.o   -c /homes/c/chaud482/workspace/design2_piped/src/src/Abs_Diff.c

src/CMakeFiles/design2_piped.dir/Abs_Diff.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/design2_piped.dir/Abs_Diff.c.i"
	cd /homes/c/chaud482/workspace/design2_piped/src/build/src && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /homes/c/chaud482/workspace/design2_piped/src/src/Abs_Diff.c > CMakeFiles/design2_piped.dir/Abs_Diff.c.i

src/CMakeFiles/design2_piped.dir/Abs_Diff.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/design2_piped.dir/Abs_Diff.c.s"
	cd /homes/c/chaud482/workspace/design2_piped/src/build/src && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /homes/c/chaud482/workspace/design2_piped/src/src/Abs_Diff.c -o CMakeFiles/design2_piped.dir/Abs_Diff.c.s

src/CMakeFiles/design2_piped.dir/Abs_Diff.c.o.requires:

.PHONY : src/CMakeFiles/design2_piped.dir/Abs_Diff.c.o.requires

src/CMakeFiles/design2_piped.dir/Abs_Diff.c.o.provides: src/CMakeFiles/design2_piped.dir/Abs_Diff.c.o.requires
	$(MAKE) -f src/CMakeFiles/design2_piped.dir/build.make src/CMakeFiles/design2_piped.dir/Abs_Diff.c.o.provides.build
.PHONY : src/CMakeFiles/design2_piped.dir/Abs_Diff.c.o.provides

src/CMakeFiles/design2_piped.dir/Abs_Diff.c.o.provides.build: src/CMakeFiles/design2_piped.dir/Abs_Diff.c.o


src/CMakeFiles/design2_piped.dir/Sum.c.o: src/CMakeFiles/design2_piped.dir/flags.make
src/CMakeFiles/design2_piped.dir/Sum.c.o: ../src/Sum.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/homes/c/chaud482/workspace/design2_piped/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object src/CMakeFiles/design2_piped.dir/Sum.c.o"
	cd /homes/c/chaud482/workspace/design2_piped/src/build/src && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/design2_piped.dir/Sum.c.o   -c /homes/c/chaud482/workspace/design2_piped/src/src/Sum.c

src/CMakeFiles/design2_piped.dir/Sum.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/design2_piped.dir/Sum.c.i"
	cd /homes/c/chaud482/workspace/design2_piped/src/build/src && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /homes/c/chaud482/workspace/design2_piped/src/src/Sum.c > CMakeFiles/design2_piped.dir/Sum.c.i

src/CMakeFiles/design2_piped.dir/Sum.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/design2_piped.dir/Sum.c.s"
	cd /homes/c/chaud482/workspace/design2_piped/src/build/src && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /homes/c/chaud482/workspace/design2_piped/src/src/Sum.c -o CMakeFiles/design2_piped.dir/Sum.c.s

src/CMakeFiles/design2_piped.dir/Sum.c.o.requires:

.PHONY : src/CMakeFiles/design2_piped.dir/Sum.c.o.requires

src/CMakeFiles/design2_piped.dir/Sum.c.o.provides: src/CMakeFiles/design2_piped.dir/Sum.c.o.requires
	$(MAKE) -f src/CMakeFiles/design2_piped.dir/build.make src/CMakeFiles/design2_piped.dir/Sum.c.o.provides.build
.PHONY : src/CMakeFiles/design2_piped.dir/Sum.c.o.provides

src/CMakeFiles/design2_piped.dir/Sum.c.o.provides.build: src/CMakeFiles/design2_piped.dir/Sum.c.o


src/CMakeFiles/design2_piped.dir/Printer.c.o: src/CMakeFiles/design2_piped.dir/flags.make
src/CMakeFiles/design2_piped.dir/Printer.c.o: ../src/Printer.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/homes/c/chaud482/workspace/design2_piped/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object src/CMakeFiles/design2_piped.dir/Printer.c.o"
	cd /homes/c/chaud482/workspace/design2_piped/src/build/src && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/design2_piped.dir/Printer.c.o   -c /homes/c/chaud482/workspace/design2_piped/src/src/Printer.c

src/CMakeFiles/design2_piped.dir/Printer.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/design2_piped.dir/Printer.c.i"
	cd /homes/c/chaud482/workspace/design2_piped/src/build/src && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /homes/c/chaud482/workspace/design2_piped/src/src/Printer.c > CMakeFiles/design2_piped.dir/Printer.c.i

src/CMakeFiles/design2_piped.dir/Printer.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/design2_piped.dir/Printer.c.s"
	cd /homes/c/chaud482/workspace/design2_piped/src/build/src && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /homes/c/chaud482/workspace/design2_piped/src/src/Printer.c -o CMakeFiles/design2_piped.dir/Printer.c.s

src/CMakeFiles/design2_piped.dir/Printer.c.o.requires:

.PHONY : src/CMakeFiles/design2_piped.dir/Printer.c.o.requires

src/CMakeFiles/design2_piped.dir/Printer.c.o.provides: src/CMakeFiles/design2_piped.dir/Printer.c.o.requires
	$(MAKE) -f src/CMakeFiles/design2_piped.dir/build.make src/CMakeFiles/design2_piped.dir/Printer.c.o.provides.build
.PHONY : src/CMakeFiles/design2_piped.dir/Printer.c.o.provides

src/CMakeFiles/design2_piped.dir/Printer.c.o.provides.build: src/CMakeFiles/design2_piped.dir/Printer.c.o


# Object files for target design2_piped
design2_piped_OBJECTS = \
"CMakeFiles/design2_piped.dir/design2_piped.c.o" \
"CMakeFiles/design2_piped.dir/Source.c.o" \
"CMakeFiles/design2_piped.dir/Duplicate.c.o" \
"CMakeFiles/design2_piped.dir/Approx.c.o" \
"CMakeFiles/design2_piped.dir/Abs_Diff.c.o" \
"CMakeFiles/design2_piped.dir/Sum.c.o" \
"CMakeFiles/design2_piped.dir/Printer.c.o"

# External object files for target design2_piped
design2_piped_EXTERNAL_OBJECTS =

../bin/design2_piped: src/CMakeFiles/design2_piped.dir/design2_piped.c.o
../bin/design2_piped: src/CMakeFiles/design2_piped.dir/Source.c.o
../bin/design2_piped: src/CMakeFiles/design2_piped.dir/Duplicate.c.o
../bin/design2_piped: src/CMakeFiles/design2_piped.dir/Approx.c.o
../bin/design2_piped: src/CMakeFiles/design2_piped.dir/Abs_Diff.c.o
../bin/design2_piped: src/CMakeFiles/design2_piped.dir/Sum.c.o
../bin/design2_piped: src/CMakeFiles/design2_piped.dir/Printer.c.o
../bin/design2_piped: src/CMakeFiles/design2_piped.dir/build.make
../bin/design2_piped: libs/orcc-native/liborcc-native.a
../bin/design2_piped: libs/orcc-runtime/liborcc-runtime.a
../bin/design2_piped: libs/roxml/libroxml.a
../bin/design2_piped: /usr/lib/x86_64-linux-gnu/libSDLmain.a
../bin/design2_piped: /usr/lib/x86_64-linux-gnu/libSDL.so
../bin/design2_piped: libs/orcc-native/liborcc-native.a
../bin/design2_piped: libs/orcc-runtime/liborcc-runtime.a
../bin/design2_piped: /usr/lib/x86_64-linux-gnu/libSDLmain.a
../bin/design2_piped: /usr/lib/x86_64-linux-gnu/libSDL.so
../bin/design2_piped: libs/roxml/libroxml.a
../bin/design2_piped: src/CMakeFiles/design2_piped.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/homes/c/chaud482/workspace/design2_piped/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking C executable ../../bin/design2_piped"
	cd /homes/c/chaud482/workspace/design2_piped/src/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/design2_piped.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/design2_piped.dir/build: ../bin/design2_piped

.PHONY : src/CMakeFiles/design2_piped.dir/build

src/CMakeFiles/design2_piped.dir/requires: src/CMakeFiles/design2_piped.dir/design2_piped.c.o.requires
src/CMakeFiles/design2_piped.dir/requires: src/CMakeFiles/design2_piped.dir/Source.c.o.requires
src/CMakeFiles/design2_piped.dir/requires: src/CMakeFiles/design2_piped.dir/Duplicate.c.o.requires
src/CMakeFiles/design2_piped.dir/requires: src/CMakeFiles/design2_piped.dir/Approx.c.o.requires
src/CMakeFiles/design2_piped.dir/requires: src/CMakeFiles/design2_piped.dir/Abs_Diff.c.o.requires
src/CMakeFiles/design2_piped.dir/requires: src/CMakeFiles/design2_piped.dir/Sum.c.o.requires
src/CMakeFiles/design2_piped.dir/requires: src/CMakeFiles/design2_piped.dir/Printer.c.o.requires

.PHONY : src/CMakeFiles/design2_piped.dir/requires

src/CMakeFiles/design2_piped.dir/clean:
	cd /homes/c/chaud482/workspace/design2_piped/src/build/src && $(CMAKE_COMMAND) -P CMakeFiles/design2_piped.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/design2_piped.dir/clean

src/CMakeFiles/design2_piped.dir/depend:
	cd /homes/c/chaud482/workspace/design2_piped/src/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /homes/c/chaud482/workspace/design2_piped/src /homes/c/chaud482/workspace/design2_piped/src/src /homes/c/chaud482/workspace/design2_piped/src/build /homes/c/chaud482/workspace/design2_piped/src/build/src /homes/c/chaud482/workspace/design2_piped/src/build/src/CMakeFiles/design2_piped.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/design2_piped.dir/depend

