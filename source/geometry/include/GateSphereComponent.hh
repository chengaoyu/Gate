#ifndef GATESPHERECOMPONENT_HH
#define GATESPHERECOMPONENT_HH
#include "GateSystemComponent.hh"

class GateSphere;


class GateSphereComponent : public GateSystemComponent
{
public:
    /*! \brief Constructor

         \param itsName:       	    the name chosen for this system-component
         \param itsMotherComponent:  the mother of the component (0 if top of a tree)
         \param itsSystem:           the system to which the component belongs
     */
    GateSphereComponent(const G4String& itsName,
                            GateSystemComponent* itsMotherComponent,
                            GateVSystem* itsSystem);
    //! Destructor
    virtual ~GateSphereComponent();

    //! Method overloading the method IsValidAttachmentRequest() of the base-class GateSystemComponent
    //! It tells whether an Creator may be attached to this component
    //! In addition to the test performed by the base-class' method, it also
    //! checks that the Creator is indeed connected to a Sphere creator
    virtual G4bool IsValidAttachmentRequest(GateVVolume* anCreator) const;

    inline GateSphere* GetSphereCreator() const
        { return GetSphereCreator(GetCreator());}

    G4double GetSphereRmin() const ;
    G4double GetSphereRmax() const ;
    G4double GetSphereSPhi() const ;
    G4double GetSphereDPhi() const ;
    G4double GetSphereSTheta() const ;
    G4double GetSphereDTheta() const ;

    static inline GateSphere* GetSphereCreator(GateVVolume* anCreator)
        {  return anCreator ? CastToSphereCreator( anCreator->GetCreator() ) : 0 ; }

    static GateSphere* CastToSphereCreator(GateVVolume* creator);
};
#endif // GATESPHERECOMPONENT_HH
