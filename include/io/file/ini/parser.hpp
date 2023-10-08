#pragma once

#include <map>
#include <string>
#include <vector>

#include "io/file/iparser.hpp"
#include "io/reader.hpp"

namespace io::file::ini {
class Parser : virtual public IParser {
public:
	struct Section {
		using Property = std::pair<std::string, std::string>;

		std::string name;
		std::map<std::string, std::string> properties;

		void clear() {
			name.clear();
			properties.clear();
		}
	};

	using Parameters = std::vector<Section>;
	using Data = io::Reader::Data;

public:
	Parser(Data data);

public:
	bool Process();
	const Parameters& Get() const noexcept;

protected:
	static Section::Property ProcessProperty(const std::string& value);
	static bool IsSectionHeader(const std::string& value);
	static std::string ProcessSectionHeader(const std::string& value);

protected:
	Parameters parameters_;
	Data data_;
};
} // namespace io::file::ini