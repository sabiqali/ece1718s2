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
CMAKE_SOURCE_DIR = /homes/c/chaud482/workspace/ece1718_milestone2design2/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /homes/c/chaud482/workspace/ece1718_milestone2design2/src/build

# Include any dependencies generated for this target.
include src/CMakeFiles/TopTesting2.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/TopTesting2.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/TopTesting2.dir/flags.make

src/CMakeFiles/TopTesting2.dir/TopTesting2.c.o: src/CMakeFiles/TopTesting2.dir/flags.make
src/CMakeFiles/TopTesting2.dir/TopTesting2.c.o: ../src/TopTesting2.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/homes/c/chaud482/workspace/ece1718_milestone2design2/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/CMakeFiles/TopTesting2.dir/TopTesting2.c.o"
	cd /homes/c/chaud482/workspace/ece1718_milestone2design2/src/build/src && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/TopTesting2.dir/TopTesting2.c.o   -c /homes/c/chaud482/workspace/ece1718_milestone2design2/src/src/TopTesting2.c

src/CMakeFiles/TopTesting2.dir/TopTesting2.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TopTesting2.dir/TopTesting2.c.i"
	cd /homes/c/chaud482/workspace/ece1718_milestone2design2/src/build/src && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /homes/c/chaud482/workspace/ece1718_milestone2design2/src/src/TopTesting2.c > CMakeFiles/TopTesting2.dir/TopTesting2.c.i

src/CMakeFiles/TopTesting2.dir/TopTesting2.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TopTesting2.dir/TopTesting2.c.s"
	cd /homes/c/chaud482/workspace/ece1718_milestone2design2/src/build/src && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /homes/c/chaud482/workspace/ece1718_milestone2design2/src/src/TopTesting2.c -o CMakeFiles/TopTesting2.dir/TopTesting2.c.s

src/CMakeFiles/TopTesting2.dir/TopTesting2.c.o.requires:

.PHONY : src/CMakeFiles/TopTesting2.dir/TopTesting2.c.o.requires

src/CMakeFiles/TopTesting2.dir/TopTesting2.c.o.provides: src/CMakeFiles/TopTesting2.dir/TopTesting2.c.o.requires
	$(MAKE) -f src/CMakeFiles/TopTesting2.dir/build.make src/CMakeFiles/TopTesting2.dir/TopTesting2.c.o.provides.build
.PHONY : src/CMakeFiles/TopTesting2.dir/TopTesting2.c.o.provides

src/CMakeFiles/TopTesting2.dir/TopTesting2.c.o.provides.build: src/CMakeFiles/TopTesting2.dir/TopTesting2.c.o


src/CMakeFiles/TopTesting2.dir/Source.c.o: src/CMakeFiles/TopTesting2.dir/flags.make
src/CMakeFiles/TopTesting2.dir/Source.c.o: ../src/Source.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/homes/c/chaud482/workspace/ece1718_milestone2design2/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object src/CMakeFiles/TopTesting2.dir/Source.c.o"
	cd /homes/c/chaud482/workspace/ece1718_milestone2design2/src/build/src && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/TopTesting2.dir/Source.c.o   -c /homes/c/chaud482/workspace/ece1718_milestone2design2/src/src/Source.c

src/CMakeFiles/TopTesting2.dir/Source.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TopTesting2.dir/Source.c.i"
	cd /homes/c/chaud482/workspace/ece1718_milestone2design2/src/build/src && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /homes/c/chaud482/workspace/ece1718_milestone2design2/src/src/Source.c > CMakeFiles/TopTesting2.dir/Source.c.i

src/CMakeFiles/TopTesting2.dir/Source.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TopTesting2.dir/Source.c.s"
	cd /homes/c/chaud482/workspace/ece1718_milestone2design2/src/build/src && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /homes/c/chaud482/workspace/ece1718_milestone2design2/src/src/Source.c -o CMakeFiles/TopTesting2.dir/Source.c.s

src/CMakeFiles/TopTesting2.dir/Source.c.o.requires:

.PHONY : src/CMakeFiles/TopTesting2.dir/Source.c.o.requires

src/CMakeFiles/TopTesting2.dir/Source.c.o.provides: src/CMakeFiles/TopTesting2.dir/Source.c.o.requires
	$(MAKE) -f src/CMakeFiles/TopTesting2.dir/build.make src/CMakeFiles/TopTesting2.dir/Source.c.o.provides.build
