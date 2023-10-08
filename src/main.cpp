#include <string>

#include "application.hpp"

int main(int argc, char** argv) {
	std::string config_file{  "config.ini" };
	Application app{ config_file };
	app.Start();

	return 0;
}