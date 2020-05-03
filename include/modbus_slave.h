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

class ModbusSlave {
public:
    ModbusSlave(std::uint8_t slave_id, ArgType *arg);

    /**
     * @brief receiveAdu Receives a Modbus RTU ADU and prepares the response.
     *
     * @attention If you mark the data as unstable, this method will make a copy.
     *            This is usefull if you are passing a data pointer that can be
     *            altered by a different thread or an interrupt.
     *
     * @attention The response pointer will point to memory of the internal
     *            pool. You must call free when done using the response packet.
     *
     * @param[in] packet Pointer to the packet holding the received ADU.
     * @param[in] arg User argument, will be passed through to callback.
     * @param[in] stable Flag indicating if the data is stable or not.
     *
     * @return Pointer to the prepared response packet if any.
     */
    Packet *receiveAdu(Packet *packet, ArgType *arg, bool stable = true);

    /**
     * @brief receiveMbap Receives a Modbus TCP MBAP frame and prepares the response.
     *
     * @attention If you mark the data as unstable, this method will make a copy.
     *            This is usefull if you are passing a data pointer that can be
     *            altered by a different thread or an interrupt.
     *
     * @attention The response pointer will point to memory of the internal
     *            pool. You must call free when done using the response packet.
     *
     * @param[in] packet Pointer to the packet holding the received ADU.
     * @param[in] arg User argument, will be passed through to callback.
     * @param[in] stable Flag indicating if the data is stable or not.
     *
     * @return Pointer to the prepared response packet if any.
     */
    Packet *receiveMbap(Packet *packet, ArgType *arg, bool stable = true);

    /**
     * @brief freeResponse Frees the response packet on the internal memory pool.
     *
     * @param[in] packet Pointer to the packet to be freed.
     */
    void freeResponse(Packet *packet);
private:
    std::size_t _receivePdu(const std::uint8_t *pdu, std::size_t pdu_length, std::uint8_t *response_pdu, ArgType *arg);
    std::size_t _unsupportedFc(const std::uint8_t *pdu, std::size_t pdu_length, std::uint8_t *response_pdu, ArgType *arg);

    Packet *_copyPacket(Packet *packet, ArgType *arg);

    PacketPool _pool;
    std::uint8_t _slave_id;
};

}
