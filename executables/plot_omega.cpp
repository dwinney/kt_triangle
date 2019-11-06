#include "triangle.hpp"

#include <iostream>
#include <string>
#include <ctime>

int main()
{

  // Initialize a triangle object
  triangle tri;

  // Set the exchange rho particle mass and width,
  tri.set_exchangeMass(.770, .145);

  // Set the two other intermediate particles, in this case both pions
  tri.set_internalMass(mPi, mPi);

  // Set the two external particles: omega and pion
  // here argument 1 >= argument 2
  tri.set_externalMasses(0.780, mPi);

  // Choose the name for the output files to have (sans and extentions)
  std::string filename = "omega";

  // Plotting bounds
  double low = 1.e-3;
  double high = 81. * mPi * mPi;

  int Np = 25; // Number of points to plot

// ---------------------------------------------------------------------------
// You shouldnt need to change anything below this line
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// Calculate the triangle function first with the feynman representation

  std::cout << "\n";
  std::cout << "Calulating Feynman triangle... \n";

  std::vector<double> s;
  std::vector< std::complex<double> > feyn;

  clock_t begin = clock();

  std::complex<double> fxf_0 = tri.eval_feynman(low);   // Normalization

  for (int i = 0; i < Np; i++)
  {
    double si = low + double(i) * (high - low) / double(Np);

    std::complex<double> fx_f = tri.eval_feynman(si) / fxf_0;

    s.push_back(sqrt(si) / mPi);
    feyn.push_back(fx_f);
  }

  clock_t end = clock();
  double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

  std::cout << "Done in " << elapsed_secs << " seconds. \n";
  std::cout << "\n";

  // Plot the vectors and save them in .pdf and .dat
  quick_plot(s, feyn, filename + "_feyn");
  quick_print(s, feyn, filename + "_feyn");

  std::cout << "\n";

// ---------------------------------------------------------------------------
// Calculate the same thing now with the dispersive representation

  std::cout << "Calulating Dispersive triangle... \n";

  begin = clock();

  std::vector<std::complex<double>> disp;
  std::complex<double> fxd_0 = tri.eval_dispersive(low);

  s.clear();
  for (int i = 0; i < Np; i++)
  {
    double si = low + double(i) * (high - low) / double(Np);

    std::complex<double> fx_d = tri.eval_dispersive(si) / fxd_0;

    s.push_back(sqrt(si) / mPi);
    disp.push_back(fx_d);
  }

  end = clock();
  elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

  std::cout << "Done in " << elapsed_secs << " seconds. \n";
  std::cout << "\n";

  quick_plot(s, disp, filename + "_disp");
  quick_print(s, disp, filename + "_disp");

  std::cout << "\n";

// ---------------------------------------------------------------------------
  return 1.;
};