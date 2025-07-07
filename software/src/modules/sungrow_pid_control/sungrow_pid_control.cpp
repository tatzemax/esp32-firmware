#include "sungrow_pid_control.h"
#include "modbus_client.h"  // Dein Minimal-Modbus-Client
#include <math.h>
#include <stdio.h>

// IPs deiner Sungrow Wechselrichter
static const char* sungrow_ips[5] = {
    "192.168.8.36",
    "192.168.8.37",
    "192.168.8.38",
    "192.168.8.39",
    "192.168.8.40"
};

#define SOC_MIN 20
#define SOC_MAX 95
#define EMS_COMMAND_CHARGE     170
#define EMS_COMMAND_DISCHARGE  187
#define EMS_COMMAND_STOP       204

#define EMS_COMMAND_REGISTER 13050
#define EMS_POWER_REGISTER   13051
#define SOC_REGISTER         13022
#define BATTERY_POWER_REGISTER 13021

#define DEFAULT_MAX_POWER_W 5000
#define KP 0.3
#define KI 1.0
#define KD 0.0005

extern energy_data_t energy_data;

SungrowPidModule::SungrowPidModule()
: DeviceModule("sungrow_pid")
{}

void SungrowPidModule::pre_init() {
    printf("[SungrowPID] pre_init()\n");
}

void SungrowPidModule::pre_setup() {
    printf("[SungrowPID] pre_setup()\n");
}

void SungrowPidModule::setup() {
    printf("[SungrowPID] setup()\n");
}

void SungrowPidModule::tick() {
    double grid_power = (double)energy_data.grid_power;
    double total_battery_power = 0;

    // Alle WR BatteryPower lesen
    for (int i = 0; i < 5; ++i) {
        uint16_t battery_power_raw = 0;
        if (modbus_read_input_registers(
                sungrow_ips[i], 502, 1,
                BATTERY_POWER_REGISTER, 1, &battery_power_raw) != 0) {
            printf("[WR %d] Fehler BatteryPower\n", i+1);
            continue;
        }
        total_battery_power += battery_power_raw;
    }

    double consumption = grid_power + total_battery_power;

    double output = 0;
    int16_t command = EMS_COMMAND_STOP;

    if (consumption > 40000) {
        double error = 40000.0 - consumption;
        double P = KP * error;
        integral += KI * error;
        double D = KD * (error - previous_error);
        output = P + integral + D;
        previous_error = error;
        command = EMS_COMMAND_DISCHARGE;
    } else if (consumption < 30000) {
        double error = 30000.0 - consumption;
        double P = KP * error;
        integral += KI * error;
        double D = KD * (error - previous_error);
        output = -(P + integral + D);
        previous_error = error;
        command = EMS_COMMAND_CHARGE;
    } else {
        integral = 0;
        previous_error = 0;
        output = 0;
        command = EMS_COMMAND_STOP;
    }

    int total_max_power = DEFAULT_MAX_POWER_W * 5;
    if (output > total_max_power) output = total_max_power;
    if (output < -total_max_power) output = -total_max_power;

    int16_t per_wr_power = (int16_t)(fabs(output) / 5);

    for (int i = 0; i < 5; ++i) {
        uint16_t soc = 0;
        if (modbus_read_holding_registers(
                sungrow_ips[i], 502, 1,
                SOC_REGISTER, 1, &soc) != 0) {
            printf("[WR %d] Fehler SOC\n", i+1);
            continue;
        }

        bool do_send = false;
        if (command == EMS_COMMAND_CHARGE && soc < SOC_MAX) {
            do_send = true;
        } else if (command == EMS_COMMAND_DISCHARGE && soc > SOC_MIN) {
            do_send = true;
        }

        if (do_send) {
            modbus_write_single_register(
                sungrow_ips[i], 502, 1,
                EMS_COMMAND_REGISTER, command);
            modbus_write_single_register(
                sungrow_ips[i], 502, 1,
                EMS_POWER_REGISTER, per_wr_power);
            printf("[WR %d] CMD %d, Power %d\n", i+1, command, per_wr_power);
        } else {
            modbus_write_single_register(
                sungrow_ips[i], 502, 1,
                EMS_COMMAND_REGISTER, EMS_COMMAND_STOP);
            modbus_write_single_register(
                sungrow_ips[i], 502, 1,
                EMS_POWER_REGISTER, 0);
            printf("[WR %d] STOP (SOC)\n", i+1);
        }
    }
}