.PHONY : src/CMakeFiles/TopTesting2.dir/Source.c.o.provides

src/CMakeFiles/TopTesting2.dir/Source.c.o.provides.build: src/CMakeFiles/TopTesting2.dir/Source.c.o


src/CMakeFiles/TopTesting2.dir/Duplicate.c.o: src/CMakeFiles/TopTesting2.dir/flags.make
src/CMakeFiles/TopTesting2.dir/Duplicate.c.o: ../src/Duplicate.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/homes/c/chaud482/workspace/ece1718_milestone2design2/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object src/CMakeFiles/TopTesting2.dir/Duplicate.c.o"
	cd /homes/c/chaud482/workspace/ece1718_milestone2design2/src/build/src && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/TopTesting2.dir/Duplicate.c.o   -c /homes/c/chaud482/workspace/ece1718_milestone2design2/src/src/Duplicate.c

src/CMakeFiles/TopTesting2.dir/Duplicate.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TopTesting2.dir/Duplicate.c.i"
	cd /homes/c/chaud482/workspace/ece1718_milestone2design2/src/build/src && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /homes/c/chaud482/workspace/ece1718_milestone2design2/src/src/Duplicate.c > CMakeFiles/TopTesting2.dir/Duplicate.c.i

src/CMakeFiles/TopTesting2.dir/Duplicate.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TopTesting2.dir/Duplicate.c.s"
	cd /homes/c/chaud482/workspace/ece1718_milestone2design2/src/build/src && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /homes/c/chaud482/workspace/ece1718_milestone2design2/src/src/Duplicate.c -o CMakeFiles/TopTesting2.dir/Duplicate.c.s

src/CMakeFiles/TopTesting2.dir/Duplicate.c.o.requires:

.PHONY : src/CMakeFiles/TopTesting2.dir/Duplicate.c.o.requires

src/CMakeFiles/TopTesting2.dir/Duplicate.c.o.provides: src/CMakeFiles/TopTesting2.dir/Duplicate.c.o.requires
	$(MAKE) -f src/CMakeFiles/TopTesting2.dir/build.make src/CMakeFiles/TopTesting2.dir/Duplicate.c.o.provides.build
.PHONY : src/CMakeFiles/TopTesting2.dir/Duplicate.c.o.provides

src/CMakeFiles/TopTesting2.dir/Duplicate.c.o.provides.build: src/CMakeFiles/TopTesting2.dir/Duplicate.c.o


src/CMakeFiles/TopTesting2.dir/Abs_Diff.c.o: src/CMakeFiles/TopTesting2.dir/flags.make
src/CMakeFiles/TopTesting2.dir/Abs_Diff.c.o: ../src/Abs_Diff.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/homes/c/chaud482/workspace/ece1718_milestone2design2/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object src/CMakeFiles/TopTesting2.dir/Abs_Diff.c.o"
	cd /homes/c/chaud482/workspace/ece1718_milestone2design2/src/build/src && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/TopTesting2.dir/Abs_Diff.c.o   -c /homes/c/chaud482/workspace/ece1718_milestone2design2/src/src/Abs_Diff.c

src/CMakeFiles/TopTesting2.dir/Abs_Diff.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TopTesting2.dir/Abs_Diff.c.i"
	cd /homes/c/chaud482/workspace/ece1718_milestone2design2/src/build/src && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /homes/c/chaud482/workspace/ece1718_milestone2design2/src/src/Abs_Diff.c > CMakeFiles/TopTesting2.dir/Abs_Diff.c.i

src/CMakeFiles/TopTesting2.dir/Abs_Diff.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TopTesting2.dir/Abs_Diff.c.s"
	cd /homes/c/chaud482/workspace/ece1718_milestone2design2/src/build/src && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /homes/c/chaud482/workspace/ece1718_milestone2design2/src/src/Abs_Diff.c -o CMakeFiles/TopTesting2.dir/Abs_Diff.c.s

src/CMakeFiles/TopTesting2.dir/Abs_Diff.c.o.requires:

.PHONY : src/CMakeFiles/TopTesting2.dir/Abs_Diff.c.o.requires

src/CMakeFiles/TopTesting2.dir/Abs_Diff.c.o.provides: src/CMakeFiles/TopTesting2.dir/Abs_Diff.c.o.requires
	$(MAKE) -f src/CMakeFiles/TopTesting2.dir/build.make src/CMakeFiles/TopTesting2.dir/Abs_Diff.c.o.provides.build
