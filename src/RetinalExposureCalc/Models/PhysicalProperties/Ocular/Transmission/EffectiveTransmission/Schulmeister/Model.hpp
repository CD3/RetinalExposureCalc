#pragma once

/** @file Model.hpp
 * @brief
 * @author C.D. Clark III
 * @date 09/23/20
 */



#include <BoostUnitDefinitions/Units.hpp>
#include "../../../../../ModelBase.hpp"

namespace RetinalExposureCalc
{
  namespace PhysicalProperties
  {
    namespace Ocular
    {
      namespace Transmission
      {
        namespace EffectiveTransmission
        {
          namespace Schulmeister
          {
            /**
             * Computes the "effective transmission" by combining the total and direct transmissions
             * in a way that depends on the spot size as described by Schulmeister, 2013, "Validation of a computer model to predict laser induced thermal injury thresholds of the retina".
             */
            template<typename TOTAL_TRANSMISSION_MODEL = CIE203_2012::Total::Model>
              class Model : public ModelBase
            {
              protected:
                TOTAL_TRANSMISSION_MODEL m_TotalTransmission;

              public:
                Model()
                {

                  this->addReference(R"EOF(
                  @Article{JEAN--2017--Validationofacomputermodeltopredictlaserinducedretinalinjurythresholds,
  author  = {Mathieu Jean and Karl Schulmeister},
  title   = {Validation of a computer model to predict laser induced retinal injury thresholds},
  journal = {Journal of Laser Applications},
  year    = {2017},
  url     = {https://lia.scitation.org/doi/10.2351/1.4997831},
}
)EOF");

          this->addNote("This transmission model computes an 'effective transmission' that is intended to account for the effect of spot size. For large retinal spots, the total transmission is assumed to be appropriate, but for small retinal spots the direct transmission is assumed to be appropriate. This effective transmission is varies between total and direct transmission based on retinal spot size. It is based on the CIE 203:2012 tabulated values for total transmission. See Jean & Schulmeister 2017.");

for( auto& ref: m_TotalTransmission.getReferences() )
{
  this->addReference( ref );
}
}

template<typename L1, typename L2>
boost::units::quantity<boost::units::t::dimless> operator()(
    boost::units::quantity<L1> a_wavelength, boost::units::quantity<L2> a_diameter) const
{

  static_assert(
      std::is_same<typename L1::dimension_type, typename boost::units::t::um::dimension_type>::value,
      "First argument to EffectiveTransmission::Schulmeister::Model::operator()(...) must be a length.");
  static_assert(
      std::is_same<typename L2::dimension_type, typename boost::units::t::um::dimension_type>::value,
      "Second argument to EffectiveTransmission::Schulmeister::Model::operator()(...) must be a length.");

  double Ttot = m_TotalTransmission( a_wavelength );
  double l = boost::units::quantity<boost::units::t::nm>(a_wavelength).value();
  double theta = boost::units::quantity<boost::units::t::um>(a_diameter).value();
  double g = exp( -l/883 );
  double h = 0.5*exp( -theta/600 );

  return Ttot*(1 - g*h)*boost::units::i::dimensionless;

}
};
}
}
}
}
}
}
