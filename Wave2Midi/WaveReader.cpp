#include "WaveReader.h"

WaveReader::WaveReader(const void* data, size_t size) : _data(data), _size(size)
{
	if (_size < sizeof(WAV_RIFF_HEADER) + sizeof(WAV_SUBCHUNK_HEADER) + sizeof(WAV_SUBCHUNK_FORMAT) + sizeof(WAV_SUBCHUNK_HEADER))
	{
		
	}
}

WAV_RIFF_HEADER WaveReader::readRiffHeader()
{
	WAV_RIFF_HEADER header;
	memset(&header, 0, sizeof(header));
	memcpy(&header, _data, sizeof(header));

	header.size = changeEndian(header.size);

	return header;
}

WAV_SUBCHUNK_FORMAT WaveReader::readFormatData()
{
}

int WaveReader::validateFile()
{
}


uint16_t WaveReader::changeEndian(uint16_t data)
{
	return (((data & 0x00FF) << 8) |
		((data & 0xFF00) >> 8));
}

uint32_t WaveReader::changeEndian(uint32_t data)
{
	return (((data & 0x000000FF) << 24) |
		((data & 0x0000FF00) << 8) |
		((data & 0x00FF0000) >> 8) |
		((data & 0xFF000000) >> 24));
}