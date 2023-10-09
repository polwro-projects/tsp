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

#include <deque>
#include <list>

#include "io/file/tsp/parser.hpp"
#include "math/matrix.hpp"

class TSP {
public:
	using DistanceMatrix = io::file::tsp::Parser::DistanceMatrix;
	using PositionList = std::deque<uint32_t>;

public:
	/**
	 * @brief Construct a new TSP object
	 * 
	 * @param distances - the distance matrix to work on
	 */
	TSP(DistanceMatrix distances);

public:
	/**
	 * @brief Solve the TS problem 
	 * 
	 * @return PositionList - the solution to the problem
	 */
	PositionList Solve() const;

private:
	/**
	 * @brief Generate the initial set of positions
	 * 
	 * @param size - the size of the list
	 * @return PositionList - the list of positions
	 */
	static PositionList GeneratePositionList(uint32_t size);

	/**
	 * @brief Get the length of the given path
	 * 
	 * @param value - the path to calculate the length for
	 * @return uint32_t - the length of the path
	 */
	uint32_t CalculateDistance(const PositionList& value) const;

private:
	DistanceMatrix distances_;
	uint32_t positions_;
};