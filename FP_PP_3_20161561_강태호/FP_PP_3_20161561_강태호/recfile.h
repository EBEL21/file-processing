#ifndef RECFILE_H
#define RECFILE_H

#include "buffile.h"
#include "iobuffer.h"
// template class to support direct read and write of records
// The template parameter RecType must support the following
//	int Pack (BufferType &); pack record into buffer
//	int Unpack (BufferType &); unpack record from buffer

template <class RecType>
class RecordFile: public BufferFile
{public:
	int Read (RecType & record, int recaddr = -1);
	int Write (const RecType & record, int recaddr = -1);
	int Append (const RecType & record, int recaddr = -1);
	int Append2 (const RecType & record, int recaddr = -1);
	int Update(const RecType & record, int recaddr);
	int Delete(int recaddr);
	int FindSpace();
	RecordFile (IOBuffer & buffer): BufferFile (buffer) {}
};

// template method bodies
template <class RecType>
int RecordFile<RecType>::Read (RecType & record, int recaddr)
{
	int readAddr = 0, result;
	while (readAddr == 0) {
		readAddr = BufferFile::Read(recaddr);
	}
	if (readAddr == -1) return -1;
	result = record . Unpack (Buffer);
	if (!result) return -1;
	return readAddr;
}

template <class RecType>
int RecordFile<RecType>::Write (const RecType & record, int recaddr)
{
	int result;
	result = record . Pack (Buffer);
	if (!result) return -1;
	return BufferFile::Write (recaddr);
}

template <class RecType>
int RecordFile<RecType>::Append (const RecType & record, int recaddr)
{
	int result;
	result = record . Pack (Buffer);
	if (!result) return -1;
	return BufferFile::Append ();
}

template <class RecType>
int RecordFile<RecType>::Append2(const RecType & record, int recaddr)
{
	int result;
	result = record.Pack(Buffer);
	if (!result) return -1;
	return BufferFile::Append2();
}

template <class RecType>
int RecordFile<RecType>::Update(const RecType & record, int recaddr)
{
	int prev_size, prev_addr, diff, result;
	prev_addr = BufferFile::Read(recaddr);
	prev_size = Buffer.SizeOfBuffer();
	result = record.Pack(Buffer);
	diff = prev_size - Buffer.SizeOfBuffer();
	return BufferFile::Update(prev_addr, diff);
}

template <class RecType>
int RecordFile<RecType>::Delete(int recaddr)
{
	return BufferFile::Delete(recaddr);
}

#endif