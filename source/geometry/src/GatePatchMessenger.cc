/*----------------------
   Copyright (C): OpenGATE Collaboration

This software is distributed under the terms
of the GNU Lesser General  Public Licence (LGPL)
See GATE/LICENSE.txt for further details
----------------------*/

#include "GatePatchMessenger.hh"
#include "GatePatch.hh"

GatePatchMessenger::GatePatchMessenger(
  GatePatch* itsCreator )
: GateVolumeMessenger( itsCreator )
{
  G4String dir = GetDirectoryName() + "geometry/";

  G4String cmdName;
  cmdName = dir + "setPathToPatchFile";
  PathToPatchFileCmd = new G4UIcmdWithAString( cmdName, this );
  PathToPatchFileCmd->SetGuidance( "Set path to Patch file" );
}

GatePatchMessenger::~GatePatchMessenger()
{
  delete PathToPatchFileCmd;
}

void GatePatchMessenger::SetNewValue( G4UIcommand* command,
  G4String newValue )
{
  if( command == PathToPatchFileCmd )
  {
    GetPatchCreator()->SetPathToPatchFile( newValue );
  }
  else
  {
    GateVolumeMessenger::SetNewValue( command, newValue );
  }
}
