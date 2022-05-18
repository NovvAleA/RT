cmake_minimum_required(VERSION 2.8)

project(RT)

set(RT_src main.cpp figure.cpp )
set(RT_hdr BMP.h function.h Factory.h class_vector.h  figure.h )

add_executable(${PROJECT_NAME} ${RT_src} ${RT_hdr})