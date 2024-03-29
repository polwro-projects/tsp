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

#include "application/configuration/factory/algorithm/factory.hpp"
#include "application/iapplication.hpp"
#include "io/file/configuration/ini/parser.hpp"

namespace application::configuration {

namespace algorithm {
class Factory;
} // namespace algorithm

/**
 * @brief This class represents the application and is used to pass data from parsers to the algorithms and print the output
 * 
 */
class Application : public IApplication {
	using AlgorithmFactory = application::configuration::factory::algorithm::Factory;
	using ConfigurationParameters = io::file::configuration::ini::Parser::Parameters;

public:
	/**
	 * @brief Construct a new Application object
	 * 
	 * @param config_file - the path to the configuration file
	 */
	Application(const std::string& config_file);

	/**
	 * @brief Destroy the Application object
	 * 
	 */
	virtual ~Application();

public:
	/**
	 * @brief Start the application execution
	 * 
	 */
	void Start() override;

protected:
	/**
	 * @brief Get the configuration from the given file
	 * 
	 * @param file - the configuration file 
	 * @return ConfigurationParameters - the parameters
	 */
	static ConfigurationParameters GetConfigurationParameters(const std::string& file);

	/**
	 * @brief Get the output file
	 * 
	 * @return std::string - the file to store output
	 */
	std::string GetOutputFile() const;

	/**
	 * @brief Get the specified timeout
	 * 
	 * @return TimeoutType the timeout of the algorithm
	 */
	TimeoutType GetTimeout() const;

	/**
	 * @brief Output the test results 
	 * 
	 * @param value - the test results
	 */
	void OutputResults(const TestResult& value) override;

	/**
	 * @brief Create the factory based on the input
	 * 
	 * @param value - the name of the algorithm
	 * @return std::unique_ptr<tsp::algorithm::Algorithm> 
	 */
	static std::unique_ptr<AlgorithmFactory> CreateFactory(const std::string& value);

protected:
	ConfigurationParameters parameters_;
	std::ofstream output_file_;
};
} // namespace application::configuration