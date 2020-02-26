// Kernel functions for the triangle convolution integral. Higher ordered
// kernels correspond to higher number of subtractions.
//
// Author:       Daniel Winney (2019)
// Affiliation:  Joint Physics Analysis Center (JPAC)
// Email:        dwinney@iu.edu
// ---------------------------------------------------------------------------

#include "feynman_triangle.hpp"

// ---------------------------------------------------------------------------
// Vanilla Triangle function (no powers of k^2 in numerator)
// ---------------------------------------------------------------------------

std::complex<double> feynman_triangle::mT0(double s, double t)
{
  check_weights();

  //integrate over x
  std::complex<double> sum = 0.;
  for (int i = 0; i < xN; i++)
  {
    double x_i = abscissas[i];

    // coeffs of denominator polynomial
    std::complex<double> a, b, c;

    a = mPi2;
    b = mPi2 + (x_i - 1.) * mPi2 + x_i * mDec2 - x_i * s - t;
    c = (1. - x_i) * t + x_i * mPi2 + x_i*(x_i-1.)* mDec2;

    // the integrand is the analytic form of the y_integral subtracted at:
    // s = 0
    sum += weights[i] * (ri_poly1(1.-x_i,a,b,c) - ri_poly1(0.,a,b,c));
  }

  return sum / M_PI;
};

// ---------------------------------------------------------------------------
// k^2 in the numerator
// ---------------------------------------------------------------------------

// Evaluate the kernel function by integrating over x
std::complex<double> feynman_triangle::mT1(double s, double t)
{
  check_weights();

  //integrate over x
  std::complex<double> sum1 = 0., sum2 = 0.;
  for (int i = 0; i < xN; i++)
  {
    double x_i = abscissas[i];

    // the integrand is the analytic form of the y_integral subtracted at:
    // s = 0
    sum1 += weights[i] * ( mT1_yintegral1(s, t, x_i) - mT1_yintegral1(0., t, x_i) );
    sum2 += weights[i] * ( mT1_yintegral2(s, t, x_i) - mT1_yintegral2(0., t, x_i) );
  }

  std::complex<double> result = sum1 - sum2 * 2.;

  return result / M_PI;
};

// ---------------------------------------------------------------------------
// Intermediate functions for the mT1 y_integral

// Analytic form of the first integral over y
std::complex<double> feynman_triangle::mT1_yintegral1(double s, double t, double x)
{
  std::complex<double> a, b, c, d;
  std::complex<double> e, f, g;

  // coeffs of denominator polynomial
  a = mPi2;
  b = mPi2 + (x - 1.) * mPi2 + x * mDec2 - x * s - t;
  c = (1. - x) * t + x * mPi2 + x*(x-1.)* mDec2 - ieps;

  // coeffs of numerator polynomial
  e = mPi2;
  f = x * (mDec2 + mPi2 - s);
  g = x*x * mDec2;

  // Evaluate definite integral with bounds y = [0, 1-x]
  return ri_poly2(1. - x, a, b, c, e, f, g) - ri_poly2(0., a, b, c, e, f, g);
};

// Analytic form of the second integral over y
std::complex<double> feynman_triangle::mT1_yintegral2(double s, double t, double x)
{
  std::complex<double> a, b, c, d;

  // coeffs of denominator polynomial
  a = mPi2;
  b = mPi2 + (x - 1.) * mPi2 + x * mDec2 - x * s - t;
  c = (1. - x) * t + x * mPi2 + x * (x-1.) * mDec2 - ieps;

  // Evaluate definite integral with bounds y = [0, 1-x]
  return ri_log1(1. - x, a, b, c) - ri_log1(0., a, b, c);
}
