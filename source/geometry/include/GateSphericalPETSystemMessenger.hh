/* ----------------------
 * this file is add by CGY
 * at 2016/11/21
 * to provide the prism component
 * to construct the GateSphericalPETSystem
--------------*/

#ifndef GATESPHERICALPETSYSTEMMESSENGER_HH
#define GATESPHERICALPETSYSTEMMESSENGER_HH

#include "GateClockDependentMessenger.hh"

class GateSphericalPETSystem;
class G4UIcmdWithAString;


/*! \class GateSphericalPETSystemMessenger
    \brief Base class for GateSphericalPETSystem messengers

    - GateSphericalPETSystemMessenger - by Daniel.Strul@iphe.unil.ch

    - The GateSphericalPETSystemMessenger inherits from the abilities/responsabilities
      of the GateClockDependentMessenger base-class: creation and management
      of a Gate UI directory for a Gate object; creation of the UI command "describe"

    - In addition, it proposes and manages the UI commands 'enable' and 'disable'.

*/
class GateSphericalPETSystemMessenger: public GateClockDependentMessenger
{
  public:
    //! Constructor
    //! The flags are passed to the base-class GateClockDependentMessenger
    GateSphericalPETSystemMessenger(GateSphericalPETSystem* itsSphericalPETSystem,
                                const G4String& itsDirectoryName="");

   ~GateSphericalPETSystemMessenger();  //!< destructor

    //! UI command interpreter method
    void SetNewValue(G4UIcommand*, G4String);

    //! Get the clock-dependent object
    inline GateSphericalPETSystem* GetSphericalPETSystem()
      { return (GateSphericalPETSystem*) GetClockDependent(); }

  private:

    //G4UIcmdWithAString*    addNewRsectorcmd;
};


#endif // GATESPHERICALPETSYSTEMMESSENGER_HH
