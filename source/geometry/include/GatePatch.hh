/* ----------------------
 * this file is add by CGY
 * at 2017/09/09
 * for constructing the geometry Patch
 * Patch is an irregular block with two surface, each with equal number of vertices.
 * And a patch is construct by
--------------*/

#ifndef GATEPATCH_HH
#define GATEPATCH_HH

/*! \class  GatePatch creates a solid and logical volume for a patch.
    \brief  A GatePatch is constuct by
*/

#include "globals.hh"

#include "GateVVolume.hh"
#include "GateVolumeManager.hh"
//#include "G4UnionSolid.hh"

class G4UnionSolid;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Tet;
class GatePatchMessenger;
//to be added


class GatePatch : public GateVVolume
{
 public:
    GatePatch(const G4String& itsName,
              G4bool acceptsChildren,
              G4int depth);
    GatePatch(const G4String& itsName,
              const G4String& itsMaterialName);

    //Destructor
    virtual ~GatePatch();

    FCT_FOR_AUTO_CREATOR_VOLUME(GatePatch)

    virtual G4LogicalVolume* ConstructOwnSolidAndLogicalVolume(G4Material* mater,G4bool flagUpdateOnly);
    virtual void DestroyOwnSolidAndLogicalVolume();
    virtual void DescribeMyself(size_t level);
    G4double ComputeMyOwnVolume()  const;
    inline virtual  G4double GetHalfDimension(size_t axis)
    {
        //to be added
        return 0;
    }

    void SetPathToPatchFile(G4String );

    //G4Tet* createTet(G4ThreeVector* v);
   // G4UnionSolid* createG4Prism(G4ThreeVector* s1, G4ThreeVector* s2);

    inline G4UnionSolid* GetPatchSolid(){ return m_patch_solid;}

private:
    //void ReadPatch();
    //void DescribeMyself(size_t level);
    //G4double ComputeMyOwnVolume() const;
    //! name own geometry
    G4UnionSolid* m_patch_solid;
    G4LogicalVolume* m_patch_log;

    //! \name parameters
    G4String m_PathToPatchFile;
    unsigned long nbEdges;

    //! Messenger
    GatePatchMessenger* m_Messenger;
};

MAKE_AUTO_CREATOR_VOLUME(patch, GatePatch)

#endif // GATEPATCH_HH
