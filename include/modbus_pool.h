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

#include <array>
#include <bitset>
#include <cstddef>
#include <cstdint>

#include "modbus_opt.h"
#include "modbus_types.h"

namespace modbus {

class PacketPool {
public:
    PacketPool();
    Packet *allocate(ArgType *arg);
    void free(Packet *packet, ArgType *arg);
private:
    int _findFree();
    int _findIndex(Packet *packet);

    std::array<std::array<std::uint8_t, MODBUS_MBAP_SIZE_MAX>, MODBUS_PACKET_POOL_SIZE> _memory;
    std::array<Packet, MODBUS_PACKET_POOL_SIZE> _pool;
    std::bitset<MODBUS_PACKET_POOL_SIZE> _allocated;
};

} // End namespace modbus.
