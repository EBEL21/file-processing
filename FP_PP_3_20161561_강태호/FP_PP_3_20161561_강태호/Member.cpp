#include "Member.h"
#include <sstream>

Member::Member()
{
}

Member::Member(string id) {
	update_ID(id);
}


Member & Member::operator=(const Member m)
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	update_ID(m.ID);
	update_PW(m.Password);
	update_Name(m.Name);
	update_PN(m.Phone_Number);
	update_Address(m.Address);
	update_Mileage(m.Mileage);
	update_Level(m.Level);
	return *this;
}

bool Member::operator==(const Member& m) {
	if (ID.compare(m.ID.c_str()) == 0) {
		return true;
	}
	else {
		return false;
	}
}

bool Member::operator!=(const Member& m) {
	if (ID.compare(m.ID.c_str()) == 0) {
		return false;
	}
	else {
		return true;
	}
}

istream & operator>>(istream & is, Member &m) {
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
	m.update_ID(token);
	getline(iss, token, '|');
	m.update_PW(token);
	getline(iss, token, '|');
	m.update_Name(token);
	getline(iss, token, '|');
	m.update_PN(token);
	getline(iss, token, '|');
	m.update_Address(token);
	getline(iss, token, '|');
	m.update_Mileage(token.data());
	getline(iss, token);
	m.update_Level(token.data());

	return is;
}

ostream & operator << (ostream &os, Member &m) {

	cout << "******************************" << endl;
	os << "ID : " << m.ID << endl;
	os << "Password : " << m.Password << endl;
	os << "Name : " << m.Name << endl;
	os << "Phone Number : " << m.Phone_Number << endl;
	os << "Address : " << m.Address << endl;
	os << "Mileage : " << m.Mileage << endl;
	os << "Level : " << m.Level << endl;
	cout << "******************************" << endl;
	return os;
}

void Member::update_ID(const string new_id)
{
	ID = new_id;
}

void Member::update_PW(const string new_pw)
{
	Password = new_pw;
}

void Member::update_Name(const string new_name)
{
	Name = new_name;
}

void Member::update_PN(const string new_pn)
{
	Phone_Number = new_pn;
}

void Member::update_Address(const string new_address)
{
	Address = new_address;
}

void Member::update_Mileage(const char * new_mileage)
{
	memcpy(Mileage, new_mileage, LEN_MIL);
}

void Member::update_Level(const char* new_level)
{
	memcpy(Level, new_level, LEN_LEVEL);
}

bool Member::Pack(IOBuffer & Buffer) const
{
	int numBytes;

	Buffer.Clear();

	string s_mil(Mileage, LEN_MIL);
	string s_level(Level, LEN_LEVEL);

	numBytes = Buffer.Pack(ID.c_str());
	if (numBytes == -1) return false;
	numBytes = Buffer.Pack(Password.c_str());
	if (numBytes == -1) return false;
	numBytes = Buffer.Pack(Name.c_str());
	if (numBytes == -1) return false;
	numBytes = Buffer.Pack(Phone_Number.c_str());
	if (numBytes == -1) return false;
	numBytes = Buffer.Pack(Address.c_str());
	if (numBytes == -1) return false;
	numBytes = Buffer.Pack(s_mil.c_str());
	if (numBytes == -1) return false;
	numBytes = Buffer.Pack(s_level.c_str());
	if (numBytes == -1) return false;

	return true;
}

bool Member::Unpack(IOBuffer &Buffer)
{
	int numBytes;
	char buf[256];

	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1) return false;
	ID = buf;

	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1) return false;
	Password = buf;

	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1) return false;
	Name = buf;

	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1) return false;
	Phone_Number = buf;

	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1) return false;
	Address = buf;

	numBytes = Buffer.Unpack(Mileage, LEN_MIL);
	if (numBytes == -1) return false;

	numBytes = Buffer.Unpack(Level, LEN_LEVEL);
	if (numBytes == -1) return false;

	return true;
}

char * Member::Key()
{
	memcpy(key, ID.c_str(), ID.size());
	return key;
}

bool Member::checkPassword(string pw)
{
	return Password == pw;
}

int Member::getLevel()
{
	return (int)(Level[0] - '0');
}
