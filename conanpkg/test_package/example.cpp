#include <iostream>
#include "versioning/semver/2_0_0/version.h"

int main() {
    std::cout << "Version: 1.2.3-alpha.1+build.no.123" << std::endl;
    versioning::semver::v200::Version v("1.2.3-alpha.1+build.no.123");
    std::cout << "Major: " << v.Major() << std::endl;
    std::cout << "Minor: " << v.Minor() << std::endl;
    std::cout << "Patch: " << v.Patch() << std::endl;
    std::cout << "Pre-release: " << v.PreRelease() << std::endl;
    std::cout << "Build: " << v.Build() << std::endl;
}
