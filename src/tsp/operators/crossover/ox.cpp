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

#include "tsp/operators/crossover/ox.hpp"

#include <algorithm>

namespace tsp::operators::crossover {
OX::OX(PathSizeType path_size)
	: Algorithm{path_size} { }

OX::Path OX::Cross(Path lhs, Path rhs) const {
	if(lhs.size() != rhs.size() || lhs.size() != kPathSize) {
		// FIXME : change to a more concrete type
		throw std::runtime_error("The paths meant for crossing don't have correct size");
	}

	// Generate random indexes for accessing a range of values in both paths
	const auto [start, end] = GetRandomRange();

	// Erase all the elements in the second parent that are in the randomized range of the first one
	std::erase_if(rhs, [&](auto value) {
		const auto start_iterator = lhs.begin() + start;
		const auto end_iterator = lhs.begin() + end;
		const auto iterator = std::find(start_iterator, end_iterator, value);

		return iterator != end_iterator;
	});

	// Replace first parent's elements by those from the second one
	std::copy(rhs.begin(), rhs.begin() + start, lhs.begin());
	std::copy(rhs.begin() + start, rhs.end(), lhs.begin() + end);

	return lhs;
}
} // namespace tsp::operators::crossover
