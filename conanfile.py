from conans import ConanFile, CMake, tools
import os

class image_manager(ConanFile):
    name = "image_manager"
    version = "0.0.0"
    license = "None"
    author = "fDarkShadow"
    settings = "os", "compiler", "arch", "build_type"
    url = "http://www.(...)"
    export_sources = ["include/*", "CMakeLists.txt", "tests/*"]
    no_copy_source = True
    generators = "cmake", "txt"

    def imports(self):
        self.copy("*.cmake")

    def build_requirements(self):
        self.build_requires("CMakeCommonOptions/[^1.0.0]@common/stable")
        self.build_requires("catch2/[^2.13.4]@common/stable")

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
        cmake.test()

    def package(self):
        self.copy("*.hpp", dst="include",src="include")