#ifndef INC_DRIVER_LIDAR_H_
#define INC_DRIVER_LIDAR_H_

#include <stdint.h>

/* ================= CONFIG ================= */
#define UART_DMA_RX_SIZE   1024
#define LIDAR_FIFO_SIZE   4096
#define MAX_SAMPLES        40

/* ================= YDLIDAR X2 ================= */
#define YLIDAR_START_BYTE1 0x55
#define YLIDAR_START_BYTE2 0xAA
#define YLIDAR_HEADER_SIZE 10
#define PI 3.14159265359f

/* ================= STRUCTURES ================= */

typedef struct {
    float angle;
    uint16_t distance;
} LIDAR_Point_t;

typedef struct {
    uint8_t fifo[LIDAR_FIFO_SIZE];
    volatile uint16_t head;
    volatile uint16_t tail;
} LIDAR_FIFO_t;

typedef struct {
    uint8_t packet[256];
    uint16_t packet_index;
    uint8_t sample_quantity;
    LIDAR_Point_t points[MAX_SAMPLES];
} h_YLIDARX2_t;

/* ================= API ================= */

void YLIDAR_Init(h_YLIDARX2_t *h);
void YLIDAR_PushBytes(uint8_t *data, uint16_t len);
void YLIDAR_Process(h_YLIDARX2_t *h);

#endif
