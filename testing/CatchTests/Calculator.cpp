#include "catch.hpp"

#include <RetinalExposureCalc/Calculator.hpp>

TEST_CASE("Calculator")
{

  RetinalExposureCalc::Calculator calc;

  std::string config = R"EOF(
  {
  "propagation model":
  {
  "name" : "Vincelette Reduced Eye"
  },
  "transmission model":
  {
  "name" : "shulmeister:cie203:2012:effective"
  },
  "cornea exposure":
  {
  "wavelength": "532 nm",
  "beam-width": "3 mm",
  "beam-width-type": "1/e:d",
  "power": "1 mW"
  }
  }
  )EOF";

  auto result = calc.run(config);


}
