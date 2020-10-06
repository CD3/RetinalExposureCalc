#include "catch.hpp"
#include <iostream>

#include <RetinalExposureCalc/Models/PhysicalProperties/Ocular/Transmission/Manual/Model.hpp>
#include <RetinalExposureCalc/Models/PhysicalProperties/Ocular/Transmission/CIE203_2012/Direct.hpp>
#include <RetinalExposureCalc/Models/PhysicalProperties/Ocular/Transmission/CIE203_2012/Total.hpp>
#include <RetinalExposureCalc/Models/PhysicalProperties/Ocular/Transmission/EffectiveTransmission/Schulmeister/Model.hpp>

TEST_CASE("Manual Transmission Model")
{
  using namespace boost::units;
  RetinalExposureCalc::PhysicalProperties::Ocular::Transmission::Manual::Model trans(0.5*boost::units::i::dimless);

  CHECK( trans( 100*boost::units::i::nm ).value() == Approx(0.5) );
  CHECK( trans( 1000*boost::units::i::nm ).value() == Approx(0.5) );
  trans.setValue(1.0*boost::units::i::dimensionless);
  CHECK( trans( 100*boost::units::i::nm ).value() == Approx(1) );
  CHECK( trans( 1000*boost::units::i::nm ).value() == Approx(1) );
  trans.setValue(0.5*boost::units::i::dimensionless);
  CHECK( trans( 100*boost::units::i::nm ).value() == Approx(0.5) );
  CHECK( trans( 1000*boost::units::i::nm ).value() == Approx(0.5) );
}


TEST_CASE("CIE203:2012 Direct Transmission Model")
{
  RetinalExposureCalc::PhysicalProperties::Ocular::Transmission::CIE203_2012::Direct::Model trans;

  CHECK( trans(400*boost::units::i::nm).value() == Approx(0.0121) );
  CHECK( trans(500*boost::units::i::nm).value() == Approx(0.516) );
  CHECK( trans(600*boost::units::i::nm).value() == Approx(0.597) );
  CHECK( trans(700*boost::units::i::nm).value() == Approx(0.646) );
  CHECK( trans(1400*boost::units::i::nm).value()+1 == Approx(1+1.58E-19) );
}

TEST_CASE("CIE203:2012 Total Transmission Model")
{
  RetinalExposureCalc::PhysicalProperties::Ocular::Transmission::CIE203_2012::Total::Model trans;

  CHECK( trans(400*boost::units::i::nm).value() == Approx(0.02271) );
  CHECK( trans(500*boost::units::i::nm).value() == Approx(0.7631) );
  CHECK( trans(600*boost::units::i::nm).value() == Approx(0.8204) );
  CHECK( trans(700*boost::units::i::nm).value() == Approx(0.8384) );
  CHECK( trans(1400*boost::units::i::nm).value()+1 == Approx(1+1.843E-19) );

}

TEST_CASE("CIE203:2012 Effective Transmission Model")
{
  RetinalExposureCalc::PhysicalProperties::Ocular::Transmission::EffectiveTransmission::Schulmeister::Model<> trans;

  CHECK( trans(400 *boost::units::i::nm, 5000*boost::units::i::um).value() == Approx(0.02271).epsilon(0.01) );
  CHECK( trans(500 *boost::units::i::nm, 5000*boost::units::i::um).value() == Approx(0.7631).epsilon(0.01) );
  CHECK( trans(600 *boost::units::i::nm, 5000*boost::units::i::um).value() == Approx(0.8204).epsilon(0.01) );
  CHECK( trans(700 *boost::units::i::nm, 5000*boost::units::i::um).value() == Approx(0.8384).epsilon(0.01) );
  CHECK( trans(1400*boost::units::i::nm, 5000*boost::units::i::um).value()+1 == Approx(1+1.843E-19) );

  CHECK( trans(400 *boost::units::i::nm, 1*boost::units::i::um).value() == Approx(0.0121).epsilon(0.30) );
  CHECK( trans(500 *boost::units::i::nm, 1*boost::units::i::um).value() == Approx(0.516).epsilon(0.10) );
  CHECK( trans(600 *boost::units::i::nm, 1*boost::units::i::um).value() == Approx(0.597).epsilon(0.05) );
  CHECK( trans(700 *boost::units::i::nm, 1*boost::units::i::um).value() == Approx(0.646).epsilon(0.05) );
  CHECK( trans(1400*boost::units::i::nm, 1*boost::units::i::um).value()+1 == Approx(1+1.58E-19) );

}

