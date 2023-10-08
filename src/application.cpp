#include "application.hpp"

#include <chrono>

#include "io/file/tsp/parser.hpp"

Application::Application(const std::string& config_file) {
	// Read the parameters
	io::Reader reader(config_file);
	reader.Process();

	io::file::ini::Parser parser{reader.Get()};
	parser.Process();
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
	math::Matrix<uint32_t> positions;

	for(const auto& section : parameters_) {
		// Skip the output section as it was checked already
		if(section.name == "output") {
			continue;
		}

		// Save the name of the section to the output
		output_file_ << section.name << std::endl;

		io::Reader reader(section.properties.at("filename"));
		reader.Process();

		io::file::tsp::Parser parser{reader.Get()};
		parser.Process();
		positions = parser.Get();

		for(uint32_t index{1}; index <= std::stoi(section.properties.at("count")); ++index) {
			const auto start_point = std::chrono::system_clock::now();

			if(section.properties.find("start") != section.properties.end()) {
				Solve(positions, std::stoi(section.properties.at("start")));
			} else {
				Solve(positions);
			}

			const auto end_point = std::chrono::system_clock::now();

			// Store the duration of the operation
			output_file_ << std::chrono::duration_cast<std::chrono::microseconds>(end_point -
																				  start_point)
								.count()
						 << std::endl;
		}

		// Visually separate the sections
		output_file_ << std::endl;
	}
}

TSP::PositionList Application::Solve(const math::Matrix<uint32_t>& matrix, int32_t start_position) {
	TSP tsp{matrix};
	return tsp.Solve(start_position);
}