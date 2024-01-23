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

#include "tsp/operators/crossover/algorithm.hpp"

namespace tsp::operators::crossover {
Algorithm::Algorithm(PathSizeType path_size)
	: Operator{path_size} { }

std::tuple<Algorithm::PathIndexType, Algorithm::PathIndexType> Algorithm::GetRandomRange() const {
	// Generate the starting index
	PathIndexType start = distribution_(generator_);
	start = start == kPathSize ? start - 1 : start;

	// Try to generate the end index to be greater than the start one
	PathIndexType end;
	do {
		end = distribution_(generator_);
	} while(end <= start);

	return {start, end};
}
} // namespace tsp::operators::crossover