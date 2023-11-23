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
#include <random>

#include "math/matrix.hpp"
#include "tsp/algorithm/bb/dfs.hpp"
#include "tsp/algorithm/bf.hpp"
#include "ui/menu/callable_entry.hpp"
#include "ui/menu/submenu.hpp"

std::ostream& operator<<(std::ostream& stream,
						 tsp::algorithm::Algorithm::Solution::Path positions) {
	for(const auto position : positions) {
		stream << position << " ";
	}
	return stream;
}

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

	auto bf_entry =
		std::make_shared<menu::CallableEntry>("Calculate the TSP using BF (Brute Force)", [this]() {
			tsp::algorithm::BF bf{distance_matrix_};
			RunTest(bf);
		});

	auto bnb_dfs_entry = std::make_shared<menu::CallableEntry>(
		"Calculate the TSP using BB (Branch and Bound) algorithm with DFS", [this]() {
			tsp::algorithm::bb::DFS dfs{distance_matrix_};
			RunTest(dfs);
		});

	auto menu = std::make_unique<Menu>();
	auto root_entry = std::make_shared<menu::Submenu>("Main menu", menu.get());
	root_entry->AddChild(read_entry);
	root_entry->AddChild(generate_entry);
	root_entry->AddChild(print_entry);
	root_entry->AddChild(bf_entry);
	root_entry->AddChild(bnb_dfs_entry);
	root_entry->Enter();

	return menu;
}

MenuApplication::DistanceMatrix MenuApplication::ReadMatrix(const std::string& filename) {
	// Read the TSP file
	io::Reader reader(filename);
	if(!reader.Process()) {
		throw std::runtime_error("Reading the TSP file failed");
	}

	// Read the matrix from the file
	io::file::tsp::Parser parser{reader.Get()};
	if(!parser.Process()) {
		throw std::runtime_error("Parsing the TSP file failed");
	}

	return parser.Get();
}

std::string MenuApplication::GetInputFile() {
	std::string filename;
	std::cout << "Please, enter the name of the file: ";
	std::cin >> filename;

	return filename;
}

void MenuApplication::RunTest(tsp::algorithm::Algorithm& algorithm) const {
	// Calculate the result and get the time of function's execution
	const auto start_point = std::chrono::system_clock::now();
	algorithm.Solve();
	const auto end_point = std::chrono::system_clock::now();

	// Store the duration of the operation
	const auto duration =
		std::chrono::duration_cast<std::chrono::microseconds>(end_point - start_point);
	std::cout << duration.count() << ",";

	// Print the solution to the output file
	const auto solution = algorithm.GetSolution();
	std::cout << solution.path << ", " << solution.cost << std::endl;
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