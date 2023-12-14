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

#include <chrono>

#include "io/file/problem/iproblemparser.hpp"
#include "tsp/algorithm/inaccurate/sa/linear.hpp"

namespace app {
/**
 * @brief This class represents the application class interface
 * 
 */
class IApplication {
protected:
	using DistanceMatrix = io::file::problem::IProblemParser::DistanceMatrix;
	using EpochType = tsp::algorithm::inaccurate::sa::EpochType;
	using ExecutionDurationType = std::chrono::microseconds;
	using LinearCoefficientType = tsp::algorithm::inaccurate::sa::LinearCoefficientType;
	using TemperatureType = tsp::algorithm::inaccurate::sa::TemperatureType;
	using TimeoutType = std::chrono::seconds;

	struct TestResult {
		ExecutionDurationType duration;
		tsp::algorithm::Algorithm::Solution solution;
		bool is_complete;
	};

public:
	/**
	 * @brief Destroy the IApplication object
	 * 
	 */
	virtual ~IApplication() = default;

public:
	/**
	 * @brief Start the application execution
	 * 
	 */
	virtual void Start() = 0;

protected:
	/**
	 * @brief Read the distance matrix from the given file
	 * 
	 * @param filename - the name of the file to use
	 * @return DistanceMatrix - the distance matrix, read from the file
	 */
	static DistanceMatrix ReadMatrix(const std::string& filename);

	/**
	 * @brief Create a new parser object for the corresponding type of files
	 * 
	 * @param filename - the name of the file from where to get the extension
	 * @return std::unique_ptr<io::file::problem::IProblemParser> - the pointer to the parser instance
	 */
	static std::unique_ptr<io::file::problem::IProblemParser>
	CreateParser(const std::string& filename, const io::Reader::Data& data);

	/**
	 * @brief Output the test results 
	 * 
	 * @param value - the test results
	 */
	virtual void OutputResults(const TestResult& value) = 0;

	/**
	 * @brief Run the algorithm on the given distance matrix and print the results
	 * 
	 * @param algorithm - the algorithm to use
	 */
	TestResult RunTest(tsp::algorithm::Algorithm* algorithm) const;

protected:
	TimeoutType timeout_{};

	TemperatureType temperature_;
	EpochType epoch_size_;
	LinearCoefficientType linear_coefficient_;
};
} // namespace app