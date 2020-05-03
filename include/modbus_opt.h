/*
 * Copyright 2020 Erik Van Hamme (erik.vanhamme@gmail.com)
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

#include "modbus_opt_user.h"

#ifndef MODBUS_ARG_TYPE
#define MODBUS_ARG_TYPE int
#endif

#ifndef MODBUS_PACKET_POOL_SIZE
#define MODBUS_PACKET_POOL_SIZE 2
#endif

#ifndef MODBUS_WEAK
#define MODBUS_WEAK __attribute__((weak))
#endif

namespace modbus {

using ArgType = MODBUS_ARG_TYPE;

} // End namespace modbus.
