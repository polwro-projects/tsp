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

#include "app/preconfigured_application.hpp"

#include <chrono>

#include "io/reader.hpp"
#include "math/matrix.hpp"
#include "tsp/algorithm/accurate/bb/dfs.hpp"
#include "tsp/algorithm/accurate/bf.hpp"
#include "tsp/neighborhood/random.hpp"

namespace app {
PreconfiguredApplication::PreconfiguredApplication(const std::string& config_file) {
	// Read the parameters
	parameters_ = GetConfigurationParameters(config_file);

	// Open the output file
	output_file_.open(GetOutputFile());

	// Get the timeout
	timeout_ = GetTimeout();
}

PreconfiguredApplication::~PreconfiguredApplication() {
	output_file_.close();
}

void PreconfiguredApplication::Start() {
	for(const auto& section : parameters_) {
		// Skip the output section as it was checked already
		if(section.name == "output") {
			continue;
		}

		// Save the name of the section to the output
		output_file_ << section.name << std::endl;

		// Read the parameters if they exist
		try {
			linear_coefficient_ = std::stof(section.properties.at("linear_coefficient"));
			temperature_ = std::stof(section.properties.at("temperature"));
			epoch_size_ = std::stoi(section.properties.at("epoch_size"));
		} catch(const std::exception& e) {
			// Do nothing, maybe the algorithm is not correct or something
		}

		// Get the algorithm type
		std::string algorithm_type;
		try {
			algorithm_type = section.properties.at("algorithm");
		} catch(const std::exception& e) {
			throw std::runtime_error("No algorithm specified.");
		}

		// Create the TSP solver instance from the given matrix and find the solution
		const auto filename = section.properties.at("filename");
		const auto distances = ReadMatrix(filename);
		auto algorithm = CreateAlgorithm(algorithm_type, std::move(distances));
		for(uint32_t index{1}; index <= std::stoi(section.properties.at("count")); ++index) {
			const auto result = RunTest(algorithm.get());
			OutputResults(result);

			// Clear the internal solution
			algorithm->Clear();
		}

		// Visually separate sections
		output_file_ << std::endl;
	}
}

PreconfiguredApplication::ConfigurationParameters
PreconfiguredApplication::GetConfigurationParameters(const std::string& file) {
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

std::string PreconfiguredApplication::GetOutputFile() const {
	auto iterator = std::find_if(parameters_.cbegin(), parameters_.cend(), [](const auto& section) {
		return section.name == "output";
	});
	if(iterator == parameters_.cend() ||
	   iterator->properties.find("filename") == iterator->properties.cend()) {
		throw std::runtime_error("Output file was not specified");
	}

	return iterator->properties.at("filename");
}

PreconfiguredApplication::TimeoutType PreconfiguredApplication::GetTimeout() const {
	auto iterator = std::find_if(parameters_.cbegin(), parameters_.cend(), [](const auto& section) {
		return section.name == "output";
	});
	if(iterator == parameters_.cend() ||
	   iterator->properties.find("timeout") == iterator->properties.cend()) {
		return {};
	}

	return TimeoutType(std::stoi(iterator->properties.at("timeout")));
}

void PreconfiguredApplication::OutputResults(const TestResult& value) {
	// Store the duration of the operation
	output_file_ << value.duration.count() << ",";

	// Print the path, it's cost and if the calculation was finished}
	for(uint32_t index = 0; index < value.solution.path.size() - 2; ++index) {
		const auto position = value.solution.path.at(index);
		output_file_ << position << "->";
	}
	output_file_ << value.solution.path.back() << ", " << value.solution.cost << ", "
				 << value.is_complete << std::endl;
}

std::unique_ptr<tsp::algorithm::Algorithm>
PreconfiguredApplication::CreateAlgorithm(const std::string& value,
										  const DistanceMatrix& matrix) const {
	using namespace tsp::algorithm;

	if(value == "bf") {
		return std::make_unique<accurate::BF>(matrix);
	} else if(value == "bnb_dfs") {
		return std::make_unique<accurate::bb::DFS>(matrix);
	} else if(value == "linear_sa") {
		return std::make_unique<inaccurate::sa::Linear<tsp::neighborhood::Random>>(
			matrix, temperature_, epoch_size_, linear_coefficient_);
	}

	return {};
}
} // namespace app