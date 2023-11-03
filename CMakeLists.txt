cmake_minimum_required(VERSION 3.26)
set(Boost_NO_WARN_NEW_VERSIONS 1)
project(Factorio_Launcher)

find_package(Boost 1.83 REQUIRED program_options filesystem)
#include_directories(${Boost_INCLUDE_DIR})

find_package(fmt CONFIG REQUIRED)

find_package(spdlog CONFIG REQUIRED)

find_package(nlohmann_json CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 20)

add_executable(Factorio_Launcher src/main2.cpp)

target_link_libraries(Factorio_Launcher fmt::fmt Boost::boost Boost::program_options Boost::filesystem spdlog::spdlog nlohmann_json::nlohmann_json)
