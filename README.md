# Simple Config System

A lightweight C++ 20 configuration system for managing settings.

## Usage

1. **Include the Files**: Add `config.hpp` and `config.cpp` to your project.

2. **Set Default Values**: In `config.cpp`, initialize default values for your settings using the `config::init()` function.

    ```cpp
    void config::init() {
        // Add default values here
        config::set<bool>("test_bool", false);
        config::set<float>("test_float", 1.f);
    }
    ```

3. **Access Settings**: Use `config::get<type>(const char*)` to retrieve the value of a setting and `config::set<type>(const char*, type value)` to modify it.

    ```cpp
    // Example: Getting the value of a setting
    bool boolValue = *config::get<bool>("test_bool");
    float floatValue = *config::get<float>("test_float");
    ```

4. **Save and Load Configurations**: Use `config::save(std::string)` and `config::load(std::string)` to save and load configurations respectively.

    ```cpp
    // Example: Saving and loading configs
    config::save("config_name.cfg");
    config::load("config_name.cfg");
    ```

## Example

```cpp
#include <iostream>
#include "config.hpp"

int main() {
    // Initialize the configuration system
    config::init();

    // Get the path to the config folder
    std::cout << "Config Folder Path: " << config::get_config_folder() << std::endl;

    // List all config files in the config folder
    std::cout << "Config Files:" << std::endl;
    for (const auto& config_name : config::config_names)
        std::cout << "- " << config_name << std::endl;

    // Example: Accessing setting values
    std::cout << "Test Bool Value: " << (*config::get<bool>("test_bool") ? "true" : "false") << std::endl;
    std::cout << "Test Float Value: " << *config::get<float>("test_float") << std::endl;

    return 0;
}
