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

#include "application/configuration/factory/algorithm/factory.hpp"
#include "tsp/algorithm/inaccurate/sa/linear.hpp"

namespace application::configuration::factory::algorithm {
/**
 * @brief This class is an implementation of the factory, used to provide 
 * 		  an instance to the simulated annealing algorithm factory
 * 
 */
class SimulatedAnnealing : public Factory {
	using EpochSizeType = tsp::algorithm::inaccurate::sa::EpochType;
	using LinearCoefficientType = tsp::algorithm::inaccurate::sa::LinearCoefficientType;
	using TemperatureType = tsp::algorithm::inaccurate::sa::TemperatureType;

public:
	/**
	 * @brief Create an algorithm based on the input
	 * 
	 * @param matrix - the distance matrix 
	 * @return std::unique_ptr<tsp::algorithm::Algorithm> - a pointer to the algorithm instance or nullptr
	 */
	std::unique_ptr<tsp::algorithm::Algorithm>
	Create(const DistanceMatrix& matrix, const ConfigurationParameters& parameters) const override;

protected:
	/**
	 * @brief Get the epoch size
	 * 
	 * @param parameters - the parameters where to look for the value
	 * @return EpochSizeType - the size of the epoch
	 */
	EpochSizeType GetEpochSize(const ConfigurationParameters& parameters) const;

	/**
	 * @brief Get the temperature
	 * 
	 * @param parameters - the parameters where to look for the value
	 * @return TemperatureType - the temperature to use
	 */
	TemperatureType GetTemperature(const ConfigurationParameters& parameters) const;

	/**
	 * @brief Get the linear coefficient
	 * 
	 * @param parameters - the parameters where to look for the value
	 * @return LinearCoefficientType - the linear coefficient to use for the BnB algorithm
	 */
	LinearCoefficientType GetLinearCoefficient(const ConfigurationParameters& parameters) const;
};

} // namespace application::configuration::factory::algorithm