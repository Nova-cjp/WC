# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.15

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "E:\Program Files\JetBrains\CLion 2019.3.3\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "E:\Program Files\JetBrains\CLion 2019.3.3\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\24277\Desktop\WC

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\24277\Desktop\WC\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles\WC.dir\depend.make

# Include the progress variables for this target.
include CMakeFiles\WC.dir\progress.make

# Include the compile flags for this target's objects.
include CMakeFiles\WC.dir\flags.make

CMakeFiles\WC.dir\main.cpp.obj: CMakeFiles\WC.dir\flags.make
CMakeFiles\WC.dir\main.cpp.obj: ..\main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\24277\Desktop\WC\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/WC.dir/main.cpp.obj"
	C:\PROGRA~2\MICROS~4\2019\COMMUN~1\VC\Tools\MSVC\1421~1.277\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\WC.dir\main.cpp.obj /FdCMakeFiles\WC.dir\ /FS -c C:\Users\24277\Desktop\WC\main.cpp
<<

CMakeFiles\WC.dir\main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/WC.dir/main.cpp.i"
	C:\PROGRA~2\MICROS~4\2019\COMMUN~1\VC\Tools\MSVC\1421~1.277\bin\Hostx86\x86\cl.exe > CMakeFiles\WC.dir\main.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\24277\Desktop\WC\main.cpp
<<

CMakeFiles\WC.dir\main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/WC.dir/main.cpp.s"
	C:\PROGRA~2\MICROS~4\2019\COMMUN~1\VC\Tools\MSVC\1421~1.277\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\WC.dir\main.cpp.s /c C:\Users\24277\Desktop\WC\main.cpp
<<

# Object files for target WC
WC_OBJECTS = \
"CMakeFiles\WC.dir\main.cpp.obj"

# External object files for target WC
WC_EXTERNAL_OBJECTS =

WC.exe: CMakeFiles\WC.dir\main.cpp.obj
WC.exe: CMakeFiles\WC.dir\build.make
WC.exe: CMakeFiles\WC.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\24277\Desktop\WC\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable WC.exe"
	"E:\Program Files\JetBrains\CLion 2019.3.3\bin\cmake\win\bin\cmake.exe" -E vs_link_exe --intdir=CMakeFiles\WC.dir --rc=C:\PROGRA~2\WI3CF2~1\10\bin\100177~1.0\x86\rc.exe --mt=C:\PROGRA~2\WI3CF2~1\10\bin\100177~1.0\x86\mt.exe --manifests  -- C:\PROGRA~2\MICROS~4\2019\COMMUN~1\VC\Tools\MSVC\1421~1.277\bin\Hostx86\x86\link.exe /nologo @CMakeFiles\WC.dir\objects1.rsp @<<
 /out:WC.exe /implib:WC.lib /pdb:C:\Users\24277\Desktop\WC\cmake-build-debug\WC.pdb /version:0.0  /machine:X86 /debug /INCREMENTAL /subsystem:console kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib 
<<

# Rule to build all files generated by this target.
CMakeFiles\WC.dir\build: WC.exe

.PHONY : CMakeFiles\WC.dir\build

CMakeFiles\WC.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\WC.dir\cmake_clean.cmake
.PHONY : CMakeFiles\WC.dir\clean

CMakeFiles\WC.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" C:\Users\24277\Desktop\WC C:\Users\24277\Desktop\WC C:\Users\24277\Desktop\WC\cmake-build-debug C:\Users\24277\Desktop\WC\cmake-build-debug C:\Users\24277\Desktop\WC\cmake-build-debug\CMakeFiles\WC.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles\WC.dir\depend

