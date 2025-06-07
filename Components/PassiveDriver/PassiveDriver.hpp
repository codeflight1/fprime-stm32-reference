// ======================================================================
// \title  PassiveDriver.hpp
// \author nate
// \brief  hpp file for PassiveDriver component implementation class
// ======================================================================

#ifndef Components_PassiveDriver_HPP
#define Components_PassiveDriver_HPP

#include "Components/PassiveDriver/PassiveDriverComponentAc.hpp"

namespace Components {

  class PassiveDriver final :
    public PassiveDriverComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Component construction and destruction
      // ----------------------------------------------------------------------

      //! Construct PassiveDriver object
      PassiveDriver(
          const char* const compName //!< The component name
      );

      //! Destroy PassiveDriver object
      ~PassiveDriver();

      void call();

    private:
      Os::RawTime m_rawTime;

  };

}

#endif
