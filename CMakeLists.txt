cmake_minimum_required(VERSION 2.8)
project(versioning)

set(CMAKE_CXX_STANDARD 14)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(VERSION_MAJOR   "2")
set(VERSION_MINOR   "0")
set(VERSION_PATCH   "0")
set(VERSION_RELEASE "")
set(VERSION_BUILD   "")

# Build full version string, including optional components
string(COMPARE NOTEQUAL VERSION_RELEASE "" HAVE_RELEASE)
string(COMPARE NOTEQUAL VERSION_BUILD "" HAVE_BUILD)
set(VERSION_FULL "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")
if(HAVE_RELEASE)
	set(VERSION_FULL "${VERSION_FULL}-${VERSION_RELEASE}")
endif()
if(HAVE_BUILD)
	set(VERSION_FULL "${VERSION_FULL}+${VERSION_BUILD}")
endif()

if(UNIX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -pedantic")
endif()

if(WIN32)
	add_definitions(-DWINVER=0x0601)
	add_definitions(-D_WIN32_WINNT=0x0601)
endif()

if(MSVC)
    add_definitions(-DWall)
    add_definitions(-DWX) #Warnings as errors
	add_definitions(-D_SCL_SECURE_NO_WARNINGS)
endif()


#set sources
FILE(GLOB_RECURSE LIB_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
#set library
add_library (versioning STATIC ${LIB_SOURCE_FILES})

#set includes
target_include_directories(versioning PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:include>
		PRIVATE src)

add_subdirectory(test)

enable_testing()
add_test(NAME semver200_parser_tests COMMAND semver200_parser_tests)
add_test(NAME semver200_comparator_tests COMMAND semver200_comparator_tests)
add_test(NAME semver200_version_tests COMMAND semver200_version_tests)
add_test(NAME semver200_modifier_tests COMMAND semver200_modifier_tests)
