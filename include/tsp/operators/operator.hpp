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

#include <random>

#include "tsp/algorithm/algorithm.hpp"

namespace tsp::operators {
/**
 * @brief This is a base class for all the operators (f.e. crossover or mutation)
 * 
 */
class Operator {
public:
	using Solution = tsp::algorithm::Algorithm::Solution;
	using PopulationType = std::vector<Solution>;
	using PopulationSizeType = uint32_t;

protected:
	using GeneratorType = std::mt19937;
	using RandomValueType = GeneratorType::result_type;
	using DistributionType = std::uniform_int_distribution<RandomValueType>;

public:
	/**
	 * @brief Construct a new Algorithm object
	 * 
	 * @param max - the maximum possible random value
	 */
	explicit Operator(RandomValueType max);

	/**
	 * @brief Deleted copy constructor
	 * 
	 */
	Operator(const Operator&) = delete;

	/**
	 * @brief Destroy the Operator object
	 * 
	 */
	virtual ~Operator() = default;

protected:
	mutable GeneratorType generator_;
	mutable DistributionType distribution_;
};
} // namespace tsp::operators
