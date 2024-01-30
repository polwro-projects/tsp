/**
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *  http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#include "application/configuration/application.hpp"

#include <chrono>

#include "application/configuration/factory/algorithm/branch_and_bound.hpp"
#include "application/configuration/factory/algorithm/bruteforce.hpp"
#include "application/configuration/factory/algorithm/genetic.hpp"
#include "application/configuration/factory/algorithm/simulated_annealing.hpp"
#include "io/reader.hpp"
#include "math/matrix.hpp"

namespace application::configuration {
Application::Application(const std::string& config_file) {
	// Read the parameters
	parameters_ = GetConfigurationParameters(config_file);

	// Open the output file
	output_file_.open(GetOutputFile());

	// Get the timeout
	timeout_ = GetTimeout();
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

		// Get the algorithm type
		std::string algorithm_type;
		try {
			algorithm_type = section.properties.at("algorithm");
		} catch(const std::exception& e) {
			throw std::runtime_error("No algorithm specified.");
		}

		// Create the algorithm factory
		const auto factory = CreateFactory(algorithm_type);
		if(!factory) {
			throw std::runtime_error(
				"The algorithm is not correct. Please, refer to the documentation.");
		}

		// Create the TSP solver instance from the given matrix and find the solution
		const auto filename = section.properties.at("filename");
		const auto distances = ReadMatrix(filename);
		auto algorithm = factory->Create(std::move(distances), parameters_);
		for(uint32_t index{1}; index <= std::stoi(section.properties.at("count")); ++index) {
			const auto result = RunAlgorithm(algorithm.get());
			OutputResults(result);

			// Clear the internal solution
			algorithm->Clear();
		}

		// Visually separate sections
		output_file_ << std::endl;
	}
}

Application::ConfigurationParameters
Application::GetConfigurationParameters(const std::string& file) {
	io::Reader reader(file);
	if(!reader.Process()) {
		throw std::runtime_error("Reading the INI file failed");
	}

	io::file::configuration::ini::Parser parser{reader.Get()};
	if(!parser.Process()) {
		throw std::runtime_error("Parsing the INI file failed");
	}

	return parser.Get();
}

std::string Application::GetOutputFile() const {
	auto iterator = std::find_if(parameters_.cbegin(), parameters_.cend(), [](const auto& section) {
		return section.name == "output";
	});
	if(iterator == parameters_.cend() ||
	   iterator->properties.find("filename") == iterator->properties.cend()) {
		throw std::runtime_error("Output file was not specified");
	}

	return iterator->properties.at("filename");
}

Application::TimeoutType Application::GetTimeout() const {
	auto iterator = std::find_if(parameters_.cbegin(), parameters_.cend(), [](const auto& section) {
		return section.name == "output";
	});
	if(iterator == parameters_.cend() ||
	   iterator->properties.find("timeout") == iterator->properties.cend()) {
		return {};
	}

	return TimeoutType(std::stoi(iterator->properties.at("timeout")));
}

void Application::OutputResults(const TestResult& value) {
	// Store the duration of the operation
	output_file_ << value.duration.count() << ",";

	// Print the path, it's cost and if the calculation was finished}
	for(uint32_t index = 0; index < value.solution.path.size() - 1; ++index) {
		const auto position = value.solution.path.at(index);
		output_file_ << position << "->";
	}
	output_file_ << value.solution.path.back() << ", " << value.solution.cost << ", "
				 << value.is_complete << std::endl;
}

std::unique_ptr<Application::AlgorithmFactory>
Application::CreateFactory(const std::string& value) {
	using namespace application::configuration::factory::algorithm;

	if(value == "bf") {
		return std::make_unique<BruteForce>();
	} else if(value == "bnb") {
		return std::make_unique<BranchAndBound>();
	} else if(value == "sa") {
		return std::make_unique<SimulatedAnnealing>();
	} else if(value == "ga") {
		return std::make_unique<Genetic>();
	}

	return {};
}

} // namespace application::configuration