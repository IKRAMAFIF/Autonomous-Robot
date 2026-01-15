#include "driver_LIDAR.h"
#include <string.h>
#include <stdio.h>


static LIDAR_FIFO_t fifo;

static inline uint8_t fifo_available(void)
{
	return fifo.head != fifo.tail;
}

static inline void fifo_push(uint8_t b)
{
	fifo.fifo[fifo.head++] = b;
	fifo.head %= LIDAR_FIFO_SIZE;
}

static inline uint8_t fifo_pop(void)
{
	uint8_t b = fifo.fifo[fifo.tail++];
	fifo.tail %= LIDAR_FIFO_SIZE;
	return b;
}


void YLIDAR_Init(h_YLIDARX2_t *h)
{
	memset(h, 0, sizeof(*h));
	memset(&fifo, 0, sizeof(fifo));
}


void YLIDAR_PushBytes(uint8_t *data, uint16_t len)
{
	for (uint16_t i = 0; i < len; i++)
		fifo_push(data[i]);
}


static void YLIDAR_ParsePacket(h_YLIDARX2_t *h)
{
	uint16_t fsa = h->packet[4] | (h->packet[5] << 8);
	uint16_t lsa = h->packet[6] | (h->packet[7] << 8);

	float start = (fsa >> 1) / 64.0f;
	float end   = (lsa >> 1) / 64.0f;
	float diff  = (end >= start) ? (end - start) : (360.0f + end - start);

	for (uint8_t i = 0; i < h->sample_quantity; i++)
	{
		uint16_t raw = h->packet[10 + i*2] |
				(h->packet[11 + i*2] << 8);

		h->points[i].distance = raw >> 2;
		h->points[i].angle =
				start + diff * ((float)i / (h->sample_quantity - 1));

		printf("Angle=%.2f° Dist=%d mm\r\n",
				h->points[i].angle,
				h->points[i].distance);
	}
}


void YLIDAR_Process(h_YLIDARX2_t *h)
{
	while (fifo_available())
	{
		uint8_t b = fifo_pop();
		h->packet[h->packet_index++] = b;

		if (h->packet_index >= 2)
		{
			if (h->packet[0] != YLIDAR_START_BYTE2 ||
					h->packet[1] != YLIDAR_START_BYTE1)
			{
				memmove(h->packet, h->packet + 1, --h->packet_index);
				continue;
			}
		}

		if (h->packet_index >= YLIDAR_HEADER_SIZE)
		{
			h->sample_quantity = h->packet[3];
			printf("LIDAR sample quantity: %d\r\n", h->sample_quantity);
			uint16_t total =
					YLIDAR_HEADER_SIZE + h->sample_quantity * 2;

			if (h->packet_index >= total)
			{
				YLIDAR_ParsePacket(h);
				h->packet_index = 0;
			}
		}

		if (h->packet_index >= sizeof(h->packet))
			h->packet_index = 0;
	}
}
