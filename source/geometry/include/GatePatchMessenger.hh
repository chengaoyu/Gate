#ifndef GATEPATCHMESSENGER_HH
#define GATEPATCHMESSENGER_HH

#include "globals.hh"
#include "GateVolumeMessenger.hh"

class GatePatch;
class GatePatchMessenger : public GateVolumeMessenger
{
public:
    GatePatchMessenger( GatePatch* itsCreator);
    virtual ~GatePatchMessenger();
    void SetNewValue(G4UIcommand*, G4String);
    virtual inline GatePatch* GetPatchCreator(){
        return (GatePatch*) GetVolumeCreator();
    }

private:
    G4UIcmdWithAString* PathToPatchFileCmd;

};


#endif // GATEPATCHMESSENGER_HH
