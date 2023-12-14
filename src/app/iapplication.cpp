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

#include "app/iapplication.hpp"

#include <chrono>
#include <thread>

#include "app/patterns.hpp"
#include "io/file/problem/tsp/parser.hpp"
#include "io/file/problem/txt/parser.hpp"

namespace app {
IApplication::DistanceMatrix IApplication::ReadMatrix(const std::string& filename) {
	// Read the TSP file
	io::Reader reader(filename);
	if(!reader.Process()) {
		throw std::runtime_error("Reading the TSP file failed");
	}

	// Read the matrix from the file
	auto parser = CreateParser(filename, reader.Get());
	if(!parser || !parser->Process()) {
		throw std::runtime_error("Parsing the TSP file failed");
	}

	return parser->Get();
}

std::unique_ptr<io::file::problem::IProblemParser>
IApplication::CreateParser(const std::string& filename, const io::Reader::Data& data) {
	io::file::problem::IProblemParser* pointer{};
	std::smatch match;
	if(std::regex_match(filename, match, kTextFilePattern)) {
		pointer = new io::file::problem::txt::Parser(data);
	}
	if(std::regex_match(filename, match, kTravelingSalesmanProblemFilePattern)) {
		pointer = new io::file::problem::tsp::Parser(data);
	}

	return std::unique_ptr<io::file::problem::IProblemParser>{pointer};
}

IApplication::TestResult IApplication::RunTest(tsp::algorithm::Algorithm* algorithm) const {
	// Create a watcher thread that will
	std::mutex mutex;
	std::condition_variable cv;
	std::thread watcher{[this, &algorithm, &cv, &mutex]() {
		// If the timeout is not set don't do anything
		if(timeout_ == std::chrono::seconds::zero()) {
			return;
		}

		std::unique_lock<std::mutex> lock(mutex);
		cv.wait_for(lock, timeout_);
		algorithm->Stop();
	}};

	// Have a small delay to make the watcher thread wait on the conditional variable
	std::this_thread::sleep_for(std::chrono::milliseconds(100));

	// Calculate the result and get the time of function's execution
	const auto start_point = std::chrono::system_clock::now();
	const auto is_complete = algorithm->Solve();
	const auto end_point = std::chrono::system_clock::now();

	// Wait for the thread to finish
	cv.notify_one();
	watcher.join();

	// Return the result of the execution
	const auto duration =
		std::chrono::duration_cast<std::chrono::microseconds>(end_point - start_point);
	const auto solution = algorithm->GetSolution();
	return {duration, solution, is_complete};
}
} // namespace app