#include "NewsAgency.h"
#include<sstream>

NewsAgency::NewsAgency()
{
}

NewsAgency::NewsAgency(const char * id)
{
	update_id(id);
}

NewsAgency & NewsAgency::operator=(const NewsAgency m)
{
	update_id(m.NewsAgency_ID);
	update_name(m.Name);
	update_address(m.Address);
	return *this;
}

bool NewsAgency::operator==(const NewsAgency& m) {
	if (strcmp(this->NewsAgency_ID, m.NewsAgency_ID) == 0) {
		return true;
	}
	else {
		return false;
	}
}

bool NewsAgency::operator!=(const NewsAgency& m) {
	if (strcmp(this->NewsAgency_ID, m.NewsAgency_ID) == 0) {
		return false;
	}
	else {
		return true;
	}
}

istream & operator>>(istream & is, NewsAgency & m)
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
	m.update_id(token.data());
	getline(iss, token, '|');
	m.update_name(token);
	getline(iss, token);
	m.update_address(token);

	return is;
}

ostream & operator << (ostream &os, NewsAgency & m) {

	os << "******************************" << endl;
	os << "ID : " << m.NewsAgency_ID << endl;
	os << "Name : " << m.Name<< endl;
	os << "Address : " << m.Address << endl;
	os << "******************************" << endl;
	return os;
}

void NewsAgency::update_id(const char * new_id)
{
	memcpy(NewsAgency_ID, new_id, LEN_ID - 1);
}

void NewsAgency::update_name(const string new_name)
{
	Name = new_name;
}

void NewsAgency::update_address(const string new_addr)
{
	Address = new_addr;
}

bool NewsAgency::Pack(IOBuffer & Buffer) const
{
	int numBytes;

	Buffer.Clear();

	string s_na_id(NewsAgency_ID, LEN_ID);

	numBytes = Buffer.Pack(s_na_id.c_str());
	if (numBytes == -1) return false;
	numBytes = Buffer.Pack(Name.c_str());
	if (numBytes == -1) return false;
	numBytes = Buffer.Pack(Address.c_str());
	if (numBytes == -1) return false;

	return true;
}

bool NewsAgency::Unpack(IOBuffer &Buffer)
{
	int numBytes;
	char buf[256];

	numBytes = Buffer.Unpack(NewsAgency_ID, LEN_ID);
	if (numBytes == -1) return false;

	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1) return false;
	Name = buf;

	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1) return false;
	Address = buf;

	return true;
}

char * NewsAgency::Key()
{
	key.assign(NewsAgency_ID, LEN_ID - 1);
	return (char*)(key.c_str());
}
