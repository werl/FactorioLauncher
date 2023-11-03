#include <iostream>
#include <fstream>
#include <filesystem>
#include "boost/process.hpp"
#include "boost/program_options.hpp"
#include "boost/filesystem.hpp"
#include "nlohmann/json.hpp"

namespace po = boost::program_options;
namespace pr = boost::process;
using json = nlohmann::json;
namespace fs = boost::filesystem;

int main(int argc, char* argv[]) {
    po::options_description generic("General Options");
    generic.add_options()
            ("help,h", "Produce help message")
            ("version", "Print version string")
            ("settings,s", po::value<std::string>(), "Path to settings file")
            ;

    po::options_description launcher("Launcher Options");
    launcher.add_options()
            ("list,l", "List instances")
            ("instance,i", po::value<std::string>(), "Name of instance")
            ("version-factorio", "Show Factorio version information")
            ("dump-data", po::value<std::string>(), "Dumps data.raw as JSON to the script output folder and exits")
            ("dump-icon-sprites", po::value<std::string>(), "Dumps all icon sprites as png files to the script output folder and exits.")
            ;

    po::options_description instance("Instance Creation/Edit Options");
    instance.add_options()
            ("new,n", "Create a new instance")
            ("edit,e", "Edit existing instance")
            ("instance,i", po::value<std::string>(), "Name of instance")
            ("factorio,f", po::value<std::string>(), "Factorio root directory")
            ("config,c", po::value<std::string>(), "Set config file")
            ("mods,m", po::value<std::string>(), "Set mods folder")
            ("mp-connect", po::value<std::string>(), "Start Factorio and connect to address")
            ("password", po::value<std::string>(), "The password to use when using mp-connect (if any)")
            ("verbose", "Add verbose option")
            ("executable-path", po::value<std::string>(), "Override autodetected __PATH__executable. Usually not needed except on very weird systems.")
            ("instrument-mod", po::value<std::string>(), "Name of a mod to enable Instrument Mode")
            ("fullscreen", po::value<bool>(), "Start game in windowed mode (saved to configuration)")
            ("window-size", po::value<std::string>(), R"(Desired window resolution. For example "1680x1050". Or "maximized")")
            ("low-vram", "Sprites that are not put into sprite atlases won't be allocated as texture objects")
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

    //TODO get settings file
    std::string settingsString = "settings.json";

    if(vm.count("settings")) {
        if (vm["settings"].as<std::string>().empty())
            std::cout << "Settings input is empty" << "\n";
        settingsString = vm["settings"].as<std::string>();
    }

    fs::path settingsPath(settingsString);
    if (fs::is_directory(settingsPath)) {
        std::cout << "Settings path needs to be a file\n";
        return 1;
    } else if(!fs::exists(settingsPath)) {
        std::ofstream file;
        file.open(settingsPath.c_str());
        file << "{}";
        file.close();
    }
    std::ifstream f(settingsPath.c_str());
    json data = json::parse(f);

    if (vm.count("new")/* TODO check if all variables are there */) {
        std::cout << "new" << "\n";
    }
}
