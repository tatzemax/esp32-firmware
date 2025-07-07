#ifndef MODBUS_CLIENT_H
#define MODBUS_CLIENT_H

#include <stdint.h>

/**
 * Liest Input-Register (Funktionscode 0x04).
 * 
 * @param ip IP-Adresse des Modbus-Geräts
 * @param port Port (Standard: 502)
 * @param unit_id Slave ID (meist 1)
 * @param start_address Startadresse des Registers
 * @param quantity Anzahl Register
 * @param dest Zeiger auf Ziel-Array (uint16_t)
 * @return 0 bei Erfolg, -1 bei Fehler
 */
int modbus_read_input_registers(
    const char *ip,
    uint16_t port,
    uint8_t unit_id,
    uint16_t start_address,
    uint16_t quantity,
    uint16_t *dest
);

/**
 * Liest Holding-Register (Funktionscode 0x03).
 * 
 * @param ip IP-Adresse des Modbus-Geräts
 * @param port Port (Standard: 502)
 * @param unit_id Slave ID
 * @param start_address Startadresse
 * @param quantity Anzahl Register
 * @param dest Ziel-Array
 * @return 0 bei Erfolg, -1 bei Fehler
 */
int modbus_read_holding_registers(
    const char *ip,
    uint16_t port,
    uint8_t unit_id,
    uint16_t start_address,
    uint16_t quantity,
    uint16_t *dest
);

/**
 * Schreibt ein einzelnes Holding-Register (Funktionscode 0x06).
 * 
 * @param ip IP-Adresse
 * @param port Port
 * @param unit_id Slave ID
 * @param address Registeradresse
 * @param value Wert
 * @return 0 bei Erfolg, -1 bei Fehler
 */
int modbus_write_single_register(
    const char *ip,
    uint16_t port,
    uint8_t unit_id,
    uint16_t address,
    uint16_t value
);

#endif // MODBUS_CLIENT_
