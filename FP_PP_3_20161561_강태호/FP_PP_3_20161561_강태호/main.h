#pragma once
#include "Member.h"
#include "NewsAgency.h"
#include "Subscription.h"
#include"recfile.h"
#include "btnode.h"
#include "btree.h"
#include <vector>

#define MAX_INPUT_LEN 30
#define MAX_MEMBER 2000
#define MAX_NEWSAGENCY 2000

int MemberTestEnable = 0;
int NewsAgencyTestEnable = 0;
int SubscriptionTestEnable = 0;

vector<Member> member_list;
vector<NewsAgency> news_agency_list;
vector<Subscription> subscription_list;

DelimFieldBuffer Memberbuffer('|', 256);
DelimFieldBuffer NewsAgencybuffer('|', 256);
DelimFieldBuffer Subscriptionbuffer('|', 256);

RecordFile<Member> MemberFile(Memberbuffer);
RecordFile<NewsAgency> NewsAgencyFile(NewsAgencybuffer);
RecordFile<Subscription> SubscriptionFile(Subscriptionbuffer);

Member curMember;

int BTree_created = 0;
const int BTreeSize = 4;
BTree<char> sub_BTree(BTreeSize);

char* member_dat_filename;
char* newsAgency_dat_filename;
char* subscription_dat_filename;

void init();

int showMember();
int showNewsAgency();
int showSubscription();
int MemberTest();
int NewsAgencyTest();
int SubscriptionTest();
int Login();
int CreateIndexFile();
int CreateSubBTree();

int NewsAgencySubscriptionSystem(); // not used in proj2 
int Admin_NASS();
int Member_NASS();
int Member_SubSys();

int SubscriptionSystem();

int command_search();
int search_member(string id); // not used in proj2 
int search_member_idx(string id, Member& m);
int search_newsAgency(const char* id); // not used in proj2 
int search_newsAgency_idx(const char* id);
int search_subscription(string id, int type, vector<int> &addrs);
int search_subscription_BTree(string id);

int command_Insert();
int insert_member();
int insert_newsAgency();
int insert_subscription(string id = string(""));
int insert_subscription_BTree();

int command_delete();
int delete_member(string id); // not used in proj2 
int delete_member_idx(string id);
int delete_newsAgency(const char* id); // not used in proj2 
int delete_newsAgency_idx(const char* id);
int delete_subscription(const char* id);
int delete_Member_subscription(const char* id, vector<int> addrs);
int delete_subscription_BTree(string id);

int command_modify();
int modify_member(string id = string(""));
int modify_newsAgency();
int modify_subscription();
int modify_Member_subscription(const char* id, vector<int> addrs);
int modify_subscription_BTree();