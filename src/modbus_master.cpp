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
#include "modbus_master.h"

#include <cstddef>
#include <cstdint>

#include "modbus_opt.h"
#include "modbus_pool.h"
#include "modbus_types.h"
#include "modbus_util.h"

namespace modbus {

Packet *ModbusMaster::allocateResponse(ArgType *arg) {
    return _pool.allocate(arg);
}

Packet *ModbusMaster::readHoldingRegistersAdu(std::uint8_t slave_id, std::uint16_t address, std::uint16_t quantity, ArgType *arg) {
    Packet *command = nullptr;
    auto error = true;

    do {
        command = _pool.allocate(arg);
        if (command == nullptr) {
            break;
        }

        command->bytes[0] = slave_id;
        command->bytes[1] = FunctionCode::READ_HOLDING_REGISTERS;
        writeWordBE(address, command->bytes, 2);
        writeWordBE(quantity, command->bytes, 4);
        auto crc = crc16(command->bytes, 6);
        writeWordBE(crc, command->bytes, 6);

        command->length = 8;

        error = false;
    } while (false);

    if ((error) && (command != nullptr)) {
        command = _pool.free(command, arg);
    }

    return command;
}

void ModbusMaster::freePacket(Packet *packet, ArgType *arg) {
    if (packet != nullptr) {
        _pool.free(packet, arg);
    }
}

} // End namespace modbus.
