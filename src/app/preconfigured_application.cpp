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
#include "tsp/algorithm/bb/dfs.hpp"
#include "tsp/algorithm/bf.hpp"

namespace app {
PreconfiguredApplication::PreconfiguredApplication(const std::string& config_file) {
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

		// Read the TSP file
		io::Reader reader(section.properties.at("filename"));
		if(!reader.Process()) {
			throw std::runtime_error("Reading the TSP file failed");
		}

		// Read the matrix from the file
		io::file::tsp::Parser parser{reader.Get()};
		if(!parser.Process()) {
			throw std::runtime_error("Parsing the TSP file failed");
		}

		// Get the algorithm type
		std::string algorithm_type;
		try {
			algorithm_type = section.properties.at("algorithm");
		} catch(const std::exception& e) {
			throw std::runtime_error("No algorithm specified.");
		}

		// Create the TSP solver instance from the given matrix and find the solution
		auto tsp = CreateAlgorithm(algorithm_type, parser.Get());
		for(uint32_t index{1}; index <= std::stoi(section.properties.at("count")); ++index) {
			RunTest(tsp.get());

			// Clear the internal solution
			tsp->Clear();
		}

		// Visually separate sections
		output_file_ << std::endl;
	}
}

void PreconfiguredApplication::RunTest(tsp::algorithm::Algorithm* algorithm) {
	// Calculate the result and get the time of function's execution
	const auto start_point = std::chrono::system_clock::now();
	algorithm->Solve();
	const auto end_point = std::chrono::system_clock::now();

	// Store the duration of the operation
	const auto duration =
		std::chrono::duration_cast<std::chrono::microseconds>(end_point - start_point);
	output_file_ << duration.count() << ",";

	// Print the solution to the output file
	const auto solution = algorithm->GetSolution();
	for(const auto position : solution.path) {
		output_file_ << position << " ";
	}
	output_file_ << ", " << solution.cost << std::endl;
}

std::unique_ptr<tsp::algorithm::Algorithm>
PreconfiguredApplication::CreateAlgorithm(const std::string& value, const DistanceMatrix& matrix) {
	if(value == "bf") {
		return std::make_unique<tsp::algorithm::BF>(matrix);
	} else if(value == "bnb_dfs") {
		return std::make_unique<tsp::algorithm::bb::DFS>(matrix);
	}

	return {};
}
} // namespace app