####
# FPrime CMakeLists.txt:
#
# SOURCE_FILES: combined list of source and autocoding files
# MOD_DEPS: (optional) module dependencies
# UT_SOURCE_FILES: list of source files for unit tests
#
# More information in the F´ CMake API documentation:
# https://fprime.jpl.nasa.gov/latest/documentation/reference
#
####

register_fprime_module(
    SOURCES
        "${CMAKE_CURRENT_LIST_DIR}/Led.fpp"
        "${CMAKE_CURRENT_LIST_DIR}/Led.cpp"
)
