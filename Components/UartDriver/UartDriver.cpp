// ======================================================================
// \title  LinuxUartDriverImpl.cpp
// \author tcanham
// \brief  cpp file for LinuxUartDriver component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#include <unistd.h>
#include <Components/UartDriver/UartDriver.hpp>
#include <Os/TaskString.hpp>

#include "Fw/Types/BasicTypes.hpp"

#include "stm32_hal.h"

namespace Components {

// ----------------------------------------------------------------------
// Construction, initialization, and destruction
// ----------------------------------------------------------------------

UartDriver ::UartDriver(const char* const compName)
    : UartDriverComponentBase(compName) {
}

bool UartDriver::open() {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    /* Peripheral clock enable */
    __HAL_RCC_USART2_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    
    /**USART2 GPIO Configuration
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    uart.Instance = USART2;
    uart.Init.BaudRate = 115200;
    uart.Init.WordLength = UART_WORDLENGTH_8B;
    uart.Init.StopBits = UART_STOPBITS_1;
    uart.Init.Parity = UART_PARITY_NONE;
    uart.Init.Mode = UART_MODE_TX_RX;
    uart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    uart.Init.OverSampling = UART_OVERSAMPLING_16;
    
    if (HAL_UART_Init(&uart) != HAL_OK) {
        return false;
    }

    Fw::LogStringArg _arg = "USART2";
    this->log_ACTIVITY_HI_PortOpened(_arg);
    if (this->isConnected_ready_OutputPort(0)) {
        this->ready_out(0); // Indicate the driver is connected
    }
    return true;
}

UartDriver ::~UartDriver() {
    HAL_UART_DeInit(&uart);

    /* Peripheral clock disable */
    __HAL_RCC_USART2_CLK_DISABLE();

    /**USART2 GPIO Configuration
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2|GPIO_PIN_3);
}

// ----------------------------------------------------------------------
// Handler implementations for user-defined typed input ports
// ----------------------------------------------------------------------

void UartDriver ::send_handler(const FwIndexType portNum, Fw::Buffer& serBuffer) {
    Drv::ByteStreamStatus status = Drv::ByteStreamStatus::OP_OK;
    if (serBuffer.getData() == nullptr || serBuffer.getSize() == 0) {
        status = Drv::ByteStreamStatus::OTHER_ERROR;
    } else {
        unsigned char *data = serBuffer.getData();
        FwSizeType xferSize = static_cast<FwSizeType>(serBuffer.getSize());
        
        HAL_UART_Transmit(&uart, data, serBuffer.getSize(), HAL_MAX_DELAY);
          // this->log_WARNING_HI_WriteError(_arg, stat);
          // status = Drv::SendStatus::SEND_ERROR;
    }
    
    sendReturnOut_out(0, serBuffer, status);
}

void UartDriver::recvReturnIn_handler(FwIndexType portNum, Fw::Buffer& fwBuffer) {
    this->deallocate_out(0, fwBuffer);
}

// void UartDriver ::serialReadTaskEntry(void* ptr) {
//     FW_ASSERT(ptr != nullptr);
//     Drv::RecvStatus status = RecvStatus::RECV_ERROR;  // added by m.chase 03.06.2017
//     LinuxUartDriver* comp = reinterpret_cast<LinuxUartDriver*>(ptr);
//     while (!comp->m_quitReadThread) {
//         Fw::Buffer buff = comp->allocate_out(0,comp->m_allocationSize);
//
//         // On failed allocation, error and deallocate
//         if (buff.getData() == nullptr) {
//             Fw::LogStringArg _arg = comp->m_device;
//             comp->log_WARNING_HI_NoBuffers(_arg);
//             status = RecvStatus::RECV_ERROR;
//             comp->recv_out(0, buff, status);
//             // to avoid spinning, wait 50 ms
//             Os::Task::delay(Fw::TimeInterval(0, 50000));
//             continue;
//         }
//
//         //          timespec stime;
//         //          (void)clock_gettime(CLOCK_REALTIME,&stime);
//         //          DEBUG_PRINT("<<< Calling dsp_relay_uart_relay_read() at %d %d\n", stime.tv_sec, stime.tv_nsec);
//
//         int stat = 0;
//
//         // Read until something is received or an error occurs. Only loop when
//         // stat == 0 as this is the timeout condition and the read should spin
//         while ((stat == 0) && !comp->m_quitReadThread) {
//             stat = static_cast<int>(::read(comp->m_fd, buff.getData(), buff.getSize()));
//         }
//         buff.setSize(0);
//
//         // On error stat (-1) must mark the read as error
//         // On normal stat (>0) pass a recv ok
//         // On timeout stat (0) and m_quitReadThread, error to return the buffer
//         if (stat == -1) {
//             Fw::LogStringArg _arg = comp->m_device;
//             comp->log_WARNING_HI_ReadError(_arg, stat);
//             status = RecvStatus::RECV_ERROR;
//         } else if (stat > 0) {
//             buff.setSize(static_cast<U32>(stat));
//             status = RecvStatus::RECV_OK;  // added by m.chase 03.06.2017
//         } else {
//             status = RecvStatus::RECV_ERROR; // Simply to return the buffer
//         }
//         comp->recv_out(0, buff, status);  // added by m.chase 03.06.2017
//     }
// }
//
// void UartDriver ::start(Os::Task::ParamType priority, Os::Task::ParamType stackSize, Os::Task::ParamType cpuAffinity) {
//     Os::TaskString task("SerReader");
//     Os::Task::Arguments arguments(task, serialReadTaskEntry, this, priority, stackSize, cpuAffinity);
//     Os::Task::Status stat = this->m_readTask.start(arguments);
//     FW_ASSERT(stat == Os::Task::OP_OK, stat);
// }
//
// void UartDriver ::quitReadThread() {
//     this->m_quitReadThread = true;
// }
//
// Os::Task::Status UartDriver ::join() {
//     return m_readTask.join();
// }
//
}  // end namespace Drv
