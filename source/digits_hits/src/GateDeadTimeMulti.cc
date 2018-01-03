/*----------------------
   Copyright (C): OpenGATE Collaboration

This software is distributed under the terms
of the GNU Lesser General  Public Licence (LGPL)
See GATE/LICENSE.txt for further details
----------------------*/


#include "GateDeadTimeMulti.hh"
#include "G4UnitsTable.hh"
#include "GateDeadTimeMultiMessenger.hh"
#include "GateTools.hh"
#include "GateVolumeID.hh"
#include "GateOutputVolumeID.hh"
#include "GateDetectorConstruction.hh"
#include "GateCrystalSD.hh"
#include "GateVSystem.hh"
#include "GateObjectChildList.hh"
#include "GateVVolume.hh"
#include "GateMaps.hh"


GateDeadTimeMulti::GateDeadTimeMulti(GatePulseProcessorChain* itsChain,
               const G4String& itsName)
  : GateVPulseProcessor(itsChain,itsName)
  , m_bufferSizeMulti(0)
  , m_bufferModeMulti(0)
{
  m_isParalysableMutlti = false;
  m_deadTimeMulti = 0;
  //m_deadTimeTableMulti = NULL;

  m_messengerMulti = new GateDeadTimeMultiMessenger(this);
}




GateDeadTimeMulti::~GateDeadTimeMulti()
{
  //if(m_deadTimeTable) delete(m_deadTimeTable);
  //if(m_bufferCurrentSize) delete(m_bufferCurrentSize);
  delete m_messengerMulti;
}




void GateDeadTimeMulti::ProcessOnePulse(const GatePulse* inputPulse,GatePulseList& outputPulseList)
{
    static G4int m_doneOnce = 0;      // equal to 0 before first ProcessOnPulse use, then 1

    if(!m_doneOnce)
      {

        m_doneOnce = 1;
        if(!m_testVolumeMulti)
      {
        G4cerr << 	Gateendl << "[GateDeadTime::ProcessOnePulse]:\n"
           <<   "Sorry, but you don't have chosen any volume !\n";
      }



        if (nVerboseLevel>1)
      {
        G4cout << "first pass in dead time pulse process\n" ;
        G4cout << "deadtime set at  " << m_deadTimeMulti << " ps"<< Gateendl ;
        G4cout << "mode = " << (m_isParalysableMutlti ? "paralysable":"non-paralysable") << Gateendl ;
      }

      }
    if (!inputPulse)
      {
        if (nVerboseLevel>1)
          G4cout << "[GateDeadTime::ProcessOnePulse]: input pulse was null -> nothing to do\n\n";
        return;
      }

    if (inputPulse->GetEnergy()==0)
      {
        if (nVerboseLevel>1)
      G4cout << "[GateDeadTime::ProcessOneHit]: energy is null for " << inputPulse << " -> pulse ignored\n\n";
        return;
      }


    // FIND THE ELEMENT ID OF PULSE
    const GateVolumeID* aVolumeID = &inputPulse->GetVolumeID();
    G4int m_generalDetId = 0; // a unique number for each detector part
                              // that depends of the depth of application
                              // of the dead time
    size_t m_depth = (size_t)(aVolumeID->GetCreatorDepth(m_volumeNameMulti))+1;

    m_generalDetId = aVolumeID->GetDaughterID(m_depth);
  //////////////////////////////////////////////////////////////
    // FIND TIME OF PULSE
    unsigned long long int currentTime = (unsigned long long int)((inputPulse->GetTime())/picosecond);
    if (nVerboseLevel>5)
      {
        G4cout << "A new pulse is processed by dead time time : " << (inputPulse->GetTime())/picosecond
           << " =  "<< currentTime  << Gateendl  ;
        G4cout << "ID elt = " <<  m_generalDetId << Gateendl ;
        G4cout << "Rebirth time for elt " << m_generalDetId << " = " << m_deadTimeTableMulti[m_generalDetId]<< Gateendl ;

      }
    // IS DETECTOR DEAD ?
    if (currentTime >=  m_deadTimeTableMulti[m_generalDetId])
      {
        // NO DETECTOR IS NOT DEAD : COPY THIS PULSE TO OUTPUT PULSE LIST
        GatePulse* outputPulse = new GatePulse(*inputPulse);
        outputPulseList.push_back(outputPulse);

  //      m_deadTimeTable[m_generalDetId] = currentTime + m_deadTime;
        if (m_bufferSizeMulti>1){
          m_bufferCurrentSizeMulti[m_generalDetId]++;
      if (m_bufferCurrentSizeMulti[m_generalDetId]==m_bufferSizeMulti){
          m_deadTimeTableMulti[m_generalDetId] = currentTime + m_deadTimeMulti;
          m_bufferCurrentSizeMulti[m_generalDetId]=0;
      }
        } else {
          m_deadTimeTableMulti[m_generalDetId] = currentTime + m_deadTimeMulti;
        }
        if (nVerboseLevel>5){
        G4cout << "We have accept " << currentTime << " a pulse in element " << m_generalDetId <<
          "\trebirth time\t" << m_deadTimeTableMulti[m_generalDetId] << Gateendl;
        G4cout << "Copied pulse to output:\n"
           << *outputPulse << Gateendl << Gateendl ;
        }
      }
    else
      {
        // YES DETECTOR IS DEAD : REMOVE PULSE
        if (nVerboseLevel>5)
      G4cout << "Removed pulse, due to dead time:\n";
        // AND IF "PARALYSABLE" DEAD TIME, MAKE THE DEATH OF DETECTOR LONGER
        if ((m_bufferSizeMulti>1) && (m_bufferModeMulti==1)){
      if (m_bufferCurrentSizeMulti[m_generalDetId]<m_bufferSizeMulti-1) {
              m_bufferCurrentSizeMulti[m_generalDetId]++;
              outputPulseList.push_back(new GatePulse(*inputPulse));
      }
        } else {
          if(m_isParalysableMutlti && (m_bufferSizeMulti<2)){
          m_deadTimeTableMulti[m_generalDetId]  = currentTime + m_deadTimeMulti;
      }
        }
      }
    if (nVerboseLevel>99)
      getchar();


}



