#include <boost/program_options.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <RetinalExposureCalc/Calculator.hpp>

#include <iostream>
#include <fstream>
#include <sstream>

namespace po = boost::program_options;
using namespace boost::units;

int main(int argc, const char** argv)
{

  // define command line options
  po::options_description po_opts("Options");
  po_opts.add_options()("help,h", "print help message.");

  // now define our arguments.
  po::options_description po_args("Arguments");
  po_args.add_options()
    ("config-file"  , po::value<std::string>(), "JSON file containing exposure configuration.")
    ;

  // combine the options and arguments into one option list.
  // this is what we will use to parse the command line, but
  // when we output a description of the options, we will just use
  // po_opts
  po::options_description all_options("Options and Arguments");
  all_options.add(po_opts).add(po_args);

  // tell boost how to translate positional options to named options
  po::positional_options_description args;
  args.add("config-files", -1);

  po::variables_map vm;
  po::store(po::command_line_parser(argc, argv)
      .options(all_options)
      .positional(args)
      .run(),
      vm);
  po::notify(vm);

  if (argc == 1 || vm.count("help")) {
    std::cout << R"EOL(A command line application computing retinal exposures from cornea exposure.
)EOL";
    return 0;
  }


  try{
    std::ifstream in( vm["config-file"].as<std::string>().c_str() );
    boost::property_tree::ptree config;
    boost::property_tree::read_json(in,config);
    in.close();

    RetinalExposureCalc::Calculator calc;

    auto result = calc.run(config);

    std::ostringstream out;
    boost::property_tree::write_json(out, result);
    std::cout << out.str()<< std::endl;

  }
  catch(std::runtime_error e)
  {
    std::cerr << "There was an error calculating the exposure.\n";
    std::cerr << "Error Message: " << e.what() << std::endl;
  }
  catch(...)
  {
    std::cerr << "There was an unknown error. Sorry." << std::endl;
  }


  return 0;
}
