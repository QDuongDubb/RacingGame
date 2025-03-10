# Locate SDL2 library
# This module defines
# SDL2_LIBRARY, the name of the library to link against
# SDL2_FOUND, if false, do not try to link to SDL2
# SDL2_INCLUDE_DIR, where to find SDL.h
#
# This module responds to the the flag:
# SDL2_BUILDING_LIBRARY
# If this is defined, then no SDL2_main will be linked in because
# only applications need main().
# Otherwise, it is assumed you are building an application and this
# module will attempt to locate and set the the proper link flags
# as part of the returned SDL2_LIBRARY variable.
#
# Don't forget to include SDL2main.h and SDL2main.m your project for the
# OS X framework based version. (Other versions link to -lSDL2main which
# this module will try to find on your behalf.) Also for OS X, this
# module will automatically add the -framework Cocoa on your behalf.
#
#
# Additional Note: If you see an empty SDL2_LIBRARY_TEMP in your configuration
# and no SDL2_LIBRARY, it means CMake did not find your SDL2 library
# (SDL2.dll, libsdl2.so, SDL2.framework, etc).
# Set SDL2_LIBRARY_TEMP to point to your SDL2 library, and configure again.
# Similarly, if you see an empty SDL2MAIN_LIBRARY, you should set this value
# as appropriate. These values are used to generate the final SDL2_LIBRARY
# variable, but when these values are unset, SDL2_LIBRARY does not get created.
#
#
# $SDL2 is an environment variable that would
# correspond to the ./configure --prefix=$SDL2
# used in building SDL2.
# l.e.galup 9-20-02
#
# Modified by Eric Wing.
# Added code to assist with automated building by using environmental variables
# and providing a more controlled/consistent search behavior.
# Added new modifications to recognize OS X frameworks and
# additional Unix paths (FreeBSD, etc).
# Also corrected the header search path to follow "proper" SDL2 guidelines.
# Added a search for SDL2main which is needed by some platforms.
# Added a search for threads which is needed by some platforms.
# Added needed compile switches for MinGW.
#
# On OSX, this will prefer the Framework version (if found) over others.
# People will have to manually change the cache values of
# SDL2_LIBRARY to override this selection or set the CMake environment
# CMAKE_INCLUDE_PATH to modify the search paths.
#
# Note that the header path has changed from SDL2/SDL.h to just SDL.h
# This needed to change because "proper" SDL2 convention
# is #include "SDL.h", not <SDL2/SDL.h>. This is done for portability
# reasons because not all systems place things in SDL2/ (see FreeBSD).
#
# Ported by Johnny Patterson. This is a literal port for SDL2 of the FindSDL.cmake
# module with the minor edit of changing "SDL" to "SDL2" where necessary. This
# was not created for redistribution, and exists temporarily pending official
# SDL2 CMake modules.
#
# Note that on windows this will only search for the 32bit libraries, to search
# for 64bit change x86/i686-w64 to x64/x86_64-w64

#=============================================================================
# Copyright 2003-2009 Kitware, Inc.
#
# CMake - Cross Platform Makefile Generator
# Copyright 2000-2014 Kitware, Inc.
# Copyright 2000-2011 Insight Software Consortium
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
# * Redistributions of source code must retain the above copyright
# notice, this list of conditions and the following disclaimer.
#
# * Redistributions in binary form must reproduce the above copyright
# notice, this list of conditions and the following disclaimer in the
# documentation and/or other materials provided with the distribution.
#
# * Neither the names of Kitware, Inc., the Insight Software Consortium,
# nor the names of their contributors may be used to endorse or promote
# products derived from this software without specific prior written
# permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
# HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
# LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
# This software is distributed WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the License for more information.
#=============================================================================
# (To distribute this file outside of CMake, substitute the full
# License text for the above reference.)

FIND_PATH(SDL2_INCLUDE_DIR SDL.h
	HINTS
	${SDL2}
	$ENV{SDL2}
	PATH_SUFFIXES include/SDL2 include SDL2
	i686-w64-mingw32/include/SDL2
	x86_64-w64-mingw32/include/SDL2
	PATHS
	~/Library/Frameworks
	/Library/Frameworks
	/usr/local/include/SDL2
	/usr/include/SDL2
	/sw # Fink
	/opt/local # DarwinPorts
	/opt/csw # Blastwave
	/opt
    "C:\\SDL2-2.30.5\\i686-w64-mingw32\\include\\SDL2"
)

# Lookup the 64 bit libs on x64
IF(CMAKE_SIZEOF_VOID_P EQUAL 8)
	FIND_LIBRARY(SDL2_LIBRARY_TEMP SDL2
		HINTS
		${SDL2}
		$ENV{SDL2}
		PATH_SUFFIXES lib64 lib
		lib/x64
		x86_64-w64-mingw32/lib
		PATHS
		/sw
		/opt/local
		/opt/csw
		/opt
        "C:\\SDL2-2.30.5\\x86_64-w64-mingw32\\lib"
	)
