register_fprime_module(
    SOURCES
        "${CMAKE_CURRENT_LIST_DIR}/instances.fpp"
        # Note: Uncomment when using Svc:TlmPacketizer
        #"${CMAKE_CURRENT_LIST_DIR}/CorePackets.xml"
        "${CMAKE_CURRENT_LIST_DIR}/topology.fpp"
        "${CMAKE_CURRENT_LIST_DIR}/CoreTopology.cpp"
    DEPENDS
        Fw/Logger
)
