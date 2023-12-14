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

namespace tsp::algorithm::inaccurate::sa {

using TemperatureType = float;
using EpochType = uint32_t;

template <class NeighborhoodAlgorithm>
class Algorithm : public tsp::algorithm::Algorithm, NeighborhoodAlgorithm {
	static_assert(std::is_class_v<NeighborhoodAlgorithm>);

public:
	/**
	 * @brief Construct a new Algorithm object
	 * 
	 * @param distances - the distance matrix to use
	 * @param temperature - the starting temperature
	 * @param epoch_size - the size of the algorithm's epoch
	 */
	Algorithm(DistanceMatrix distances, TemperatureType temperature, EpochType epoch_size)
		: tsp::algorithm::Algorithm{distances}
		, NeighborhoodAlgorithm{static_cast<uint32_t>(distances.Columns())}
		, kMaxTemperature{temperature}
		, kEpochSize{epoch_size}
		, temperature_{temperature} {

		// Set up the random integer generator
		std::random_device device;
		solution_acceptor_generator_ = std::mt19937{device()};
	}

	/**
	 * @brief Solve the problem
	 * 
	 */
	bool Solve() override {
		// Unset the stop flag
		is_stopped_ = false;

		// Generate the starting solution
		current_solution_ = GeneratDefaultSolution();

		while(temperature_ > 0.1) {
			for(uint32_t iteration = 0; iteration < kEpochSize; ++iteration) {
				// Check if the flag to stop the app was risen
				if(is_stopped_) {
					return false;
				}

				// Create a neighbor and check if it can be accepted
				const auto neighbor = NeighborhoodAlgorithm::GetNeighbor(current_solution_.path);
				const Solution solution = {neighbor, CalculateCost(neighbor)};
				if(IsAccepted(solution)) {
					// Update the current solution if the neighbor is better
					current_solution_ = solution;

					// If this new solution is even better than the best solution so far, update the best one
					if(current_solution_.cost < solution_.cost) {
						solution_ = current_solution_;
					}
				}
			}

			// Change the temperature
			temperature_ = Cool(temperature_);
		}

		// Set the stop flag if the timeout was not achieved
		is_stopped_ = true;

		return true;
	}

	/**
	 * @brief Get the temperature
	 * 
	 * @return TemperatureType - the current temperature
	 */
	TemperatureType GetTemperature() const {
		return temperature_;
	}

protected:
	/**
	 * @brief Generate the starting solution
	 * 
	 * @return Solution - the starting solution
	 */
	Solution GeneratDefaultSolution() const {
		Solution solution;
		for(uint32_t index = 0; index < distances_.Columns(); ++index) {
			solution.path.push_back(index);
		}
		solution.path.push_back(0);

		// Calculate the cost of the solution and store it inside
		solution.cost = CalculateCost(solution.path);

		return solution;
	}

	/**
	 * @brief Decrease the existing temperature
	 * 
	 * @param temperature the temperature to change
	 * @return TemperatureType - the new value of the temperature which can be obtained by a certain algorithm
	 */
	virtual TemperatureType Cool(TemperatureType temperature) const = 0;

	/**
     * @brief Check if the soltuion can be accepted
     * 
     * @param path - the path to check
     * @return true if the path can be accepted
     * @return false otherwise
     */
	bool IsAccepted(const Solution& solution) const {
		const int32_t cost_difference = solution.cost - current_solution_.cost;
		if(cost_difference < 0) {
			return true;
		}

		// Check if worse solution still can be accepted
		const float probability =
			solution_acceptor_distribution_(solution_acceptor_generator_) / kAcceptorFactor;
		return probability < std::exp(-cost_difference / temperature_);
	}

	/**
	 * @brief Clear the internal state of the algorithm
	 * 
	 */
	void Clear() override {
		// Update the starting temperature
		temperature_ = kMaxTemperature;

		// Clear the currrent solution
		current_solution_.Clear();

		tsp::algorithm::Algorithm::Clear();
	}

protected:
	static constexpr uint32_t kAcceptorFactor{10};
	const TemperatureType kMaxTemperature;
	const EpochType kEpochSize;

	TemperatureType temperature_;
	Solution current_solution_;

	mutable std::mt19937 solution_acceptor_generator_;
	mutable std::uniform_int_distribution<std::mt19937::result_type>
		solution_acceptor_distribution_{0, kAcceptorFactor};
};
} // namespace tsp::algorithm::inaccurate::sa