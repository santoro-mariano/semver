if(WIN32)
    set(BOOST_INCLUDEDIR "C:/boost_1_64_0")
    set(BOOST_LIBRARYDIR "C:/boost_1_64_0/stage/lib")
    set(BOOST_ROOT "C:/boost_1_64_0/boost")
endif()

set(Boost_USE_STATIC_LIBS   ON)
set(Boost_USE_MULTITHREADED ON)

find_package(Boost COMPONENTS unit_test_framework)

include_directories(
	${Boost_INCLUDE_DIRS}
)

add_executable(semver200_parser_tests semver/2_0_0/parser_tests.cpp clang_fixes.cpp)
target_link_libraries(semver200_parser_tests
	${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
	versioning
)

add_executable(semver200_comparator_tests semver/2_0_0/comparator_tests.cpp clang_fixes.cpp)
target_link_libraries(semver200_comparator_tests
	${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
	versioning
)

add_executable(semver200_version_tests semver/2_0_0/version_tests.cpp clang_fixes.cpp)
target_link_libraries(semver200_version_tests
	${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
	versioning
)

add_executable(semver200_modifier_tests semver/2_0_0/modifier_tests.cpp clang_fixes.cpp)
target_link_libraries(semver200_modifier_tests
	${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
	versioning
)
