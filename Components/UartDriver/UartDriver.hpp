// ======================================================================
// \title  LinuxUartDriverImpl.hpp
// \author tcanham
// \brief  hpp file for LinuxUartDriver component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#ifndef UartDriver_HPP
#define UartDriver_HPP

#include <Components/UartDriver/UartDriverComponentAc.hpp>
#include <Os/Mutex.hpp>
#include <Os/Task.hpp>

#include "stm32_hal.h"

namespace Components {

class UartDriver : public UartDriverComponentBase {
  public:
    // ----------------------------------------------------------------------
    // Construction, initialization, and destruction
    // ----------------------------------------------------------------------

    //! Construct object LinuxUartDriver
    //!
    UartDriver(const char* const compName /*!< The component name*/
    );

    // Open device with specified baud and flow control.
    bool open();

    //! start the serial poll thread.
    //! buffSize is the max receive buffer size
    //!
    void start(Os::Task::ParamType priority = Os::Task::TASK_DEFAULT,
               Os::Task::ParamType stackSize = Os::Task::TASK_DEFAULT,
               Os::Task::ParamType cpuAffinity = Os::Task::TASK_DEFAULT);

    //! Quit thread
    void quitReadThread();

    //! Join thread
    Os::Task::Status join();

    //! Destroy object LinuxUartDriver
    //!
    ~UartDriver();

  PRIVATE:
    // ----------------------------------------------------------------------
    // Handler implementations for user-defined typed input ports
    // ----------------------------------------------------------------------

    //! Handler implementation for serialSend
    //!
    void send_handler(FwIndexType portNum, /*!< The port number*/
                                 Fw::Buffer& serBuffer) override;

    //! Handler implementation for recvReturnIn
    //!
    //! Port receiving back ownership of data sent out on $recv port
    void recvReturnIn_handler(FwIndexType portNum,  //!< The port number
                                Fw::Buffer& fwBuffer  //!< The buffer
                                ) override;

    //! This method will be called by the new thread to wait for input on the serial port.
    static void serialReadTaskEntry(void* ptr);

    UART_HandleTypeDef uart;
};

}  // end namespace Drv

#endif
