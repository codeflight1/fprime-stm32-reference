// ======================================================================
// \title  Main.cpp
// \brief main program for the F' application. Intended for CLI-based systems (Linux, macOS)
//
// ======================================================================
// Used to access topology functions
#include <Core/Top/CoreTopology.hpp>

// OSAL initialization
#include <Os/Os.hpp>

/**
 * \brief execute the program
 *
 * @return: 0 on success, something else on failure
 */
int fsw_main() {
    Os::init();

    Core::TopologyState inputs;

    // Setup, cycle, and teardown topology
    Core::setupTopology(inputs);
    Core::startSimulatedCycle(Fw::TimeInterval(1,0));  // Program loop cycling rate groups at 1Hz
    Core::teardownTopology(inputs);
    return 0;
}
