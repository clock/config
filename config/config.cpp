#include "config.hpp"
#include <string>
#include <any>
#include <fstream>
#include <vector>
#include <filesystem>
#include <windows.h>
#include <shlobj.h>

std::string config::get_config_folder() {
    PWSTR documents_path;
    if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_Documents, 0, NULL, &documents_path))) {
        std::wstring wide_path(documents_path);
        CoTaskMemFree(documents_path);

        return std::string(wide_path.begin(), wide_path.end()) + "\\" + config::config_folder_name + "\\";
    }
    return "";
}

void config::init() {
    config::config_folder_path = config::get_config_folder();
    CreateDirectoryA(config_folder_path.c_str(), NULL);
    config::get_config_names();

    //  adding default values
    config::set<bool>("test_bool", false);
    config::set<float>("test_float", 1.f);
}

void config::get_config_names() {
    for (const auto& entry : std::filesystem::directory_iterator(config::config_folder_path)) {
        if (entry.is_regular_file() && entry.path().extension() == config::config_ext)
            config::config_names.push_back(entry.path().string());
    }
}

bool config::save(std::string name) {
    std::ofstream file(config::config_folder_path + name, std::ios::binary);

    for (const auto& [key, value] : settings) {
        uint8_t keyLength = static_cast<uint8_t>(strlen(key.c_str()));
        file.write(reinterpret_cast<const char*>(&keyLength), sizeof(keyLength));
        file.write(key.c_str(), strlen(key.c_str()));
        file.write(value.data, sizeof(value));
    }

    file.close();
    return true;
}

bool config::load(std::string name) {
    std::ifstream file(config::config_folder_path + name, std::ios::binary);

    if (!file.is_open())
        return false;

    while (true) {
        uint8_t keyLength;
        if (!file.read(reinterpret_cast<char*>(&keyLength), sizeof(keyLength)))
            break;

        std::string key;
        key.resize(keyLength);

        if (!file.read(&key[0], keyLength))
            return false;

        data value;
        if (!file.read(reinterpret_cast<char*>(&value.data), sizeof(value.data)))
            return false;

        settings[key] = value;
    }

    file.close();
    return true;
}