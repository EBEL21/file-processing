#include "Subscription.h"
#include <sstream>

Subscription::Subscription()
{
}

Subscription::Subscription(const char * sub_id)
{
	update_sub_id(sub_id);
}

Subscription & Subscription::operator=(const Subscription m)
{
	update_sub_id(m.Subscription_ID);
	update_na_id(m.NewsAgency_ID);
	update_member_id(m.Member_ID);
	update_mileage(m.Mileage);
	return *this;
}

bool Subscription::operator==(const Subscription& m) {
	if (strcmp(this->Subscription_ID, m.Subscription_ID) == 0) {
		return true;
	}
	else {
		return false;
	}
}

bool Subscription::operator!=(const Subscription& m) {
	if (strcmp(this->Subscription_ID, m.Subscription_ID) == 0) {
		return false;
	}
	else {
		return true;
	}
}

istream & operator>>(istream & is, Subscription & m)
{
	string st;
	is.exceptions(istream::failbit | istream::badbit);

	try {
		getline(is, st);
	}
	catch (istream::failure e) {
		return is;
	}

	istringstream iss(st);
	string token;

	getline(iss, token, '|');
	m.update_sub_id(token.data());
	getline(iss, token, '|');
	m.update_na_id(token.data());
	getline(iss, token, '|');
	m.update_member_id(token);
	getline(iss, token);
	m.update_mileage(token.data());

	return is;
}

ostream & operator << (ostream &os, Subscription & m) {

	os << "******************************" << endl;
	os << "Subscription ID : " << m.Subscription_ID << endl;
	os << "News AgencyID : " << m.NewsAgency_ID << endl;
	os << "Member ID : " << m.Member_ID << endl;
	os << "Mileage : " << m.Mileage << endl;
	os << "******************************" << endl;
	return os;
}

void Subscription::update_sub_id(const char * new_sub_id)
{
	memcpy(Subscription_ID, new_sub_id, LEN_SUB_ID);
}

void Subscription::update_na_id(const char * new_na_id)
{
	memcpy(NewsAgency_ID, new_na_id, LEN_NA_ID);
}

void Subscription::update_member_id(const string new_member_id)
{
	Member_ID = new_member_id;
}

void Subscription::update_mileage(const char * new_mileage)
{
	memcpy(Mileage, new_mileage, LEN_MIL);
}

char Subscription::Key()
{
	int i = 0;
	int key = 0;
	for (i = 0; i < LEN_SUB_ID; i++) {
		if (Subscription_ID[i] != 0) { break; }
	}
	key = atoi(Subscription_ID + i);
	return (char)key;
}

bool Subscription::Pack(IOBuffer & Buffer) const
{
	int numBytes;

	Buffer.Clear();
	
	string s_sub_id(Subscription_ID, LEN_SUB_ID);
	string s_na_id(NewsAgency_ID, LEN_NA_ID);
	string s_mil(Mileage, LEN_MIL);

	numBytes = Buffer.Pack(s_sub_id.c_str());
	if (numBytes == -1) return false;
	numBytes = Buffer.Pack(s_na_id.c_str());
	if (numBytes == -1) return false;
	numBytes = Buffer.Pack(Member_ID.c_str());
	if (numBytes == -1) return false;
	numBytes = Buffer.Pack(s_mil.c_str());
	if (numBytes == -1) return false;

	return true;
}

bool Subscription::Unpack(IOBuffer &Buffer)
{
	int numBytes;
	char buf[256];

	numBytes = Buffer.Unpack(Subscription_ID, LEN_SUB_ID);
	if (numBytes == -1) return false;

	numBytes = Buffer.Unpack(NewsAgency_ID, LEN_NA_ID);
	if (numBytes == -1) return false;

	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1) return false;
	Member_ID = buf;

	numBytes = Buffer.Unpack(Mileage, LEN_MIL);
	if (numBytes == -1) return false;

	return true;
}
