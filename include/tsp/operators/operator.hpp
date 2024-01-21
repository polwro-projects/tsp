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
protected:
	using Path = tsp::algorithm::Algorithm::Solution::Path;
	using PathSizeType = Path::size_type;
	using PathIndexType = Path::size_type;

public:
	/**
	 * @brief Construct a new Algorithm object
	 * 
	 * @param path_size - the size of a path to work with
	 */
	explicit Operator(PathSizeType path_size);

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
	const PathSizeType kPathSize;

	mutable std::mt19937 generator_;
	mutable std::uniform_int_distribution<std::mt19937::result_type> distribution_;
};
} // namespace tsp::operators
