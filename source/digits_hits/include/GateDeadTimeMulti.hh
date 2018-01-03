#ifndef GATEDEADTIMEMULTI_HH
#define GATEDEADTIMEMULTI_HH

#include "globals.hh"
#include <iostream>
#include <vector>
#include "G4ThreeVector.hh"

#include "GateVPulseProcessor.hh"
#include "GateObjectStore.hh"

class GateDeadTimeMultiMessenger;


/*! \class  GateDeadTime
    \brief  Pulse-processor modelling a simple dead time discriminator.

    - GateDeadTimeMulti - by chengaoyu2013@gmail.com

    - The method ProcessOnePulse of this class models a simple
      deadTime discriminator. User chooses value of dead time, mode
      (paralysable or not) and geometric level of application (crystal, module,...)

      \sa GateVPulseProcessor
      \sa GateVolumeID
      \sa GatePulseProcessorChainMessenger
*/
class GateDeadTimeMulti : public GateVPulseProcessor
{
public:



  //! Destructor
  virtual ~GateDeadTimeMulti() ;


  //! Check the validity of the volume name where the dead time will be applied
  void CheckVolumeName(G4String val);


  //! Constructs a new dead time attached to a GateDigitizer
  GateDeadTimeMulti(GatePulseProcessorChain* itsChain,
                 const G4String& itsName);

public:

  //! Returns the deadTime
  unsigned long long int GetDeadTime() {return m_deadTimeMulti;}

  //! Set the deadTime
  void SetDeadTime(G4double val)   { m_deadTimeMulti = (unsigned long long int )(val/picosecond);}


  //! Set the deadTime mode ; candidates : paralysable nonparalysable
  void SetDeadTimeMode(G4String val);
  //! Set the buffer mode ;
  void SetBufferMode(G4int val){m_bufferModeMulti=val;}
  //! Set the buffer mode ;
  void SetBufferSize(G4double val){m_bufferSizeMulti=val;}
  //! Set the buffer mode ;

  //! Implementation of the pure virtual method declared by the base class GateClockDependent
  //! print-out the attributes specific of the deadTime
  virtual void DescribeMyself(size_t indent);

protected:

  /*! Implementation of the pure virtual method declared by the base class GateVPulseProcessor
    This methods processes one input-pulse
    It is is called by ProcessPulseList() for each of the input pulses
    The result of the pulse-processing is incorporated into the output pulse-list
    This method manages the updating of the "rebirth time table", the table of times when
    the detector volume will be alive again.
  */
  void ProcessOnePulse(const GatePulse* inputPulse,GatePulseList&  outputPulseList);


  //! To summarize it finds the number of elements of the different scanner levels
  void FindLevelsParams(GateObjectStore* anInserterStore);

private:

  G4String m_volumeNameMulti; //!< Name of the volumes where Dead time is applied
  G4int m_testVolumeMulti;    //!< equal to 1 if the volume name is valid, 0 else
  //G4int *numberOfComponentForLevelMulti;   //!< Table of number of element for each geometric level
  //G4int numberOfHigherLevelsMulti;         //!< number of geometric level higher than the one chosen by the user
  unsigned long long int m_deadTimeMulti;  //!< DeadTime value
  G4bool m_isParalysableMutlti;            //!< dead time mode : paralysable (true) nonparalysable (false)
  unsigned long long int* m_deadTimeTableMulti; //!< contains the "rebirth times". Alocated once at the first call.
  G4double m_bufferSizeMulti;              //!< contains the rebirth time.
  G4double* m_bufferCurrentSizeMulti; //!< contains the buffers sizes
  G4int m_bufferModeMulti;  //! 0 : DT during writing, 1 : DT if writing AND buffer full
  GateDeadTimeMultiMessenger *m_messengerMulti; //!< Messenger
  //G4int m_deadtimeLevelMulti;
};

#endif // GATEDEADTIMEMULTI_HH
