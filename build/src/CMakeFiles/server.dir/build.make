# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.27

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
CMAKE_COMMAND = C:\Users\admin-12\AppData\Local\Programs\Python\Python311\Lib\site-packages\cmake\data\bin\cmake.exe

# The command to remove a file.
RM = C:\Users\admin-12\AppData\Local\Programs\Python\Python311\Lib\site-packages\cmake\data\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\Studio\C\Minesweeper-2023-main

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Studio\C\build

# Include any dependencies generated for this target.
include src/CMakeFiles/server.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/CMakeFiles/server.dir/compiler_depend.make

# Include the progress variables for this target.
include src/CMakeFiles/server.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/server.dir/flags.make

src/CMakeFiles/server.dir/main.cpp.obj: src/CMakeFiles/server.dir/flags.make
src/CMakeFiles/server.dir/main.cpp.obj: src/CMakeFiles/server.dir/includes_CXX.rsp
src/CMakeFiles/server.dir/main.cpp.obj: D:/Studio/C/Minesweeper-2023-main/src/main.cpp
src/CMakeFiles/server.dir/main.cpp.obj: src/CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:\Studio\C\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/server.dir/main.cpp.obj"
	cd /d D:\Studio\C\build\src && C:\MinGW\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/server.dir/main.cpp.obj -MF CMakeFiles\server.dir\main.cpp.obj.d -o CMakeFiles\server.dir\main.cpp.obj -c D:\Studio\C\Minesweeper-2023-main\src\main.cpp

src/CMakeFiles/server.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/server.dir/main.cpp.i"
	cd /d D:\Studio\C\build\src && C:\MinGW\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Studio\C\Minesweeper-2023-main\src\main.cpp > CMakeFiles\server.dir\main.cpp.i

src/CMakeFiles/server.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/server.dir/main.cpp.s"
	cd /d D:\Studio\C\build\src && C:\MinGW\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Studio\C\Minesweeper-2023-main\src\main.cpp -o CMakeFiles\server.dir\main.cpp.s

# Object files for target server
server_OBJECTS = \
"CMakeFiles/server.dir/main.cpp.obj"

# External object files for target server
server_EXTERNAL_OBJECTS =

src/server.exe: src/CMakeFiles/server.dir/main.cpp.obj
src/server.exe: src/CMakeFiles/server.dir/build.make
src/server.exe: src/CMakeFiles/server.dir/linkLibs.rsp
src/server.exe: src/CMakeFiles/server.dir/objects1.rsp
src/server.exe: src/CMakeFiles/server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=D:\Studio\C\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable server.exe"
	cd /d D:\Studio\C\build\src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\server.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/server.dir/build: src/server.exe
.PHONY : src/CMakeFiles/server.dir/build

src/CMakeFiles/server.dir/clean:
	cd /d D:\Studio\C\build\src && $(CMAKE_COMMAND) -P CMakeFiles\server.dir\cmake_clean.cmake
.PHONY : src/CMakeFiles/server.dir/clean

src/CMakeFiles/server.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Studio\C\Minesweeper-2023-main D:\Studio\C\Minesweeper-2023-main\src D:\Studio\C\build D:\Studio\C\build\src D:\Studio\C\build\src\CMakeFiles\server.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : src/CMakeFiles/server.dir/depend
