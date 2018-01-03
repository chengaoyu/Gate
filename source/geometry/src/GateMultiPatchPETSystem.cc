/* ----------------------
 * this file is add by CGY
 * at 2017/09/10
 * to provide the patch component
 * to construct the GateMultiPatchsPETSystem
--------------*/

#include "GateMultiPatchPETSystem.hh"

#include "G4UnitsTable.hh"
#include "GateClockDependentMessenger.hh"
#include "GateBox.hh"
#include "GateVolumePlacement.hh"
#include "GateCoincidenceSorter.hh"
#include "GateOutputMgr.hh"

#include "GateConfiguration.h"

#ifdef GATE_USE_LMF
#include "GateToLMF.hh"
#endif

#include "GateDigitizer.hh"


GateMultiPatchPETSystem::GateMultiPatchPETSystem(const G4String& itsName)
    :GateVSystem(itsName,true)
{
    m_messenger = new GateClockDependentMessenger(this);
    m_messenger->SetDirectoryGuidance(G4String("control the system '")+GetObjectName()+"'");

    //Define the scanner components
    GateSystemComponent* aComponent;
    aComponent = new GateSystemComponent("container",GetBaseComponent(),this);
    size_t maxCompNum = 100;
    //new GateSystemComponent("patchName",aComponent,this);
    for (size_t iComp = 0; iComp < maxCompNum; iComp++ ){
        G4String patchName = "Patch" + std::to_string(iComp+1);
        new GateSystemComponent(patchName,aComponent,this);
    }
    // Integrate a coincidence sorter into the digitizer
    G4double coincidenceWindow = 10.* ns;
    GateDigitizer* digitizer = GateDigitizer::GetInstance();
    GateCoincidenceSorter* coincidenceSorter = new GateCoincidenceSorter(digitizer,"Coincidences",coincidenceWindow);
    digitizer->StoreNewCoincidenceSorter(coincidenceSorter);

#ifdef GATE_USE_LMF

  // Insert an LMF output module into the output manager
  GateOutputMgr *outputMgr = GateOutputMgr::GetInstance();
  GateToLMF* gateToLMF1 = new GateToLMF("lmf", outputMgr,this,GateOutputMgr::GetDigiMode()); // this for geometry
  outputMgr->AddOutputModule((GateVOutputModule*)gateToLMF1);

#endif
  SetOutputIDName((char *)"containerID",1);
/*  SetOutputIDName((char *)"level5ID",5);*/
  SetOutputIDName((char *)"patchID",2);
}

GateMultiPatchPETSystem::~GateMultiPatchPETSystem(){
    delete m_messenger;
}
