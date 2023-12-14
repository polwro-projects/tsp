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

#include "app/menu_application.hpp"

#include <chrono>
#include <condition_variable>
#include <random>
#include <thread>

#include "math/matrix.hpp"
#include "tsp/algorithm/accurate/bb/dfs.hpp"
#include "tsp/algorithm/accurate/bf.hpp"
#include "tsp/algorithm/inaccurate/sa/linear.hpp"
#include "tsp/neighborhood/random.hpp"
#include "ui/menu/callable_entry.hpp"
#include "ui/menu/submenu.hpp"

namespace app {
MenuApplication::MenuApplication()
	: menu_{CreateMenu()} { }

void MenuApplication::Start() {
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

std::unique_ptr<ui::Menu> MenuApplication::CreateMenu() {
	using namespace ui;

	auto timeout_entry = std::make_shared<menu::CallableEntry>("Set a timeout", [this]() {
		uint32_t seconds;
		std::cout << "Please, enter the timeout value in seconds for the algorithms: ";
		std::cin >> seconds;

		timeout_ = std::chrono::seconds(seconds);
	});

	auto bf_entry =
		std::make_shared<menu::CallableEntry>("Calculate the TSP using BF (Brute Force)", [this]() {
			auto algorithm = std::make_unique<tsp::algorithm::accurate::BF>(distance_matrix_);
			const auto results = RunTest(algorithm.get());
			OutputResults(results);
		});

	auto bnb_dfs_entry = std::make_shared<menu::CallableEntry>(
		"Calculate the TSP using BB (Branch and Bound) algorithm with DFS", [this]() {
			auto algorithm = std::make_unique<tsp::algorithm::accurate::bb::DFS>(distance_matrix_);
			const auto results = RunTest(algorithm.get());
			OutputResults(results);
		});

	// Create the main menu
	auto menu = std::make_unique<Menu>();
	auto root_entry = std::make_shared<menu::Submenu>("Main menu", menu.get());

	auto matrix_submenu = CreateMatrixSubmenu(menu.get());
	matrix_submenu->SetParent(root_entry);

	auto sa_submenu = CreateSASubmenu(menu.get());
	sa_submenu->SetParent(root_entry);

	// Set the main menu
	root_entry->AddChild(std::move(matrix_submenu));
	root_entry->AddChild(timeout_entry);
	root_entry->AddChild(bf_entry);
	root_entry->AddChild(bnb_dfs_entry);
	root_entry->AddChild(std::move(sa_submenu));
	root_entry->Enter();

	return menu;
}

std::unique_ptr<ui::menu::Submenu> MenuApplication::CreateSASubmenu(ui::Menu* menu) {
	using namespace ui;

	auto temperature_entry =
		std::make_shared<menu::CallableEntry>("Set the starting temperature", [this]() {
			std::cout << "Please, enter the starting temperature value: ";
			std::cin >> temperature_;
		});

	auto epoch_size_entry = std::make_shared<menu::CallableEntry>("Set the epoch size", [this]() {
		std::cout << "Please, enter the epoch size value: ";
		std::cin >> epoch_size_;
	});

	auto linear_coefficient_entry =
		std::make_shared<menu::CallableEntry>("Set the linear coefficient of cooling", [this]() {
			std::cout << "Please, enter the linear coefficient value: ";
			std::cin >> linear_coefficient_;
		});

	auto sa_linear_entry = std::make_shared<menu::CallableEntry>(
		"Calculate the TSP with the linear cooling scheme", [this]() {
			auto algorithm =
				std::make_unique<tsp::algorithm::inaccurate::sa::Linear<tsp::neighborhood::Random>>(
					distance_matrix_, temperature_, epoch_size_, linear_coefficient_);
			const auto results = RunTest(algorithm.get());
			OutputResults(results);

			// Get some additional output based on the temperature
			const auto temperature = algorithm->GetTemperature();
			std::cout << "exp(-1/T_k) :" << std::exp(-1 / temperature)
					  << " | Temperature : " << temperature << std::endl;
		});

	auto submenu = std::make_unique<menu::Submenu>("Simulated Annealing", menu);
	submenu->AddChild(temperature_entry);
	submenu->AddChild(epoch_size_entry);
	submenu->AddChild(linear_coefficient_entry);
	submenu->AddChild(sa_linear_entry);

	return std::move(submenu);
}

std::unique_ptr<ui::menu::Submenu> MenuApplication::CreateMatrixSubmenu(ui::Menu* menu) {
	using namespace ui;

	auto read_entry = std::make_shared<menu::CallableEntry>("Read matrix from the file", [this]() {
		const auto filename = std::move(GetInputFile());
		distance_matrix_ = std::move(ReadMatrix(filename));
	});

	auto generate_entry =
		std::make_shared<menu::CallableEntry>("Generate a random matrix", [this]() {
			uint32_t size;
			std::cout << "Please, enter the size of the matrix: ";
			std::cin >> size;

			// Handle some smartasses' requests to generate 0x0 matrixes
			if(size == 0) {
				std::cout << "The size is incorrect. Please, try again." << std::endl;
				return;
			}

			distance_matrix_ = std::move(GenerateRandomMatrix(size));
		});

	auto print_entry = std::make_shared<menu::CallableEntry>(
		"Print current matrix", [this]() { std::cout << distance_matrix_ << std::endl; });

	auto submenu = std::make_unique<menu::Submenu>("Matrix manipulation", menu);
	submenu->AddChild(read_entry);
	submenu->AddChild(generate_entry);
	submenu->AddChild(print_entry);

	return std::move(submenu);
}

MenuApplication::DistanceMatrix MenuApplication::ReadMatrix(const std::string& filename) {
	// Read the TSP file
	io::Reader reader(filename);
	if(!reader.Process()) {
		throw std::runtime_error("Reading the TSP file failed");
	}

	// Read the matrix from the file
	auto parser = CreateParser(filename, reader.Get());
	if(!parser || !parser->Process()) {
		throw std::runtime_error("Parsing the TSP file failed");
	}

	return parser->Get();
}

std::string MenuApplication::GetInputFile() {
	std::string filename;
	std::cout << "Please, enter the name of the file: ";
	std::cin >> filename;

	return filename;
}

void MenuApplication::OutputResults(const TestResult& value) {
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

MenuApplication::DistanceMatrix MenuApplication::GenerateRandomMatrix(uint32_t size) {
	DistanceMatrix matrix;
	for(uint32_t row_index = 0; row_index < size; ++row_index) {
		DistanceMatrix::RowType row;
		for(uint32_t column_index = 0; column_index < size; ++column_index) {
			if(column_index == row_index) {
				row.push_back(-1);
				continue;
			}

			// Generate a random value to be used as a distance
			const auto value = GetRandomNumber(1, size);
			row.push_back(value);
		}

		matrix.InsertRow(std::move(row));
	}
	return std::move(matrix);
}

uint32_t MenuApplication::GetRandomNumber(uint32_t min, uint32_t max) {
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist(min, max);
	return dist(rng);
}
} // namespace app