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

#include "io/file/tsp/parser.hpp"
#include "tsp/algorithm/inaccurate/sa/algorithm.hpp"
#include "tsp/algorithm/inaccurate/sa/linear.hpp"

namespace app {
/**
 * @brief This class represents the application class interface
 * 
 */
class IApplication {
protected:
	using DistanceMatrix = io::file::tsp::Parser::DistanceMatrix;

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
	std::chrono::seconds timeout_{};
	tsp::algorithm::inaccurate::sa::TemperatureType temperature_;
	tsp::algorithm::inaccurate::sa::EpochType epoch_size_;
	tsp::algorithm::inaccurate::sa::LinearCoefficientType linear_coefficient_;
};
} // namespace app