cmake_minimum_required( VERSION 3.1 )

project(RetinalExposureCalc-Applications)

if( EXISTS "${CMAKE_BINARY_DIR}/conanbuildinfo.cmake" )
  include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
  conan_basic_setup(TARGETS)
endif()

if( NOT TARGET CONAN_PKG::boost )
find_package( Boost COMPONENTS filesystem program_options REQUIRED )
endif()

add_subdirectory( .. RetinalExposureCalc)

add_executable( rec-cli rec-cli.cpp )
target_link_libraries( rec-cli RetinalExposureCalc::RetinalExposureCalc
                        $<$<TARGET_EXISTS:CONAN_PKG::boost>:CONAN_PKG::boost>
                        $<$<NOT:$<TARGET_EXISTS:CONAN_PKG::boost>>:Boost::program_options>
  )

