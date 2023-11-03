//
// Created by peter on 2023-11-01.
//

#ifndef FACTORIO_LAUNCHER_SETTINGS_H
#define FACTORIO_LAUNCHER_SETTINGS_H

#include "Instance.h"

#include "nlohmann/json.hpp"

using json = nlohmann::json;

namespace werl::factorio_launcher {

    struct settings {

    };

    void to_json(json& j, const settings& p);

} // werl::factorio_launcher

#endif //FACTORIO_LAUNCHER_SETTINGS_H
