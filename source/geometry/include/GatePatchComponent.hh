#ifndef GATEPATCHCOMPONENT_HH
#define GATEPATCHCOMPONENT_HH

#include "GateSystemComponent.hh"

class GatePatch;

class GatePatchComponent : public GateSystemComponent
{
public:
    /*! \brief Constructor

         \param itsName:       	    the name chosen for this system-component
         \param itsMotherComponent:  the mother of the component (0 if top of a tree)
         \param itsSystem:           the system to which the component belongs
     */
    GatePatchComponent(const G4String& itsName,
                            GateSystemComponent* itsMotherComponent,
                            GateVSystem* itsSystem);
    //! Destructor
    virtual ~GatePatchComponent();
    //! Method overloading the method IsValidAttachmentRequest() of the base-class GateSystemComponent
    //! It tells whether an Creator may be attached to this component
    //! In addition to the test performed by the base-class' method, it also
    //! checks that the Creator is indeed connected to a prism creator
    virtual G4bool IsValidAttachmentRequest(GateVVolume* anCreator) const;

    inline GatePatch* GetPatchCreator() const
    {    return GetPatchCreator(GetCreator());}

    static inline GatePatch* GetPatchCreator(GateVVolume* anCreator)
    { return anCreator ? CastToPatchCreator(anCreator->GetCreator()) : 0 ;}

    static GatePatch* CastToPatchCreator(GateVVolume* creator);
};



#endif // GATEPATCHCOMPONENT_HH
