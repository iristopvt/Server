#include "pch.h"
#include "RecvBuffer.h"

RecvBuffer::RecvBuffer(int32 bufferSize)
	: _bufferSize(bufferSize)
{
	_capacity = bufferSize * BUFF_COUNT; // 1000
	_buffer.resize(_capacity);
}

RecvBuffer::~RecvBuffer()
{
}

void RecvBuffer::Clean()
{
	int32 dataSize = DataSize();

	if (dataSize == 0)
	{
		// 딱 읽기 + 쓰기 커서가 동일한 위치. => 둘 다 리셋
		_readPos = _writePos = 0;
	}
	else
	{
		// 여유 공간을 체크해서 버퍼 1개 크기 미만이면, 데이터를 앞으로 땡긴다.
		if (FreeSize() < _bufferSize)
		{
			::memcpy(&_buffer[0], &_buffer[_readPos], dataSize);
			_readPos = 0;
			_writePos = dataSize;
		}
	}
}

bool RecvBuffer::OnRead(int32 numOfBytes)
{
	if (numOfBytes > DataSize())
		return false;

	_readPos += numOfBytes;
	return true;
}

bool RecvBuffer::OnWrite(int32 numOfBytes)
{
	if (numOfBytes > FreeSize())
		return false;

	_writePos += numOfBytes;
	return true;
}