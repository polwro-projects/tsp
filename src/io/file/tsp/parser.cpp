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

#include "io/file/tsp/patterns.hpp"
#include "utils/tokenizer.hpp"

namespace io::file::tsp {
Parser::Parser(Data data)
	: data_{std::move(data)} { }

bool Parser::Process() {
	// Check if the data is empty
	if(data_.empty()) {
		return false;
	}

	for(const auto& line : data_) {
		if(IsDimensionParameter(line)) {
			dimension_ = GetDimensionParameter(line);
			break;
		}
	}

	// Read the matrix itself and check if the size is correct
	matrix_ = GetDistanceMatrix(data_);
	return matrix_.Columns() == dimension_;
}

bool Parser::IsDimensionParameter(const std::string& value) const {
	std::smatch match;
	return std::regex_match(value, match, kDimensionParameter);
}

uint32_t Parser::GetDimensionParameter(const std::string& value) {
	std::smatch matches;

	if(!std::regex_search(value, matches, kDimensionParameter)) {
		throw std::runtime_error("Can't find the parameter 'DIMENSION'");
	}

	// FIXME : add more error handling
	return std::stoi(matches[1].str());
}

bool Parser::HasMatrixData(const std::string& value) const {
	std::smatch match;
	return std::regex_match(value, match, kMatrixCells);
}

const Parser::DistanceMatrix& Parser::Get() const noexcept {
	return matrix_;
}

Parser::DistanceMatrix Parser::GetDistanceMatrix(const Data& data) const {
	// Check if the given data is empty
	if(data.empty()) {
		throw std::runtime_error("Content is empty. Was the file opened?");
	}

	DistanceMatrix matrix;
	DistanceMatrix::RowType weights;
	for(const auto line : data) {
		if(!HasMatrixData(line)) {
			continue;
		}
		const auto tokens = utils::Tokenizer::tokenize(line, ' ');
		for(const auto token : tokens) {
			// If the row is full, we need to push it
			if(weights.size() >= dimension_) {
				matrix.InsertRow(std::move(weights));
				weights = DistanceMatrix::RowType();
			}
			weights.push_back(std::stoi(token));
		}
	}

	// Add the last row to the matrix
	matrix.InsertRow(std::move(weights));

	return std::move(matrix);
}
} // namespace io::file::tsp