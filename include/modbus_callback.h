/*
 * Copyright 2020 Erik Van Hamme
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#pragma once

#include <string>

#include "modbus_opt.h"
#include "modbus_types.h"

namespace modbus {

void errorCallback(std::string message, ArgType *arg);
void warningCallback(std::string message, ArgType *arg);
bool isSupportedFunctionCallback(FunctionCode fc, ArgType *arg);

bool isHoldingRegisterAddressInRangeCallback(std::uint16_t address, ArgType *arg);
std::uint16_t readHoldingRegisterCallback(std::uint16_t address, ArgType *arg);

} // End namespace modbus.
