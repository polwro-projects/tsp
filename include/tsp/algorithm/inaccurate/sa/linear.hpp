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

#include "tsp/algorithm/inaccurate/sa/algorithm.hpp"

namespace tsp::algorithm::inaccurate::sa {

using LinearCoefficientType = float;

template <class NeighborhoodAlgorithm>
class Linear : public Algorithm<NeighborhoodAlgorithm> {
public:
	using DistanceMatrix = typename Algorithm<NeighborhoodAlgorithm>::DistanceMatrix;

public:
	/**
	 * @brief Construct a new Algorithm object
	 * 
	 * @param distances - the distance matrix to use
	 * @param temperature - the starting temperature
	 * @param epoch_size - the size of the algorithm's epoch
     * @param coefficient - linear coefficient used for changing the temperature
	 */
	Linear(DistanceMatrix distances,
		   TemperatureType temperature,
		   EpochType epoch_size,
		   LinearCoefficientType coefficient)
		: Algorithm<NeighborhoodAlgorithm>{distances, temperature, epoch_size}
		, coefficient_{coefficient} { }

public:
	/**
	 * @brief Decrease the existing temperature
	 * 
	 * @param temperature the temperature to change
	 * @return TemperatureType - the new value of the temperature which can be obtained by a certain algorithm
	 */
	inline TemperatureType Cool(TemperatureType temperature) const override {
		return coefficient_ * temperature;
	}

protected:
	const LinearCoefficientType coefficient_;
};
} // namespace tsp::algorithm::inaccurate::sa