// FP_PP_2_20161561.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include "main.h"
#include "textind.h"
#include "tindbuff.h"
#include "buffile.h"
#include "indfile.h"


using namespace std;

inline bool FileExist(const char* filename) {
	struct stat buffer;
	return (stat(filename, &buffer) == 0);
}

int main()
{
	int command;
	init();

	while (true) {
		cout << "******************************" << endl;
		cout << "1. showMember" << endl;
		cout << "2. showNewsAgency" << endl;
		cout << "3. showSubscription" << endl;
		cout << "4. MemberTest" << endl;
		cout << "5. NewsAgencyTest" << endl;
		cout << "6. SubscriptionTest" << endl;
		cout << "7. NewsAgencySubscriptionSystem" << endl;
		cout << "8. quit" << endl;
		cout << "******************************" << endl;
		cout << endl << "input your command : ";
		cin >> command;
		if (cin.fail() || cin.bad()) {
			cout << "Wrong command!" << endl;
			cin.clear();
			cin.ignore(256, '\n');
		}
		if (command == 8) {
			break;
		}
		else if (command == 1) {
			showMember();
		}
		else if (command == 2) {
			showNewsAgency();
		}
		else if (command == 3) {
			showSubscription();
		}
		else if (command == 4) {
			if (MemberTestEnable) {
				MemberTest();
			}
			else {
				cout << "Error: showMember를 먼저 실행해야 합니다!" << endl;
			}
		}
		else if (command == 5) {
			if (NewsAgencyTestEnable) {
				NewsAgencyTest();
			}
			else {
				cout << "Error: showNewsAgency를 먼저 실행해야 합니다!" << endl;
			}
		}
		else if (command == 6) {
			if (SubscriptionTestEnable) {
				SubscriptionTest();
			}
			else {
				cout << "Error: showSubscription을 먼저 실행해야 합니다!" << endl;
			}
		}
		else if (command == 7) {
			CreateIndexFile();
			int mode = Login();
			if (mode == 1) {
				Admin_NASS();
			}
			else if (mode == 9) {
				Member_NASS();
			}
			else {
				cout << "Login Fail!" << endl;
			}
		}
	}
}

void init()
{
	member_dat_filename = (char *)malloc(18);
	memcpy(member_dat_filename, "fileOfMember.dat\0", 18);

	newsAgency_dat_filename = (char *)malloc(22);
	memcpy(newsAgency_dat_filename, "fileOfNewsAgency.dat\0", 22);

	subscription_dat_filename = (char *)malloc(24);
	memcpy(subscription_dat_filename, "fileOfSubscription.dat\0", 24);
}

int showMember() {
	ifstream ifs("listOfMember.txt");
	if (ifs.fail()) {
		cout << "File Open error!" << endl;
		return -1;
	}

	int n;
	ifs >> n;
	ifs.ignore(numeric_limits<streamsize>::max(), '\n');

	for (int i = 0; i < n; i++) {
		Member m;
		ifs >> m;
		if (i < 10) {
			cout << m;
		}
		member_list.push_back(m);
	}

	Member m1 = member_list[0];
	Member m2 = member_list[1];

	if (m1 == m1) cout << "'==' works well!" << endl;
	if (m1 != m2) cout << "'!=' works well!" << endl;

	Member m3;
	m3 = m1;
	cout << m3;
	cout << "'=' works well!" << endl;

	cout << "showMember 종료!" << endl;
	MemberTestEnable = 1;
	return 1;
}

int showNewsAgency() {
	ifstream ifs("listOfNewsAgency.txt");
	if (ifs.fail()) {
		cout << "File Open error!" << endl;
		return -1;
	}

	int n;
	ifs >> n;
	ifs.ignore(numeric_limits<streamsize>::max(), '\n');

	for (int i = 0; i < n; i++) {
		NewsAgency na;
		ifs >> na;
		if (i < 10) {
			cout << na;
		}
		news_agency_list.push_back(na);
	}

	NewsAgency na1 = news_agency_list[0];
	NewsAgency na2 = news_agency_list[1];

	if (na1 == na1) cout << "'==' works well!" << endl;
	if (na1 != na2) cout << "'!=' works well!" << endl;

	NewsAgency na3;
	na3 = na1;
	cout << na3;
	cout << "'=' works well!" << endl;

	cout << "showNewsAgency 종료!" << endl;
	NewsAgencyTestEnable = 1;
	return 1;
}

int showSubscription() {
	ifstream ifs("listOfSubscription.txt");
	if (ifs.fail()) {
		cout << "File Open error!" << endl;
		return -1;
	}

	int n;
	ifs >> n;
	ifs.ignore(numeric_limits<streamsize>::max(), '\n');

	for (int i = 0; i < n; i++) {
		Subscription s;
		ifs >> s;
		if (i < 10) {
			cout << s;
		}
		subscription_list.push_back(s);
	}
	Subscription s1 = subscription_list[0];
	Subscription s2 = subscription_list[1];

	if (s1 == s1) cout << "'==' works well!" << endl;
	if (s1 != s2) cout << "'!=' works well!" << endl;

	Subscription s3;
	s3 = s1;
	cout << s3;
	cout << "'=' works well!" << endl;

	cout << "showSubscription 종료!" << endl;
	SubscriptionTestEnable = 1;
	return 1;
}

