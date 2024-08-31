cmake_minimum_required(VERSION 3.15)

project(glad VERSION 1.0 LANGUAGES C)

add_library(glad STATIC src/glad.c)
target_include_directories(glad PUBLIC "include/")