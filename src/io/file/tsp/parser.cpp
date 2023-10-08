#include "io/file/tsp/parser.hpp"

#include "utils/tokenizer.hpp"

// FIXME
#include <iostream>

namespace io::file::tsp {
Parser::Parser(Data data)
	: data_{std::move(data)} { }

bool Parser::Process() {
	if(data_.empty()) {
		return false;
	}

	uint32_t dimension;
	try {
		dimension = std::stoi(data_.at(0).c_str());
	} catch(const std::exception& e) {
		return false;
	}

	matrix_ = GetDistanceMatrix(data_);
	return matrix_.Columns() == dimension;
}

const Parser::DistanceMatrix& Parser::Get() const noexcept {
	return matrix_;
}

Parser::DistanceMatrix Parser::GetDistanceMatrix(const Data& data) {
	if(data.empty()) {
		throw std::runtime_error("Content is empty. Was the file opened?");
	}

	DistanceMatrix matrix;
	for(auto iterator = ++data.begin(); iterator != data.end(); ++iterator) {
		// Convert the parsed string to a row of matrix
		const auto line = *iterator;
		const auto data = utils::Tokenizer::tokenize(line, ' ');
		std::deque<int32_t> weights;
		std::for_each(data.cbegin(), data.cend(), [&weights](const std::string& value) {
			weights.push_back(std::stoi(value));
		});

		matrix.insert(weights);
	}

	return std::move(matrix);
}
} // namespace io::file::tsp