# On 32bit build find the 32bit libs
ELSE(CMAKE_SIZEOF_VOID_P EQUAL 8)
	FIND_LIBRARY(SDL2_LIBRARY_TEMP SDL2
		HINTS
		${SDL2}
		$ENV{SDL2}
		PATH_SUFFIXES lib
		lib/x86
		i686-w64-mingw32/lib
		PATHS
		/sw
		/opt/local
		/opt/csw
		/opt
        "C:\\SDL2-2.30.5\\i686-w64-mingw32\\lib"
	)
ENDIF(CMAKE_SIZEOF_VOID_P EQUAL 8)

IF(NOT SDL2_BUILDING_LIBRARY)
	IF(NOT ${SDL2_INCLUDE_DIR} MATCHES ".framework")
		# Non-OS X framework versions expect you to also dynamically link to
		# SDL2main. This is mainly for Windows and OS X. Other (Unix) platforms
		# seem to provide SDL2main for compatibility even though they don't
		# necessarily need it.
		# Lookup the 64 bit libs on x64
		IF(CMAKE_SIZEOF_VOID_P EQUAL 8)
			FIND_LIBRARY(SDL2MAIN_LIBRARY
				NAMES SDL2main
				HINTS
				${SDL2}
				$ENV{SDL2}
				PATH_SUFFIXES lib64 lib
				lib/x64
				x86_64-w64-mingw32/lib
				PATHS
				/sw
				/opt/local
				/opt/csw
				/opt
                "C:\\SDL2-2.30.5\\x86_64-w64-mingw32\\lib"
				)
			# On 32bit build find the 32bit libs
		ELSE(CMAKE_SIZEOF_VOID_P EQUAL 8)
			FIND_LIBRARY(SDL2MAIN_LIBRARY
				NAMES SDL2main
				HINTS
				${SDL2}
				$ENV{SDL2}
				PATH_SUFFIXES lib
				lib/x86
				i686-w64-mingw32/lib
				PATHS
				/sw
				/opt/local
				/opt/csw
				/opt
                "C:\\SDL2-2.30.5\\i686-w64-mingw32\\lib"
				)
		ENDIF(CMAKE_SIZEOF_VOID_P EQUAL 8)
	ENDIF(NOT ${SDL2_INCLUDE_DIR} MATCHES ".framework")
ENDIF(NOT SDL2_BUILDING_LIBRARY)

# SDL2 may require threads on your system.
# The Apple build may not need an explicit flag because one of the
# frameworks may already provide it.
# But for non-OSX systems, I will use the CMake Threads package.
IF(NOT APPLE)
	FIND_PACKAGE(Threads)
ENDIF(NOT APPLE)

# MinGW needs an additional library, mwindows
# It's total link flags should look like -lmingw32 -lSDL2main -lSDL2 -lmwindows
# (Actually on second look, I think it only needs one of the m* libraries.)
IF(MINGW)
	SET(MINGW32_LIBRARY mingw32 CACHE STRING "mwindows for MinGW")
ENDIF(MINGW)

SET(SDL2_FOUND "NO")
	IF(SDL2_LIBRARY_TEMP)
		# For SDL2main
		IF(NOT SDL2_BUILDING_LIBRARY)
			IF(SDL2MAIN_LIBRARY)
				SET(SDL2_LIBRARY_TEMP ${SDL2MAIN_LIBRARY} ${SDL2_LIBRARY_TEMP})
			ENDIF(SDL2MAIN_LIBRARY)
		ENDIF(NOT SDL2_BUILDING_LIBRARY)

		# For OS X, SDL2 uses Cocoa as a backend so it must link to Cocoa.
		# CMake doesn't display the -framework Cocoa string in the UI even
		# though it actually is there if I modify a pre-used variable.
		# I think it has something to do with the CACHE STRING.
		# So I use a temporary variable until the end so I can set the
		# "real" variable in one-shot.
		IF(APPLE)
			SET(SDL2_LIBRARY_TEMP ${SDL2_LIBRARY_TEMP} "-framework Cocoa")
		ENDIF(APPLE)

		# For threads, as mentioned Apple doesn't need this.
		# In fact, there seems to be a problem if I used the Threads package
		# and try using this line, so I'm just skipping it entirely for OS X.
		IF(NOT APPLE)
			SET(SDL2_LIBRARY_TEMP ${SDL2_LIBRARY_TEMP} ${CMAKE_THREAD_LIBS_INIT})
		ENDIF(NOT APPLE)

		# For MinGW library
		IF(MINGW)
			SET(SDL2_LIBRARY_TEMP ${MINGW32_LIBRARY} ${SDL2_LIBRARY_TEMP})
		ENDIF(MINGW)

		# Set the final string here so the GUI reflects the final state.
		SET(SDL2_LIBRARY ${SDL2_LIBRARY_TEMP} CACHE STRING "Where the SDL2 Library can be found")
		# Set the temp variable to INTERNAL so it is not seen in the CMake GUI
		SET(SDL2_LIBRARY_TEMP "${SDL2_LIBRARY_TEMP}" CACHE INTERNAL "")

		SET(SDL2_FOUND "YES")
ENDIF(SDL2_LIBRARY_TEMP)

INCLUDE(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(SDL2 REQUIRED_VARS SDL2_LIBRARY SDL2_INCLUDE_DIR)