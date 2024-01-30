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

#include "application/menu/algorithm/simulated_annealing.hpp"

#include "application/menu/application.hpp"
#include "tsp/algorithm/inaccurate/sa/linear.hpp"
#include "tsp/neighborhood/random.hpp"
#include "ui/menu/callable_entry.hpp"

namespace application::menu::algorithm {
SimulatedAnnealing::SimulatedAnnealing(Application* application)
	: Algorithm{application} { }

std::unique_ptr<ui::menu::Submenu> SimulatedAnnealing::Create(ui::Menu* menu) {
	auto temperature_entry =
		std::make_shared<ui::menu::CallableEntry>("Set the starting temperature", [this]() {
			std::cout << "Please, enter the starting temperature value: ";
			std::cin >> temperature_;
		});

	auto epoch_size_entry =
		std::make_shared<ui::menu::CallableEntry>("Set the epoch size", [this]() {
			std::cout << "Please, enter the epoch size value: ";
			std::cin >> epoch_size_;
		});

	auto linear_coefficient_entry = std::make_shared<ui::menu::CallableEntry>(
		"Set the linear coefficient of cooling", [this]() {
			std::cout << "Please, enter the linear coefficient value: ";
			std::cin >> linear_coefficient_;
		});

	auto sa_linear_entry = std::make_shared<ui::menu::CallableEntry>(
		"Calculate the TSP with the linear cooling scheme", [this]() {
			// Check if the application instance exists
			if(!application_) {
				std::cout << "The application is not set. This is a bug" << std::endl;
				return;
			}

			// Check if the matrix is valid
			if(!matrix_) {
				std::cout << "The matrix is not valid. This is a bug" << std::endl;
				return;
			}

			auto algorithm =
				std::make_unique<tsp::algorithm::inaccurate::sa::Linear<tsp::neighborhood::Random>>(
					*matrix_, temperature_, epoch_size_, linear_coefficient_);

			// Run the algorithm
			application_->CalculateSolution(algorithm.get());

			// Get some additional output based on the temperature
			const auto temperature = algorithm->GetTemperature();
			std::cout << "exp(-1/T_k): " << std::exp(-1.0 / temperature)
					  << " | Temperature: " << temperature << std::endl;
		});

	auto submenu = std::make_unique<ui::menu::Submenu>("Simulated Annealing", menu);
	submenu->AddChild(temperature_entry);
	submenu->AddChild(epoch_size_entry);
	submenu->AddChild(linear_coefficient_entry);
	submenu->AddChild(sa_linear_entry);

	return std::move(submenu);
}
} // namespace application::menu::algorithm