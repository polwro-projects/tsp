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

#include "tsp/algorithm/bb/dfs.hpp"

#include <algorithm>
#include <stdexcept>

namespace tsp::algorithm::bb {
DFS::DFS(DistanceMatrix distances)
	: Algorithm{distances}
	, is_visited_{std::vector<bool>(distances_.Rows())} {
	// Create the starting stack of vertexes to visit
	for(uint32_t vertex = 1; vertex < distances_.Rows(); ++vertex) {
		stack_.push({vertex, 1});
	}
}

void DFS::Solve() {
	Solution partial_solution{{0}, 0};
	while(!stack_.empty()) {
		const auto [vertex, level] = stack_.top();
		stack_.pop();

		// Going up the hierarchy to get to the next path
		Backtrack(partial_solution, partial_solution.path.size() - level);

		const auto cost = partial_solution.cost + distances_(partial_solution.path.back(), vertex);
		if(cost < solution_.cost) {
			// Visit the vertex and add it to the current path
			partial_solution.path.push_back(vertex);
			partial_solution.cost = cost;
			is_visited_.at(vertex) = true;

			// Checking all the children of the current vertex
			const auto size = distances_.Rows();
			for(uint32_t child = 1; child < size; ++child) {
				if(child != vertex && !is_visited_.at(child)) {
					stack_.push({child, level + 1});
				}
			}
		}

		// If the path is finished
		if(IsSolutionComplete(partial_solution)) {
			AcceptSolution(partial_solution);
		}
	}
}

void DFS::Clear() {
	Algorithm::Clear();

	// Clear the list of visited vertexes
	is_visited_ = std::vector<bool>(distances_.Rows());

	// Re-create the starting stack of the vertexes to visit
	for(uint32_t vertex = 1; vertex < distances_.Rows(); ++vertex) {
		stack_.push({vertex, 1});
	}
}

void DFS::Backtrack(Solution& solution, uint32_t level) {
	for(; level > 0; --level) {
		const auto path_end = solution.path.back();

		// Remove the last vertex in the path
		solution.cost -= distances_(solution.path.at(solution.path.size() - 2), path_end);
		solution.path.pop_back();

		// Un-visit the last vertex of the current path
		is_visited_.at(path_end) = false;
	}
}

bool DFS::AcceptSolution(Solution& solution) {
	const auto cost = solution.cost + distances_(solution.path.back(), 0);
	if(cost < solution_.cost) {
		solution_ = solution;

		// Add the last element of the path to create a loop
		solution_.cost = cost;
		solution_.path.push_back(0);

		return true;
	}

	return false;
}

inline bool DFS::IsSolutionComplete(Solution& solution) const noexcept {
	return solution.path.size() == distances_.Rows();
}
} // namespace tsp::algorithm::bb