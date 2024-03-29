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

#include <memory>
#include <string>

#include "application/configuration/application.hpp"
#include "application/menu/application.hpp"

int main(int argc, char** argv) {
	using namespace application;

	std::unique_ptr<IApplication> application;
	if(argc == 2) {
		// Get the name of the configuration file
		const std::string config_file{argv[1]};

		application = std::make_unique<configuration::Application>(config_file);
	} else {
		application = std::make_unique<menu::Application>();
	}

	application->Start();

	return 0;
}