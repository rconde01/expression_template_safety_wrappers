# This file was generated by Conan. Remove this comment if you edit this file or Conan
# will destroy your changes.
from cppstd_compat import cppstd_compat


def compatibility(conanfile):
    configs = cppstd_compat(conanfile)
    # TODO: Append more configurations for your custom compatibility rules
    return configs
