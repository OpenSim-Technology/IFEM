// $Id$
//==============================================================================
//!
//! \file SplineUtils.h
//!
//! \date Mar 29 2012
//!
//! \author Knut Morten Okstad / SINTEF
//!
//! \brief Various utility functions on spline objects - GoTools extensions.
//!
//==============================================================================

#ifndef _SPLINE_UTILS_H
#define _SPLINE_UTILS_H

#include "Function.h"
#include "MatVec.h"

class Vec4;

namespace Go {
  class Point;
  struct BasisDerivsSf;
  struct BasisDerivsSf2;
  struct BasisDerivs;
  struct BasisDerivs2;
  class SplineCurve;
  class SplineSurface;
  class SplineVolume;
}


namespace SplineUtils //! Various utility functions on spline objects.
{
  //! \brief Helper method for casting a \a Go::Point object to Vec3.
  Vec3 toVec3(const Go::Point& X, int nsd = 3);
  //! \brief Helper method for casting a \a Go::Point and time object to Vec4.
  Vec4 toVec4(const Go::Point& X, Real time = Real(0));

  //! \brief Evaluates given spline curve at a parametric point.
  void point(Vec3& X, double u, Go::SplineCurve* curve);
  //! \brief Evaluates given spline surface at a parametric point.
  void point(Vec3& X, double u, double v, Go::SplineSurface* surf);
  //! \brief Evaluates given spline colume at a parametric point.
  void point(Vec3& X, double u, double v, double w, Go::SplineVolume* vol);

  //! \brief Establishes matrices with basis functions and 1st derivatives.
  void extractBasis(const Go::BasisDerivsSf& spline,
                    Vector& N, Matrix& dNdu);
  //! \brief Establishes matrices with basis functions, 1st and 2nd derivatives.
  void extractBasis(const Go::BasisDerivsSf2& spline,
                    Vector& N, Matrix& dNdu, Matrix3D& d2Ndu2);

  //! \brief Establishes matrices with basis functions and 1st derivatives.
  void extractBasis(const Go::BasisDerivs& spline,
                    Vector& N, Matrix& dNdu);
  //! \brief Establishes matrices with basis functions, 1st and 2nd derivatives.
  void extractBasis(const Go::BasisDerivs2& spline,
                    Vector& N, Matrix& dNdu, Matrix3D& d2Ndu2);

  //! \brief Projects a scalar-valued function onto a spline curve.
  Go::SplineCurve* project(const Go::SplineCurve* curve,
                           const RealFunc& f, Real time = Real(0));
  //! \brief Projects a vector-valued function onto a spline curve.
  Go::SplineCurve* project(const Go::SplineCurve* curve,
                           const VecFunc& f, int nComp, Real time = Real(0));

  //! \brief Projects a scalar-valued function onto a spline surface.
  Go::SplineSurface* project(const Go::SplineSurface* surface,
                             const RealFunc& f, Real time = Real(0));
  //! \brief Projects a vector-valued function onto a spline surface.
  Go::SplineSurface* project(const Go::SplineSurface* surface,
                             const VecFunc& f, int nComp, Real time = Real(0));

  //! \brief Projects a scalar-valued function onto a spline volume.
  Go::SplineVolume* project(const Go::SplineVolume* volume,
                            const RealFunc& f, Real time = Real(0));
  //! \brief Projects a vector-valued function onto a spline volume.
  Go::SplineVolume* project(const Go::SplineVolume* volume,
                            const VecFunc& f, int nComp, Real time = Real(0));
}

#endif