int MemberTest() {

	// Wirte Test
	MemberFile.Create(member_dat_filename, ios::out | ios::trunc);
	for (int i = 0; i < (int)member_list.size(); i++) {
		Member m = member_list[i];
		int recaddr;
		if ((recaddr = MemberFile.Write(m)) == -1) {
			cout << "Write Error!" << endl;
			return 0;
		}
		else {
			cout << "Write at " << recaddr << endl;
		}
	}
	MemberFile.Close();

	//Read Test
	cout << "상위 10개의 Member 정보 출력." << endl;
	MemberFile.Open(member_dat_filename, ios::in);
	for (int i = 0; i < 10; i++) {
		Member m;
		MemberFile.Read(m);
		cout << m;
	}
	MemberFile.Close();
	cout << "MemberTest 종료!" << endl;
	return 1;
}

int NewsAgencyTest() {

	// Wirte Test
	NewsAgencyFile.Create(newsAgency_dat_filename, ios::out | ios::trunc);
	for (int i = 0; i < (int)news_agency_list.size(); i++) {
		NewsAgency na = news_agency_list[i];
		int recaddr;
		if ((recaddr = NewsAgencyFile.Write(na)) == -1) {
			cout << "Write Error!" << endl;
			return 0;
		}
		else {
			cout << "Write at " << recaddr << endl;
		}
	}
	NewsAgencyFile.Close();

	//Read Test
	cout << "상위 10개의 News Agency 정보 출력." << endl;
	NewsAgencyFile.Open(newsAgency_dat_filename, ios::in);
	for (int i = 0; i < 10; i++) {
		NewsAgency na;
		NewsAgencyFile.Read(na);
		cout << na;
	}
	NewsAgencyFile.Close();

	cout << "NewsAgencyTest 종료!" << endl;

	return 1;
}

int SubscriptionTest() {

	// Wirte Test
	SubscriptionFile.Create(subscription_dat_filename, ios::out | ios::trunc);
	for (int i = 0; i < (int)subscription_list.size(); i++) {
		Subscription s = subscription_list[i];
		int recaddr;
		if ((recaddr = SubscriptionFile.Write(s)) == -1) {
			cout << "Write Error!" << endl;
			return 0;
		}
		else {
			cout << "Write at " << recaddr << endl;
		}
	}
	SubscriptionFile.Close();
	cout << "write end!" << endl;
	//Read Test
	cout << "상위 10개의 Subscription 정보 출력." << endl;
	SubscriptionFile.Open(subscription_dat_filename, ios::in);
	for (int i = 0; i < 10; i++) {
		Subscription s;
		SubscriptionFile.Read(s);
		cout << s << endl;
	}
	SubscriptionFile.Close();
	cout << "SubscriptionTest 종료!" << endl;
	return 1;
}

int Login()
{
	string id;
	string pw;
	cout << "로그인이 필요합니다." << endl;
	cin.clear();
	cin.ignore(256, '\n');
	cout << "ID: ";
	cin >> id;
	int result = search_member_idx(id, curMember);
	if (result == -1) {
		cout << "존재하지 않는 사용자입니다." << endl;
		return -1;
	}
	cout << "PW: ";
	cin >> pw;
	if (curMember.checkPassword(pw)) {
		return curMember.getLevel();
	}
	else { return -1; }
}

int CreateIndexFile()
{
	if (!FileExist("fileOfMember.ind")) {
		cout << "create fileOfMember.ind" << endl;
		TextIndex MemberIndex(MAX_MEMBER);
		// 멤버 데이터 파일을 읽어서 인덱스 생성
		MemberFile.Open(member_dat_filename, ios::in);
		while (1) {
			Member m;
			int recaddr = MemberFile.Read(m);
			if (recaddr == -1) break;
			//cout << m.Key() << endl;
			MemberIndex.Insert(m.Key(), recaddr);
		}
		MemberFile.Close();

		//생성한 멤버 인덱스를 파일로 저장
		TextIndexBuffer MemIdxbuf(MAX_ID_LEN, MAX_MEMBER);
		BufferFile MemIdxFile(MemIdxbuf);
		MemIdxFile.Create((char *)"fileOfMember.ind\0", ios::out | ios::trunc);
		MemIdxFile.Rewind();
		MemIdxbuf.Pack(MemberIndex);
		int result = MemIdxFile.Write();
		MemIdxFile.Close();
	}
	if (!FileExist("fileOfNewsAgency.ind")) {
		cout << "create fileOfNewsAgency.ind" << endl;
		TextIndex NewsIndex(MAX_NEWSAGENCY);

		//언론사 데이터 파일을 읽어서 인덱스 생성
		NewsAgencyFile.Open(newsAgency_dat_filename, ios::in);
		while (1) {
			NewsAgency na;
			int recaddr = NewsAgencyFile.Read(na);
			if (recaddr == -1) break;
			NewsIndex.Insert(na.Key(), recaddr);
		}
		NewsAgencyFile.Close();

		//생성한 언론사 인덱스를 파일로 저장
		TextIndexBuffer NAIdxbuf(LEN_NA_ID, MAX_NEWSAGENCY);
		BufferFile NAIdxFile(NAIdxbuf);
		NAIdxFile.Create((char *)"fileOfNewsAgency.ind\0", ios::out | ios::trunc);
		NAIdxFile.Rewind();
		NAIdxbuf.Pack(NewsIndex);
		int result = NAIdxFile.Write();
		NAIdxFile.Close();
	}
	return 1;
}

