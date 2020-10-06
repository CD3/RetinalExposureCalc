#pragma once

/** @file Total.hpp
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
          namespace Total
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
                    1.4,  1.41,  1.42, 1.43,  1.44, 1.45,  1.46, 1.47,  1.48, 1.49,
                    1.5,  1.51,  1.52, 1.53,  1.54, 1.55,  1.56, 1.57,  1.58, 1.59,
                    1.6,  1.61,  1.62, 1.63,  1.64, 1.65,  1.66, 1.67,  1.68, 1.69,
                    1.7,  1.71,  1.72, 1.73,  1.74, 1.75,  1.76, 1.77,  1.78, 1.79,
                    1.8,  1.81,  1.82, 1.83,  1.84, 1.85,  1.86, 1.87,  1.88, 1.89,
                    1.9,  1.91,  1.92, 1.93,  1.94, 1.95,  1.96, 1.97,  1.98, 1.99,
                    2,    2.01,  2.02, 2.03,  2.04, 2.05,  2.06, 2.07,  2.08, 2.09,
                    2.1,  2.11,  2.12, 2.13,  2.14, 2.15,  2.16, 2.17,  2.18, 2.19,
                    2.2,  2.21,  2.22, 2.23,  2.24, 2.25,  2.26, 2.27,  2.28, 2.29,
                    2.3,  2.31,  2.32, 2.33,  2.34, 2.35,  2.36, 2.37,  2.38, 2.39,
                    2.4,  2.41,  2.42, 2.43,  2.44, 2.45,  2.46, 2.47,  2.48, 2.49,
                    2.5};
                  std::vector<double> transmissions = {
                    1.217E-07,  3.919E-06,  0.0002833,  0.003561,   0.01177,    0.01188,
                    0.009472,   0.006676,   0.00424,    0.002686,   0.001591,   0.001076,
                    0.00103,    0.001077,   0.001123,   0.001188,   0.001773,   0.003161,
                    0.005486,   0.01041,    0.02271,    0.05047,    0.1233,     0.2248,
                    0.3351,     0.4404,     0.514,      0.5813,     0.6279,     0.6571,
                    0.6749,     0.6901,     0.7001,     0.7124,     0.723,      0.7301,
                    0.7404,     0.7449,     0.7567,     0.757,      0.7631,     0.7694,
                    0.7731,     0.7762,     0.7782,     0.7817,     0.7867,     0.7912,
                    0.7955,     0.797,      0.7993,     0.802,      0.8017,     0.8049,
                    0.8086,     0.8103,     0.8122,     0.8157,     0.8168,     0.8195,
                    0.8204,     0.8223,     0.8241,     0.8245,     0.8269,     0.8281,
                    0.8276,     0.8287,     0.829,      0.8313,     0.8332,     0.8344,
                    0.8327,     0.8346,     0.8353,     0.8354,     0.8363,     0.8363,
                    0.8368,     0.8372,     0.8384,     0.8395,     0.839,      0.8375,
                    0.836,      0.8344,     0.831,      0.8291,     0.8244,     0.827,
                    0.8263,     0.8269,     0.829,      0.8312,     0.8333,     0.835,
                    0.8356,     0.8359,     0.8395,     0.8341,     0.8297,     0.824,
                    0.8149,     0.8037,     0.7965,     0.7927,     0.785,      0.7728,
                    0.7643,     0.7505,     0.7366,     0.72,       0.6861,     0.6159,
                    0.5156,     0.3797,     0.2817,     0.269,      0.2772,     0.3184,
                    0.3647,     0.4112,     0.474,      0.5314,     0.581,      0.615,
                    0.6373,     0.635,      0.6242,     0.5896,     0.5585,     0.5154,
                    0.4658,     0.3552,     0.1752,     0.07834,    0.05902,    0.05566,
                    0.05174,    0.05507,    0.05081,    0.05684,    0.06128,    0.06721,
                    0.07255,    0.07975,    0.0819,     0.07859,    0.07037,    0.05747,
                    0.04104,    0.02577,    0.009856,   0.003438,   0.001019,   0.0003671,
                    8.524E-05,  4.045E-06,  8.095E-08,  1.583E-12,  1.843E-19,  3.244E-27,
                    5.151E-31,  1.055E-32,  9.29E-34,   2.455E-33,  8.276E-33,  7.46E-30,
                    1.565E-27,  2.293E-24,  1.272E-21,  3.401E-19,  3.442E-17,  2.731E-15,
                    1.046E-13,  1.514E-12,  2.193E-11,  2.002E-10,  1.332E-09,  5.454E-09,
                    1.709E-08,  4.2E-08,    1.007E-07,  1.761E-07,  3.08E-07,   4.77E-07,
                    5.936E-07,  7.037E-07,  7.388E-07,  6.542E-07,  5.008E-07,  3.395E-07,
                    1.941E-07,  8.094E-08,  2.583E-08,  6.011E-09,  1.239E-09,  3.1E-10,
                    1.145E-10,  7.76E-11,   7.574E-11,  7.042E-11,  5.134E-11,  2.797E-11,
                    5.104E-12,  1.333E-13,  3.442E-17,  1.583E-25,  4.855E-41,  4.114E-69,
                    1.997E-109, 7.207E-118, 3.811E-123, 4.329E-122, 8.261E-136, 1.548E-111,
                    4.239E-105, 5.049E-96,  2.494E-92,  5.55E-80,   1.062E-72,  4.729E-66,
                    9.048E-59,  1.711E-53,  3.632E-49,  6.046E-45,  6.118E-43,  1.143E-39,
                    4.971E-37,  1.926E-33,  6.568E-31,  4.088E-29,  2.544E-27,  7.639E-26,
                    8.677E-25,  4.754E-24,  4.235E-23,  1.82E-22,   4.811E-22,  9.973E-22,
                    1.272E-21,  1.272E-21,  7.821E-22,  4.811E-22,  1.82E-22,   5.4E-23,
                    7.729E-24,  1.106E-24,  7.639E-26,  6.725E-27,  1.757E-28,  4.588E-30,
                    8.276E-33,  1.33E-34,   8.082E-37,  4.325E-40,  1.636E-40,  1.617E-42,
                    2.567E-46,  5.904E-49,  3.547E-53,  6.321E-58,  1.437E-62,  2.281E-66,
                    2.774E-74,  1.666E-78,  4.302E-82,  2.866E-89,  6.592E-92,  2.962E-104,
                    4.816E-104};

                  interpolator.setData(wavelengths, transmissions);
          this->addReference(R"EOF(
@TechReport{LUND--2012--Acomputerizedapproachtotransmissionandabsorptioncharacteristicsofthehumaneye,
  author      = {D. Lund and J. Marshall and J. Mellerio and T. Okuno and K. Schulmeister and D. Sliney and P. S\"{o}derberg and B. Stuck and D. {van Norren} and J. Zuclich},
  title       = {A computerized approach to transmission and absorption characteristics of the human eye},
  institution = {International Commission on Illumination},
  year        = {2012},
  url         = {http://cie.co.at/publications/computerized-approach-transmission-and-absorption-characteristics-human-eye},
}
)EOF");

          this->addReference(R"EOF(
@Article{STEFFEN--1990--Asimplemethodformonotonicinterpolationinonedimension,
  author  = {M. Steffen},
  title   = {A simple method for monotonic interpolation in one dimension},
  journal = {Astronomy and Astrophysics},
  year    = {1990},
  url     = {http://adsabs.harvard.edu/full/1990A%26A...239..443S},
}
)EOF");


          this->addNote("This transmission model is based on the tabulated total transmission values for the young human eye in the 2012 CIE technical report 203:2012. The report tabulates values between 300 - 2500 nm every 5 - 10 nm.");
          this->addNote("Values at wavelengths between tabulated values are interpolated using a monotonic interpolation method to avoid overshoot (see Steffen 1990).");

          }

                template<typename L>
                  boost::units::quantity<boost::units::t::dimless> operator()(
                      boost::units::quantity<L> a_wavelength) const
                  {
                    static_assert(
                        std::is_same<typename L::dimension_type, typename boost::units::t::um::dimension_type>::value,
                        "Argument to CIE203_2012::Total::Model::operator()(...) must be a length.");

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