.PHONY : src/CMakeFiles/TopTesting2.dir/Abs_Diff.c.o.provides

src/CMakeFiles/TopTesting2.dir/Abs_Diff.c.o.provides.build: src/CMakeFiles/TopTesting2.dir/Abs_Diff.c.o


src/CMakeFiles/TopTesting2.dir/Sum.c.o: src/CMakeFiles/TopTesting2.dir/flags.make
src/CMakeFiles/TopTesting2.dir/Sum.c.o: ../src/Sum.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/homes/c/chaud482/workspace/ece1718_milestone2design2/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object src/CMakeFiles/TopTesting2.dir/Sum.c.o"
	cd /homes/c/chaud482/workspace/ece1718_milestone2design2/src/build/src && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/TopTesting2.dir/Sum.c.o   -c /homes/c/chaud482/workspace/ece1718_milestone2design2/src/src/Sum.c

src/CMakeFiles/TopTesting2.dir/Sum.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TopTesting2.dir/Sum.c.i"
	cd /homes/c/chaud482/workspace/ece1718_milestone2design2/src/build/src && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /homes/c/chaud482/workspace/ece1718_milestone2design2/src/src/Sum.c > CMakeFiles/TopTesting2.dir/Sum.c.i

src/CMakeFiles/TopTesting2.dir/Sum.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TopTesting2.dir/Sum.c.s"
	cd /homes/c/chaud482/workspace/ece1718_milestone2design2/src/build/src && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /homes/c/chaud482/workspace/ece1718_milestone2design2/src/src/Sum.c -o CMakeFiles/TopTesting2.dir/Sum.c.s

src/CMakeFiles/TopTesting2.dir/Sum.c.o.requires:

.PHONY : src/CMakeFiles/TopTesting2.dir/Sum.c.o.requires

src/CMakeFiles/TopTesting2.dir/Sum.c.o.provides: src/CMakeFiles/TopTesting2.dir/Sum.c.o.requires
	$(MAKE) -f src/CMakeFiles/TopTesting2.dir/build.make src/CMakeFiles/TopTesting2.dir/Sum.c.o.provides.build
.PHONY : src/CMakeFiles/TopTesting2.dir/Sum.c.o.provides

src/CMakeFiles/TopTesting2.dir/Sum.c.o.provides.build: src/CMakeFiles/TopTesting2.dir/Sum.c.o


src/CMakeFiles/TopTesting2.dir/Printer.c.o: src/CMakeFiles/TopTesting2.dir/flags.make
src/CMakeFiles/TopTesting2.dir/Printer.c.o: ../src/Printer.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/homes/c/chaud482/workspace/ece1718_milestone2design2/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object src/CMakeFiles/TopTesting2.dir/Printer.c.o"
	cd /homes/c/chaud482/workspace/ece1718_milestone2design2/src/build/src && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/TopTesting2.dir/Printer.c.o   -c /homes/c/chaud482/workspace/ece1718_milestone2design2/src/src/Printer.c

src/CMakeFiles/TopTesting2.dir/Printer.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TopTesting2.dir/Printer.c.i"
	cd /homes/c/chaud482/workspace/ece1718_milestone2design2/src/build/src && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /homes/c/chaud482/workspace/ece1718_milestone2design2/src/src/Printer.c > CMakeFiles/TopTesting2.dir/Printer.c.i

src/CMakeFiles/TopTesting2.dir/Printer.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TopTesting2.dir/Printer.c.s"
	cd /homes/c/chaud482/workspace/ece1718_milestone2design2/src/build/src && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /homes/c/chaud482/workspace/ece1718_milestone2design2/src/src/Printer.c -o CMakeFiles/TopTesting2.dir/Printer.c.s

src/CMakeFiles/TopTesting2.dir/Printer.c.o.requires:

.PHONY : src/CMakeFiles/TopTesting2.dir/Printer.c.o.requires

src/CMakeFiles/TopTesting2.dir/Printer.c.o.provides: src/CMakeFiles/TopTesting2.dir/Printer.c.o.requires
	$(MAKE) -f src/CMakeFiles/TopTesting2.dir/build.make src/CMakeFiles/TopTesting2.dir/Printer.c.o.provides.build
.PHONY : src/CMakeFiles/TopTesting2.dir/Printer.c.o.provides

