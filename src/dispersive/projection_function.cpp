// Spin projection functions, Q_j(s,t)
//
// Author:       Daniel Winney (2020)
// Affiliation:  Joint Physics Analysis Center (JPAC)
// Email:        dwinney@iu.edu
// ---------------------------------------------------------------------------

#include "dispersive/projection_function.hpp"

// ---------------------------------------------------------------------------
// Evaluate the cross-channel exchange projected amplitude
// Q_{jjp}(s,t)
std::complex<double> projection_function::eval(double s, double t)
{
  std::complex<double> result = 0.;

  auto error = [&] ()
  {
    std::cout << "\n Error! projection_function:";
    std::cout << " j = " << std::to_string(qns->j);
    std::cout << " and j' = " << std::to_string(qns->jp);
    std::cout << " combination not available. Quitting... \n";
    exit(1);
  };

  switch (qns->j)
  {
    // s-wave projection
    case 0:
    {
      switch (qns->jp)
      {
        // s wave, scalar exchange
        case 0:
        {
          result = Q(qns->l, s, t);
          break;
        }

        // s wave, vector exchange
        case 1: //
        {
          result = Q(qns->l+1, s, t);
          result += (2.*s - mDec2 - 3.*mPi2) * Q(qns->l, s, t);
          break;
        }
        default: error();
      }
      break;
    }

    // p-wave projection
    case 1:
    {
      switch (qns->jp)
      {
        // p - wave, scalar exchange
        case 0:
        {
          result = 2. * Q(qns->l+1, s, t);
          result += (s - mDec2 - 3.*mPi2) * Q(qns->l, s, t);
          break;
        }

        // p - wave, vector exchange
        case 1:
        {
          result = 2. * Q(qns->l+2, s, t);
          result += (5.*s + - 3. * mDec2 - 9. * mPi2) * Q(qns->l+1, s, t);
          result += (2.*s*s - 3.*mDec2*s - 9.*mPi2*s + mDec2*mDec2 + 6.*mDec2*mPi2 + 9.*mPi2*mPi2) * Q(qns->l,s,t);
          break;
        }
        default: error();
      }

      result /= Kacser(s);
      break;
    }

    // d-wave projection
    case 2:
    {
      if (qns->jp == 0)
      {
        result = 12.* Q(qns->l+2, s, t);
        result += (12. * s - 12. * mDec2 - 36. * mPi2) * Q(qns->l+1, s, t);
        result += (3.*s*s - 6.*mDec2*s + 3.*mDec2*mDec2 - 18.*mPi2*s + 18.*mPi2*mDec2 + 27.*mPi2*mPi2 - 1.) * Q(qns->l,s,t);
        result /= 2.;

        result /= pow(Kacser(s), 2.);
      }
      break;
    }
    default: error();
  }

  result *= barrier_ratio(qns->j, s);
  result /= pow(t, double(qns->l));

  return result;
};

// ---------------------------------------------------------------------------
// Angular projection Q kernel functions
// These are of the form:
// 1/Kacser(s) * \int_{t_minus}^{t_plus} x^n / (tp - tp - ieps)
std::complex<double> projection_function::Q_0(double s, double t)
{
  std::complex<double> result;
  result  = log(t - ieps - t_minus(s));
  result -= log(t - ieps - t_plus(s));

  result /= Kacser(s);
  return result;
};

std::complex<double> projection_function::Q(int k, double s, double t)
{
  switch (k)
  {
    case 0:
    {
      return Q_0(s, t);
    }
    case 1:
    {
      return t * Q_0(s, t) - 1.;
    }
    case 2:
    {
      return t*t * Q_0(s, t) - t - 0.5 * (pow(t_plus(s), 2.) - pow(t_minus(s), 2.)) / Kacser(s);
    }
    default:
    {
     std::cout << "\nNot enough Q's!!!\n";
     exit(1);
    }
  }
};

// ---------------------------------------------------------------------------
// Usual Kallen triangle function
std::complex<double> Kallen(std::complex<double> x, std::complex<double> y, std::complex<double> z)
{
  return x * x + y * y + z * z - 2. * (x * z + y * z + x * y);
};

// ---------------------------------------------------------------------------
// Kacser function which includes the correct analytic structure of
// product of breakup momenta, p(s) * q(s)
std::complex<double> projection_function::Kacser(double s)
{
  std::complex<double> result;

  result  = sqrt(pow(sqrt(s) + mPi, 2.) - mDec2 - ieps);
  result *= sqrt(pow(sqrt(s) - mPi, 2.) - mDec2 - ieps);
  result *= sqrt(Kallen(s, mPi2, mPi2)) / s;

  return result;
};

// Ratio of agular momentum barrier factors that are removed when partial wave projecting
std::complex<double> projection_function::barrier_ratio(int ell, double s)
{
  if (ell == 0)
  {
    return 1.;
  }
  else
  {
    std::complex<double> result;
    result  = sqrt(Kallen(s, mPi2, mPi2));
    result /= sqrt(pow(sqrt(s) + mPi, 2.) - mDec2 - ieps);
    result /= sqrt(pow(sqrt(s) - mPi, 2.) - mDec2 - ieps);

    return pow(result, xr * double(ell));
  }
};

// ---------------------------------------------------------------------------
// complex Bounds of integration
std::complex<double> projection_function::t_minus(double s)
{
  return (mDec2 + ieps) + mPi2 - (s + mDec2 + ieps - mPi2) / 2. - Kacser(s) / 2.;
};

std::complex<double> projection_function::t_plus(double s)
{
  return (mDec2 + ieps) + mPi2 - (s + mDec2 + ieps - mPi2) / 2. + Kacser(s) / 2.;
};
