cmake_minimum_required(VERSION 3.3)
project(CmakeProject)
add_executable(BoomExe src/main.cpp)
add_executable(BoomMac MACOSX_BUNDLE src/main.cpp)