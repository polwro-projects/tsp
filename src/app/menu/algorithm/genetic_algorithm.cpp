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

#include "app/menu/algorithm/genetic_algorithm.hpp"

#include "app/menu/application.hpp"
#include "tsp/algorithm/inaccurate/genetic/algorithm.hpp"
#include "tsp/operators/crossover/ox.hpp"
#include "tsp/operators/mutation/swap.hpp"
#include "tsp/operators/selection/roulette.hpp"
#include "ui/menu/callable_entry.hpp"

namespace application::menu::algorithm {
GeneticAlgorithm::GeneticAlgorithm(Application* application)
	: Algorithm{application} { }

std::unique_ptr<ui::menu::Submenu> GeneticAlgorithm::Create(ui::Menu* menu) {
	auto crossover_entry =
		std::make_shared<::ui::menu::CallableEntry>("Set the crossover probability", [this]() {
			std::cout << "Please, enter the value: ";
			std::cin >> crossover_probability_;
		});

	auto mutation_entry =
		std::make_shared<::ui::menu::CallableEntry>("Set the mutation probability", [this]() {
			std::cout << "Please, enter the value: ";
			std::cin >> mutation_probability_;
		});

	auto population_entry =
		std::make_shared<::ui::menu::CallableEntry>("Set the population size", [this]() {
			std::cout << "Please, enter value: ";
			std::cin >> population_size_;
		});

	auto algorithm_entry =
		std::make_shared<::ui::menu::CallableEntry>("Calculate the TSP solution", [this]() {
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

			const auto crossover_algorithm =
				new ::tsp::operators::crossover::OX(matrix_->Columns());
			crossover_algorithm->SetProbability(crossover_probability_);

			const auto mutation_algorithm =
				new ::tsp::operators::mutation::Swap(matrix_->Columns());
			mutation_algorithm->SetProbability(mutation_probability_);

			const auto selection_algorithm =
				new ::tsp::operators::selection::Roulette(population_size_);

			auto algorithm = std::make_unique<tsp::algorithm::inaccurate::genetic::Algorithm>(
				*matrix_, population_size_, population_size_ / 2);
			algorithm->SetCrossoverAlgorithm(
				std::unique_ptr<tsp::operators::crossover::Algorithm>{crossover_algorithm});
			algorithm->SetMutationAlgorithm(
				std::unique_ptr<tsp::operators::mutation::Algorithm>(mutation_algorithm));
			algorithm->SetSelectionAlgorithm(
				std::unique_ptr<tsp::operators::selection::Algorithm>(selection_algorithm));

			// Run the algorithm
			application_->CalculateSolution(algorithm.get());
		});

	auto submenu = std::make_unique<ui::menu::Submenu>("Genetic Algorithm", menu);
	submenu->AddChild(crossover_entry);
	submenu->AddChild(mutation_entry);
	submenu->AddChild(population_entry);
	submenu->AddChild(algorithm_entry);

	return std::move(submenu);
}
} // namespace application::menu::algorithm