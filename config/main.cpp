#include <iostream>
#include "config.hpp"

int main() {
	config::init();
	
	// getting the config folder path
	std::cout << config::get_config_folder() << std::endl;

	// looping through the config names in the config folder
	for (const auto config_name : config::config_names)
		std::cout << config_name << std::endl;

	// saving and loading the configs based on the config name
	//config::save("test.cfg");
	//config::load("test.cfg");
	
	// getting the value of a setting
	std::cout << (*config::get<bool>("test_bool") ? "true" : "false") << std::endl;
	std::cout << *config::get<float>("test_float") << std::endl;

	return 0;
}