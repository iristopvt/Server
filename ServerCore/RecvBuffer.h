#pragma once
class RecvBuffer
{
	enum { BUFF_COUNT = 10 };
public:
	RecvBuffer(int32 bufferSize);
	~RecvBuffer();

	void Clean();
	bool OnRead(int32 numOfBytes);
	bool OnWrite(int32 numOfBytes);

	// Read CursorÀÇ À§Ä¡ ¹ÝÈ¯
	BYTE* ReadPos() { return &_buffer[_readPos]; }
	// Write CursorÀÇ À§Ä¡ ¹ÝÈ¯
	BYTE* WritePos() { return &_buffer[_writePos]; }
	int32	DataSize() { return _writePos - _readPos; }
	int32	FreeSize() { return _capacity - _writePos; }

private:
	int32 _capacity = 0;
	int32 _bufferSize = 0;
	int32 _readPos = 0; // Read Cursor
	int32 _writePos = 0; // Write Cursor

	Vector<BYTE> _buffer;
};