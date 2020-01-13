#pragma once
#ifndef NEWSAGENCY_H
#define NEWSAGENCY_H

#include <iostream>
#include <string>
#include "delim.h"

#define LEN_ID 13

using namespace std;

class NewsAgency {
private:
	char NewsAgency_ID[LEN_ID] = { '\0', };
	string Name;
	string Address;
	string key;
public:

	NewsAgency();
	NewsAgency(const char* id);
	NewsAgency& operator = (const NewsAgency m);
	bool operator == (const NewsAgency& m);
	bool operator != (const NewsAgency& m);
	friend istream & operator >> (istream &is, NewsAgency & m);
	friend ostream & operator << (ostream &os, NewsAgency & m);

	// ��� ���� ����
	void update_id(const char *new_id);
	void update_name(const string new_name);
	void update_address(const string new_addr);

	bool Pack(IOBuffer &Buffer) const;
	bool Unpack(IOBuffer &);

	char * Key();
};

#endif