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

#include "application/menu/algorithm/algorithm.hpp"
#include "tsp/algorithm/accurate/bf.hpp"
#include "ui/menu/submenu.hpp"

namespace application::menu::algorithm {
/**
 * @brief An implementation of the genetic algorithm menu
 * 
 */
class BruteForce : public application::menu::algorithm::Algorithm {
public:
	/**
      * @brief Construct a new BruteForce object
      * 
      * @param application - a pointer to the menu application instance
      */
	BruteForce(application::menu::Application* application);

public:
	/**
     * @brief Create a Menu object
     * 
     * @param menu - the top level menu object 
     * @return std::unique_ptr<ui::menu::Submenu> - the submenu instance
     */
	std::unique_ptr<ui::menu::Submenu> Create(ui::Menu* menu) override;
};
} // namespace application::menu::algorithm