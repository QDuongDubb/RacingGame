# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.30

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
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\ADMIN\Desktop\LazyFoo\01_hello_SDL\01_hello_SDL

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\ADMIN\Desktop\LazyFoo\01_hello_SDL\01_hello_SDL\build

# Include any dependencies generated for this target.
include CMakeFiles/Lesson3.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Lesson3.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Lesson3.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Lesson3.dir/flags.make

CMakeFiles/Lesson3.dir/src/main.cpp.obj: CMakeFiles/Lesson3.dir/flags.make
CMakeFiles/Lesson3.dir/src/main.cpp.obj: CMakeFiles/Lesson3.dir/includes_CXX.rsp
CMakeFiles/Lesson3.dir/src/main.cpp.obj: C:/Users/ADMIN/Desktop/LazyFoo/01_hello_SDL/01_hello_SDL/src/main.cpp
CMakeFiles/Lesson3.dir/src/main.cpp.obj: CMakeFiles/Lesson3.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\ADMIN\Desktop\LazyFoo\01_hello_SDL\01_hello_SDL\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Lesson3.dir/src/main.cpp.obj"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Lesson3.dir/src/main.cpp.obj -MF CMakeFiles\Lesson3.dir\src\main.cpp.obj.d -o CMakeFiles\Lesson3.dir\src\main.cpp.obj -c C:\Users\ADMIN\Desktop\LazyFoo\01_hello_SDL\01_hello_SDL\src\main.cpp

CMakeFiles/Lesson3.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Lesson3.dir/src/main.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\ADMIN\Desktop\LazyFoo\01_hello_SDL\01_hello_SDL\src\main.cpp > CMakeFiles\Lesson3.dir\src\main.cpp.i

CMakeFiles/Lesson3.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Lesson3.dir/src/main.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\ADMIN\Desktop\LazyFoo\01_hello_SDL\01_hello_SDL\src\main.cpp -o CMakeFiles\Lesson3.dir\src\main.cpp.s

# Object files for target Lesson3
Lesson3_OBJECTS = \
"CMakeFiles/Lesson3.dir/src/main.cpp.obj"

# External object files for target Lesson3
Lesson3_EXTERNAL_OBJECTS =

Lesson3.exe: CMakeFiles/Lesson3.dir/src/main.cpp.obj
Lesson3.exe: CMakeFiles/Lesson3.dir/build.make
Lesson3.exe: C:/SDL2-2.30.5/i686-w64-mingw32/lib/libSDL2main.a
Lesson3.exe: C:/SDL2-2.30.5/i686-w64-mingw32/lib/libSDL2.dll.a
Lesson3.exe: C:/SDL2-2.30.5/i686-w64-mingw32/lib/libSDL2_image.dll.a
Lesson3.exe: CMakeFiles/Lesson3.dir/linkLibs.rsp
Lesson3.exe: CMakeFiles/Lesson3.dir/objects1.rsp
Lesson3.exe: CMakeFiles/Lesson3.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:\Users\ADMIN\Desktop\LazyFoo\01_hello_SDL\01_hello_SDL\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Lesson3.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Lesson3.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Lesson3.dir/build: Lesson3.exe
.PHONY : CMakeFiles/Lesson3.dir/build

CMakeFiles/Lesson3.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Lesson3.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Lesson3.dir/clean

CMakeFiles/Lesson3.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\ADMIN\Desktop\LazyFoo\01_hello_SDL\01_hello_SDL C:\Users\ADMIN\Desktop\LazyFoo\01_hello_SDL\01_hello_SDL C:\Users\ADMIN\Desktop\LazyFoo\01_hello_SDL\01_hello_SDL\build C:\Users\ADMIN\Desktop\LazyFoo\01_hello_SDL\01_hello_SDL\build C:\Users\ADMIN\Desktop\LazyFoo\01_hello_SDL\01_hello_SDL\build\CMakeFiles\Lesson3.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/Lesson3.dir/depend

