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
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2020.2.4\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2020.2.4\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\user\Desktop\FEUP\2_Ano\2_Semestre\CAL\Hackrank

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\user\Desktop\FEUP\2_Ano\2_Semestre\CAL\Hackrank\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Hackrank.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Hackrank.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Hackrank.dir/flags.make

CMakeFiles/Hackrank.dir/balancing_weights.cpp.obj: CMakeFiles/Hackrank.dir/flags.make
CMakeFiles/Hackrank.dir/balancing_weights.cpp.obj: ../balancing_weights.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\user\Desktop\FEUP\2_Ano\2_Semestre\CAL\Hackrank\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Hackrank.dir/balancing_weights.cpp.obj"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Hackrank.dir\balancing_weights.cpp.obj -c C:\Users\user\Desktop\FEUP\2_Ano\2_Semestre\CAL\Hackrank\balancing_weights.cpp

CMakeFiles/Hackrank.dir/balancing_weights.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Hackrank.dir/balancing_weights.cpp.i"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\user\Desktop\FEUP\2_Ano\2_Semestre\CAL\Hackrank\balancing_weights.cpp > CMakeFiles\Hackrank.dir\balancing_weights.cpp.i

CMakeFiles/Hackrank.dir/balancing_weights.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Hackrank.dir/balancing_weights.cpp.s"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\user\Desktop\FEUP\2_Ano\2_Semestre\CAL\Hackrank\balancing_weights.cpp -o CMakeFiles\Hackrank.dir\balancing_weights.cpp.s

# Object files for target Hackrank
Hackrank_OBJECTS = \
"CMakeFiles/Hackrank.dir/balancing_weights.cpp.obj"

# External object files for target Hackrank
Hackrank_EXTERNAL_OBJECTS =

Hackrank.exe: CMakeFiles/Hackrank.dir/balancing_weights.cpp.obj
Hackrank.exe: CMakeFiles/Hackrank.dir/build.make
Hackrank.exe: CMakeFiles/Hackrank.dir/linklibs.rsp
Hackrank.exe: CMakeFiles/Hackrank.dir/objects1.rsp
Hackrank.exe: CMakeFiles/Hackrank.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\user\Desktop\FEUP\2_Ano\2_Semestre\CAL\Hackrank\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Hackrank.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Hackrank.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Hackrank.dir/build: Hackrank.exe

.PHONY : CMakeFiles/Hackrank.dir/build

CMakeFiles/Hackrank.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Hackrank.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Hackrank.dir/clean

CMakeFiles/Hackrank.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\user\Desktop\FEUP\2_Ano\2_Semestre\CAL\Hackrank C:\Users\user\Desktop\FEUP\2_Ano\2_Semestre\CAL\Hackrank C:\Users\user\Desktop\FEUP\2_Ano\2_Semestre\CAL\Hackrank\cmake-build-debug C:\Users\user\Desktop\FEUP\2_Ano\2_Semestre\CAL\Hackrank\cmake-build-debug C:\Users\user\Desktop\FEUP\2_Ano\2_Semestre\CAL\Hackrank\cmake-build-debug\CMakeFiles\Hackrank.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Hackrank.dir/depend

