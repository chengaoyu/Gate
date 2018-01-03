/* ----------------------
 * this file is add by CGY
 * at 2016/11/20
 * for constructing the geometry
 * of polyhegon
 * three tetras construct the prism
 * then prisms construct pentagons and hexagons
--------------*/


#ifndef GATEPRISM_HH
#define GATEPRISM_HH

/*! \class  GatePrism creates a solid and logical volume for a prism.
    \brief  A GatePrism is consist of three tetras
*/

#include "globals.hh"

#include "GateVVolume.hh"
#include "GateVolumeManager.hh"
#include "G4UnionSolid.hh"

class G4UnionSolid;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4UnionSolid;
//class G4Tet;
//class GateTetra;
class GatePrismMessenger;
//to be added


class GatePrism : public GateVVolume
{
 public:
    GatePrism(const G4String& itsName,
              G4bool acceptsChildren=true,
              G4int depth=0);

    GatePrism(const G4String& itsName,
              const G4String& itsMaterialName,
              G4ThreeVector itsVin1,
              G4ThreeVector itsVin2,
              G4ThreeVector itsVin3,
              G4ThreeVector itsVout1,
              G4ThreeVector itsVout2,
              G4ThreeVector itsVout3,
             G4bool acceptsChildren=true,
             G4int depth=0);
    //Destructor
    virtual ~GatePrism();

    FCT_FOR_AUTO_CREATOR_VOLUME(GatePrism)

    virtual G4LogicalVolume* ConstructOwnSolidAndLogicalVolume(G4Material* mater,G4bool flagUpdateOnly);
    virtual void DestroyOwnSolidAndLogicalVolume();
    virtual void DescribeMyself(size_t level);
    G4double ComputeMyOwnVolume()  const;
    inline G4double GetHalfDimension(size_t axis)
    {
        //to be added
        return 0;
    }
    inline G4ThreeVector GetPrismP      (size_t index)      {return mPrismP[index];}
    inline G4ThreeVector GetPrismP1() 	{ return mPrismP[0];}
    inline G4ThreeVector GetPrismP2() 	{ return mPrismP[1];}
    inline G4ThreeVector GetPrismP3() 	{ return mPrismP[2];}
    inline G4ThreeVector GetPrismP4() 	{ return mPrismP[3];}
    inline G4ThreeVector GetPrismP5() 	{ return mPrismP[4];}
    inline G4ThreeVector GetPrismP6() 	{ return mPrismP[5];}

    void SetPrismP (G4ThreeVector val, size_t index) {mPrismP[index] = val;}
    void SetPrismP1(G4ThreeVector val)	{ mPrismP[0]= val; }
    void SetPrismP2(G4ThreeVector val)	{ mPrismP[1]= val; }
    void SetPrismP3(G4ThreeVector val)	{ mPrismP[2]= val; }
    void SetPrismP4(G4ThreeVector val)	{ mPrismP[3] = val; }
    void SetPrismP5(G4ThreeVector val)	{ mPrismP[4] = val; }
    void SetPrismP6(G4ThreeVector val)	{ mPrismP[5] = val; }

    inline G4UnionSolid* GetPrismSolid(){ return m_prism_solid;}

private:
    //! name own geometry
    //G4Tet* m_tetra1;
    //G4Tet* m_tetra2;
    //G4Tet* m_tetra3;
    G4UnionSolid* m_prism_solid;
    G4LogicalVolume* m_prism_log;

    //! \name parameters
    G4ThreeVector mPrismP[6];
    //G4ThreeVector m_pin1;
    //G4ThreeVector m_pin2;
    //G4ThreeVector m_pin3;
    //G4ThreeVector m_pout1;
    //G4ThreeVector m_pout2;
    //G4ThreeVector m_pout3;

    //! Messenger
    GatePrismMessenger* m_Messenger;
};

MAKE_AUTO_CREATOR_VOLUME(prism, GatePrism)

#endif // GATEPRISM_HH
