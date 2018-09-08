#include "WaveReader.h"

WaveReader::WaveReader(const void* data, size_t size) : _data(data), _size(size)
{
	if (_size < sizeof(WAV_RIFF_HEADER) + sizeof(WAV_CHUNK_HEADER) + sizeof(WAV_CHUNK_FORMAT) + sizeof(WAV_CHUNK_HEADER))
	{
		throw std::invalid_argument("Wave File Size is Smaller than Header");
	}

	_subchunk_headers = std::list<WAV_CHUNK_HEADER>();

	_readRiff();
	_readAllChunkHeaders();

}

WAV_RIFF_HEADER WaveReader::_readRiff()
{
	WAV_RIFF_HEADER riff_header;

	memset(&riff_header, 0, sizeof(riff_header));
	memcpy(&riff_header, _data, sizeof(riff_header));

	riff_header.size = changeEndian(riff_header.size);

	if (memcmp(WAV_MAGIC_RIFF, riff_header.magic1, sizeof(WAV_MAGIC_RIFF)) != 0)
	{
		throw InvalidMagicException(WAV_MAGIC_RIFF, riff_header.magic1);		
	}

	if (memcmp(WAV_MAGIC_WAVE, riff_header.magic2, sizeof(WAV_MAGIC_WAVE)) != 0)
	{
		throw InvalidMagicException(WAV_MAGIC_WAVE, riff_header.magic2);
	}

	return riff_header;
}

// Warning : ACESS to RAW DATA : Nothing is Guaranteed
WAV_CHUNK_HEADER WaveReader::_readChunkHeader(int offset)
{
	WAV_CHUNK_HEADER header;
	memset(&header, 0, sizeof(header));
	memcpy(&header, (char*)_data + offset, sizeof(header));

	header.size = changeEndian(header.size);

	return header;
}

std::list<WAV_CHUNK_HEADER> WaveReader::_readAllChunkHeaders()
{
	std::list<WAV_CHUNK_HEADER> list = std::list<WAV_CHUNK_HEADER>();

	int offset = sizeof(WAV_RIFF_HEADER);
	
	WAV_CHUNK_HEADER header = _readChunkHeader(offset);
	if (memcmp(header.name, WAV_MAGIC_FMT0, sizeof(WAV_MAGIC_FMT0)) != 0)
	{
		throw InvalidMagicException(WAV_MAGIC_FMT0, header.name);
	}
	list.push_back(header);
	offset += header.size + 8;

	while (true)
	{
		memset(&header, 0, sizeof(header));
		header = _readChunkHeader(offset);
		if (memcmp(header.name, WAV_MAGIC_DATA, sizeof(WAV_MAGIC_DATA)) == 0)
		{
			list.push_back(header);
			break;
		}
		
		if (memcmp(header.name, WAV_MAGIC_FACT, sizeof(WAV_MAGIC_FACT)) != 0 &&
			memcmp(header.name, WAV_MAGIC_CUE0, sizeof(WAV_MAGIC_CUE0)) != 0 &&
			memcmp(header.name, WAV_MAGIC_PLST, sizeof(WAV_MAGIC_PLST)) != 0 &&
			memcmp(header.name, WAV_MAGIC_LIST, sizeof(WAV_MAGIC_LIST)) != 0 &&
			memcmp(header.name, WAV_MAGIC_LABL, sizeof(WAV_MAGIC_LABL)) != 0 && 
			memcmp(header.name, WAV_MAGIC_LTXT, sizeof(WAV_MAGIC_LTXT)) != 0 && 
			memcmp(header.name, WAV_MAGIC_NOTE, sizeof(WAV_MAGIC_NOTE)) != 0 && 
			memcmp(header.name, WAV_MAGIC_SMPL, sizeof(WAV_MAGIC_SMPL)) != 0 && 
			memcmp(header.name, WAV_MAGIC_INST, sizeof(WAV_MAGIC_INST)) != 0 )
		{
			throw InvalidChunkException(header.name);
		}

		list.push_back(header);
		offset += header.size + 8;
	}

	return list;
}

WAV_CHUNK_FORMAT WaveReader::_readFormatChunk()
{
	if (_subchunk_headers.empty())
	{
		throw std::runtime_error("Header List is Empty");
	}

	WAV_CHUNK_HEADER header = _subchunk_headers.front();
	
	WAV_CHUNK_FORMAT format;
	memset(&format, 0, sizeof(format));
	memcpy(&format, (char*)_data + sizeof(WAV_RIFF_HEADER) + sizeof(WAV_CHUNK_HEADER), header.size);



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