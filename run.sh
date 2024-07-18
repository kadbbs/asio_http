#!/bin/bash
#

if [ ! -d "./cmake-build-debug" ];then
  mkdir ./build
  cd build
  cmake ..
  make -j4

  else
  cd ./cmake-build-debug
  echo "  ./cmake-build-debug/asio_http 0.0.0.0 8090 ./"



fi

./asio_http 0.0.0.0 8090 ./

