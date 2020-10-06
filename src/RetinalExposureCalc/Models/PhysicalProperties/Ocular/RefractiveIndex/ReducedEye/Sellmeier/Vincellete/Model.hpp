#pragma once

#include <BoostUnitDefinitions/Units.hpp>
#include "../../../../../../ModelBase.hpp"

namespace RetinalExposureCalc
{
  namespace PhysicalProperties
  {
    namespace Ocular
    {
      namespace RefractiveIndex
      {
        namespace ReducedEye
        {
          namespace Sellmeier
          {
            namespace Vincelette
            {
              /**
               * Computes the refractive index of the eye for a specified wavelength using
               * the Sellmeier equation with coefficients from Vincelette, 2008, "Thermal
               * lensing in ocular media exposed to continuous-wave near-infrared
               * radiation: the 1150-1350-nm region"
               */
              class Model : public ModelBase
              {
                protected:
                  double A  = 1;          // dimensionless
                  double B1 = 7.516e-1;   // dimensionless
                  double B2 = -4.484e-3;  // dimensionless
                  double B3 = -1.503e+1;  // dimensionless
                  double C1 = 1.641e-2;   // 1/um^2
                  double C2 = 8.596e-2;   // 1/um^2
                  double C3 = -1.028e+3;  // 1/um^2

                public:
                  Model()
                  {
                    this->addReference(R"EOF(
@Article{VINCELETTE--2008--thermallensinginocularmediaexposedtocontinuous-wavenear-infraredradiation:the1150-1350-nmregion,
  Title                    = {Thermal lensing in ocular media exposed to continuous-wave near-infrared radiation: the 1150-1350-nm region},
  Author                   = {Rebecca L. Vincelette and Ashley J. Welch and Robert J. Thomas and Benjamin A. Rockwell and David J. Lund},
  Journal                  = {Journal of Biomedical Optics},
  Year                     = {2008},
  Pages                    = {054005},
  Volume                   = {13},
  url       = {https://www.spiedigitallibrary.org/journals/journal-of-biomedical-optics/volume-13/issue-05/054005/Thermal-lensing-in-ocular-media-exposed-to-continuous-wave-near/10.1117/1.2978066.full?SSO=1},
  Keywords                 = {thermal lensing, nir},
}
          )EOF"
                        );
                    this->addNote("This refractive index model computes the refractive index using the Sellmeier equation. The Sellmeier coefficients were computed by Vincelette to give agreement between her reduced eye model and refractive error measurements in the human eye. See Vincelette 2008.");
}


template<typename L>
boost::units::quantity<boost::units::t::dimless> operator()(
    boost::units::quantity<L> a_wavelength) const
{
  static_assert(
      std::is_same<typename L::dimension_type, typename boost::units::t::um::dimension_type>::value,
      "Argument to ReducedEye::Sellmeier::Vincellete::Model::operator()(...) must be a length.");

  double x = boost::units::quantity<boost::units::t::um>(a_wavelength).value();

  return sqrt(A + (B1 * x * x) / (x * x - C1) + (B2 * x * x) / (x * x - C2) +
      (B3 * x * x) / (x * x - C3)) *
    boost::units::i::dimless;
}
};
}
}
}
}
}
}
}
