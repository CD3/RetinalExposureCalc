#include <string>
#include <map>
#include <boost/variant.hpp>
#include <boost/property_tree/ptree.hpp>

#include "./Models/SchematicEyes/ReducedEye/Vincelette/Model.hpp"
#include "./Models/PhysicalProperties/Ocular/Transmission/Manual/Model.hpp"
#include "./Models/PhysicalProperties/Ocular/Transmission/CIE203_2012/Direct.hpp"
#include "./Models/PhysicalProperties/Ocular/Transmission/CIE203_2012/Total.hpp"
#include "./Models/PhysicalProperties/Ocular/Transmission/EffectiveTransmission/Schulmeister/Model.hpp"

namespace RetinalExposureCalc
{

  namespace visitors
  {
    class transform_beam : public boost::static_visitor<GaussianBeam>
    {
      public:
        GaussianBeam beam;


        template<typename M, typename T>
          GaussianBeam operator()(const M& prop, const T& trans) const
          {
            GaussianBeam beam2 = prop.transform(beam);
            beam2.setPower( trans(beam2.getWavelength()).value()*beam2.getPower() );
            return beam2;
          }

        template<typename M, typename T>
          GaussianBeam operator()(const M& prop, const PhysicalProperties::Ocular::Transmission::EffectiveTransmission::Schulmeister::Model<T>& trans) const
          {
            GaussianBeam beam2 = prop.transform(beam);
            beam2.setPower( trans(beam2.getWavelength(),beam2.getOneOverEDiameter(prop.getRetinaPosition())).value()*beam2.getPower() );
            return beam2;
          }
    };


    class get_retina_position: public boost::static_visitor<boost::units::quantity<units::t::cm>>
    {
      public:
        template<typename M>
          boost::units::quantity<units::t::cm> operator()(const M& model) const
          {
            return model.getRetinaPosition();
          }
    };

    class add_references: public boost::static_visitor<>
    {
      public:
        boost::property_tree::ptree* references;

        template<typename M>
          void operator()(const M& model) const
          {
            for( const auto& ref : model.getReferences() )
            {
              references->push_back( boost::property_tree::ptree::value_type("", boost::property_tree::ptree(ref)) );
            }

          }
    };

    class add_notes: public boost::static_visitor<>
    {
      public:
        boost::property_tree::ptree* notes;

        template<typename M>
          void operator()(const M& model) const
          {
            for( const auto& note : model.getNotes() )
            {
              notes->push_back( boost::property_tree::ptree::value_type("", boost::property_tree::ptree(note)) );
            }

          }
    };
  }

  // A wrapper class that takes all inputs as JSON strings, calculates the retinal exposure, and
  // returns the results as a JSON string.
  class Calculator
  {
    public:
      using propagation_model_variant = boost::variant<RetinalExposureCalc::SchematicEyes::ReducedEye::Vincelette::Model >;
      using transmission_model_variant = boost::variant<
            PhysicalProperties::Ocular::Transmission::CIE203_2012::Total::Model,
            PhysicalProperties::Ocular::Transmission::CIE203_2012::Direct::Model,
            PhysicalProperties::Ocular::Transmission::EffectiveTransmission::Schulmeister::Model<>,
            PhysicalProperties::Ocular::Transmission::Manual::Model
              >;

    protected:

      GaussianBeam buildBeam( boost::property_tree::ptree& ) const;
      propagation_model_variant buildPropagationModel( boost::property_tree::ptree& ) const;
      transmission_model_variant buildTransmissionModel( boost::property_tree::ptree& ) const;

      std::string clean_string(std::string str) const;


    public:

      boost::property_tree::ptree run(const boost::property_tree::ptree& config) const;
      std::string run(const std::string& config) const;
  };

}

