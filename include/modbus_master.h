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

#include <cstddef>
#include <cstdint>

#include "modbus_opt.h"
#include "modbus_pool.h"
#include "modbus_types.h"

namespace modbus {

class ModbusMaster {
public:
    Packet *allocateResponse(ArgType *arg);
    Packet *readHoldingRegistersAdu(std::uint8_t slave_id, std::uint16_t address, std::uint16_t quantity, ArgType *arg);
    Packet *readHoldingRegistersMbap(std::uint8_t slave_id, std::uint16_t address, std::uint16_t quantity, ArgType *arg);

    void freePacket(Packet *packet, ArgType *arg);
private:
    PacketPool _pool;
};

} // End namespace modbus.
