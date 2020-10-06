#include "Calculator.hpp"
#include <sstream>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/algorithm/string.hpp>
#include <UnitConvert.hpp>
#include <UnitConvert/GlobalUnitRegistry.hpp>

namespace RetinalExposureCalc
{
  std::string Calculator::clean_string(std::string str) const
  {
    boost::trim(str);
    boost::replace_all(str," ", "-");
    boost::to_lower(str);
    return str;
  }

  Calculator::propagation_model_variant Calculator::buildPropagationModel(boost::property_tree::ptree& config) const
  {
    if( clean_string(config.get<std::string>("name")) == "vincelette-reduced-eye" )
    {
      return SchematicEyes::ReducedEye::Vincelette::Model();
    }
    else
    {
      throw std::runtime_error("Unrecognized propagation model: "+config.get<std::string>("name"));
    }
  }

  Calculator::transmission_model_variant Calculator::buildTransmissionModel(boost::property_tree::ptree& config) const
  {
    if( clean_string(config.get<std::string>("name")) == "none" )
    {
      return PhysicalProperties::Ocular::Transmission::Manual::Model(1*units::i::dimless);
    }
    else if( clean_string(config.get<std::string>("name")) == "manual" )
    {
      auto& ureg = UnitConvert::getGlobalUnitRegistry();
      auto transmission = ureg.makeQuantity<double>(config.get<std::string>("value")).to<units::t::dimless>();
      return PhysicalProperties::Ocular::Transmission::Manual::Model(transmission);
    }
    else if( clean_string(config.get<std::string>("name")) == "cie203:2012:total" )
    {
      return PhysicalProperties::Ocular::Transmission::CIE203_2012::Total::Model();
    }
    else if( clean_string(config.get<std::string>("name")) == "cie203:2012:direct" )
    {
      return PhysicalProperties::Ocular::Transmission::CIE203_2012::Direct::Model();
    }
    else if( clean_string(config.get<std::string>("name")) == "shulmeister:cie203:2012:effective" )
    {
      return PhysicalProperties::Ocular::Transmission::EffectiveTransmission::Schulmeister::Model<>();
    }
    else
    {
      throw std::runtime_error("Unrecognized transmission model: "+config.get<std::string>("name"));
    }
  }

  GaussianBeam Calculator::buildBeam( boost::property_tree::ptree& config ) const
  {
    auto& ureg = UnitConvert::getGlobalUnitRegistry();
    GaussianBeam beam;
    auto wavelength = ureg.makeQuantity<double>(config.get<std::string>("wavelength")).to<units::t::nm>();
    beam.setWavelength(wavelength);

    auto beamWidth = ureg.makeQuantity<double>(config.get<std::string>("beam-width")).to<units::t::cm>();
    auto widthType = clean_string(config.get<std::string>("beam-width-type"));
    if( widthType == "1/e:d") beam.setOneOverEWaistDiameter( beamWidth );
    if( widthType == "1/e2:d") beam.setOneOverE2WaistDiameter( beamWidth );
    if( widthType == "fwhm:d") beam.setFullWidthHalfMaximumWaistDiameter( beamWidth );
    if( widthType == "1/e:r") beam.setOneOverEWaistRadius( beamWidth );
    if( widthType == "1/e2:r") beam.setOneOverE2WaistRadius( beamWidth );
    if( widthType == "fwhm:r") beam.setFullWidthHalfMaximumWaistRadius( beamWidth );

    if( config.count("beam-divergence") )
    {
      auto beamDiv = ureg.makeQuantity<double>(config.get<std::string>("beam-divergence")).to<units::t::rad>();
      auto divType = clean_string(config.get<std::string>("beam-divergence-type"));
      if( divType == "1/e:fw") beam.setOneOverEFullAngleDivergence( beamDiv );
      if( divType == "1/e2:hw") beam.setOneOverE2HalfAngleDivergence( beamDiv );
    }

    beam.setPower( 1 * units::i::W );
    if( config.count("power") > 0 ) beam.setPower( ureg.makeQuantity<double>(config.get<std::string>("power")).to<units::t::W>() );

    return beam;
  }


  std::string Calculator::run(const std::string& config) const
  {
    std::istringstream in(config);
    boost::property_tree::ptree conf;
    boost::property_tree::read_json(in,conf);

    auto result = run(conf);

    std::ostringstream out;
    boost::property_tree::write_json(out,result);

    return out.str();
  }

  boost::property_tree::ptree  Calculator::run(const boost::property_tree::ptree& config) const
  {
    boost::property_tree::ptree result;

    auto cornea_exposure = config.get_child("cornea exposure");
    auto propagation_model = config.get_child("propagation model");
    auto transmission_model = config.get_child("transmission model");

    auto beam = buildBeam(cornea_exposure);

    result.put( "cornea.1/e:d", beam.getOneOverEDiameter( ) );
    result.put( "cornea.1/e:d0", beam.getOneOverEWaistDiameter( ) );
    result.put( "cornea.1/e2:d", beam.getOneOverE2Diameter( ) );
    result.put( "cornea.1/e2:d0", beam.getOneOverE2WaistDiameter( ) );

    result.put( "cornea.1/e:fw", beam.getOneOverEFullAngleDivergence( ) );
    result.put( "cornea.1/e2:hw", beam.getOneOverE2HalfAngleDivergence( ) );

    result.put( "cornea.Phi", beam.getPower() );
    result.put( "cornea.E", beam.getPeakIrradiance( 0*units::i::cm ) );
    result.put( "cornea.E@z0", beam.getPeakIrradiance( ) );
    result.put( "cornea.z0", beam.getRelativeWaistPosition( ) );

    auto prop = buildPropagationModel(propagation_model);
    auto trans = buildTransmissionModel(transmission_model);

    visitors::transform_beam transform;
    transform.beam = beam;
    auto beam2 = boost::apply_visitor( transform, prop, trans );
    auto xr = boost::apply_visitor( visitors::get_retina_position(), prop );
    beam2.setCurrentPosition(xr);


    result.put( "retina.1/e:d", beam2.getOneOverEDiameter( ) );
    result.put( "retina.1/e:d0", beam2.getOneOverEWaistDiameter( ) );
    result.put( "retina.1/e2:d", beam2.getOneOverE2Diameter( ) );
    result.put( "retina.1/e2:d0", beam2.getOneOverE2WaistDiameter( ) );

    result.put( "retina.1/e:fw", beam2.getOneOverEFullAngleDivergence( ) );
    result.put( "retina.1/e2:hw", beam2.getOneOverE2HalfAngleDivergence( ) );

    result.put( "retina.Phi", beam2.getPower() );
    result.put( "retina.E", beam2.getPeakIrradiance( ) );
    result.put( "retina.E@z0", beam2.getPeakIrradiance( ) );
    result.put( "retina.z0", beam2.getRelativeWaistPosition( ) );


    boost::property_tree::ptree references;
    visitors::add_references add_references_visitor;
    add_references_visitor.references = &references;

    boost::apply_visitor( add_references_visitor, prop);
    boost::apply_visitor( add_references_visitor, trans);

    result.add_child("references",references);


    boost::property_tree::ptree notes;
    visitors::add_notes add_notes_visitor;
    add_notes_visitor.notes = &notes;

    boost::apply_visitor( add_notes_visitor, prop);
    boost::apply_visitor( add_notes_visitor, trans);

    result.add_child("notes",notes);



    return result;
  }

}

