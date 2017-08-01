cmake_minimum_required( VERSION 3.7.2 )
cmake_policy(SET CMP0048 NEW)
project (Jui VERSION 0.0.2)

message(STATUS "")
message(STATUS "Jui [${PROJECT_VERSION}] config init...")

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
set(CMAKE_AUTOMOC ON)

set(cacheDir ${CMAKE_SOURCE_DIR}/cache)
set(buildDir ${CMAKE_SOURCE_DIR}/build)
set(installDir ${CMAKE_SOURCE_DIR}/install)

message(STATUS "\t cacheDir: ${cacheDir}")
message(STATUS "\t buildDir: ${buildDir}")
message(STATUS "\t installDir: ${installDir}")

add_subdirectory(source)

message(STATUS "Jui config done...\n")