int NewsAgencySubscriptionSystem() {

	int command = 0;
	while (true) {
		cout << "******************************" << endl;
		cout << "1. Search" << endl;
		cout << "2. Insert" << endl;
		cout << "3. Delete" << endl;
		cout << "4. Modify" << endl;
		cout << "5. go back" << endl;
		cout << "******************************" << endl;
		cout << endl << "input your command : ";
		cin >> command;
		if (cin.fail() || cin.bad()) {
			cout << "Wrong command!" << endl;
			cin.clear();
			cin.ignore(256, '\n');
		}
		if (command == 5) return 0;
		switch (command) {
		case 1:
			command_search();
			break;
		case 2:
			command_Insert();
			break;
		case 3:
			command_delete();
			break;
		case 4:
			command_modify();
			break;
		default:
			cout << "Wrong command!" << endl;
			break;
		}
	}
	return 1;
}

int Admin_NASS()
{
	int command = 0;
	while (1) {
		cout << "******************************" << endl;
		cout << "*        관리자 모드         *" << endl;
		cout << "******************************" << endl;
		cout << "1. 검색" << endl;
		cout << "2. 삽입" << endl;
		cout << "3. 삭제" << endl;
		cout << "4. 수정" << endl;
		cout << "5. 나가기" << endl;
		cout << "******************************" << endl;
		cout << endl << "input your command : ";
		cin >> command;
		if (cin.fail() || cin.bad()) {
			cout << "Wrong command!" << endl;
			cin.clear();
			cin.ignore(256, '\n');
		}
		if (command == 5) return 0;
		switch (command) {
		case 1:
			command_search();
			break;
		case 2:
			command_Insert();
			break;
		case 3:
			command_delete();
			break;
		case 4:
			command_modify();
			break;
		default:
			cout << "Wrong command!" << endl;
			break;
		}
	}
	return 0;
}

int Member_NASS()
{
	int command = 0;
	int result = 0;
	string id;
	while (1) {
		cout << "******************************" << endl;
		cout << "*         회원 모드          *" << endl;
		cout << "******************************" << endl;
		cout << "1. 내 정보 수정" << endl;
		cout << "2. 언론사 보기" << endl;
		cout << "3. 내 구독" << endl;
		cout << "4. 탈퇴" << endl;
		cout << "5. 로그아웃" << endl;
		cout << "******************************" << endl;
		cout << endl << "input your command : ";
		cin >> command;
		if (cin.fail() || cin.bad()) {
			cout << "Wrong command!" << endl;
			cin.clear();
			cin.ignore(256, '\n');
		}
		if (command == 5) return 0;
		else if (command == 1) {
			modify_member(curMember.getId());
		}
		else if (command == 2) {
			char id[LEN_NA_ID] = { '\0', };
			cout << "Search NewsAgency for id: ";
			cin >> id;
			if (strlen(id) != LEN_NA_ID - 1) {
				cout << "Error: News Agency ID는 10개의 숫자형식입니다!" << endl;
			}
			result = search_newsAgency_idx(id);
			if (result == -1) cout << "No Found!" << endl;
		}
		else if (command == 3) {
			result = Member_SubSys();
		}
		else if (command == 4) {
			delete_member_idx(curMember.getId());
			curMember = Member();
			return 0;
		}
		else {
			cout << "Wrong command!" << endl;
		}
	}
	return 0;
}

int Member_SubSys()
{
	int result = 0, command = 0;
	string input;
	vector<int> addrs;
	int count = 0;
	cout << "내 구독 목록" << endl;
	count = search_subscription(curMember.getId(), 1, addrs);
	if (addrs.size() == 0) {
		result = -1;
	}
	if (result == -1) {
		cout << "No Found!" << endl;
		return result;
	}
	cout << "Find " << addrs.size() << endl;
	while (1) {
		cout << "******************************" << endl;
		cout << "*         구독 관리          *" << endl;
		cout << "******************************" << endl;
		cout << "1. 내 구독 목록" << endl;
		cout << "2. 새 구독 추가" << endl;
		cout << "3. 구독 수정" << endl;
		cout << "4. 기존 구독 해제" << endl;
		cout << "5. 뒤로" << endl;
		cout << "******************************" << endl;
		cout << endl << "input your command : ";
		cin >> command;
		if (cin.fail() || cin.bad()) {
			cout << "Wrong command!" << endl;
			cin.clear();
			cin.ignore(256, '\n');
		}
		if (command == 1) {
			cout << "내 구독 목록" << endl;
			addrs.clear();
			count = search_subscription(curMember.getId(), 1, addrs);
			if (addrs.size() == 0) {
				result = -1;
			}
			if (result == -1) {
				cout << "No Found!" << endl;
			}
			else {
				cout << "Find " << addrs.size() << endl;
			}
		}
		else if (command == 2) {
			insert_subscription(curMember.getId());
		}
		else if (command == 3) {
			cout << "수정할 Subscription의 ID를 입력해주세요." << endl;
			input.clear();
			cin.clear();
			cin >> input;
			if (input.length() != LEN_SUB_ID - 1) {
				cout << "구독 ID는 16개의 숫자로 이루어져 있어야합니다!" << endl;
			}
			else {
				result = modify_Member_subscription(input.c_str(), addrs);
			}
		}
		else if (command == 4) {
			cout << "삭제할 구독 ID를 입력하세요" << endl;
			input.clear();
			cin.clear();
			cin >> input;
			if (input.length() != LEN_SUB_ID - 1) {
				cout << "구독 ID는 16개의 숫자로 이루어져 있어야합니다!" << endl;
			}
			else {
				result = delete_Member_subscription(input.c_str(), addrs);
			}
		}
		else if (command == 5) {
			break;
		}
		else {
			cout << "Wrong command!" << endl;
		}
	}
	return 1;
}

