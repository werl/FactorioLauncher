//
// Created by peter on 2023-11-01.
//

#ifndef FACTORIO_LAUNCHER_INSTANCE_H
#define FACTORIO_LAUNCHER_INSTANCE_H
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include "nlohmann/detail/macro_scope.hpp"

namespace werl::factorio_launcher {

    using json = nlohmann::json;

    class Instance {
        std::string factorioPath;
        std::string modsPath;
        std::string configPath;
        bool verbose;
        std::string executablePath;
        std::string instrumentMod;
        bool fullscreen;
        std::string widowSize;
        bool lowVRAM;
        bool isMultiplayer;
        std::string server;
        std::string password;

    public:
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(Instance, factorioPath, modsPath, verbose, executablePath, instrumentMod, fullscreen, widowSize, lowVRAM, isMultiplayer, server, password)
    };

} // werl::factorio_launcher

#endif //FACTORIO_LAUNCHER_INSTANCE_H
