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

#include "io/file/problem/iproblemparser.hpp"
#include "math/matrix.hpp"

namespace tsp::algorithm {
/**
 * @brief This class is an abactraction for other TSP algorithms
 * 
 */
class Algorithm {
public:
	using DistanceMatrix = io::file::problem::IProblemParser::DistanceMatrix;
	using VertexType = uint32_t;

public:
	/**
	 * @brief The struct holds the results of the calculation
	 * 
	 */
	struct Solution {
		using Path = std::vector<VertexType>;
		using SizeType = uint32_t;

		/**
		 * @brief Clear the existing solution
		 * 
		 */
		void Clear();

		Path path;
		SizeType cost{std::numeric_limits<SizeType>::max()};
	};

public:
	/**
	 * @brief Construct a new Algorithm object
	 * 
	 * @param distances - the distance matrix to use
	 */
	explicit Algorithm(DistanceMatrix distances);

	/**
	 * @brief Destroy the Algorithm object
	 * 
	 */
	virtual ~Algorithm() { }

public:
	/**
	 * @brief Solve the problem
	 * 
	 * @return Solution - the solution to the problem
	 */
	virtual bool Solve() = 0;

	/**
	 * @brief Stop the algorithm's execution
	 * 
	 */
	void Stop() noexcept;

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
	/**
	 * @brief Get the length of the given path
	 * 
	 * @param value - the path to calculate the length for
	 * @return uint32_t - the length of the path
	 */
	uint32_t CalculateCost(const Solution::Path& value) const;

protected:
	DistanceMatrix distances_;
	Solution solution_;
	bool is_stopped_{true};
};
} // namespace tsp::algorithm