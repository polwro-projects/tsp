#include "io/reader.hpp"

namespace io {
Reader::Reader(const std::string& file)
	: filename_{file} { }

bool Reader::Process() {
	std::ifstream stream{filename_};
	if(!stream.is_open()) {
		return false;
	}

	std::string line;
	while(std::getline(stream, line)) {
		if(line.empty()) {
			continue;
		}

		// Remove the end of line symbols
		line.erase(std::remove_if(line.begin(),
								  line.end(),
								  [](char symbol) { return symbol == '\n' || symbol == '\r'; }),
				   line.cend());

		data_.emplace_back(std::move(line));
	}

	return !data_.empty();
}

const Reader::Data& Reader::Get() const noexcept {
	return data_;
}

} // namespace io