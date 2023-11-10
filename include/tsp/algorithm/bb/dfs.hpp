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

#include <stack>

#include "math/matrix.hpp"
#include "tsp/algorithm/algorithm.hpp"

namespace tsp::algorithm::bb {
class DFS : public Algorithm {
public:
	using DistanceMatrix = Algorithm::DistanceMatrix;

	/**
	 * @brief This struct represents a solution node in the tree of solutions
	 * 
	 */
	struct Node {
		uint32_t vertex;
		uint32_t level;
	};

public:
	/**
	 * @brief Construct a new DFS object
	 * 
	 * @param distances - the distance matrix to use
	 */
	DFS(DistanceMatrix distances);

public:
	/**
	 * @brief Solve the problem
	 * 
	 */
	void Solve() override;

	/**
	 * @brief Clear the internal state of the algorithm
	 * 
	 */
	void Clear() override;

protected:
	/**
	 * @brief Undo the last move in the solution
	 * 
	 * @param solution - the solution to modify
	 * @param level - the level of the solution
	 */
	void Backtrack(Solution& solution, uint32_t level);

	/**
	 * @brief Check if the solution can be accepted
	 * 
	 * @param solution - the solution to check
	 * @return true - if the solution can be accepted as a new best solution
	 * @return false otherwise
	 */
	bool AcceptSolution(Solution& solution);

	/**
	 * @brief Check if the solution is complete
	 * 
	 * @param solution - the solution to check
	 * @return true - if the solution is complete
	 * @return false otherwise
	 */
	bool IsSolutionComplete(Solution& solution) const noexcept;

private:
	std::stack<Node> stack_;
	std::vector<bool> is_visited_;
};
} // namespace tsp::algorithm::bb