int command_search() {
	int type, result = 0;
	cout << "******************************" << endl;
	cout << "검색할 Class Type을 선택해주세요" << endl;
	cout << "1. Member" << endl;
	cout << "2. NewsAgency" << endl;
	cout << "3. Subscription" << endl;
	cout << "4. go back" << endl;
	cout << "******************************" << endl;
	cout << "input your command: ";
	cin >> type;
	if (cin.fail() || cin.bad()) {
		cout << "Wrong command!" << endl;
		cin.clear();
		cin.ignore(256, '\n');
	}
	if (type == 4) return 0;
	else if (type == 1) {
		string id;
		Member m;
		cout << "Search Member for id: ";
		cin >> id;
		result = search_member_idx(id, m);
		cout << m << endl;
		if (result == -1) cout << "No Found!" << endl;
	}
	else if (type == 2) {
		char id[LEN_NA_ID] = { '\0', };
		cout << "Search NewsAgency for id: ";
		cin >> id;
		if (strlen(id) != LEN_NA_ID - 1) {
			cout << "Error: News Agency ID는 10개의 숫자형식입니다!" << endl;
			return -1;
		}
		result = search_newsAgency_idx(id);
		if (result == -1) cout << "No Found!" << endl;
	}
	else if (type == 3) {
		char input[100] = { '\0', };
		vector<int> addrs;
		int count = 0;
		cout << "Search Subscription(Member_ID, NewsAgency_ID, Subscription_ID) " << endl;
		cin >> input;
		if (strlen(input) == LEN_SUB_ID-1) {
			count = search_subscription(input, 3, addrs);
			if (addrs.size() == 0) {
				count = search_subscription(input, 1, addrs);
				if (addrs.size() == 0) {
					result = -1;
				}
			}
		}
		else if (strlen(input) == LEN_NA_ID-1) {
			count = search_subscription(input, 2, addrs);
			if (addrs.size() == 0) {
				result = -1;
			}
		}
		else {
			count = search_subscription(input, 1, addrs);
			if (addrs.size() == 0) {
				result = -1;
			}
		}

		if (result == -1) cout << "No Found!" << endl;
		else cout << "Find "<< addrs.size() << endl;
	} else { cout << "Wrong command!" << endl; }
	return result;
}

int search_member(string id) {

	Member target(id);
	int recaddr = 0;

	MemberFile.Open(member_dat_filename, ios::in);
	while(recaddr != -1) {
		Member m;
		recaddr = MemberFile.Read(m);
		if (target == m) {
			//cout << "find!" << endl;
			cout << m;
			MemberFile.Close();
			curMember = m;
			return recaddr;
		}
	}
	MemberFile.Close();
	return -1;
}

int search_member_idx(string id, Member& m) {
	TextIndexedFile<Member> MemberIdxFile(Memberbuffer, MAX_ID_LEN, 2000);
	MemberIdxFile.Open((char *)"fileOfMember");
	char m_id[20] = { '\0' };
	memcpy(m_id, id.c_str(), id.size());
	int result = MemberIdxFile.Read((char*)m_id, m);
	MemberIdxFile.Close();
	return result;
}

int search_newsAgency(const char* id) {

	NewsAgency target(id);

	int recaddr = 0;
	NewsAgencyFile.Open(newsAgency_dat_filename, ios::in);
	while (recaddr != -1) {
		NewsAgency na;
		recaddr = NewsAgencyFile.Read(na);
		if (target == na) {
			cout << na;
			NewsAgencyFile.Close();
			return recaddr;
		}
	}
	NewsAgencyFile.Close();
	return -1;
}

int search_newsAgency_idx(const char * id)
{
	TextIndexedFile<NewsAgency> NewsIdxFile(NewsAgencybuffer, LEN_NA_ID, MAX_NEWSAGENCY);
	NewsIdxFile.Open((char *)"fileOfNewsAgency");
	NewsAgency na;
	int result = NewsIdxFile.Read((char*)id, na);
	if (result != -1) {
		cout << na << endl;
	}
	NewsIdxFile.Close();
	return result;
}

/*
type 1: find by member_id
type 2: find by newsAgency_id
type 3: find by subscription_id
*/
int search_subscription(string id, int type, vector<int> &addrs) {

	int recaddr = 0;
	SubscriptionFile.Open(subscription_dat_filename, ios::in);
	while(recaddr != -1) {
		Subscription s;
		recaddr = SubscriptionFile.Read(s);
		if (recaddr == -1) break;
		switch (type)
		{
		case 1:
			if (id.compare(s.get_member_id()) == 0) {
				addrs.push_back(recaddr);
				cout << s;
			}
			break;
		case 2:
			if (id.compare(s.get_newsAgency_id()) == 0) {
				addrs.push_back(recaddr);
				cout << s;
			}
			break;
		case 3:
			if (id.compare(s.get_subscription_id()) == 0) {
				addrs.push_back(recaddr);
				cout << s;
			}
			break;
		default:
			break;
		}
	}
	SubscriptionFile.Close();
	return (int)addrs.size();
}

