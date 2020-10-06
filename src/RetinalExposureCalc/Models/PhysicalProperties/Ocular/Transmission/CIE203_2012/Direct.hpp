#pragma once

/** @file Direct.hpp
 * @brief
 * @author C.D. Clark III
 */

#include <vector>

#include <libInterpolate/Interpolate.hpp>
#include <BoostUnitDefinitions/Units.hpp>
#include "../../../../ModelBase.hpp"

namespace RetinalExposureCalc
{
  namespace PhysicalProperties
  {
    namespace Ocular
    {
      namespace Transmission
      {
        namespace CIE203_2012
        {
          namespace Direct
          {
            class Model : public ModelBase
            {
              protected:
                _1D::MonotonicInterpolator<double> interpolator;

              public:
                Model()
                {
                  std::vector<double> wavelengths = {
                    0.3,  0.305, 0.31, 0.315, 0.32, 0.325, 0.33, 0.335, 0.34, 0.345,
                    0.35, 0.355, 0.36, 0.365, 0.37, 0.375, 0.38, 0.385, 0.39, 0.395,
                    0.4,  0.405, 0.41, 0.415, 0.42, 0.425, 0.43, 0.435, 0.44, 0.445,
                    0.45, 0.455, 0.46, 0.465, 0.47, 0.475, 0.48, 0.485, 0.49, 0.495,
                    0.5,  0.505, 0.51, 0.515, 0.52, 0.525, 0.53, 0.535, 0.54, 0.545,
                    0.55, 0.555, 0.56, 0.565, 0.57, 0.575, 0.58, 0.585, 0.59, 0.595,
                    0.6,  0.605, 0.61, 0.615, 0.62, 0.625, 0.63, 0.635, 0.64, 0.645,
                    0.65, 0.655, 0.66, 0.665, 0.67, 0.675, 0.68, 0.685, 0.69, 0.695,
                    0.7,  0.705, 0.71, 0.715, 0.72, 0.725, 0.73, 0.735, 0.74, 0.745,
                    0.75, 0.755, 0.76, 0.765, 0.77, 0.775, 0.78, 0.785, 0.79, 0.795,
                    0.8,  0.81,  0.82, 0.83,  0.84, 0.85,  0.86, 0.87,  0.88, 0.89,
                    0.9,  0.91,  0.92, 0.93,  0.94, 0.95,  0.96, 0.97,  0.98, 0.99,
                    1,    1.01,  1.02, 1.03,  1.04, 1.05,  1.06, 1.07,  1.08, 1.09,
                    1.1,  1.11,  1.12, 1.13,  1.14, 1.15,  1.16, 1.17,  1.18, 1.19,
                    1.2,  1.21,  1.22, 1.23,  1.24, 1.25,  1.26, 1.27,  1.28, 1.29,
                    1.3,  1.31,  1.32, 1.33,  1.34, 1.35,  1.36, 1.37,  1.38, 1.39,
                    1.4};
                  std::vector<double> transmissions = {
                    8.71E-09, 3.42E-07, 2.95E-05, 0.000433, 0.00165,  0.00174,  0.00145,
                    0.00107,  0.000704, 0.000452, 0.000272, 0.000186, 0.000181, 0.000192,
                    0.000202, 0.000289, 0.000456, 0.00115,  0.0028,   0.00543,  0.0121,
                    0.0274,   0.0681,   0.126,    0.192,    0.256,    0.304,    0.35,
                    0.384,    0.408,    0.426,    0.441,    0.452,    0.462,    0.471,
                    0.479,    0.489,    0.494,    0.506,    0.508,    0.516,    0.522,
                    0.526,    0.531,    0.534,    0.538,    0.543,    0.547,    0.551,
                    0.554,    0.557,    0.562,    0.565,    0.57,     0.575,    0.578,
                    0.582,    0.586,    0.589,    0.594,    0.597,    0.6,      0.604,
                    0.606,    0.61,     0.613,    0.615,    0.618,    0.621,    0.624,
                    0.627,    0.629,    0.629,    0.632,    0.634,    0.636,    0.638,
                    0.639,    0.642,    0.643,    0.646,    0.648,    0.649,    0.651,
                    0.652,    0.652,    0.651,    0.651,    0.648,    0.652,    0.653,
                    0.655,    0.658,    0.661,    0.664,    0.667,    0.669,    0.67,
                    0.674,    0.671,    0.67,     0.667,    0.661,    0.653,    0.648,
                    0.646,    0.641,    0.632,    0.625,    0.614,    0.604,    0.593,
                    0.567,    0.51,     0.428,    0.317,    0.235,    0.223,    0.231,
                    0.267,    0.305,    0.344,    0.399,    0.449,    0.491,    0.522,
                    0.542,    0.542,    0.534,    0.505,    0.478,    0.442,    0.398,
                    0.304,    0.149,    0.0666,   0.0502,   0.0474,   0.0441,   0.0471,
                    0.0435,   0.0487,   0.0524,   0.0576,   0.062,    0.0684,   0.0706,
                    0.0677,   0.0608,   0.0496,   0.0354,   0.0222,   0.00846,  0.00295,
                    0.000873, 0.000314, 7.3E-05,  3.46E-06, 6.93E-08, 1.35E-12, 1.58E-19};

                  interpolator.setData(wavelengths, transmissions);


          this->addReference(R"EOF(
@TechReport{LUND--2012--Acomputerizedapproachtotransmissionandabsorptioncharacteristicsofthehumaneye,
  author      = {D. Lund and J. Marshall and J. Mellerio and T. Okuno and K. Schulmeister and D. Sliney and P. S\"{o}derberg and B. Stuck and D. {van Norren} and J. Zuclich},
  title       = {A computerized approach to transmission and absorption characteristics of the human eye},
  institution = {International Commission on Illumination},
  year        = {2012},
  url         = {http://cie.co.at/publications/computerized-approach-transmission-and-absorption-characteristics-human-eye},
}
)EOF"
              );

          this->addReference(R"EOF(
@Article{STEFFEN--1990--Asimplemethodformonotonicinterpolationinonedimension,
  author  = {M. Steffen},
  title   = {A simple method for monotonic interpolation in one dimension},
  journal = {Astronomy and Astrophysics},
  year    = {1990},
  url     = {http://adsabs.harvard.edu/full/1990A%26A...239..443S},
}
)EOF");


          this->addNote("This transmission model is based on the tabulated direct transmission values for the young human eye in the 2012 CIE technical report 203:2012. The report tabulates values between 300 - 2500 nm every 5 - 10 nm.");
          this->addNote("Values at wavelengths between tabulated values are interpolated using a monotonic interpolation method to avoid overshoot (see Steffen 1990).");

          }

                template<typename L>
                  boost::units::quantity<boost::units::t::dimless> operator()(
                      boost::units::quantity<L> a_wavelength) const
                  {
                    static_assert(
                        std::is_same<typename L::dimension_type, typename boost::units::t::um::dimension_type>::value,
                        "Argument to CIE203_2012::Direct::Model::operator()(...) must be a length.");

                    return interpolator(boost::units::quantity<boost::units::t::um>(a_wavelength).value()) *
                      boost::units::i::dimless;
                  }
            };
          }
        }
      }
    }
  }
}
