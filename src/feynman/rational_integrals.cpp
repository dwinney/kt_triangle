// Analytic forms of integrals over rational functions which show up in Feynman integrals
//
// Author:       Daniel Winney (2019)
// Affiliation:  Joint Physics Analysis Center (JPAC)
// Email:        dwinney@iu.edu
// ---------------------------------------------------------------------------

#include "rational_integrals.hpp"

// redefine arctangent in terms of logarithms for complex argument to better control
// singularity structure
std::complex<double> c_atan(std::complex<double> z)
{
  std::complex<double> result = log((z + xi) / (z - xi));
  result /= -2.*xi;

  return result;
};

// ---------------------------------------------------------------------------
// Integral over 1/(a y^2 + b y + c)
std::complex<double> ri_poly1(double y,
  std::complex<double> a,
  std::complex<double> b,
  std::complex<double> c)
{
  std::complex<double> d = 4. * a * c - b * b; // discriminant

  std::complex<double> result = c_atan((2.*a*y+b) / sqrt(d*xr));;
  result *= 2. / sqrt(d*xr);

  return result;
};

// ---------------------------------------------------------------------------
// Integral over (e y^2 + f y + g) / (a y ^2 + b y + c)
std::complex<double> ri_poly2(double y,
  std::complex<double> a,
  std::complex<double> b,
  std::complex<double> c,
  std::complex<double> e,
  std::complex<double> f,
  std::complex<double> g)
{
  std::complex<double> d = b * b - 4. * a * c; // discriminant

  // Antiderivative done by mathematica
  std::complex<double> term1;
  term1 = c_atan((2. * a * y + b) / sqrt(-d));
  term1 *= b*b*e - a*f*b + 2.*a*(a*g-c*e);
  term1 /= a*a * sqrt(-d);

  std::complex<double> term2;
  term2 = log(a*y*y + b*y + c * xr);
  term2 *= a*f - b*e;
  term2 /= 2.*a*a;

  std::complex<double> term3;
  term3 = e * y / a;

  return term1 + term2 + term3;
};

// ---------------------------------------------------------------------------
// Integral over Log(1/(a y^2 + b y + c))
std::complex<double> ri_log1(double y,
    std::complex<double> a,
    std::complex<double> b,
    std::complex<double> c)
{
  std::complex<double> d = b * b - 4. * a * c; // discriminant

  std::complex<double> term1;
  term1 = - c_atan((2.*a*y + b) / sqrt(-d * xr));
  term1 *= sqrt(-d * xr) / a;

  std::complex<double> term2;
  term2 = y * log(xr / (a*y*y + b*y + c * xr));

  std::complex<double> term3;
  term3 = log(a*y*y + b*y + c);
  term3 *= -b / (2. * a);

  std::complex<double> term4 = 2.*y;

  return term1 + term2 + term3 + term4;
};
