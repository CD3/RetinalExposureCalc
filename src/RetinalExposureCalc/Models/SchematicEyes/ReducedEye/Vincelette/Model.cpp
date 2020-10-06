#include "Model.hpp"
#include <libGBP/OpticalElements/SphericalInterface.hpp>
#include "../../../PhysicalProperties/Ocular/RefractiveIndex/ReducedEye/Sellmeier/Vincellete/Model.hpp"
#include <memory>
#include <sstream>

namespace RetinalExposureCalc
{
  namespace SchematicEyes
  {
    namespace ReducedEye
    {
      namespace Vincelette
      {
        Model::Model()
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
          this->addNote("Vincelette used a simple reduced eye model to calculate retinal image size. The eye consists of a single spherical refracting surface (cornea) with a 6.1 cm radius of curvature and a retinal plane at 2.44 cm. A set of Sellmeier coefficients for the refractive index of the eye were found by fitting to refractive indices computed from measured refractive error in the Human eye. This means the refractive index used for the eye model should produce retinal image sizes close to those in the nonaccommodated human eye, but are not necessarily the true refractive index of any ocular tissue. See Vincelette 2008.");

          }

boost::units::quantity<units::t::dimless>
Model::getRefractiveIndex(boost::units::quantity<units::t::nm> wavelength) const
{
  return RefractiveIndex(wavelength);
}

OpticalSystem<units::t::cm>
Model::getOpticalTrain(boost::units::quantity<units::t::nm> wavelength) const
{
  OpticalSystem<units::t::cm> system;

  auto interface = std::make_shared<SphericalInterface<units::t::centimeter>>();

  interface->setInitialRefractiveIndex(1);

  interface->setFinalRefractiveIndex(getRefractiveIndex(wavelength));
  interface->setRadiusOfCurvature(CorneaRadiusOfCurvature);

  system.addElement(interface, 0*units::i::cm);



  return system;
}

boost::units::quantity<units::t::cm>
Model::getRetinaPosition() const
{
  return this->LengthOfEye;
}

GaussianBeam
Model::transform( const GaussianBeam& beam) const
{
  auto train = this->getOpticalTrain( beam.getWavelength<units::t::nm>() );
  auto beam2 = train.transform(beam);
  return beam2;
}


}
}
}
}
