#include "io/basereader.hpp"

namespace io {
BaseReader::BaseReader(const std::string& file) {
	stream_.open(file);
	if(!stream_.is_open()) {
		std::runtime_error("Input file " + file + " was not opened");
	}
}

BaseReader::~BaseReader() {
	if(stream_.is_open()) {
		stream_.close();
	}
}

BaseReader::Content BaseReader::ReadRaw() const {
	Content content;
	std::string line;
	while(std::getline(stream_, line)) {
		if(line.empty()) {
			continue;
		}

		// Remove the end of line symbols
		line.erase(std::remove_if(line.begin(),
								  line.end(),
								  [](char symbol) { return symbol == '\n' || symbol == '\r'; }),
				   line.cend());

		content.push_back(line);
	}

	return content;
}
} // namespace io