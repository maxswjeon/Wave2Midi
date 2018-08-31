#pragma once
#include <cstdint>
#include <cstring>

typedef unsigned char uchar_t;

const uchar_t WAV_MAG1[4] = {'R', 'I', 'F', 'F'};
const uchar_t WAV_MAG2[4] = {'W', 'A', 'V', 'E'};
const uchar_t WAV_MAG3[4] = {'f', 'm', 't', 0};
const uchar_t WAV_DATA[4] = {'d', 'a', 't', 'a'};

#pragma pack(push, 1)
typedef struct
{
	uchar_t magic1[4];
	uint32_t size;
	uchar_t magic2[4];
}WAV_RIFF_HEADER;

typedef struct
{
	uchar_t name[4];
	uint8_t size;	
}WAV_SUBCHUNK_HEADER;

typedef struct
{
	uint8_t channel_num;
	uint32_t bitrate;
	uint32_t byterate;
	uint32_t align;
	uint32_t bits_per_sample;	
}WAV_SUBCHUNK_FORMAT;
#pragma pack(pop)

class WaveReader
{
public:
	WaveReader(const void* data, size_t size);

private:
	const void* _data;
	const size_t _size;

	uint16_t changeEndian(uint16_t data);
	uint32_t changeEndian(uint32_t data);
};