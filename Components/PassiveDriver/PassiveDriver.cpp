// ======================================================================
// \title  PassiveDriver.cpp
// \author nate
// \brief  cpp file for PassiveDriver component implementation class
// ======================================================================

#include "Components/PassiveDriver/PassiveDriver.hpp"
#include "PassiveDriver.hpp"

namespace Components {

  // ----------------------------------------------------------------------
  // Component construction and destruction
  // ----------------------------------------------------------------------

  PassiveDriver ::
    PassiveDriver(const char* const compName) :
      PassiveDriverComponentBase(compName)
  {

  }

  PassiveDriver ::
    ~PassiveDriver()
  {

  }

  void PassiveDriver::call() {
    this->m_rawTime.now();
    this->CycleOut_out(0,this->m_rawTime);
  }

}
