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

#include "application/menu/application.hpp"

#include <condition_variable>

#include "math/matrix.hpp"
#include "tsp/algorithm/accurate/bb/dfs.hpp"
#include "tsp/algorithm/accurate/bf.hpp"
#include "tsp/neighborhood/random.hpp"

#include "ui/menu/callable_entry.hpp"
#include "ui/menu/submenu.hpp"

namespace application::menu {
Application::Application()
	: branch_and_bound_menu_{this}
	, bruteforce_menu_{this}
	, genetic_menu_{this}
	, annealing_menu_{this}
	, menu_{CreateMenu()} {

	route_menu_.SetSolution(solution_);

	const auto matrix = matrix_menu_.GetMatrix();
	branch_and_bound_menu_.SetDistanceMatrix(matrix);
	bruteforce_menu_.SetDistanceMatrix(matrix);
	genetic_menu_.SetDistanceMatrix(matrix);
	annealing_menu_.SetDistanceMatrix(matrix);
	route_menu_.SetDistanceMatrix(matrix);
}

void Application::Start() {
	size_t index;
	while(true) {
		// Show the current menu
		menu_->Show();

		// Get the menu index
		std::cout << "Enter the index : ";
		std::cin >> index;

		// Choose the entry of the menu
		menu_->Choose(index);
	}
}

std::unique_ptr<ui::Menu> Application::CreateMenu() {
	auto timeout_entry = std::make_shared<ui::menu::CallableEntry>("Set a timeout", [this]() {
		uint32_t seconds;
		std::cout << "Please, enter the timeout value in seconds for the algorithms: ";
		std::cin >> seconds;

		timeout_ = std::chrono::seconds(seconds);
	});

	// Create the main menu
	auto menu = std::make_unique<ui::Menu>();
	auto root_entry = std::make_shared<ui::menu::Submenu>("Main menu", menu.get());

	auto matrix_submenu = matrix_menu_.Create(menu.get());
	matrix_submenu->SetParent(root_entry);

	auto route_submenu = route_menu_.Create(menu.get());
	route_submenu->SetParent(root_entry);

	auto bf_submenu = bruteforce_menu_.Create(menu.get());
	bf_submenu->SetParent(root_entry);

	auto bb_submenu = branch_and_bound_menu_.Create(menu.get());
	bb_submenu->SetParent(root_entry);

	auto sa_submenu = annealing_menu_.Create(menu.get());
	sa_submenu->SetParent(root_entry);

	auto ga_submenu = genetic_menu_.Create(menu.get());
	ga_submenu->SetParent(root_entry);

	// Set the main menu
	root_entry->AddChild(std::move(matrix_submenu));
	root_entry->AddChild(std::move(route_submenu));
	root_entry->AddChild(timeout_entry);
	root_entry->AddChild(std::move(bf_submenu));
	root_entry->AddChild(std::move(bb_submenu));
	root_entry->AddChild(std::move(sa_submenu));
	root_entry->AddChild(std::move(ga_submenu));
	root_entry->Enter();

	return menu;
}

void Application::OutputResults(const TestResult& value) {
	// Store the duration of the operation
	std::cout << "Time [ms] : " << value.duration.count() << " | Path: ";

	// Print the path, it's cost and if the calculation was finished
	for(uint32_t index = 0; index < value.solution.path.size() - 2; ++index) {
		const auto position = value.solution.path.at(index);
		std::cout << position << "->";
	}
	std::cout << value.solution.path.back() << " | Cost: " << value.solution.cost
			  << " | Has finished : " << value.is_complete << std::endl;
}

void Application::CalculateSolution(tsp::algorithm::Algorithm* algorithm) {
	// Run the algorithm and output the results
	const auto results = RunAlgorithm(algorithm);
	OutputResults(results);

	// Update the internal solution
	*solution_ = std::move(results.solution);
}

} // namespace application::menu