int command_Insert() {

	int type, result = 0;
	cout << "******************************" << endl;
	cout << "추가할 Class Type을 선택해주세요" << endl;
	cout << "1. Member" << endl;
	cout << "2. NewsAgency" << endl;
	cout << "3. Subscription" << endl;
	cout << "4. go back" << endl;
	cout << "******************************" << endl;
	cin >> type;
	if (cin.fail() || cin.bad()) {
		cout << "Wrong command!" << endl;
		cin.clear();
		cin.ignore(256, '\n');
	}
	if (type == 4) return 0;
	else if (type == 1) {
		result = insert_member();
	}
	else if (type == 2) {
		result = insert_newsAgency();
	}
	else if (type == 3) {
		result = insert_subscription();
	}
	return result;
}

int insert_member()
{
	int result;
	Member m;
	string input;
	cout << "*****INSERT NEW MEMBER*****" << endl;
	cout << "ID: ";
	cin.ignore(MAX_INPUT_LEN, '\n');
	cin.clear();
	cin >> input;
	if (input.length() > MAX_ID_LEN) return -1;
	if (search_member_idx(input, m) != -1) {
		cout << "Error: 같은 ID의 Member가 이미 존재합니다!" << endl;
		return -1;
	}
	m.update_ID(input);
	input.clear();
	cin.clear();

	cout << "PASSWORD: ";
	cin >> input;
	m.update_PW(input);
	input.clear();
	cin.clear();

	cout << "NAME: ";
	cin >> input;
	m.update_Name(input);
	input.clear();
	cin.clear();

	cout << "PHONE NUMBER: ";
	cin >> input;
	m.update_PN(input);
	input.clear();
	cin.clear();

	cout << "ADDRESS: ";
	cin >> input;
	m.update_Address(input);
	input.clear();
	cin.clear();

	cout << "MILEAGE: ";
	cin >> input;
	if (input.length() != LEN_MIL - 1) {
		cout << "Error: Mileage는 10개의 숫자형식입니다!" << endl;
		return -1;
	}
	m.update_Mileage(input.c_str());
	input.clear();
	cin.clear();
	m.update_Level("9\0");

	//m.Pack(Memberbuffer);

	TextIndexedFile<Member> MemberIdxFile(Memberbuffer, MAX_ID_LEN, 2000);
	MemberIdxFile.Open((char *)"fileOfMember");
	/*MemberFile.Open(member_dat_filename, ios::out);
	result = MemberFile.Append(m);*/
	result = MemberIdxFile.Append(m);
	cout << result << endl;
	//MemberFile.Close();
	return 0;
}

int insert_newsAgency()
{
	int result;
	string input;
	cout << "*****INSERT NEW NEWS AGENCY*****" << endl;
	cout << "ID: ";
	cin.ignore(100, '\n');
	cin >> input;
	if (input.length() != LEN_NA_ID - 1) {
		cout << "News Agency ID는 12개의 숫자로 이루어져야 합니다." << endl;
		return -1;
	}
	if (search_newsAgency_idx(input.c_str()) != -1) {
		cout << "Error: 같은 ID의 News Agency가 이미 존재합니다!" << endl;
		return -1;
	}

	NewsAgency na(input.c_str());

	cin.clear();
	input.clear();

	cout << "NAME: ";
	cin >> input;
	na.update_name(input);

	cin.clear();
	input.clear();

	cout << "ADDRESS: ";
	cin >> input;
	na.update_address(input);

	na.Pack(NewsAgencybuffer);

	TextIndexedFile<NewsAgency> NewsIdxFile(NewsAgencybuffer, LEN_NA_ID, MAX_NEWSAGENCY);
	NewsIdxFile.Open((char *)"fileOfNewsAgency");
	result = NewsIdxFile.Append(na);
	/*NewsAgencyFile.Open(newsAgency_dat_filename, ios::out);
	result = NewsAgencyFile.Append(na);*/
	cout << result << endl;
	//NewsAgencyFile.Close();
	return 0;
}

int insert_subscription(string id)
{
	int result;
	string input;
	vector<int> addrs;
	cout << "*****INSERT NEW SUBSCRIPTION*****" << endl;
	cout << "SUBSCRIPTION ID: ";
	cin.clear();
	cin.ignore(MAX_INPUT_LEN, '\n');
	getline(cin, input);
	if (input.length() != LEN_SUB_ID - 1) {
		cout << "구독 ID는 16개의 숫자로 이루어져야합니다!" << endl;
		return -1;
	}

	result = search_subscription(input, 3, addrs);
	if(addrs.size() != 0) { 
		cout << "Error: 같은 ID의 Subscription이 이미 존재합니다!" << endl;
		return -1;
	}

	Subscription s(input.c_str());
	
	cin.clear();
	input.clear();

	cout << "NEWS AGENCY ID: ";
	getline(cin, input);
	if (input.length() != LEN_NA_ID - 1) return -1;
	if (search_newsAgency(input.c_str()) == -1) {
		cout << "Error: 해당 News Agency가 존재하지 않습니다. ID: " << input << endl;
		return - 1;
	}

	s.update_na_id(input.c_str());
	
	cin.clear();
	input.clear();

	if (id.size() == 0) {
		cout << "MEMBER ID: ";
		getline(cin, input);
		Member m;
		if (search_member_idx(input, m) == -1) {
			cout << "Error: 해당 Member가 존재하지 않습니다. ID: " << input << endl;
			return -1;
		}
	}
	else {
		input = id;
	}
	s.update_member_id(input);
	
	cin.clear();
	input.clear();

	cout << "MILEAGE: ";
	getline(cin, input);
	if (input.length() != LEN_MIL - 1) {
		cout << "Error: Mileage는 10개의 숫자형식입니다!" << endl;
		return -1;
	}
	s.update_mileage(input.c_str());

	s.Pack(Subscriptionbuffer);

	SubscriptionFile.Open(subscription_dat_filename, ios::out);
	result = SubscriptionFile.Append(s);
	cout << result << endl;
	SubscriptionFile.Close();
	return 0;
}

