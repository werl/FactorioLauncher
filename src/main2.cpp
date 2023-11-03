//
// Created by peter on 2023-11-02.
//
#include <iostream>
#include <filesystem>
#include "boost/process.hpp"
#include "boost/program_options.hpp"

namespace po = boost::program_options;
namespace pr = boost::process;
namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
    po::options_description generic("General Options");
    generic.add_options()
            ("help,h", "Produce help message")
            ("version", "Print version string")
            ;

    po::options_description launcher("Launcher Options");
    launcher.add_options()
            ("list,l", "List instances")
            ("instance,i", po::value<std::string>(), "Name of instance")
            ;

    po::options_description instance("Instance Creation/Edit Options");
    instance.add_options()
            ;

    po::options_description hidden("hidden options");
    hidden.add_options()

            ;

    po::options_description cmdline_options;
    cmdline_options.add(generic).add(launcher).add(instance);

    po::variables_map vm;
    po::store(po::command_line_parser (argc, argv).options(cmdline_options).run(), vm);
    po::notify(vm);
    if (vm.count("help")) {
        std::cout << cmdline_options << "\n";
        return 1;
    }
    std::cout << 2 << "\n";
    if (vm.count("list")) {
        std::cout << "listing instances...\n";
        fs::create_directories(fs::current_path().append("instances"));
        std::ranges::for_each(fs::directory_iterator{fs::current_path()}, [](const auto& entry) {
            if (fs::is_directory(entry))
                std::cout << entry << "\n";
        });
    }

    if (vm.count("instance")) {
        std::string instanceName = vm["instance"].as<std::string>();
        fs::path instancePath(fs::current_path().append("instances").append(instanceName));
        if (!fs::exists(instancePath)) {
            std::cout << "creating directory\n";
            fs::create_directories(instancePath);
        }
        if (!fs::is_directory(instancePath)) {
            std::cout << "instance: " << instanceName << " exists as a file, please remove \n";
        } else {
            std::cout << "launching instance: " << instanceName << "\n";
            pr::child factorio("./bin/x64/factorio.exe", "--mod-directory", instancePath.c_str());

            factorio.wait();

            std::cout << "Instance: " << instanceName << " has terminated\n";
        }
    }
}
