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

#include "io/file/tsp/parser.hpp"

#include "utils/tokenizer.hpp"

namespace io::file::tsp {
Parser::Parser(Data data)
	: data_{std::move(data)} { }

bool Parser::Process() {
	// Check if the data is empty
	if(data_.empty()) {
		return false;
	}

	// Read the dimensions of the matrix
	uint32_t dimension;
	try {
		dimension = std::stoi(data_.at(0).c_str());
	} catch(const std::exception& e) {
		return false;
	}

	// Read the matrix itself and check if the size is correct
	matrix_ = GetDistanceMatrix(data_);
	return matrix_.Columns() == dimension;
}

const Parser::DistanceMatrix& Parser::Get() const noexcept {
	return matrix_;
}

Parser::DistanceMatrix Parser::GetDistanceMatrix(const Data& data) {
	// Check if the given data is empty
	if(data.empty()) {
		throw std::runtime_error("Content is empty. Was the file opened?");
	}

	DistanceMatrix matrix;
	for(auto iterator = ++data.begin(); iterator != data.end(); ++iterator) {
		// Convert the parsed string to a row of matrix
		const auto line = *iterator;
		const auto data = utils::Tokenizer::tokenize(line, ' ');

		// Fill the row with the data
		std::deque<int32_t> weights;
		std::for_each(data.cbegin(), data.cend(), [&weights](const std::string& value) {
			weights.push_back(std::stoi(value));
		});

		// Add the row to the matrix
		matrix.InsertRow(weights);
	}

	return std::move(matrix);
}
} // namespace io::file::tsp