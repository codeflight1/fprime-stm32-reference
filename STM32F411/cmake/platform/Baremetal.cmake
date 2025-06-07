if (NOT DEFINED FPRIME_USE_STUBBED_DRIVERS)
   set(FPRIME_USE_STUBBED_DRIVERS ON)
endif()

add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/Platform/")

register_fprime_config(
      PlatformSTM
    CHOOSES_IMPLEMENTATIONS
      Os_Cpu_Baremetal
      Os_Memory_Baremetal
      Os_Task_Baremetal
      Os_Console_Stub
      Os_File_Stub
      Os_Generic_PriorityQueue
      Os_Mutex_Stub
      Os_RawTime_Stub
      Fw_StringFormat_snprintf
    INTERFACE # No buildable files generated
)
