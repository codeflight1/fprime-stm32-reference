// ======================================================================
// \title  Main.cpp
// \brief main program for the F' application. Intended for CLI-based systems (Linux, macOS)
//
// ======================================================================
// Used to access topology functions
#include <Core/Top/CoreTopology.hpp>

// OSAL initialization
#include <Os/Os.hpp>
// Used for signal handling shutdown
#include <signal.h>
// Used for printf functions
#include <cstdlib>

/**
 * \brief print command line help message
 *
 * This will print a command line help message including the available command line arguments.
 *
 * @param app: name of application
 */
void print_usage(const char* app) {
    (void)printf("Usage: ./%s [options]\n-b\tBaud rate\n-d\tUART Device\n", app);
}

/**
 * \brief shutdown topology cycling on signal
 *
 * The reference topology allows for a simulated cycling of the rate groups. This simulated cycling needs to be stopped
 * in order for the program to shutdown. This is done via handling signals such that it is performed via Ctrl-C
 *
 * @param signum
 */
static void signalHandler(int signum) {
    Core::stopSimulatedCycle();
}

/**
 * \brief execute the program
 *
 * This F´ program is designed to run in standard environments (e.g. Linux/macOs running on a laptop). Thus it uses
 * command line inputs to specify how to connect.
 *
 * @param argc: argument count supplied to program
 * @param argv: argument values supplied to program
 * @return: 0 on success, something else on failure
 */
int fsw_main() {
    Os::init();

    Core::TopologyState inputs;

    // Setup, cycle, and teardown topology
    Core::setupTopology(inputs);
    Core::startSimulatedCycle(Fw::TimeInterval(1,0));  // Program loop cycling rate groups at 1Hz
    Core::teardownTopology(inputs);
    // (void)printf("Exiting...\n");
    return 0;
}
