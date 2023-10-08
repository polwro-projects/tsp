#include "utils/tokenizer.hpp"

namespace utils {
	Tokenizer::Tokens Tokenizer::tokenize(std::string line, char delimiter) {
		Tokens tokens;
		size_t position;

		while ((position = line.find(delimiter)) != std::string::npos) {
			tokens.push_back(line.substr(0, position));
			line.erase(0, position + 1);
		}
		tokens.push_back(line);

		return tokens;
	}
}