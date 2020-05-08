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
#include "modbus_pool.h"

#include <array>
#include <bitset>
#include <cstddef>
#include <cstdint>

#include "modbus_callback.h"
#include "modbus_opt.h"
#include "modbus_types.h"

namespace modbus {

PacketPool::PacketPool() {
    for (std::size_t i = 0; i < MODBUS_PACKET_POOL_SIZE; ++i) {
        _pool.at(i).bytes = _memory.at(i).begin();
    }
}

Packet *PacketPool::allocate(ArgType *arg) {
    auto idx = _findFree();

    if (idx != -1) {
        _allocated.set(idx);
        return &_pool.at(idx);
    }

    errorCallback("Packet pool: no free memory.", arg);

    return nullptr;
}

Packet *PacketPool::free(Packet *packet, ArgType *arg) {
    if (packet == nullptr) {
        errorCallback("Packet pool: attempt to free nullptr.", arg);

        return nullptr;
    }

    auto idx = _findIndex(packet);
    if (idx != -1) {
        _allocated.reset(idx);
        return nullptr;
    }

    errorCallback("Packet pool: attempt to free unmanaged memory.", arg);

    return packet;
}

int PacketPool::_findFree() {
    for (int i = 0; i < MODBUS_PACKET_POOL_SIZE; ++i) {
        if (! _allocated.test(i)) {
            return i;
        }
    }

    return -1;
}

int PacketPool::_findIndex(Packet *packet) {
    if (packet != nullptr) {
        for (int i = 0; i < MODBUS_PACKET_POOL_SIZE; ++i) {
            if (&_pool.at(i) == packet) {
                return i;
            }
        }
    }

    return -1;
}

} // End namespace modbus.
