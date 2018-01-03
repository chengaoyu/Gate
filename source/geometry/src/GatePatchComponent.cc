#include "GatePatchComponent.hh"
#include "GatePatch.hh"

GatePatchComponent::GatePatchComponent(const G4String& itsName,
                                         GateSystemComponent* itsMotherComponent,
                                       GateVSystem* itsSystem)
    :GateSystemComponent(itsName, itsMotherComponent,itsSystem)
{

}

GatePatchComponent::~GatePatchComponent(){

}

G4bool GatePatchComponent::IsValidAttachmentRequest(GateVVolume *anCreator) const
{
    // Call the base-class method to do all the standard validity tests
    if (!(GateSystemComponent::IsValidAttachmentRequest(anCreator)))
      return false;

    // Check whether the inserter is connected to a Prism-creator
    GatePatch* PatchCreator = GetPatchCreator(anCreator);
    if (!PatchCreator) {
         G4cerr   << "[" << anCreator->GetObjectName() << "::IsValidAttachmentRequest]:\n"
                  << "\tThe volume creator ('" << PatchCreator->GetObjectName() << "') for this inserter does not seem to be a Patch\n" << Gateendl;
        return false;
    }

    // OK, everything's fine
    return true;
}

// Return the length along an axis of the Prism-creator attached to our inserter




// Tool method: try to cast a creator into a Prism creator
GatePatch* GatePatchComponent::CastToPatchCreator(GateVVolume* creator)
{
  return dynamic_cast<GatePatch*>(creator);
}
