/* ----------------------
 * this file is add by CGY
 * at 2016/11/21
 * to provide the prism component
 * to construct the GateSphericalPETSystem
--------------*/

#ifndef GATESPHERICALPETSYSTEM_HH
#define GATESPHERICALPETSYSTEM_HH

#include "globals.hh"

#include "GateVSystem.hh"

class GateClockDependentMessenger;
class GateSphericalPETSystemMessenger;

/*! \class  GateSphericalPETSystem
    \brief  The GateSphericalPETSystem models a sphere-shape PET scanner.

    - GateSphericalPETSystem - by chengaoyu2013@gmail.com

    - A GateSphericalPETSystem models a sphere-shape PET scanner.
      It comprises 86 wedges which are pentagons and hexagons.
      The wedges are devided into 3 or 4 prisms for each one.
      We take the GatePrime as the basic component of this System due to the limitation of Visulization.
      (If we use the prisms to construct wedges by boolean operation, the visulization system will not work normally.)
      And the GatePrism is a class which inherits from GateVVolume.

    - Unlike conventional Cylinderical PET system, the Spherical PET system do not have the ring, rsector or blocks.
      Instead, the four kinds of crystal wedges (pentagons, hexagons, generic pentagons and generic hexagons) are more irregular.
      So they can not be simply constructed by only one boxlike crystals.
      In another hand, the GatePrism are constructed by G4Tet, which is fixed by the vertex position.
      In our 92 surfaces (the whole sphere) polyhexgon case, 18 wedges can specify a Spherical PET System.
      The other wedges should be
      18 wedges:
      --------- 3 pentagons 2*5 + 1
      --------- 3 hexagons  3*5
      --------- 1 generic pentagon 1*5
      --------- 11 generic hexagons 11*5

    - This system overloads two methods of the GateVSystem base-class, Describe() and
      PrintToStream()

    - Beside the standard system methods, it also provides the method ComputeInternalRadius()
      to compute the internal radius of the scanner
*/
class GateSphericalPETSystem : public GateVSystem
{
  public:
    //! Constructor
    GateSphericalPETSystem(const G4String& itsName);
    //! Destructor
    virtual ~GateSphericalPETSystem();


    /*! \brief Method overloading the base-class virtual method Describe().
        \brief This methods prints-out a description of the system, which is
        \brief optimised for creating LMF header files

        \param indent: the print-out indentation (cosmetic parameter)
    */
    virtual void Describe(size_t indent=0);

    /*! \brief Method overloading the base-class virtual method Describe().
        \brief This methods prints out description of the system to a stream.
        \brief It is essentially to be used by the class GateToLMF, but it may also be used by Describe()

        \param aStream: the output stream
        \param doPrintNumbers: tells whether we print-out the volume numbers in addition to their dimensions
    */
    virtual void PrintToStream(std::ostream& aStream,G4bool doPrintNumbers);

    //void AddNewRSECTOR( G4String );

    //! Compute the internal radius of the crystal ring.
    virtual G4double ComputeInternalRadius();

   private:
    G4int   m_maxindex;
    G4int   m_maxrsectorID;
    std::map< G4String , G4int > m_rsectorID;
    GateSphericalPETSystemMessenger* m_messenger2;
    GateClockDependentMessenger    	*m_messenger; 	//!< pointer to the system messenger

    G4double   m_innerRadius;
    G4double   m_outerRadius;

    //! polyhedronP: used to store the vertices of the polyhexgons (totally 18 peices in GateSphericalPETSystem)
    //! polyComponent: used to store the name and corresponding vertices of a peices.
    //! polySystem: the
   // typedef std::vector<G4ThreeVector> polyhexgonP;
    //typedef std::pair<const G4String,polyhexgonP> polyComponent;
    //std::vector<polyComponent> polySystem;

};



#endif // GATESPHERICALPETSYSTEM_HH
