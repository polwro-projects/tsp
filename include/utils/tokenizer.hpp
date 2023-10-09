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

#pragma once

#include <deque>
#include <string>

namespace utils {
/**
 * @brief The class is used to break strings into arrays of tokens
 * 
 */
class Tokenizer {
public:
	using Tokens = std::deque<std::string>;

public:
	/**
	 * @brief Tokenize the given string
	 * 
	 * @param line - the string to tokenize
	 * @param delimiter - the delimiter to use to break the string
	 * @return Tokens - the array of tokens
	 */
	static Tokens tokenize(std::string line, char delimiter);
};
} // namespace utils