#pragma once

/** @file Model.hpp
 * @brief
 * @author C.D. Clark III
 * @date 09/23/20
 */



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
        namespace Manual
        {
          class Model : public ModelBase
          {
            protected:
              double value;

            public:
              template<typename U>
                Model( boost::units::quantity<U> a_value)
                {
                  setValue(a_value);;
                }

              template<typename U>
                void setValue( boost::units::quantity<U> a_value)
                {
                  static_assert(
                      std::is_same<typename U::dimension_type, typename boost::units::t::dimensionless::dimension_type>::value,
                      "Argument to Transmission::Manual::Model::setValue()(...) must be dimensionless.");
                  value = boost::units::quantity<boost::units::t::dimless>(a_value).value();
                }

              template<typename L>
                boost::units::quantity<boost::units::t::dimless> operator()(
                    boost::units::quantity<L> a_wavelength) const
                {
                  static_assert(
                      std::is_same<typename L::dimension_type, typename boost::units::t::um::dimension_type>::value,
                      "Argument to Transmission::Manual::Model::operator()(...) must be a length.");
                  return value* boost::units::i::dimless;
                }
          };
        }
      }
    }
  }
}


