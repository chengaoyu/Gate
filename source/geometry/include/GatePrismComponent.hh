/* ----------------------
 * this file is add by CGY
 * at 2016/11/21
 * to provide the prism component
 * to construct the GateSpherePETSystem
--------------*/

#ifndef GATEPRISMCOMPONENT_HH
#define GATEPRISMCOMPONENT_HH

#include "GateSystemComponent.hh"

class GatePrism;


class GatePrismComponent : public GateSystemComponent
{
public:
    /*! \brief Constructor

         \param itsName:       	    the name chosen for this system-component
         \param itsMotherComponent:  the mother of the component (0 if top of a tree)
         \param itsSystem:           the system to which the component belongs
     */
    GatePrismComponent(const G4String& itsName,
                            GateSystemComponent* itsMotherComponent,
                            GateVSystem* itsSystem);
    //! Destructor
    virtual ~GatePrismComponent();

    //! Method overloading the method IsValidAttachmentRequest() of the base-class GateSystemComponent
    //! It tells whether an Creator may be attached to this component
    //! In addition to the test performed by the base-class' method, it also
    //! checks that the Creator is indeed connected to a prism creator
    virtual G4bool IsValidAttachmentRequest(GateVVolume* anCreator) const;

    inline GatePrism* GetPrismCreator() const
        { return GetPrismCreator(GetCreator());}

    G4ThreeVector GetPrismP(size_t index) const;

    static inline GatePrism* GetPrismCreator(GateVVolume* anCreator)
        {  return anCreator ? CastToPrismCreator( anCreator->GetCreator() ) : 0 ; }

    static GatePrism* CastToPrismCreator(GateVVolume* creator);
};









#endif // GATEPRISMCOMPONENT_HH
