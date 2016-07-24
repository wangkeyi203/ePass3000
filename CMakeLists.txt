cmake_minimum_required(VERSION 3.4)
project(epass3000)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

set(SOURCE_FILES ApplicationTest.cpp ApplicationTest.h AuthTest.cpp AuthTest.h ContainerTest.cpp ContainerTest.h CryptoTest.h CryptoTest.cpp DevMgntTest.cpp DevMgntTest.h Ds_GM_Test.cpp FileOprTest.cpp FileOprTest.h StdAfx.cpp StdAfx.h Utilities.cpp Utilities.h SKFAPI.h)
add_executable(epass3000 ${SOURCE_FILES})