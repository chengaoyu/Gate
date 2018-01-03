#ifndef GATEMULTIPATCHPETSYSTEM_HH
#define GATEMULTIPATCHPETSYSTEM_HH

#include "globals.hh"
#include "GateVSystem.hh"

class GateClockDependentMessenger;

class GateMultiPatchPETSystem : public GateVSystem
{
public:
    GateMultiPatchPETSystem(const G4String& itsName);
    virtual ~GateMultiPatchPETSystem();

    //virtual void Describe(size_t indent = 0);

   // virtual void PrintToStream(std::ostream& aStream, G4bool doPrintNumbers);

    //virtual G4double ComputeInternalRadius();
private:
    GateClockDependentMessenger * m_messenger;


};



#endif // GATEMULTIPATCHPETSYSTEM_HH
