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

#include "tsp/operators/mutation/algorithm.hpp"

namespace tsp::operators::mutation {
Algorithm::Algorithm(PathSizeType path_size)
	: Operator{path_size - 1} {

	// Set up the random float generator
	std::random_device device;
	generator_ = ProbabilityGeneratorType{device()};
}

Algorithm::PathIndexType Algorithm::GetRandomIndex() const {
	return distribution_(generator_);
}

Algorithm::PopulationType Algorithm::Mutate(PopulationType population) const {
	for(auto iterator = population.begin(); iterator != population.end(); ++iterator) {
		const auto probability = probability_distribution_(probability_generator_);
		if(probability < probability_) {
			auto path = Mutate(std::move(iterator->path));
			iterator->path = std::move(path);
		}
	}

	return population;
}

void Algorithm::SetProbability(ProbabilityType value) {
	probability_ = value;
}

} // namespace tsp::operators::mutation
