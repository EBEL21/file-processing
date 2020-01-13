//textind.cc
#pragma warning (disable:4996)
#include "textind.h"
#include <iostream>
#include <string>

TextIndex:: TextIndex (int maxKeys, int unique)
	: NumKeys (0), Keys(0), RecAddrs(0)
{Init (maxKeys, unique);}

TextIndex :: ~TextIndex ()
{delete Keys; delete RecAddrs;}

int TextIndex :: Insert (const char * key, int recAddr)
{
	int i;
	int index = Find (key);
	if (Unique && index >= 0) return 0; // key already in
	if (NumKeys == MaxKeys) return 0; //no room for another key
	for (i = NumKeys-1; i >= 0; i--)
	{
		if (strcmp(key, Keys[i])>0) break; // insert into location i+1
		Keys[i+1] = Keys[i];
		RecAddrs[i+1] = RecAddrs[i];
	}
	Keys[i+1] = strdup(key);
	RecAddrs[i+1] = recAddr;
	NumKeys ++;
	return 1;
}

int TextIndex :: Remove (const char * key)
{
	int index = Find (key);
	if (index < 0) return 0; // key not in index
	for (int i = index; i < NumKeys; i++)
	{
		Keys[i] = Keys[i+1];
		RecAddrs[i] = RecAddrs[i+1];
	}
	NumKeys --;
	return 1;
}

int TextIndex::Modify(const char * key, int newAddr)
{
	int index = Find(key);
	RecAddrs[index] = newAddr;
	return 1;
}

int TextIndex :: Search (const char * key) const
{
	int index = Find (key);
	if (index < 0) return index;
	return RecAddrs[index];
}

void TextIndex :: Print (ostream & stream) const
{
	stream << "Text Index max keys "<<MaxKeys
			<<" num keys "<<NumKeys<<endl;
	for (int i = 0; i<NumKeys; i++)
		stream <<"\tKey["<<i<<"] "<<Keys[i]
			<<" RecAddr "<<RecAddrs[i]<<endl;
}

int TextIndex::FirstRecAddr()
{
	curIdx = 0;
	return RecAddrs[0];
}

int TextIndex::NextRecAddr()
{
	++curIdx;
	if (curIdx == NumKeys) curIdx = 0;
	return RecAddrs[curIdx];
}

int TextIndex :: Find (const char * key) const
{
	int Left = 0;
	int Right = NumKeys - 1;
	while (Left <= Right) {
		int middle = (Left + Right) / 2;
		int result = strcmp(key, Keys[middle]);
		if (result == 0) { return middle; }
		else if (result > 0) {
			if (Left == middle) return -1;
			Left = middle;
		}
		else if (result < 0) {
			if (Right == middle) return -1;
			Right = middle;
		}
	}
	return -1;// not found
}

int TextIndex :: Init (int maxKeys, int unique)
{
	Unique = unique != 0;
	if (maxKeys <= 0) 
	{
		MaxKeys = 0;
		return 0;
	}
	MaxKeys = maxKeys;
	Keys = new char *[maxKeys];
	RecAddrs = new int [maxKeys];
	curIdx = 0;
	return 1;
}

