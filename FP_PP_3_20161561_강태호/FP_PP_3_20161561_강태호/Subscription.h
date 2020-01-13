#pragma once
#ifndef SUBSCRIPTION_H
#define SUBSCRIPTION_H

#include <iostream>
#include <string>
#include<cstring>
#include "delim.h"

#define LEN_SUB_ID 17
#define LEN_NA_ID 13
#define LEN_MIL 11

using namespace std;

class Subscription {
private:
	char Subscription_ID[LEN_SUB_ID];
	char NewsAgency_ID[LEN_NA_ID];
	string Member_ID;
	char Mileage[LEN_MIL];
public:
	Subscription();
	Subscription(const char* sub_id);

	Subscription& operator = (const Subscription m);
	bool operator == (const Subscription& m);
	bool operator != (const Subscription& m);
	friend istream & operator >> (istream &is, Subscription & m);
	friend ostream & operator << (ostream &os, Subscription & m);

	void update_sub_id(const char* new_sub_id);
	void update_na_id(const char* new_na_id);
	void update_member_id(const string new_member_id);
	void update_mileage(const char* new_mileage);

	const char* get_subscription_id() { return Subscription_ID; }
	const char* get_newsAgency_id() { return NewsAgency_ID; }
	string get_member_id() { return Member_ID; }

	char Key();

	bool Pack(IOBuffer &Buffer) const;
	bool Unpack(IOBuffer &);
};
#endif