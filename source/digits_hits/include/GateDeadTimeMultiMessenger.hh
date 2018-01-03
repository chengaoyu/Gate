#ifndef GateDeadTimeMultiMULTIMESSENGER_HH
#define GateDeadTimeMultiMULTIMESSENGER_HH


#include "GatePulseProcessorMessenger.hh"

class G4UIdirectory;
class G4UIcmdWithoutParameter;
class G4UIcmdWithAString;
class G4UIcmdWithABool;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADouble;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWith3Vector;
class G4UIcmdWith3VectorAndUnit;

class GateDeadTimeMulti;

class GateDeadTimeMultiMessenger: public GatePulseProcessorMessenger
{
public:
  GateDeadTimeMultiMessenger(GateDeadTimeMulti* itsDeadTime);
  virtual ~GateDeadTimeMultiMessenger();

  inline void SetNewValue(G4UIcommand* aCommand, G4String aString);

  inline GateDeadTimeMulti* GetDeadTime(){ return (GateDeadTimeMulti*) GetPulseProcessor(); }

private:
  G4UIcmdWithADoubleAndUnit *deadTimeCmd; //!< set the dead time value
  G4UIcmdWithAString   *newVolCmd;        //!< set the geometric level of application
  G4UIcmdWithAString   *modeCmd;          //!< set the dead time mode
  G4UIcmdWithADoubleAndUnit   *bufferSizeCmd; //!< set the buffer size
  G4UIcmdWithAnInteger   *bufferModeCmd;      //!< set the buffer usage mode
};

#endif // GateDeadTimeMultiMULTIMESSENGER_HH
