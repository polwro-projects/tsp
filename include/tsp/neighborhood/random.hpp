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

#include "tsp/neighborhood/algorithm.hpp"

namespace tsp::neighborhood {
class Random : public Algorithm {
public:
	/**
      * @brief Construct a new Random object
      * 
      * @param size - the size of the path to use to generate random numbers
      */
	explicit Random(uint32_t size);

public:
	/**
     * @brief Get the neighbor for the existing path
     * 
     * @param path the path to find a soltuion in the neighborhood for
     * @return Path the path that is in a neighborhood to the existing one
     */
	Path GetNeighbor(const Path& path) noexcept override;

protected:
	std::mt19937 neighbor_generator_;
	std::uniform_int_distribution<std::mt19937::result_type> neighbor_distribution_;
};
} // namespace tsp::neighborhood