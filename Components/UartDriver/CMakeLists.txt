####
# F prime CMakeLists.txt:
#
# SOURCE_FILES: combined list of source and autocoding files
# MOD_DEPS: (optional) module dependencies
#
####
# restrict_platforms(Linux Darwin)

set(MOD_DEPS Os STM32_HAL)
set(SOURCE_FILES
    "${CMAKE_CURRENT_LIST_DIR}/UartDriver.fpp"
    "${CMAKE_CURRENT_LIST_DIR}/UartDriver.cpp"
)
register_fprime_module()
