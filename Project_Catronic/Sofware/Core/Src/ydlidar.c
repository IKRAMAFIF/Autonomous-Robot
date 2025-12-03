#include "ydlidar.h"
#include "usart.h"
#include <string.h>
#include <stdio.h>
#include <math.h>

extern UART_HandleTypeDef huart3;

#define MAX_PACKET_SIZE 515

typedef enum {
    STATE_WAIT_START_BYTE1, // Waiting for 0xAA
    STATE_WAIT_START_BYTE2, // Waiting for 0x55
    STATE_RECEIVE_HEADER,   // Receiving CT, LSN, FSA, LSA, CS
    STATE_RECEIVE_SAMPLES   // Receiving sample data
} parsing_state_t;

static parsing_state_t current_parsing_state = STATE_WAIT_START_BYTE1;
static uint8_t current_packet_buffer[MAX_PACKET_SIZE];
static uint16_t current_packet_idx = 0;
static uint16_t expected_packet_len = 0;


static void decode_and_publish_packet(const uint8_t* packet_data, uint16_t packet_len);

void ydlidar_init(void) {
    current_parsing_state = STATE_WAIT_START_BYTE1;
    current_packet_idx = 0;
    expected_packet_len = 0;
    printf("YDLIDAR driver initialized.\r\n");
}

void ydlidar_process_data(const uint8_t* data, size_t len) {
    for (size_t i = 0; i < len; ++i) {
        uint8_t byte = data[i];

        switch (current_parsing_state) {
            case STATE_WAIT_START_BYTE1:
                if (byte == 0xAA) {
                    current_packet_buffer[0] = byte;
                    current_parsing_state = STATE_WAIT_START_BYTE2;
                }
                break;

            case STATE_WAIT_START_BYTE2:
                if (byte == 0x55) {
                    current_packet_buffer[1] = byte;
                    current_packet_idx = 2; // PH (2 bytes) received
                    current_parsing_state = STATE_RECEIVE_HEADER;
                    expected_packet_len = 0;
                } else {
                    // If 0x55 is not received, reset state and look for 0xAA again
                    current_parsing_state = STATE_WAIT_START_BYTE1;
                }
                break;

            case STATE_RECEIVE_HEADER:
                current_packet_buffer[current_packet_idx++] = byte;
                if (current_packet_idx >= (2 + 8)) {
                    uint8_t lsn = current_packet_buffer[3];
                    expected_packet_len = 10 + (lsn * 2);
                    
                    if (expected_packet_len > MAX_PACKET_SIZE) {
                        printf("Error: Packet too large (%d bytes). Resetting.\r\n", expected_packet_len);
                        current_parsing_state = STATE_WAIT_START_BYTE1;
                        current_packet_idx = 0;
                        expected_packet_len = 0;
                        break;
                    }
                    current_parsing_state = STATE_RECEIVE_SAMPLES;
                }
                break;

            case STATE_RECEIVE_SAMPLES:
                current_packet_buffer[current_packet_idx++] = byte;

                if (current_packet_idx >= expected_packet_len) {
                    decode_and_publish_packet(current_packet_buffer, expected_packet_len);

                    current_parsing_state = STATE_WAIT_START_BYTE1;
                    current_packet_idx = 0;
                    expected_packet_len = 0;
                }
                break;
        }
    }
}


static void decode_and_publish_packet(const uint8_t* packet_data, uint16_t packet_len) {
    printf("Lidar packet received (%d bytes):", packet_len);
    for (uint16_t i = 0; i < packet_len; i++) {
        printf(" %02X", packet_data[i]);
    }
    printf("\r\n");


}
