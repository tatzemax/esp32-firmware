#include "modbus_client.h"
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdio.h>

#define MODBUS_TCP_HEADER_SIZE 7
#define MODBUS_MAX_PDU_LENGTH 253
#define MODBUS_MAX_ADU_LENGTH (MODBUS_TCP_HEADER_SIZE + MODBUS_MAX_PDU_LENGTH)

static int modbus_send_request(int sock, uint8_t *adu, size_t adu_length) {
    ssize_t sent = send(sock, adu, adu_length, 0);
    return (sent == adu_length) ? 0 : -1;
}

static int modbus_receive_response(int sock, uint8_t *adu, size_t max_length) {
    ssize_t received = recv(sock, adu, max_length, 0);
    return (received > 0) ? received : -1;
}

static int modbus_connect_tcp(const char *ip, uint16_t port) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) return -1;

    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    inet_pton(AF_INET, ip, &addr.sin_addr);

    if (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        close(sock);
        return -1;
    }
    return sock;
}

static int modbus_read_registers_generic(
    const char *ip,
    uint16_t port,
    uint8_t unit_id,
    uint16_t start_address,
    uint16_t quantity,
    uint16_t *dest,
    uint8_t function_code
) {
    int sock = modbus_connect_tcp(ip, port);
    if (sock < 0) return -1;

    uint8_t adu[MODBUS_MAX_ADU_LENGTH];
    memset(adu, 0, sizeof(adu));

    // Transaction ID
    adu[0] = 0x00;
    adu[1] = 0x01;

    // Protocol ID
    adu[2] = 0x00;
    adu[3] = 0x00;

    // Length
    adu[4] = 0x00;
    adu[5] = 0x06;

    // Unit ID
    adu[6] = unit_id;

    // Function Code
    adu[7] = function_code;

    // Start Address
    adu[8] = start_address >> 8;
    adu[9] = start_address & 0xFF;

    // Quantity
    adu[10] = quantity >> 8;
    adu[11] = quantity & 0xFF;

    if (modbus_send_request(sock, adu, 12) < 0) {
        close(sock);
        return -1;
    }

    uint8_t response[MODBUS_MAX_ADU_LENGTH];
    int resp_len = modbus_receive_response(sock, response, sizeof(response));
    if (resp_len < 9) {
        close(sock);
        return -1;
    }

    if (response[7] != function_code) {
        close(sock);
        return -1;
    }

    uint8_t byte_count = response[8];
    if (byte_count != quantity * 2) {
        close(sock);
        return -1;
    }

    for (int i = 0; i < quantity; ++i) {
        dest[i] = (response[9 + i*2] << 8) | response[10 + i*2];
    }

    close(sock);
    return 0;
}

int modbus_read_input_registers(
    const char *ip,
    uint16_t port,
    uint8_t unit_id,
    uint16_t start_address,
    uint16_t quantity,
    uint16_t *dest
) {
    return modbus_read_registers_generic(ip, port, unit_id, start_address, quantity, dest, 0x04);
}

int modbus_read_holding_registers(
    const char *ip,
    uint16_t port,
    uint8_t unit_id,
    uint16_t start_address,
    uint16_t quantity,
    uint16_t *dest
) {
    return modbus_read_registers_generic(ip, port, unit_id, start_address, quantity, dest, 0x03);
}

int modbus_write_single_register(
    const char *ip,
    uint16_t port,
    uint8_t unit_id,
    uint16_t address,
    uint16_t value
) {
    int sock = modbus_connect_tcp(ip, port);
    if (sock < 0) return -1;

    uint8_t adu[MODBUS_TCP_HEADER_SIZE + 5];

    adu[0] = 0x00; // Transaction ID
    adu[1] = 0x01;
    adu[2] = 0x00; // Protocol ID
    adu[3] = 0x00;
    adu[4] = 0x00; // Length
    adu[5] = 0x06;
    adu[6] = unit_id; // Unit ID
    adu[7] = 0x06;    // Function Code

    adu[8] = address >> 8;
    adu[9] = address & 0xFF;

    adu[10] = value >> 8;
    adu[11] = value & 0xFF;

    if (modbus_send_request(sock, adu, 12) < 0) {
        close(sock);
        return -1;
    }

    uint8_t response[12];
    int resp_len = modbus_receive_response(sock, response, sizeof(response));
    if (resp_len < 12) {
        close(sock);
        return -1;
    }

    // Optionale Prüfung der Rückgabe
    if (response[7] != 0x06) {
        close(sock);
        return -1;
    }

    close(sock);
    return 0;
}
