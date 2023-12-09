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

#include "tsp/algorithm/accurate/bb/dfs.hpp"

#include <algorithm>
#include <stdexcept>

namespace tsp::algorithm::accurate::bb {
DFS::DFS(DistanceMatrix distances)
	: Algorithm{distances}
	, is_visited_{std::vector<bool>(distances_.Rows())} {
	// Create the starting stack of vertexes to visit
	for(VertexType vertex = 1; vertex < distances_.Rows(); ++vertex) {
		stack_.push({vertex, 1, 0});
	}
}

bool DFS::Solve() {
	// Update the flag that indicates the app is running
	is_stopped_ = false;

	Solution partial_solution{{0}, 0};
	while(!stack_.empty()) {
		// Check if the flag to stop the app was risen
		if(is_stopped_) {
			return false;
		}

		const auto [vertex, level, bound] = stack_.top();
		stack_.pop();

		// Don't do anything if the bound is greater than the best solution so far
		if(bound >= solution_.cost) {
			continue;
		}

		// Undo some steps to explore the tree further (DFS)
		const auto steps = partial_solution.path.size() - level;
		if(steps != 0) {
			Backtrack(partial_solution, steps);
		}

		// Visit the vertex and add it to the current path
		VisitVertex(partial_solution, vertex);

		// Checking all the children of the current vertex
		const auto size = distances_.Rows();
		for(VertexType child = 1; child < size; ++child) {
			// Skip visited children
			if(is_visited_.at(child)) {
				continue;
			}

			const auto child_bound = CalculateLowerBound(partial_solution, child);
			stack_.push({child, level + 1, child_bound});
		}

		// If the path is finished
		if(IsSolutionComplete(partial_solution)) {
			AcceptSolution(partial_solution);
		}
	}

	is_stopped_ = true;
	return true;
}

void DFS::Clear() {
	Algorithm::Clear();

	// Clear the list of visited vertexes
	is_visited_ = std::vector<bool>(distances_.Rows());

	// Re-create the starting stack of the vertexes to visit
	for(uint32_t vertex = 1; vertex < distances_.Rows(); ++vertex) {
		stack_.push({vertex, 1, 0});
	}
}

void DFS::Backtrack(Solution& solution, uint32_t level) {
	for(; level > 0; --level) {
		const auto path_end = solution.path.back();

		// Remove the last vertex in the path
		solution.path.pop_back();
		solution.cost -= distances_(solution.path.back(), path_end);

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

uint32_t DFS::CalculateLowerBound(const Solution& solution, VertexType vertex) const noexcept {
	// Calculate the partial bound by using information about the given vertex
	uint32_t bound = solution.cost + distances_(solution.path.back(), vertex);
	bound += GetSmallestCost(vertex, is_visited_);

	// Visit every neighbor that is not visited (yet)
	for(VertexType index = 1; index < distances_.Rows(); ++index) {
		// Skip already visited vertexes
		if(is_visited_.at(index) || index == vertex) {
			continue;
		}

		// Cut the computations if the lower bound is already too big
		if(bound >= solution_.cost) {
			bound = std::numeric_limits<uint32_t>::max();
			break;
		}

		bound += GetSmallestCost(index, is_visited_);
	}

	return bound;
}

uint32_t DFS::GetSmallestCost(VertexType vertex, const std::vector<bool>& visited) const noexcept {
	auto smallest_cost{std::numeric_limits<uint32_t>::max()};
	for(VertexType neighbor = 0; neighbor < distances_.Rows(); ++neighbor) {
		// Skip already visited neighbors
		if(neighbor == vertex || visited.at(neighbor)) {
			continue;
		}

		// Get the cost of the path and update the smallest one if necessary
		const auto cost = distances_(vertex, neighbor);
		if(cost < smallest_cost) {
			smallest_cost = cost;
		}
	}

	return smallest_cost;
}

void DFS::VisitVertex(Solution& solution, VertexType vertex) {
	// Add the vertex to the given solution
	solution.cost += distances_(solution.path.back(), vertex);
	solution.path.push_back(vertex);

	// "Visit" the vertex
	is_visited_.at(vertex) = true;
}
} // namespace tsp::algorithm::accurate::bb