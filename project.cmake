# This CMake file is intended to register project-wide objects.
# This allows for reuse between deployments, or other projects.

add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/Components/Led/")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/Components/UartDriver/")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/Components/PassiveDriver/")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/Core/")