int command_delete() {
	int type, result = 0;
	cout << "******************************" << endl;
	cout << "삭제할 Class Type을 선택해주세요" << endl;
	cout << "1. Member" << endl;
	cout << "2. NewsAgency" << endl;
	cout << "3. Subscription" << endl;
	cout << "4. go back" << endl;
	cout << "******************************" << endl;
	cin >> type;
	if (cin.fail() || cin.bad()) {
		cout << "Wrong command!" << endl;
		cin.clear();
		cin.ignore(256, '\n');
	}
	if (type == 4) return 0;
	else if (type == 1) {
		string id;
		cout << "Input Member ID to Delete: ";
		cin >> id;
		result = delete_member_idx(id);
		if (result == -1) cout << "Delete Fail!" << endl;
		else cout << "Delete Member Success!" << endl;
	}
	else if (type == 2) {
		string id;
		cout << "Input NewsAgency ID to Delete: ";
		cin.ignore(MAX_INPUT_LEN, '\n');
		getline(cin, id);
		if (id.length() != LEN_NA_ID - 1) {
			cout << "Error: News Agency ID는 12개의 숫자형식입니다!" << endl;
		}
		else {
			result = delete_newsAgency_idx(id.c_str());
			if (result == -1) cout << "Delete Fail!" << endl;
			else cout << "Delete NewsAgency Success!" << endl;
		}
	}
	else if (type == 3) {
		string id;
		cout << "Input Subscription ID to Delete: ";
		cin.ignore(MAX_INPUT_LEN, '\n');
		getline(cin, id);
		if (id.length() != LEN_SUB_ID - 1) {
			cout << "Error: Subscription ID는 16개의 숫자형식입니다!" << endl;
		}
		else {
			//cout << id << endl;
			result = delete_subscription(id.c_str());
			if (result == -1) cout << "Delete Fail!" << endl;
			else cout << "Delete Subscription Success!" << endl;
		}
	}
	return result;
}

int delete_member(string id) {
	int result, recaddr;
	vector<int> addrs;
	recaddr = search_member(id);
	if (recaddr == -1) return -1;
	result = MemberFile.Open(member_dat_filename, ios::out);
	if (result != -1) {
		result = MemberFile.Delete(recaddr);
	}
	MemberFile.Close();

	//subscription에서 member정보있는거 삭제
	result = search_subscription(id, 1, addrs);
	result = SubscriptionFile.Open(subscription_dat_filename, ios::out);
	if (result == -1) { return result; }
	for (int i = 0; i < (int)addrs.size(); i++) {
		result = SubscriptionFile.Delete(addrs[i]);
		if (result == -1) return -1;
	}
	result = SubscriptionFile.Close();
	if (result == -1) return -1;
	return result;
}

int delete_member_idx(string id)
{
	vector<int> addrs;
	TextIndexedFile<Member> MemberIdxFile(Memberbuffer, MAX_ID_LEN, 2000);
	MemberIdxFile.Open((char *)"fileOfMember");
	char m_id[20] = { '\0' };
	memcpy(m_id, id.c_str(), id.size());
	int result = MemberIdxFile.Delete((char*)m_id);
	MemberIdxFile.Close();

	//subscription에서 member정보있는거 삭제
	result = search_subscription(id, 1, addrs);
	result = SubscriptionFile.Open(subscription_dat_filename, ios::out);
	if (result == -1) { return result; }
	for (int i = 0; i < (int)addrs.size(); i++) {
		result = SubscriptionFile.Delete(addrs[i]);
		if (result == -1) return -1;
	}
	result = SubscriptionFile.Close();
	if (result == -1) return -1;
	return result;
}

int delete_newsAgency(const char * id)
{
	int result, recaddr;
	vector<int> addrs;
	recaddr = search_newsAgency(id);
	if (recaddr == -1) return -1;
	result = NewsAgencyFile.Open(newsAgency_dat_filename, ios::out);
	if (result != -1) {
		result = NewsAgencyFile.Delete(recaddr);
	}
	NewsAgencyFile.Close();
	//subscription에서 NewsAgency 정보있는거 삭제
	search_subscription(id, 2, addrs);
	result = SubscriptionFile.Open(subscription_dat_filename, ios::out);
	if (result == -1) { SubscriptionFile.Close(); return result; }
	for (int i = 0; i < (int)addrs.size(); i++) {
		result = SubscriptionFile.Delete(addrs[i]);
		if (result == -1) { SubscriptionFile.Close(); return -1; }
	}
	result = SubscriptionFile.Close();
	if (result == -1) return -1;
	return result;
}

int delete_newsAgency_idx(const char * id)
{
	vector<int> addrs;
	//NewsAgency index, data 삭제
	TextIndexedFile<NewsAgency> NewsIdxFile(NewsAgencybuffer, LEN_NA_ID, MAX_NEWSAGENCY);
	NewsIdxFile.Open((char *)"fileOfNewsAgency");
	NewsAgency na;
	int result = NewsIdxFile.Delete((char*)id);
	cout << na;
	NewsIdxFile.Close();

	//subscription에서 NewsAgency 정보있는거 삭제
	search_subscription(id, 2, addrs);
	result = SubscriptionFile.Open(subscription_dat_filename, ios::out);
	if (result == -1) { SubscriptionFile.Close(); return result; }
	for (int i = 0; i < (int)addrs.size(); i++) {
		result = SubscriptionFile.Delete(addrs[i]);
		if (result == -1) { SubscriptionFile.Close(); return -1; }
	}
	result = SubscriptionFile.Close();
	if (result == -1) return -1;
	return result;
}

