/* ----------------------
 * this file is add by CGY
 * at 2017/09/10
 * for constructing the geometry Patch
 * Patch is an irregular block with two main surfaces, each with equal number of vertices.
 * And a patch is construct by
--------------*/

#include "GatePatch.hh"

#include "GatePatchMessenger.hh"

#include "GateTools.hh"
#include "G4LogicalVolume.hh"
#include "G4Colour.hh"
#include "G4UnionSolid.hh"
#include "G4Tet.hh"
#include <string>
#include <fstream>
GatePatch::GatePatch(const G4String& itsName, G4bool acceptsChildren=true,G4int depth=0)
    :GateVVolume( itsName, acceptsChildren, depth ),
      m_patch_solid( NULL ),
      m_patch_log(NULL),
      m_PathToPatchFile( "" ),
      m_Messenger(NULL)
{
    SetMaterialName("Vacuum");
    m_Messenger = new GatePatchMessenger(this);
}

GatePatch::GatePatch(const G4String& itsName, const G4String& itsMaterialName)
    : GateVVolume( itsName, false, 0),
      m_patch_solid( NULL ),
      m_patch_log(NULL),
      m_PathToPatchFile(""),
      m_Messenger(NULL)
{
    SetMaterialName( itsMaterialName );
    m_Messenger = new GatePatchMessenger(this);
}



GatePatch::~GatePatch()
{
    delete m_Messenger;
}


G4LogicalVolume* GatePatch::ConstructOwnSolidAndLogicalVolume(G4Material *mater, G4bool flagUpdateOnly){
    if(GetVerbosity()>=2){
        G4cout << "GatePatch::ConstructOwnSolidAndLogicalVolume"<<G4endl;
        DescribeMyself(1);
    }
    if(!flagUpdateOnly||!m_patch_solid){

        G4ThreeVector v;
        std::vector<G4ThreeVector> surface1;
        std::vector<G4ThreeVector> surface2;
        std::ifstream PatchFile( m_PathToPatchFile, std::ios::in );
        std::string line;
        std::istringstream vertexline;
        std::string dummy;
        nbEdges = 0;
        if( !PatchFile )
        {
          G4cerr << "No Patch file: " << m_PathToPatchFile << G4endl;
        }
        else{
            while(! PatchFile.eof()){
                std::getline(PatchFile, line);
                if(line.find("surface1") != std::string::npos){
                    std::getline(PatchFile,line);
                    while( line.find("vertex")!=std::string::npos )
                    {
                        vertexline.str(line);
                        vertexline.clear();
                        vertexline >> dummy >> v[0] >> v[1] >> v[2];
                        surface1.push_back(v);
                        std::getline(PatchFile,line);
                    }
                }
                if(line.find("surface2") != std::string::npos){
                    std::getline(PatchFile,line);
                    while( line.find("vertex")!=std::string::npos )
                    {
                        vertexline.str(line);
                        vertexline.clear();
                        vertexline >> dummy >> v[0] >> v[1] >> v[2];
                        surface2.push_back(v);
                        std::getline(PatchFile,line);
                    }
                }
            }
            PatchFile.close();
        }

        nbEdges = (surface1.size()==surface2.size())? surface1.size():-1;
        if(nbEdges>=3) //number of edge should be larger than 3
        {
            G4UnionSolid* prismUnion;
            for(G4int iPrism = 1; iPrism < nbEdges-1; iPrism ++){
                G4ThreeVector s1[3];
                s1[0] = surface1[0];
                s1[1] = surface1[iPrism];
                s1[2] = surface1[iPrism+1];
                G4ThreeVector s2[3];
                s2[0] = surface2[0];
                s2[1] = surface2[iPrism];
                s2[2] = surface2[iPrism+1];

                G4Tet* m_tetra1
              = new G4Tet("Tetra1",
                          s2[0],s1[0],s1[1],s1[2]);
                G4Tet* m_tetra2
              = new G4Tet("Tetra2",
                          s2[1],s2[0],s1[1],s1[2]);
                G4Tet* m_tetra3
              = new G4Tet("Tetra3",
                          s1[2],s2[0],s2[1],s2[2]);
                G4UnionSolid* TwoTets
              = new G4UnionSolid("TwoTets", m_tetra1, m_tetra2);
                G4UnionSolid* prism
              = new G4UnionSolid(GetSolidName(),TwoTets, m_tetra3);
               // prismUnion.push_back(prism);
                if(nbEdges == 3)
                {
                    m_patch_solid = new G4UnionSolid(GetSolidName(),TwoTets, m_tetra3);
                }
                else if(iPrism == nbEdges-2){
                    m_patch_solid = new G4UnionSolid(GetSolidName(), prismUnion,prism);
                }
                else if(iPrism>1){
                    prismUnion
                            = new G4UnionSolid("prisms", prismUnion,prism);
                    //prismUnion.clear();
                    //prismUnion.push_back(prisms);
                }
                else{
                    prismUnion =new G4UnionSolid(*prism);
                }
            }


            m_patch_log = new G4LogicalVolume(m_patch_solid,mater,GetLogicalVolumeName());
        }
        else{
            G4cerr << "PatchFile read error: patch file contains different number of vertices: surface1 " << surface1.size() <<", surface2 "<<surface2.size() << G4endl;
        }
    }
    else{
        GateMessage("Warning", 0, "GatePatch::ConstructOwnSolidAndLogicalVolume update mode not implemented\n");
    }
    return m_patch_log;
}

void GatePatch::DestroyOwnSolidAndLogicalVolume()
{
    if(m_patch_log)
        delete m_patch_log;
    m_patch_log = 0 ;

    if(m_patch_solid)
        delete m_patch_solid;
    m_patch_solid = 0;
}

void GatePatch::SetPathToPatchFile(G4String path){
    m_PathToPatchFile = path;
}

void GatePatch::DescribeMyself(size_t level)
{
    G4cout << GateTools::Indent(level)<<"Shape: Patch \n";
    G4cout << GateTools::Indent(level)<<"Number of edges: " << nbEdges <<Gateendl;
}

G4double GatePatch::ComputeMyOwnVolume() const
{
    return m_patch_solid->GetCubicVolume();

}

//G4Tet* GatePatch::createTet(G4ThreeVector* v){

//}

//G4UnionSolid* GatePatch::createG4Prism(G4ThreeVector* s1, G4ThreeVector* s2 ){

//}
