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
#pragma once

#include <fstream>
#include <memory>
#include <string>

#include "app/iapplication.hpp"
#include "io/file/configuration/ini/parser.hpp"
#include "tsp/algorithm/algorithm.hpp"

namespace app {
/**
 * @brief This class represents the application and is used to pass data from parsers to the algorithms and print the output
 * 
 */
class PreconfiguredApplication : public IApplication {
	using DistanceMatrix = IApplication::DistanceMatrix;

public:
	/**
	 * @brief Construct a new PreconfiguredApplication object
	 * 
	 * @param config_file - the path to the configuration file
	 */
	PreconfiguredApplication(const std::string& config_file);

	/**
	 * @brief Destroy the PreconfiguredApplication object
	 * 
	 */
	virtual ~PreconfiguredApplication();

public:
	/**
	 * @brief Start the application execution
	 * 
	 */
	void Start() override;

protected:
	/**
	 * @brief Output the test results 
	 * 
	 * @param value - the test results
	 */
	void OutputResults(const TestResult& value) override;

	/**
	 * @brief Create an algorithm based on the input
	 * 
	 * @param value - the name of the algorithm
	 * @param matrix - the distance matrix 
	 * @return std::unique_ptr<tsp::algorithm::Algorithm> 
	 */
	std::unique_ptr<tsp::algorithm::Algorithm> CreateAlgorithm(const std::string& value,
															   const DistanceMatrix& matrix) const;

protected:
	io::file::configuration::ini::Parser::Parameters parameters_;
	std::ofstream output_file_;
};
} // namespace app