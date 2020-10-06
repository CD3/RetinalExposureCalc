#include "catch.hpp"
#include <iostream>

#include <libGBP/GaussianBeam.hpp>
#include <RetinalExposureCalc/Models/SchematicEyes/ReducedEye/Vincelette/Model.hpp>


TEST_CASE("Vincelette Reduced Eye")
{
  using namespace boost::units;

  SECTION("Manual")
  {


  GaussianBeam beam;
  beam.setOneOverEWaistDiameter( 3*units::i::mm );

  RetinalExposureCalc::SchematicEyes::ReducedEye::Vincelette::Model Eye;



  auto train = Eye.getOpticalTrain(1300*units::i::nm);
  beam.setWavelength(1300*units::i::nm);
  auto beam2 = train.transform(beam);
  auto DR = beam2.getOneOverESquaredDiameter( Eye.getRetinaPosition() );

  CHECK( DR.value() == Approx( 180e-4 ).epsilon(0.05) );
  }

  SECTION("Transform function")
  {
  GaussianBeam beam;
  beam.setWavelength( 1300*units::i::nm);
  beam.setOneOverEWaistDiameter( 3*units::i::mm );
  beam.setPower(1*units::i::W);

  RetinalExposureCalc::SchematicEyes::ReducedEye::Vincelette::Model Eye;
  auto beam2 = Eye.transform(beam);

  auto DR = beam2.getOneOverESquaredDiameter( Eye.getRetinaPosition() );
  CHECK( DR.value() == Approx( 180e-4 ).epsilon(0.05) );
  CHECK( beam2.getPeakIrradiance( Eye.getRetinaPosition() ).value() == Approx( 1 / (M_PI*(0.25*pow(180e-4/sqrt(2),2)))).epsilon(0.05) );
  }

}

