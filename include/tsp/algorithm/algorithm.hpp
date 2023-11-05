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

#include <limits>

#include "io/file/tsp/parser.hpp"
#include "math/matrix.hpp"

namespace tsp::algorithm {
/**
 * @brief This class is an abactraction for other TSP algorithms
 * 
 */
class Algorithm {
public:
	using DistanceMatrix = io::file::tsp::Parser::DistanceMatrix;

public:
	/**
	 * @brief The struct holds the results of the calculation
	 * 
	 */
	struct Solution {
		using Path = std::vector<uint32_t>;

		Path path;
		uint32_t cost{std::numeric_limits<uint32_t>::max()};

		/**
		 * @brief Clear the existing solution
		 * 
		 */
		void Clear();
	};

public:
	/**
	 * @brief Construct a new Algorithm object
	 * 
	 * @param distances - the distance matrix to use
	 */
	explicit Algorithm(DistanceMatrix distances);

public:
	/**
	 * @brief Solve the problem
	 * 
	 * @return Solution - the solution to the problem
	 */
	virtual void Solve() = 0;

	/**
	 * @brief Get the solution, calculated in the previous step
	 * 
	 * @return Solution - the solution to the problem
	 */
	Solution GetSolution() const noexcept;

	/**
	 * @brief Clear the internal state of the algorithm
	 * 
	 */
	virtual void Clear();

protected:
	DistanceMatrix distances_;
	Solution solution_;
};
} // namespace tsp::algorithm