src/CMakeFiles/TopTesting2.dir/Printer.c.o.provides.build: src/CMakeFiles/TopTesting2.dir/Printer.c.o


# Object files for target TopTesting2
TopTesting2_OBJECTS = \
"CMakeFiles/TopTesting2.dir/TopTesting2.c.o" \
"CMakeFiles/TopTesting2.dir/Source.c.o" \
"CMakeFiles/TopTesting2.dir/Duplicate.c.o" \
"CMakeFiles/TopTesting2.dir/Abs_Diff.c.o" \
"CMakeFiles/TopTesting2.dir/Sum.c.o" \
"CMakeFiles/TopTesting2.dir/Printer.c.o"

# External object files for target TopTesting2
TopTesting2_EXTERNAL_OBJECTS =

../bin/TopTesting2: src/CMakeFiles/TopTesting2.dir/TopTesting2.c.o
../bin/TopTesting2: src/CMakeFiles/TopTesting2.dir/Source.c.o
../bin/TopTesting2: src/CMakeFiles/TopTesting2.dir/Duplicate.c.o
../bin/TopTesting2: src/CMakeFiles/TopTesting2.dir/Abs_Diff.c.o
../bin/TopTesting2: src/CMakeFiles/TopTesting2.dir/Sum.c.o
../bin/TopTesting2: src/CMakeFiles/TopTesting2.dir/Printer.c.o
../bin/TopTesting2: src/CMakeFiles/TopTesting2.dir/build.make
../bin/TopTesting2: libs/orcc-native/liborcc-native.a
../bin/TopTesting2: libs/orcc-runtime/liborcc-runtime.a
../bin/TopTesting2: libs/roxml/libroxml.a
../bin/TopTesting2: /usr/lib/x86_64-linux-gnu/libSDLmain.a
../bin/TopTesting2: /usr/lib/x86_64-linux-gnu/libSDL.so
../bin/TopTesting2: libs/orcc-native/liborcc-native.a
../bin/TopTesting2: libs/orcc-runtime/liborcc-runtime.a
../bin/TopTesting2: /usr/lib/x86_64-linux-gnu/libSDLmain.a
../bin/TopTesting2: /usr/lib/x86_64-linux-gnu/libSDL.so
../bin/TopTesting2: libs/roxml/libroxml.a
../bin/TopTesting2: src/CMakeFiles/TopTesting2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/homes/c/chaud482/workspace/ece1718_milestone2design2/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking C executable ../../bin/TopTesting2"
	cd /homes/c/chaud482/workspace/ece1718_milestone2design2/src/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TopTesting2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/TopTesting2.dir/build: ../bin/TopTesting2

.PHONY : src/CMakeFiles/TopTesting2.dir/build

src/CMakeFiles/TopTesting2.dir/requires: src/CMakeFiles/TopTesting2.dir/TopTesting2.c.o.requires
src/CMakeFiles/TopTesting2.dir/requires: src/CMakeFiles/TopTesting2.dir/Source.c.o.requires
src/CMakeFiles/TopTesting2.dir/requires: src/CMakeFiles/TopTesting2.dir/Duplicate.c.o.requires
src/CMakeFiles/TopTesting2.dir/requires: src/CMakeFiles/TopTesting2.dir/Abs_Diff.c.o.requires
src/CMakeFiles/TopTesting2.dir/requires: src/CMakeFiles/TopTesting2.dir/Sum.c.o.requires
src/CMakeFiles/TopTesting2.dir/requires: src/CMakeFiles/TopTesting2.dir/Printer.c.o.requires

.PHONY : src/CMakeFiles/TopTesting2.dir/requires

src/CMakeFiles/TopTesting2.dir/clean:
	cd /homes/c/chaud482/workspace/ece1718_milestone2design2/src/build/src && $(CMAKE_COMMAND) -P CMakeFiles/TopTesting2.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/TopTesting2.dir/clean

src/CMakeFiles/TopTesting2.dir/depend:
	cd /homes/c/chaud482/workspace/ece1718_milestone2design2/src/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /homes/c/chaud482/workspace/ece1718_milestone2design2/src /homes/c/chaud482/workspace/ece1718_milestone2design2/src/src /homes/c/chaud482/workspace/ece1718_milestone2design2/src/build /homes/c/chaud482/workspace/ece1718_milestone2design2/src/build/src /homes/c/chaud482/workspace/ece1718_milestone2design2/src/build/src/CMakeFiles/TopTesting2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/TopTesting2.dir/depend

