cmake_minimum_required(VERSION 2.6)
project(01_HELLO_SDL)

# Use our modified FindSDL2* modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${01_HELLO_SDL_SOURCE_DIR}/cmake")
# Set an output directory for our binaries
set(BIN_DIR ${01_HELLO_SDL_SOURCE_DIR}/bin)

# Bump up warning levels appropriately for clang, gcc & msvc
# Also set debug/optimization flags depending on the build type. IDE users choose this when
# selecting the build mode in their IDE
if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -std=c++11")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG} -g")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE} -O2")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
	if (CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
		string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	else()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
	endif()
endif()

# Look up SDL2 and add the include directory to our include path
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})


find_package(SDL2_image REQUIRED)
include_directories(${SDL2_IMAGE_INCLUDE_DIR})
file(GLOB SRC_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)
# Install target is the same as before
find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_TTF_INCLUDE_DIR})

find_package(SDL2_mixer REQUIRED)
include_directories(${SDL2_MIXER_INCLUDE_DIR})

# Look in the Lesson0 subdirectory to find its CMakeLists.txt so we can build the executable

add_executable(01_HELLO_SDL ${SRC_FILES})
target_link_libraries(01_HELLO_SDL ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${SDL2_TTF_LIBRARY} ${SDL2_MIXER_LIBRARY})	
install(TARGETS 01_HELLO_SDL RUNTIME DESTINATION ${BIN_DIR})