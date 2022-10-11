cmake_minimum_required(VERSION 3.23)
project(RayTracingToy)

set(CMAKE_CXX_STANDARD 17)

add_executable(RayTracingToy main.cpp vec3.h ray.h hitable.h sphere.h hitablelist.h camera.h material.h)
