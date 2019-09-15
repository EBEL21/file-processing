#pragma warning (disable:4996)

#include <iostream>
#include <string>
#include<cstring>

using namespace std;


class Member {
private:

public:
	string ID;
	string Password;
	string Name;
	string Phone_Number;
	string Address;
	char Mileage[10];

	Member()
	{
	}

	Member(string _ID, string _Password, string _Name,
		string _Phone_Number, string _Address, const char _Mileage[10])
	{
		this->ID = _ID;
		this->Password = _Password;
		this->Name = _Name;
		this->Phone_Number = _Phone_Number;
		this->Address = _Address;
		strcpy(this->Mileage, _Mileage);
	}

	Member& operator = (Member m);
	bool operator == (Member& m);
	bool operator != (Member& m);


	friend istream & operator >> (istream &is, Member & m);
	friend ostream & operator << (ostream &os, Member & m);


};

Member & Member::operator=(Member m)
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	Member new_member = Member();
	new_member.ID = m.ID;
	new_member.Password = m.Password;
	new_member.Name = m.Name;
	new_member.Phone_Number = m.Phone_Number;
	new_member.Address = m.Address;
	strcpy(new_member.Mileage, m.Mileage);

	return new_member;
}

bool Member::operator==(Member& m) {
	if (this->ID.compare(m.ID) == 0) {
		return true;
	}
	else {
		return false;
	}
}

bool Member::operator!=(Member& m) {
	if (this->ID.compare(m.ID) == 0) {
		return false;
	}
	else {
		return true;
	}
}


istream & operator>>(istream & is, Member &m) {
	return is;
}

ostream & operator << (ostream &os, Member &m) {

	cout << m.ID << "|" << m.Password << "|" << m.Name << "|" << m.Phone_Number << "|" << m.Address
		<< "|" << m.Mileage;
	return os;
}



class NewsAgency {
private:

public:
	char NewsAgency_ID[16];
	string Name;
	string Address;

	NewsAgency& operator = (NewsAgency m);
	bool operator == (NewsAgency& m);
	bool operator != (NewsAgency& m);

	friend istream & operator >> (istream &is, NewsAgency & m);
	friend ostream & operator << (ostream &os, NewsAgency & m);
};

NewsAgency & NewsAgency::operator=(NewsAgency m)
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	NewsAgency new_NewsAgency = NewsAgency();
	
	strcpy(new_NewsAgency.NewsAgency_ID, m.NewsAgency_ID);
	new_NewsAgency.Name = m.Name;
	new_NewsAgency.Address = m.Address;

	return new_NewsAgency;
}

bool NewsAgency::operator==(NewsAgency& m) {
	if (strcmp(this->NewsAgency_ID, m.NewsAgency_ID) == 0) {
		return true;
	}
	else {
		return false;
	}
}

bool NewsAgency::operator!=(NewsAgency& m) {
	if (strcmp(this->NewsAgency_ID,m.NewsAgency_ID) == 0) {
		return false;
	}
	else {
		return true;
	}
}

istream & operator>>(istream & is, NewsAgency & m)
{
	return is;
}

ostream & operator << (ostream &os, NewsAgency & m) {

	return os;
}

class Subscription {
private:
public:
	char Subscription_ID[16];
	char NewsAgency_ID[16];
	string Member_ID;
	char Mileage[10];

	Subscription& operator = (Subscription m);
	bool operator == (Subscription& m);
	bool operator != (Subscription& m);

	friend istream & operator >> (istream &is, Subscription & m);
	friend ostream & operator << (ostream &os, Subscription & m);
};

Subscription & Subscription::operator=(Subscription m)
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	Subscription new_Subscription = Subscription();

	strcpy(new_Subscription.Subscription_ID, m.Subscription_ID);
	strcpy(new_Subscription.NewsAgency_ID, m.NewsAgency_ID);
	new_Subscription.Member_ID = m.Member_ID;
	strcpy(new_Subscription.Mileage, m.Mileage);

	return new_Subscription;
}

bool Subscription::operator==(Subscription& m) {
	if (strcmp(this->Subscription_ID, m.Subscription_ID) == 0) {
		return true;
	}
	else {
		return false;
	}
}

bool Subscription::operator!=(Subscription& m) {
	if (strcmp(this->Subscription_ID, m.Subscription_ID) == 0) {
		return false;
	}
	else {
		return true;
	}
}

istream & operator>>(istream & is, Subscription & m)
{
	return is;
}

ostream & operator << (ostream &os, Subscription & m) {
	
	return os;
}

int main(void) {
	Member mem = Member(string("id"), string("pw"), string("name"), string("pn"), string("addr"), "000016595");
	cout << mem;

	return 0;
}