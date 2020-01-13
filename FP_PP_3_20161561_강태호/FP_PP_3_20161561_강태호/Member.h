#pragma once
#ifndef MEMBER_H
#define MEMBER_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "delim.h"

#define LEN_MIL 11
#define LEN_LEVEL 2

#define ADMIN_LEVEL 1
#define USER_LEVEL 9

#define MAX_ID_LEN 20
#define MAX_PW_LEN 20
#define MAX_NAME_LEN 20
#define MAX_PN_LEN 20
#define MAX_ADDR_LEN 20

using namespace std;


class Member {
private:
	string ID;
	string Password;
	string Name;
	string Phone_Number;
	string Address;
	char Level[LEN_LEVEL];
	char Mileage[LEN_MIL] = { '\0', };
	char key[MAX_ID_LEN] = { '\0', };
public:

	Member();
	Member(string id);
	Member& operator = (const Member m);
	bool operator == (const Member& m);
	bool operator != (const Member& m);
	friend istream & operator >> (istream &is, Member & m);
	friend ostream & operator << (ostream &os, Member & m);

	void update_ID(const string new_id);
	void update_PW(const string new_pw);
	void update_Name(const string new_name);
	void update_PN(const string new_pn);
	void update_Address(const string new_address);
	void update_Mileage(const char* new_mileage);
	void update_Level(const char* new_level);

	bool Pack(IOBuffer &Buffer) const;
	bool Unpack(IOBuffer &);

	char * Key();
	bool checkPassword(string pw);

	string getId() { return ID; }
	int getLevel();
};
#endif