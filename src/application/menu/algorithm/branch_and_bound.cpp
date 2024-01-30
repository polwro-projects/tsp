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

#include "application/menu/algorithm/branch_and_bound.hpp"

#include "application/menu/application.hpp"
#include "ui/menu/callable_entry.hpp"

namespace application::menu::algorithm {
BranchAndBound::BranchAndBound(Application* application)
	: Algorithm{application} { }

std::unique_ptr<ui::menu::Submenu> BranchAndBound::Create(ui::Menu* menu) {
	auto entry = std::make_shared<ui::menu::CallableEntry>(
		"Calculate a solution for the TSP using DFS", [this]() {
			if(!matrix_) {
				std::cout << "[ERROR] The distance matrix was not initialized. It is a bug."
						  << std::endl;
				return;
			}

			// Run the algorithm
			auto algorithm = std::make_unique<tsp::algorithm::accurate::bb::DFS>(*matrix_);
			application_->CalculateSolution(algorithm.get());
		});

	auto submenu = std::make_unique<ui::menu::Submenu>("Branch'n'Bound algorithm", menu);
	submenu->AddChild(entry);

	return std::move(submenu);
}
} // namespace application::menu::algorithm