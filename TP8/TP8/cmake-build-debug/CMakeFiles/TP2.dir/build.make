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
CMAKE_SOURCE_DIR = C:\Users\user\Desktop\FEUP\2_Ano\2_Semestre\CAL\TP8\TP8

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\user\Desktop\FEUP\2_Ano\2_Semestre\CAL\TP8\TP8\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/TP2.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/TP2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TP2.dir/flags.make

CMakeFiles/TP2.dir/main.cpp.obj: CMakeFiles/TP2.dir/flags.make
CMakeFiles/TP2.dir/main.cpp.obj: CMakeFiles/TP2.dir/includes_CXX.rsp
CMakeFiles/TP2.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\user\Desktop\FEUP\2_Ano\2_Semestre\CAL\TP8\TP8\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/TP2.dir/main.cpp.obj"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\TP2.dir\main.cpp.obj -c C:\Users\user\Desktop\FEUP\2_Ano\2_Semestre\CAL\TP8\TP8\main.cpp

CMakeFiles/TP2.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TP2.dir/main.cpp.i"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\user\Desktop\FEUP\2_Ano\2_Semestre\CAL\TP8\TP8\main.cpp > CMakeFiles\TP2.dir\main.cpp.i

CMakeFiles/TP2.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TP2.dir/main.cpp.s"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\user\Desktop\FEUP\2_Ano\2_Semestre\CAL\TP8\TP8\main.cpp -o CMakeFiles\TP2.dir\main.cpp.s

# Object files for target TP2
TP2_OBJECTS = \
"CMakeFiles/TP2.dir/main.cpp.obj"

# External object files for target TP2
TP2_EXTERNAL_OBJECTS =

TP2.exe: CMakeFiles/TP2.dir/main.cpp.obj
TP2.exe: CMakeFiles/TP2.dir/build.make
TP2.exe: lib/libgtest_maind.a
TP2.exe: lib/libgmock_maind.a
TP2.exe: lib/libgmockd.a
TP2.exe: lib/libgtestd.a
TP2.exe: CMakeFiles/TP2.dir/linklibs.rsp
TP2.exe: CMakeFiles/TP2.dir/objects1.rsp
TP2.exe: CMakeFiles/TP2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\user\Desktop\FEUP\2_Ano\2_Semestre\CAL\TP8\TP8\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable TP2.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\TP2.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/TP2.dir/build: TP2.exe

.PHONY : CMakeFiles/TP2.dir/build

CMakeFiles/TP2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\TP2.dir\cmake_clean.cmake
.PHONY : CMakeFiles/TP2.dir/clean

CMakeFiles/TP2.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\user\Desktop\FEUP\2_Ano\2_Semestre\CAL\TP8\TP8 C:\Users\user\Desktop\FEUP\2_Ano\2_Semestre\CAL\TP8\TP8 C:\Users\user\Desktop\FEUP\2_Ano\2_Semestre\CAL\TP8\TP8\cmake-build-debug C:\Users\user\Desktop\FEUP\2_Ano\2_Semestre\CAL\TP8\TP8\cmake-build-debug C:\Users\user\Desktop\FEUP\2_Ano\2_Semestre\CAL\TP8\TP8\cmake-build-debug\CMakeFiles\TP2.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/TP2.dir/depend
