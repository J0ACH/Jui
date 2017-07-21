cmake_policy(SET CMP0048 NEW)

project (Jui VERSION 0.1.0)
cmake_minimum_required( VERSION 3.7.2 )

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
set(CMAKE_AUTOMOC ON)

add_subdirectory(src)