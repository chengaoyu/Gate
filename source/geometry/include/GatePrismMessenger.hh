/*
 * GatePrismMessenger.hh
 *
 * Create on 2016/11/20
 * by CGY
 *
 */

#ifndef GATEPRISMMESSENGER_HH
#define GATEPRISMMESSENGER_HH

#include"globals.hh"
#include"GateVolumeMessenger.hh"

class GatePrism;
class GatePrismMessenger: public GateVolumeMessenger
{
public:
    GatePrismMessenger(GatePrism* itsCreator);
    ~GatePrismMessenger();

    void SetNewValue(G4UIcommand* ,G4String);
    virtual inline GatePrism* GetPrismCreator()
    {return (GatePrism*)GetVolumeCreator();}
private:
    G4UIcmdWith3VectorAndUnit* PrismP1Cmd;
    G4UIcmdWith3VectorAndUnit* PrismP2Cmd;
    G4UIcmdWith3VectorAndUnit* PrismP3Cmd;
    G4UIcmdWith3VectorAndUnit* PrismP4Cmd;
    G4UIcmdWith3VectorAndUnit* PrismP5Cmd;
    G4UIcmdWith3VectorAndUnit* PrismP6Cmd;
};


#endif // GATEPRISMMESSENGER_HH
