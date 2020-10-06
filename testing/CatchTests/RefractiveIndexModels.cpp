#include "catch.hpp"
#include <iostream>

#include <RetinalExposureCalc/Models/PhysicalProperties/Ocular/RefractiveIndex/ReducedEye/Sellmeier/Vincellete/Model.hpp>

TEST_CASE("Reduced Eye Sellmeier Refractive Index Model")
{
  using namespace boost::units;
  RetinalExposureCalc::PhysicalProperties::Ocular::RefractiveIndex::ReducedEye::Sellmeier::Vincelette::Model refind;

  // values taken from Vincelette paper using plot digitizer
  CHECK( refind( 0.3993993063388224*i::um ).value() == Approx(1.350769230769231).epsilon(0.001) );
  CHECK( refind( 399.3993063388224*i::nm ).value()  == Approx(1.350769230769231).epsilon(0.001) );
  CHECK( refind( 0.5537909335288367*i::um ).value() == Approx( 1.335594405594405).epsilon(0.001) );
  CHECK( refind( 0.9319208681103843*i::um ).value() == Approx( 1.322447552447552).epsilon(0.001) );
  CHECK( refind( 1.1552012839311228*i::um ).value() == Approx( 1.317622377622377).epsilon(0.001) );
  CHECK( refind( 1.3999682776900522*i::um ).value() == Approx( 1.313356643356643).epsilon(0.001) );
}

