#include "io/file/ini/parser.hpp"

#include <regex>

#include "io/file/ini/patterns.hpp"
#include "utils/tokenizer.hpp"

namespace io::file::ini {
Parser::Parser(Data data)
	: data_{std::move(data)} { }

bool Parser::Process() {
	if(data_.empty()) {
		return false;
	}

	Section section;
	for(const auto& line : data_) {
		if(IsSectionHeader(line)) {
			if(!section.name.empty()) {
				parameters_.push_back(section);
			}

			// Update the section
			section.clear();
			section.name = ProcessSectionHeader(line);

			continue;
		}

		try {
			auto property = ProcessProperty(line);
			section.properties.insert(property);
		} catch(const std::exception& e) {
			return false;
		}
	}

	// Save the latest section
	parameters_.push_back(section);

	return parameters_.empty();
}

const Parser::Parameters& Parser::Get() const noexcept {
	return parameters_;
}

Parser::Section::Property Parser::ProcessProperty(const std::string& value) {
	auto parsed_line = utils::Tokenizer::tokenize(value, '=');
	if(parsed_line.size() != 2) {
		throw std::runtime_error("Property is not defined properly.");
	}

	return {parsed_line.at(0), parsed_line.at(1)};
}

bool Parser::IsSectionHeader(const std::string& value) {
	std::smatch match;
	return std::regex_match(value, match, kSectionHeaderPattern);
}

std::string Parser::ProcessSectionHeader(const std::string& value) {
	return value.substr(1, value.size() - 2);
}
} // namespace io::file::ini