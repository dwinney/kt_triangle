// Header file with global phyiscal constants.
// Everything is in GeV unless explicitly stated otherwise.
//
// Author:       Daniel Winney (2019)
// Affiliation:  Joint Physics Analysis Center (JPAC)
// Email:        dwinney@iu.edu
// ---------------------------------------------------------------------------

#ifndef _CONSTANT_
#define _CONSTANT_

#include <cmath>
#include <complex>

//-----------------------------------------------------------------------------
const double conv = (M_PI / 180.);
const double EPS = 1.e-6;

//Masses
const double mPi = 0.13957061;
const double mK = 0.496;
const double mEta = 0.54753;

const double mRho = .77545;
const double mF2 = 1.2754;

//Thresholds for pi, eta, and K
const double sthPi = 4.*mPi*mPi;
const double sthK = 4.*mK*mK;
const double sthEta = 4.*mEta*mEta;

//Unit imaginary and real
const std::complex<double> xr(1., 0.);
const std::complex<double> xi(0., 1.);
const std::complex<double> ieps(0., EPS);

#endif
