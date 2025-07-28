cmake_minimum_required(VERSION 3.29)
project(TestProject)

set(CMAKE_CXX_STANDARD 26)

add_executable(Main testing_solution.cpp)


# StressTesting


add_executable(Generator StressTesting/randobjects.hpp StressTesting/generator.cpp)
add_executable(Solution StressTesting/solution.cpp)
add_executable(Checker StressTesting/checker.cpp)
add_executable(Launcher StressTesting/launcher.cpp)

add_compile_definitions(Main PRIVATE STRESS)
add_dependencies(Launcher Generator)
target_compile_definitions(Generator PRIVATE STRESS)
add_dependencies(Launcher Solution)
target_compile_definitions(Solution PRIVATE STRESS)
add_dependencies(Launcher Checker)
target_compile_definitions(Checker PRIVATE STRESS)
add_dependencies(Launcher Main)