// fvarlen.h
#ifndef VARLEN_H
#define VARLEN_H

#include <stdlib.h>
#include <iostream>
#include "iobuffer.h"

class VariableLengthBuffer: public IOBuffer
// Abstract class designed to support variablelength records
// Fields may be of a variety of types
//   
{  public:
	VariableLengthBuffer (int MaxBytes = 1000);
	VariableLengthBuffer (const VariableLengthBuffer & buffer) // copy constructor
		: IOBuffer(buffer){}

	void Clear (); // clear fields from buffer
	int Read (istream &);
	int Write (ostream &) const;
	int Delete(ostream & , int) const;
	int ReadHeader (istream &); // write a buffer to the stream
	int WriteHeader (ostream &) const; // write a buffer to the stream
	int PackFixLen (void *, int);
	int PackDelimeted (void *, int);
	int PackLength (void *, int);
	void Print (ostream &) const;
	int SizeOfBuffer () const; // return current size of buffer
	int FindSpace(istream &, int*, int*, unsigned short*);

 	int Init ();
 protected:
	 const char deletion_mark = '*';
};

#endif