int delete_subscription(const char * id)
{
	int result;
	vector<int> addrs;
	result = search_subscription(id, 3, addrs);
	//if (addrs.size() == 0) return -1;
	result = SubscriptionFile.Open(subscription_dat_filename, ios::out);
	if (result != -1) {
		result = SubscriptionFile.Delete(addrs[0]);
	}
	SubscriptionFile.Close();
	return result;
}

int delete_Member_subscription(const char * id, vector<int> addrs)
{
	int i, result;
	Subscription s, target(id);
	result = SubscriptionFile.Open(subscription_dat_filename, ios::out);
	for (i = 0; i < (int)addrs.size(); i++) {
		result = SubscriptionFile.Read(s, addrs[i]);
		if (result == -1) { return -1; }
		if (target == s) break;
	}
	if (i != addrs.size()) {
		result = SubscriptionFile.Delete(addrs[i]);
		if (result != -1) cout << "구독 " << id <<" 가 해제되었습니다." << endl;
	}
	else {
		cout << "잘못된 Subscription ID입니다. 본인의 구독 ID인지 확인하세요." << endl;
		result = -1;
	}
	SubscriptionFile.Close();
	return result;
}

int command_modify() {

	int type, result = 0;
	cout << "******************************" << endl;
	cout << "수정할 Class Type을 선택해주세요" << endl;
	cout << "1. Member" << endl;
	cout << "2. NewsAgency" << endl;
	cout << "3. Subscription" << endl;
	cout << "4. go back" << endl;
	cout << "******************************" << endl;
	cin >> type;
	if (cin.fail() || cin.bad()) {
		cout << "Wrong command!" << endl;
		cin.clear();
		cin.ignore(256, '\n');
	}
	if (type == 4) return 0;
	else if (type == 1) {
		result = modify_member();
	}
	else if (type == 2) {
		result = modify_newsAgency();
	}
	else if (type == 3) {
		result = modify_subscription();
	}
	return result;
}

int modify_member(string id)
{
	int result;
	string input;
	if (id.length() == 0) {
		cout << "수정할 Member의 ID를 입력해주세요." << endl;
		cin.ignore(MAX_INPUT_LEN, '\n');
		getline(cin, input);
		if (!cin.good()) return -1;
	}
	else {
		input = id;
		cin.ignore(MAX_INPUT_LEN, '\n');
	}
	/*addr = search_member(input);
	if (addr == -1) return -1;*/

	TextIndexedFile<Member> MemberIdxFile(Memberbuffer, MAX_ID_LEN, 2000);
	MemberIdxFile.Open((char *)"fileOfMember");
	Member m;
	MemberIdxFile.Read((char*)input.c_str(), m);
	cout << m << endl;
	/*result = MemberFile.Open(member_dat_filename, ios::in);
	if (result == -1) return -1;
	result = MemberFile.Read(m, addr);
	MemberFile.Close();*/
	cout << "Password의 수정값을 입력해주세요.(기존값 유지 '*')" << endl;
	input.clear();
	cin.clear();
	getline(cin, input);
	if (input != "*") {
		m.update_PW(input);
	}
	input.clear();
	cin.clear();

	cout << "Name의 수정값을 입력해주세요.(기존값 유지 '*')" << endl;
	getline(cin, input);
	if (input != "*") {
		m.update_Name(input);
	}
	input.clear();
	cin.clear();

	cout << "Phone Number의 수정값을 입력해주세요.(기존값 유지 '*')" << endl;
	getline(cin, input);
	if (input != "*") {
		m.update_PN(input);
	}
	input.clear();
	cin.clear();

	cout << "Address의 수정값을 입력해주세요.(기존값 유지 '*')" << endl;
	getline(cin, input);
	if (input != "*") {
		m.update_Address(input);
	}
	input.clear();
	cin.clear();

	cout << "Mileage의 수정값을 입력해주세요.(기존값 유지 '*')" << endl;
	getline(cin, input);
	if (input != "*") {
		if (input.length() != LEN_MIL - 1) {
			cout << "Error: Mileage는 10개의 숫자형식입니다!" << endl;
			return -1;
		}
		m.update_Mileage(input.c_str());
	}
	input.clear();

	/*result = MemberFile.Open(member_dat_filename, ios::out);
	if (result == -1) return -1;
	MemberFile.Update(m, addr);
	MemberFile.Close();*/
	result = MemberIdxFile.Update(m.Key(), m);
	MemberIdxFile.Close();

	return 1;
}

