// varlen.cc

#include "varlen.h"
#include <string.h>

//class VariableLengthBuffer

// public members

VariableLengthBuffer :: VariableLengthBuffer (int maxBytes)
 // construct with a maximum of maxFields
: IOBuffer (maxBytes)
{
	Init ();
}

void VariableLengthBuffer :: Clear ()
// clear fields from buffer
{
	IOBuffer::Clear();
}

int VariableLengthBuffer :: Read (istream & stream)
// write the number of bytes in the buffer field definitions
// the record length is represented by an unsigned short value
{
	if (stream.eof()) return -1;
	int recaddr = (int)stream . tellg ();
	Clear ();
	unsigned short bufferSize;
	stream . read ((char *)&bufferSize, sizeof(bufferSize));
	if (! stream . good ()){stream.clear(); return -1;}
	BufferSize = bufferSize;
	if (BufferSize > MaxBytes) return -1; // buffer overflow
	stream . read (Buffer, BufferSize);
	if (Buffer[0] == deletion_mark) return 0;
	if (! stream . good ()){stream.clear(); return -1;}

	return recaddr;
}


int VariableLengthBuffer :: Write (ostream & stream) const
// write the length and buffer into the stream
{
	int recaddr = (int)stream . tellp ();
	unsigned short bufferSize;
	bufferSize = BufferSize;
	stream . write ((char *)&bufferSize, sizeof(bufferSize));
	if (!stream) return -1;
	stream . write (Buffer, BufferSize);
	if (! stream . good ()) return -1;
	return recaddr;
}

const int delRecordSize = 1 + sizeof(unsigned short) + sizeof(int);

int VariableLengthBuffer::Delete(ostream & stream, int recaddr) const
{
	stream.seekp(recaddr + 2, ios::beg);
	//unsigned short bufferSize;
	//bufferSize = BufferSize;
	////put deletion record information into file
	//stream.write((char *)&bufferSize, sizeof(bufferSize));
	//if (!stream) return -1;
	stream.write(&deletion_mark, 1);
	if (!stream) return -1;
	stream.write((char*)&DeleteAddr, sizeof(DeleteAddr));
	if (!stream.good()) return -1;
	
	//update deletion header
	//memcpy((char *)&DeleteAddr, (char *)&recaddr, sizeof(DeleteAddr));
	WriteDeleteAddr(stream, -1, recaddr);

	return 0;
}

const char * headerStr = "Variable";
//const int headerSize = strlen (headerStr);
const int headerSize = 8;

int VariableLengthBuffer :: ReadHeader (istream & stream)
// read the header and check for consistency
{
	char str[headerSize+1];
	int result;
	// read the IOBuffer header
	result = IOBuffer::ReadHeader (stream);
	if (!result) return FALSE;
	// read the header string
	stream . read (str, headerSize);
	if (!stream.good()) return FALSE;
	if (strncmp (str, headerStr, headerSize) != 0) return FALSE;
	// read and check the record description
	return (int)stream . tellg ();
}

int VariableLengthBuffer :: WriteHeader (ostream & stream) const
// write a buffer header to the beginning of the stream
// A header consists of the 
//	IOBUFFER header	
//	header string
//	Variable sized record of length fields
//		that describes the file records
{
	int result;
	// write the parent (IOBuffer) header
	result = IOBuffer::WriteHeader (stream);
	if (!result) return FALSE;
	// write the header string
	stream . write (headerStr, headerSize);
	if (!stream . good ()) return FALSE;
	// write the record description
	return (int)stream . tellp();
}

void VariableLengthBuffer :: Print (ostream & stream) const
{
	IOBuffer::Print (stream);
}

int VariableLengthBuffer::SizeOfBuffer() const
{
	return BufferSize;
}

int VariableLengthBuffer::FindSpace(istream & stream, int *prev, int* next, unsigned short* diff)
{
	int addr;
	unsigned short space_size;
	*prev = ReadDeleteAddr(stream);
	addr = DeleteAddr;
	while (addr != -1) {
		stream.seekg(addr, ios::beg);
		stream.read((char *)&space_size, sizeof(space_size));
		if (!stream.good()) { stream.clear(); return -1; }
		stream.get();
		if (!stream.good()) { stream.clear(); return -1; }
		stream.read((char*)next, sizeof(*next));
		if (!stream.good()) { stream.clear(); return -1; }
		//딱 맞는 space를 찾으면 while문 종료
		if ((int)space_size == BufferSize) {
			*diff = 0;
			break;
		}
		// 딱 맞지 않으면 deletion_mark, 길이 , delimeter가 들어갈 공간(최소 4byte)이 필요.
		else if ((int)space_size >= BufferSize + 4) {
			*diff = (unsigned short)((int)space_size - BufferSize - 2);
			break;
		}
		else {
			*prev = addr + 3;
			addr = *next;
		}
	}
	
	return addr;
}

int VariableLengthBuffer :: Init ()
 // construct with a maximum of maxFields
{
	Clear();
	return TRUE;
}

