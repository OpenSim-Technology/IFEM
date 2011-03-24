// $Id$
//==============================================================================
//!
//! \file NonlinearElasticityULMixed.h
//!
//! \date Dec 22 2010
//!
//! \author Knut Morten Okstad / SINTEF
//!
//! \brief Integrand implementations for mixed nonlinear elasticity problems.
//!
//==============================================================================

#ifndef _NONLINEAR_ELASTICITY_UL_MIXED_H
#define _NONLINEAR_ELASTICITY_UL_MIXED_H

#include "NonlinearElasticityUL.h"
#include "ElmMats.h"
#include "Tensor.h"


/*!
  \brief Class representing the integrand of the nonlinear elasticity problem.
  \details This class implements a mixed Updated Lagrangian formulation with
  continuous pressure and volumetric change fields.
*/

class NonlinearElasticityULMixed : public NonlinearElasticityUL
{
  //! \brief Class representing the element matrices of the mixed formulation.
  class MixedElmMats : public ElmMats
  {
  public:
    //! \brief Default constructor.
    MixedElmMats();
    //! \brief Empty destructor.
    virtual ~MixedElmMats() {}
    //! \brief Returns the element-level Newton matrix.
    virtual const Matrix& getNewtonMatrix() const;
    //! \brief Returns the element-level right-hand-side vector
    //! associated with the Newton matrix.
    virtual const Vector& getRHSVector() const;
  };

public:
  //! \brief The default constructor invokes the parent class constructor.
  //! \param[in] n Number of spatial dimensions
  NonlinearElasticityULMixed(unsigned short int n = 3);
  //! \brief Empty destructor.
  virtual ~NonlinearElasticityULMixed() {}

  //! \brief Prints out problem definition to the given output stream.
  virtual void print(std::ostream& os) const;

  //! \brief Defines the solution mode before the element assembly is started.
  //! \param[in] mode The solution mode to use
  virtual void setMode(SIM::SolutionMode mode);

  //! \brief Initializes current element for numerical integration.
  //! \param[in] MNPC1 Nodal point correspondance for the basis 1
  //! \param[in] MNPC2 Nodal point correspondance for the basis 2
  //! \param[in] n1 Number of nodes in basis 1 on this patch
  virtual bool initElement(const std::vector<int>& MNPC1,
                           const std::vector<int>& MNPC2, size_t n1);
  //! \brief Initializes current element for numerical boundary integration.
  //! \param[in] MNPC1 Nodal point correspondance for the basis 1
  //! \param[in] MNPC2 Nodal point correspondance for the basis 2
  virtual bool initElementBou(const std::vector<int>& MNPC1,
			      const std::vector<int>& MNPC2, size_t);

  //! \brief Evaluates the mixed field problem integrand at an interior point.
  //! \param elmInt The local integral object to receive the contributions
  //! \param[in] prm Nonlinear solution algorithm parameters
  //! \param[in] detJW Jacobian determinant times integration point weight
  //! \param[in] N1 Basis function values, field 1 (displacements)
  //! \param[in] N2 Basis function values, field 2 (pressure and volume change)
  //! \param[in] dN1dX Basis function gradients, field 1
  //! \param[in] dN2dX Basis function gradients, field 2
  //! \param[in] X Cartesian coordinates of current integration point
  virtual bool evalInt(LocalIntegral*& elmInt,
		       const TimeDomain& prm, double detJW,
		       const Vector& N1, const Vector& N2,
		       const Matrix& dN1dX, const Matrix& dN2dX,
		       const Vec3& X) const;

  //! \brief Evaluates the integrand at a boundary point.
  //! \param elmInt The local integral object to receive the contributions
  //! \param[in] detJW Jacobian determinant times integration point weight
  //! \param[in] N1 Basis function values, field 1
  //! \param[in] dN1dX Basis function gradients, field 1
  //! \param[in] X Cartesian coordinates of current integration point
  //! \param[in] normal Boundary normal vector at current integration point
  //!
  //! \details The boundary integral is the same as that of the parent class.
  //! It does not depend on the pressure and volumetric change fields.
  //! Thus, this call is forwarded to the single-field parent class method.
  virtual bool evalBou(LocalIntegral*& elmInt, double detJW,
                       const Vector& N1, const Vector&,
                       const Matrix& dN1dX, const Matrix&,
                       const Vec3& X, const Vec3& normal) const
  {
    return this->NonlinearElasticityUL::evalBou(elmInt,detJW,N1,dN1dX,X,normal);
  }

protected:
  mutable Tensor Fbar; //!< Mixed model deformation gradient
  mutable Matrix Dmat; //!< Projected mixed constitutive matrix
};

#endif
