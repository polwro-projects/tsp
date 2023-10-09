#include "application.hpp"

#include <chrono>

#include "io/file/tsp/parser.hpp"

Application::Application(const std::string& config_file) {
	// Read the parameters
	io::Reader reader(config_file);
	if(!reader.Process()) {
		throw std::runtime_error("Reading the INI file failed");
	}

	io::file::ini::Parser parser{reader.Get()};
	if(!parser.Process()) {
		throw std::runtime_error("Parsing the INI file failed");
	}
	parameters_ = parser.Get();

	// Open the output file
	auto iterator = std::find_if(parameters_.cbegin(), parameters_.cend(), [](const auto& section) {
		return section.name == "output";
	});
	if(iterator == parameters_.cend()) {
		throw std::runtime_error("Output file was not specified");
	}
	output_file_.open(iterator->properties.at("filename"));
}

Application::~Application() {
	output_file_.close();
}

void Application::Start() {
	for(const auto& section : parameters_) {
		// Skip the output section as it was checked already
		if(section.name == "output") {
			continue;
		}

		// Save the name of the section to the output
		output_file_ << section.name << std::endl;

		io::Reader reader(section.properties.at("filename"));
		if(!reader.Process()) {
			throw std::runtime_error("Reading the TSP file failed");
		}

		io::file::tsp::Parser parser{reader.Get()};
		if(!parser.Process()) {
			throw std::runtime_error("Parsing the TSP file failed");
		}

		TSP tsp{parser.Get()};
		for(uint32_t index{1}; index <= std::stoi(section.properties.at("count")); ++index) {
			const auto start_point = std::chrono::system_clock::now();
			const auto solution = tsp.Solve();
			const auto end_point = std::chrono::system_clock::now();

			// Store the duration of the operation
			const auto duration =
				std::chrono::duration_cast<std::chrono::microseconds>(end_point - start_point);
			output_file_ << duration.count() << ",";

			for(const auto position : solution) {
				output_file_ << position << "->";
			}
			output_file_ << solution.at(0) << std::endl;
		}

		// Visually separate the sections
		output_file_ << std::endl;
	}
}