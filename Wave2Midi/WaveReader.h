#pragma once
#include "InvalidMagicException.h"
#include "InvalidChunkException.h"
#include "EmptyListException.h"

#include <cstdint>
#include <cstring>

#include <list>

typedef unsigned char uchar_t;

const uchar_t WAV_MAGIC_RIFF[4] = {'R', 'I', 'F', 'F'};
const uchar_t WAV_MAGIC_WAVE[4] = {'W', 'A', 'V', 'E'};
const uchar_t WAV_MAGIC_FMT0[4] = {'f', 'm', 't', ' '};
const uchar_t WAV_MAGIC_FACT[4] = {'f', 'a', 'c', 't'};
const uchar_t WAV_MAGIC_CUE0[4] = {'c', 'u', 'e', ' '};
const uchar_t WAV_MAGIC_PLST[4] = {'p', 'l', 's', 't'};
const uchar_t WAV_MAGIC_LIST[4] = {'l', 'i', 's', 't'};
const uchar_t WAV_MAGIC_LABL[4] = {'l', 'a', 'b', 'l'};
const uchar_t WAV_MAGIC_LTXT[4] = {'l', 't', 'x', 't'};
const uchar_t WAV_MAGIC_NOTE[4] = {'n', 'o', 't', 'e'};
const uchar_t WAV_MAGIC_SMPL[4] = {'s', 'm', 'p', 'l'};
const uchar_t WAV_MAGIC_INST[4] = {'i', 'n', 's', 't'};
const uchar_t WAV_MAGIC_DATA[4] = {'d', 'a', 't', 'a'};


#pragma pack(push, 1)
typedef struct _T_WAV_RIFF_HEADER
{
	uchar_t magic1[4];
	uint32_t size;
	uchar_t magic2[4];
}WAV_RIFF_HEADER;

typedef struct _T_WAV_CHUNK_HEADER
{
	uchar_t name[4];
	uint32_t size;	
}WAV_CHUNK_HEADER;

typedef struct _T_WAV_CHUNK_FORMAT
{
	uint16_t comp_code;
	uint16_t channel_num;
	uint32_t bitrate;
	uint32_t byterate;
	uint16_t align;
	uint16_t bits_per_sample;
	uint16_t extsize;
	uint16_t ext;
}WAV_CHUNK_FORMAT;
#pragma pack(pop)

class WaveReader
{
public:
	WaveReader(const void* data, size_t size);

	WAV_CHUNK_HEADER GetChunkHeader(int index);
	WAV_CHUNK_HEADER GetChunkHeader(char* name);
	void* GetChunk(WAV_CHUNK_HEADER header);

private:
	const void* _data;
	const size_t _size;
	
	WAV_RIFF_HEADER _riff_header;
	std::list<WAV_CHUNK_HEADER> _subchunk_headers;
	WAV_CHUNK_FORMAT _format_data;

	WAV_RIFF_HEADER _readRiff();
	WAV_CHUNK_HEADER _readChunkHeader(int offset = sizeof(WAV_RIFF_HEADER));
	std::list<WAV_CHUNK_HEADER> _readAllChunkHeaders();
	WAV_CHUNK_FORMAT _readFormatChunk();

	uint16_t changeEndian(uint16_t data);
	uint32_t changeEndian(uint32_t data);
};