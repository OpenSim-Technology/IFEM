// $Id$
//==============================================================================
//!
//! \file MaterialBase.h
//!
//! \date Mar 01 2011
//!
//! \author Knut Morten Okstad / SINTEF
//!
//! \brief Base class for material models.
//!
//==============================================================================

#ifndef _MATERIAL_BASE_H
#define _MATERIAL_BASE_H

#include "MatVec.h"

class Vec3;
class Tensor;
class SymmTensor;
struct TimeDomain;


/*!
  \brief Base class representing a material model of a solid mechanics problem.
*/

class Material
{
protected:
  //! \brief The default constructor is protected to allow sub-classes only.
  Material() {}

public:
  //! \brief Empty destructor.
  virtual ~Material() {}

  //! \brief Returns \e false if plane stress in 2D.
  virtual bool isPlaneStrain() const { return true; }

  //! \brief Prints out material parameters to the given output stream.
  virtual void print(std::ostream&) const {}

  //! \brief Initializes the material model for a new integration loop.
  virtual void initIntegration(const TimeDomain&) {}
  //! \brief Initializes the material model for a new result point loop.
  virtual void initResultPoints() {}

  //! \brief Evaluates the mass density at current point.
  virtual double getMassDensity(const Vec3&) const { return 0.0; }

  //! \brief Evaluates the constitutive relation at an integration point.
  //! \param[out] C Constitutive matrix at current point
  //! \param[out] sigma Stress tensor at current point
  //! \param[out] U Strain energy density at current point
  //! \param[in] X Cartesian coordinates of current point
  //! \param[in] F Deformation gradient at current point
  //! \param[in] eps Strain tensor at current point
  //! \param[in] iop Calculation option;
  //!  -1 : Calculate the inverse constitutive matrix only,
  //!   0 : Calculate the consitutive matrix only,
  //!   1 : Calculate Cauchy stresses and the tangent constitutive matrix,
  //!   2 : 2nd Piola-Kirchhoff stresses and tangent constitutive matrix,
  //!   3 : Calculate the strain energy density only.
  //! \param[in] prm Nonlinear solution algorithm parameters
  virtual bool evaluate(Matrix& C, SymmTensor& sigma, double& U,
			const Vec3& X, const Tensor& F, const SymmTensor& eps,
			char iop = 1, const TimeDomain* prm = 0) const = 0;
};

#endif