void GateDeadTimeMulti::SetDeadTimeMode(G4String val)
{
  if((val!="paralysable")&&(val!="nonparalysable"))
    G4cout << "*** GateDeadTimeMulti.cc : Wrong dead time mode : candidates are : paralysable nonparalysable\n";
  else
   m_isParalysableMutlti = (val=="paralysable");

}


void GateDeadTimeMulti::DescribeMyself(size_t indent)
{
  G4cout << GateTools::Indent(indent) << "DeadTime: " << G4BestUnit(m_deadTimeMulti,"Time") << Gateendl;
}

void GateDeadTimeMulti::CheckVolumeName(G4String val)
{
  GateObjectStore* anInserterStore = GateObjectStore::GetInstance();


  if (anInserterStore->FindCreator(val)) {
    m_volumeNameMulti = val;

    FindLevelsParams(anInserterStore);
    m_testVolumeMulti = 1;
  }
  else {
    G4cout << "Wrong Volume Name\n";
  }
}


void GateDeadTimeMulti::FindLevelsParams(GateObjectStore*  anInserterStore)
{

    G4int numberTotalOfComponentInLevel = 0;

    //GateVVolume* anInserter = anInserterStore->FindCreator(val);
   //GateVVolume* anotherInserter = anInserter; // just to buffer anInserter


    if(nVerboseLevel>1)
      G4cout << "DEAD TIME IS APPLIED ON " <<  m_volumeNameMulti << Gateendl;


    // How many levels higher than volumeName level ?
//    numberOfHigherLevelsMulti = 1;
//    while(anotherInserter->GetMotherList())
//      {
//        anotherInserter =  anotherInserter->GetMotherList()->GetCreator();
//        numberOfHigherLevelsMulti ++;
//      }
    //  numberOfHigherLevels--;
    //anotherInserter = anInserter;
    //G4cout<<"Nof Higher level "<<numberOfHigherLevelsMulti<< Gateendl;

    // How many components for each levels ?
    //  G4int* numberOfComponentForLevel = new G4int[numberOfHigherLevels];
    //numberOfComponentForLevelMulti = (G4int*)malloc(sizeof(G4int)*(numberOfHigherLevelsMulti));
//    if(!numberOfComponentForLevelMulti)
//      {
//        G4cout << "[GateDeadTime::FindLevelsParams]: new failed\n\n";
//        return;
//      }

    GateObjectChildList* ChildList = anInserterStore->FindCreator(m_volumeNameMulti)->GetTheChildList();
    for(size_t i = 0; i < ChildList->size();i++)
    {
        numberTotalOfComponentInLevel += ChildList->GetVolume(i)->GetVolumeNumber();
    }

    //numberTotalOfComponentInLevel = 1;


    if(nVerboseLevel>5)
      G4cout << "total number of elements = " <<numberTotalOfComponentInLevel << Gateendl;

    // create the table of "rebirth time" (detector is dead than it rebirth)
    //unsigned long long int* m_deadTimeTable = new unsigned long long int[numberTotalOfComponentInLevel];
    m_deadTimeTableMulti = (unsigned long long int*)malloc(sizeof(unsigned long long int)*numberTotalOfComponentInLevel);
    m_bufferCurrentSizeMulti = (G4double*)malloc(sizeof(G4double)*numberTotalOfComponentInLevel);

    //  printf("alocated for %d elements\n",numberTotalOfComponentInLevel);getchar();


    if( (!m_deadTimeTableMulti) || (!m_bufferCurrentSizeMulti)){
        G4cout << "[GateDeadTime::FindLevelsParams]: malloc failed\n\n";
        return;
    }
    else{
        for(G4int i=0;i<numberTotalOfComponentInLevel;i++){
              m_deadTimeTableMulti[i] = 0;
              m_bufferCurrentSizeMulti[i] = 0.;
        }
    }


}

