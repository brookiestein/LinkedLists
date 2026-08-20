cmake_minimum_required(VERSION 4.2)

project(Asignacion2 VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_SOURCES
  main.cpp
  product.hpp
  product.cpp
  product_list.hpp
)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
