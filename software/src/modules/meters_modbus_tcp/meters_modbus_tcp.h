/* esp32-firmware
 * Copyright (C) 2023 Mattias Schäffersmann <mattias@tinkerforge.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#pragma once

#include <stdint.h>
#include <TFTools/Micros.h>

#include "module.h"
#include "modules/meters/imeter_generator.h"
#include "config.h"
#include "meter_modbus_tcp_table_id.enum.h"

#if defined(__GNUC__)
    #pragma GCC diagnostic push
    #include "gcc_warnings.h"
    #pragma GCC diagnostic ignored "-Weffc++"
#endif

class MetersModbusTCP final : public IModule, public IMeterGenerator
{
public:
    // for IModule
    void pre_setup() override;

    // for IMeterGenerator
    [[gnu::const]] MeterClassID get_class() const override;
    virtual IMeter *new_meter(uint32_t slot, Config *state, Config *errors) override;
    [[gnu::const]] virtual const Config *get_config_prototype() override;
    [[gnu::const]] virtual const Config *get_state_prototype()  override;
    [[gnu::const]] virtual const Config *get_errors_prototype() override;

    void trace_timestamp();

private:
    Config config_prototype;
    Config table_custom_registers_prototype;
    std::vector<ConfUnionPrototype<MeterModbusTCPTableID>> table_prototypes;
    Config errors_prototype;

    size_t trace_buffer_index;
    micros_t last_trace_timestamp = -1_us;
};

#if defined(__GNUC__)
    #pragma GCC diagnostic pop
#endif