int modify_newsAgency()
{
	int result;
	string input;

	cout << "수정할 News Agency의 ID를 입력해주세요." << endl;
	cin.ignore(MAX_INPUT_LEN, '\n');
	getline(cin, input);
	if (!cin.good()) return -1;

	/*addr = search_newsAgency_idx(input.c_str());
	if (addr == -1) {
		cout << "Error: 해당 News Agency가 존재하지 않습니다. ID: " << input << endl;
		return -1;
	}*/
	
	TextIndexedFile<NewsAgency> NewsIdxFile(NewsAgencybuffer, LEN_NA_ID, MAX_NEWSAGENCY);
	NewsIdxFile.Open((char *)"fileOfNewsAgency");
	NewsAgency na;
	result = NewsIdxFile.Read((char*)input.c_str(), na);
	/*
	result = NewsAgencyFile.Open(newsAgency_dat_filename, ios::in);
	if (result == -1) return -1;
	result = NewsAgencyFile.Read(na, addr);
	NewsAgencyFile.Close();*/

	input.clear();
	cin.clear();
	cout << "Name의 수정값을 입력해주세요.(기존값 유지 '*')" << endl;
	getline(cin, input);
	if (input != "*") {
		na.update_name(input);
	}
	input.clear();
	cin.clear();

	cout << "Address의 수정값을 입력해주세요.(기존값 유지 '*')" << endl;
	getline(cin, input);
	if (input != "*") {
		na.update_address(input);
	}
	input.clear();

	/*result = NewsAgencyFile.Open(newsAgency_dat_filename, ios::out);
	if (result == -1) return -1;
	NewsAgencyFile.Update(na, addr);
	NewsAgencyFile.Close();*/
	NewsIdxFile.Update(na.Key(), na);
	NewsIdxFile.Close();

	return 1;
}

int modify_subscription()
{
	int result, addr;
	vector<int> addrs;
	string input;

	cout << "수정할 Subscription의 ID를 입력해주세요." << endl;
	cin.ignore(MAX_INPUT_LEN, '\n');
	getline(cin, input);
	if (!cin.good()) return -1;

	result = search_subscription(input, 3, addrs);
	if (addrs.size() == 0) {
		cout << "Error: 해당 Subscription이 존재하지 않습니다. ID: " << input << endl;
		return -1;
	}

	Subscription s;
	result = SubscriptionFile.Open(subscription_dat_filename, ios::in);
	if (result == -1) return -1;
	addr = SubscriptionFile.Read(s, addrs[0]);
	SubscriptionFile.Close();

	cout << addr << " " << addrs[0] << endl;

	input.clear();
	cin.clear();

	cout << "Member ID의 수정값을 입력해주세요.(기존값 유지 '*')" << endl;
	getline(cin, input);
	if (input != "*") {
		Member m;
		addr = search_member_idx(input,m);
		if (addr == -1) {
			cout << "Error: 해당 Member가 존재하지 않습니다. ID: " << input << endl;
			return -1;
		}
		s.update_member_id(input);
	}

	input.clear();
	cin.clear();

	cout << "News Agency ID의 수정값을 입력해주세요.(기존값 유지 '*')" << endl;
	getline(cin, input);
	if (input != "*") {
		if (input.length() != LEN_NA_ID - 1) {
			cout << "Error: News Agency ID는 12개의 숫자형식입니다!" << endl;
			return -1;
		}
		addr = search_newsAgency(input.c_str());
		if (addr == -1) {
			cout << "Error: 해당 News Agency가 존재하지 않습니다. ID: " << input << endl;
			return -1;
		}
		s.update_na_id(input.c_str());
	}

	input.clear();
	cin.clear();

	cout << "Mileage의 수정값을 입력해주세요.(기존값 유지 '*')" << endl;
	getline(cin, input);
	if (input != "*") {
		if (input.length() != LEN_MIL - 1) {
			cout << "Error: Mileage는 10개의 숫자형식입니다!" << endl;
			return -1;
		}
		s.update_mileage(input.c_str());
	}
	input.clear();

	cout << s << endl;

	result = SubscriptionFile.Open(subscription_dat_filename, ios::out);
	if (result == -1) return -1;
	result = SubscriptionFile.Update(s, addrs[0]);
	cout << "기록 주소: " << result << endl;
	SubscriptionFile.Close();

	return 1;
}

int modify_Member_subscription(const char * id, vector<int> addrs)
{
	int result, i;
	string input;

	Subscription s, target(id);
	result = SubscriptionFile.Open(subscription_dat_filename, ios::out);
	for (i = 0; i < (int)addrs.size(); i++) {
		result = SubscriptionFile.Read(s, addrs[i]);
		if (result == -1) { 
			return -1; 
		}
		if (target == s) break;
	}
	if (i == addrs.size()) {
		cout << "잘못된 Subscription ID입니다. 본인의 구독 ID인지 확인하세요." << endl;
		return -1;
	}

	cin.ignore(MAX_INPUT_LEN, '\n');
	cout << "News Agency ID의 수정값을 입력해주세요.(기존값 유지 '*')" << endl;
	cin >> input;
	if (input != "*") {
		if (input.length() != LEN_NA_ID - 1) {
			cout << "Error: News Agency ID는 12개의 숫자형식입니다!" << endl;
			return -1;
		}
		result = search_newsAgency_idx(input.c_str());
		if (result == -1) {
			cout << "Error: 해당 News Agency가 존재하지 않습니다. ID: " << input << endl;
			return -1;
		}
		s.update_na_id(input.c_str());
	}

	input.clear();
	cin.clear();

	cout << "Mileage의 수정값을 입력해주세요.(기존값 유지 '*')" << endl;
	cin >> input;
	if (input != "*") {
		if (input.length() != LEN_MIL - 1) {
			cout << "Error: Mileage는 10개의 숫자형식입니다!" << endl;
			return -1;
		}
		s.update_mileage(input.c_str());
	}
	input.clear();

	cout << s << endl;

	result = SubscriptionFile.Update(s, addrs[0]);
	cout << "기록 주소: " << result << endl;
	SubscriptionFile.Close();
	return 1;
}
