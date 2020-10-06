# RetinalExposureCalc

## Description

A C++ library for calculating the retinal exposure from various light sources.

## Building and Installing

All dependencies can be installed with Conan. Once installed,
build the library with Cmake is used to configure, build, and install:

```
$ mkdir build
$ cd build
$ conan install ..
$ cmake ..
$ cmake --build .
$ cmake --build . --target install
```
