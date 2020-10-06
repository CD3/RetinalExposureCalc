#pragma once

/** @file Model.hpp
 * @brief
 * @author C.D. Clark III
 * @date 09/14/20
 */


#include <map>
#include <string>
#include <BoostUnitDefinitions/Units.hpp>
#include <libGBP/OpticalSystem.hpp>
#include <libGBP/GaussianBeam.hpp>
#include "../../../ModelBase.hpp"
#include "../../../PhysicalProperties/Ocular/RefractiveIndex/ReducedEye/Sellmeier/Vincellete/Model.hpp"

namespace RetinalExposureCalc
{
  namespace SchematicEyes
  {
    namespace ReducedEye
    {
      namespace Vincelette
      {
        class Model : public ModelBase
        {
          private:
            PhysicalProperties::Ocular::RefractiveIndex::ReducedEye::Sellmeier::Vincelette::Model RefractiveIndex;
            boost::units::quantity< units::t::cm > CorneaRadiusOfCurvature = 0.61*boost::units::i::cm;
            boost::units::quantity< units::t::cm > LengthOfEye = 2.44*boost::units::i::cm;

          public:
            Model();

            boost::units::quantity<units::t::dimless> 
            getRefractiveIndex(boost::units::quantity<units::t::nm> wavelength) const;

            OpticalSystem<units::t::cm>
            getOpticalTrain(boost::units::quantity<units::t::nm> wavelength) const;

            boost::units::quantity<units::t::cm> getRetinaPosition() const;

            GaussianBeam transform( const GaussianBeam& beam) const;

        };
      }
    }
  }
}
