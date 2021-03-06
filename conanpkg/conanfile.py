from conans import ConanFile, CMake, tools


class SemverConan(ConanFile):
    name = "Versioning"
    version = "2.0.0"
    license = "MIT"
    url = "https://github.com/santoro-mariano/semver.git"
    description = "Validating semantic versioning (semver) parser and comparator written in C++"
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False]}
    default_options = "shared=False"
    generators = "cmake"

    def source(self):
        self.run("git clone https://github.com/santoro-mariano/semver.git")
        self.run("cd semver")
	#removing testing part (to avoid boost dependency)
	tools.replace_in_file("semver/CMakeLists.txt", "add_subdirectory(test)", "")
        # This small hack might be useful to guarantee proper /MT /MD linkage in MSVC
        # if the packaged project doesn't have variables to set it properly
        tools.replace_in_file("semver/CMakeLists.txt", "project(versioning)", '''project(versioning)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()''')

    def build(self):
        cmake = CMake(self)
        cmake.configure(source_dir="%s/semver" % self.source_folder)
        cmake.build()
        
    def package(self):
	self.copy("*.*", dst="include", src="semver/include")
        self.copy("*versioning.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.dylib", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ["versioning"]
