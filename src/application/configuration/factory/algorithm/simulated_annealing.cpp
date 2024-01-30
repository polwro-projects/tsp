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

#include "application/configuration/factory/algorithm/simulated_annealing.hpp"

#include <algorithm>

#include "tsp/neighborhood/random.hpp"

namespace application::configuration::factory::algorithm {

std::unique_ptr<tsp::algorithm::Algorithm>
SimulatedAnnealing ::Create(const DistanceMatrix& matrix,
							const ConfigurationParameters& parameters) const {
	const auto temperature = GetTemperature(parameters);
	const auto epoch_size = GetEpochSize(parameters);
	const auto linear_coefficient = GetLinearCoefficient(parameters);
	return std::make_unique<tsp::algorithm::inaccurate::sa::Linear<tsp::neighborhood::Random>>(
		matrix, temperature, epoch_size, linear_coefficient);
}

SimulatedAnnealing::EpochSizeType
SimulatedAnnealing::GetEpochSize(const ConfigurationParameters& parameters) const {
	// FIXME : the key as a literal repeated twice
	// FIXME : std::stoi doesn't belong here where aliases are used
	// FIXME : no exception handling

	const auto iterator = std::find_if(parameters.begin(), parameters.end(), [](auto section) {
		return section.properties.contains("epoch_size");
	});

	return iterator != parameters.end() ? std::stoi(iterator->properties.at("epoch_size")) : 0;
}

SimulatedAnnealing::TemperatureType
SimulatedAnnealing::GetTemperature(const ConfigurationParameters& parameters) const {
	// FIXME : the key as a literal repeated twice
	// FIXME : std::stod doesn't belong here where aliases are used
	// FIXME : no exception handling

	const auto iterator = std::find_if(parameters.begin(), parameters.end(), [](auto section) {
		return section.properties.contains("temperature");
	});

	return iterator != parameters.end() ? std::stod(iterator->properties.at("temperature")) : 0.0;
}

SimulatedAnnealing::LinearCoefficientType
SimulatedAnnealing::GetLinearCoefficient(const ConfigurationParameters& parameters) const {
	// FIXME : the key as a literal repeated twice
	// FIXME : std::stof doesn't belong here where aliases are used
	// FIXME : no exception handling

	const auto iterator = std::find_if(parameters.begin(), parameters.end(), [](auto section) {
		return section.properties.contains("coefficient");
	});

	return iterator != parameters.end() ? std::stof(iterator->properties.at("coefficient")) : 0.0;
}
} // namespace application::configuration::factory::algorithm