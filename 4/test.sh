#!/bin/bash
cp file2.cpp file11.cpp
./vcon help
./vcon log
./vcon init
./vcon add file1.cpp file2.cpp file3.cpp
./vcon fix
rm -rf file1.cpp
mv file11.cpp file1.cpp
./vcon fix file1.cpp
./vcon diff file1.cpp
./vcon diff file1.cpp 1
./vcon diff file1.cpp 1 2
./vcon remove file2.cpp
./vcon fix file2.cpp
./vcon step file1.cpp 1
./vcon log
./vcon extendedlog
./vcon tracked
