//btree.tc
#include "btnode.h"
#include "indbuff.h"
#include "btree.h"
#include <iostream>

const int MaxHeight = 5;
template <class keyType>
BTree<keyType>::BTree(int order, int keySize, int unique)
: Buffer (1+2*order,sizeof(int)+order*keySize+order*sizeof(int)),
	BTreeFile (Buffer), Root (order)
{
	Height = 1;
	Order = order;
	PoolSize = MaxHeight*2;
	Nodes = new BTNode * [PoolSize];
	BTNode::InitBuffer(Buffer,order);
	Nodes[0] = &Root;
}

template <class keyType>
BTree<keyType>::~BTree()
{
	Close();
	delete Nodes;
}

template <class keyType>
int BTree<keyType>::Open (char * name, int mode)
{
	int result;
	result = BTreeFile.Open(name, mode);
	if (!result) return result;
	// load root
	BTreeFile.Read(Root);
	Height = 1; // find height from BTreeFile!
	return 1;
}

template <class keyType>
int BTree<keyType>::Create (char * name, int mode)
{
	int result;
	result = BTreeFile.Create(name, mode);
	if (!result) return result;
	// append root node
	result = BTreeFile.Write(Root);
	Root.RecAddr=result;
	return result != -1;	
}

template <class keyType>
int BTree<keyType>::Close ()
{
	int result;
	result = BTreeFile.Rewind();
	if (!result) return result;
	result = BTreeFile.Write(Root);
	if (result==-1) return 0;
	return BTreeFile.Close();
}


template <class keyType>
int BTree<keyType>::Insert (const keyType key, const int recAddr)
{
	int result; int level = Height-1; 
	int newLargest=0; keyType prevKey, largestKey; 
	BTNode * thisNode, * newNode, * parentNode;
	thisNode = FindLeaf (key);

	// test for special case of new largest key in tree
	if (key > thisNode->LargestKey())
		{newLargest = 1; prevKey=thisNode->LargestKey();}

	result = thisNode -> Insert (key, recAddr);
	newNode = NULL;
	// handle special case of new largest key in tree
	if (newLargest)
		for (int i = 0; i<Height-1; i++) 
		{
			Nodes[i]->UpdateKey(prevKey,key);
			if (i>0) Store (Nodes[i]);
		}

	while (result==-1) // if overflow and not root
	{
		//remember the largest key
		largestKey=thisNode->LargestKey();
		// split the node
		newNode = NewNode();
		thisNode->Split(newNode);
		Store(thisNode); Store(newNode);
		level--; // go up to parent level
		if (level < 0) break;
		// insert newNode into parent of thisNode
		parentNode = Nodes[level];
		result = parentNode->UpdateKey
			(largestKey,thisNode->LargestKey());
		result = parentNode->Insert
			(newNode->LargestKey(),newNode->RecAddr);
		thisNode=parentNode;
	}
	Store(thisNode);
	if (level >= 0) return 1;// insert complete
	// else we just split the root
	int newAddr = BTreeFile.Append2(Root); // put previous root into file
	// insert 2 keys in new root node
	Root.Keys[0]=thisNode->LargestKey();
	Root.RecAddrs[0]=newAddr;
	Root.Keys[1]=newNode->LargestKey();
	Root.RecAddrs[1]=newNode->RecAddr;
	Root.NumKeys=2; 
	Height++;
	return 1;	
}

template <class keyType>
int BTree<keyType>::Remove (const keyType key, const int recAddr)
{
	BTNode *thisNode, *parentNode, *siblings;
	int level = Height - 1, isMax = 0 , result;
	thisNode = FindLeaf(key);

	// 삭제하려는 key가 노드의 max값이 아니면 그냥 삭제.
	if (key == thisNode->LargestKey()) {
		isMax = 1;
	}
	result = thisNode->Remove(key, Search(key));
	if (result == 0) return 0;
	// 삭제하려는 key가 노드의 max값이면 부모 node update 필요.
	if(isMax) {
		while (1) {
			level--;
			if (level < 0) break;
			parentNode = Nodes[level];
			if (!parentNode->UpdateKey(key, thisNode->LargestKey())) {
				break;
			}
			Store(parentNode);
		}
	}
	level = Height - 1;
	// 노드 n의 key 개수가 최소 개수일 때 underflow 발생.
	if (result == -1) {
		parentNode = Nodes[level - 1];
		int idx = parentNode->Find(thisNode->LargestKey());
		//cout << "idx: " << idx << endl;

		keyType oldkey;

		// 현재 node보다 작은 sibling과 합병 시도.
		if (idx > 0) {
			siblings = Fetch(parentNode->RecAddrs[idx - 1]);
			oldkey = siblings->LargestKey();
			cout << (char)oldkey << endl;
			if (siblings->Merge(thisNode)) {
				parentNode->Remove(thisNode->LargestKey());
				parentNode->UpdateKey(oldkey, siblings->LargestKey());
				Store(parentNode);
				Store(siblings);
				Store(thisNode);
				return 1;
			}
		}
		//현재 node보다 큰 sibling과 합병 시도.
		if (idx < parentNode->numKeys() - 1) {
			siblings = Fetch(parentNode->RecAddrs[idx + 1]);
			oldkey = thisNode->LargestKey();
			if (thisNode->Merge(siblings)) {
				parentNode->Remove(siblings->LargestKey());
				parentNode->UpdateKey(oldkey, thisNode->LargestKey());
				Store(parentNode);
				Store(siblings);
				Store(thisNode);
				return 1;
			}
		}
		// 여분의 키가 있는 node에서 재분배.
		//cout << "재분배" << endl;
		oldkey = thisNode->LargestKey();
		int recaddr = thisNode->Search(oldkey);
		//cout << "recaddr: " << recaddr << endl;
		thisNode->Remove(thisNode->LargestKey());
		while (1) {
			if (!parentNode->Remove(oldkey)) {
				break;
			}
			Store(parentNode);
			level--;
			if (level < 0) break;
			parentNode = Nodes[level];
		}
		Insert(oldkey, recaddr);
	}
	Store(thisNode);
	return 1;
}

template<class keyType>
int BTree<keyType>::Update(const keyType key, const int recAddr)
{
	BTNode* node;
	node = FindLeaf(key);
	node->Update(key, recAddr);
	Store(node);
	return 1;
}

template <class keyType>
int BTree<keyType>::Search (const keyType key, const int recAddr)
{
	BTNode * leafNode;
	leafNode = FindLeaf (key); 
	return leafNode -> Search (key, recAddr);
}

template <class keyType>
void BTree<keyType>::Print (ostream & stream) 
{
	stream << "BTree of height "<<Height<<" is "<<endl;
	Root.Print(stream);
	if (Height>1)
		for (int i = 0; i<Root.numKeys(); i++)
		{
			Print(stream, Root.RecAddrs[i], 2);
		}
	stream <<"end of BTree"<<endl;
}

template <class keyType>
void BTree<keyType>::Print 
	(ostream & stream, int nodeAddr, int level) 
{
	BTNode * thisNode = Fetch(nodeAddr);
	stream<<"Node at level "<<level<<" address "<<nodeAddr<<' ';
	thisNode -> Print(stream);
	if (Height>level)
	{
		level++;
		for (int i = 0; i<thisNode->numKeys(); i++)
		{
			Print(stream, thisNode->RecAddrs[i], level);
		}
		stream <<"end of level "<<level<<endl;
	}
}

template <class keyType>
BTreeNode<keyType> * BTree<keyType>::FindLeaf (const keyType key)
// load a branch into memory down to the leaf with key
{
	int recAddr, level;
	for (level = 1; level < Height; level++)
	{
		recAddr = Nodes[level-1]->Search(key,-1,0);//inexact search
		Nodes[level]=Fetch(recAddr);
	}
	return Nodes[level-1];
}

template <class keyType>
BTreeNode<keyType> * BTree<keyType>::NewNode ()
{// create a fresh node, insert into tree and set RecAddr member
	BTNode * newNode = new BTNode(Order);
	int recAddr = BTreeFile . Append2(*newNode);
	newNode -> RecAddr = recAddr;
	return newNode;
}

template <class keyType>
BTreeNode<keyType> * BTree<keyType>::Fetch(const int recaddr)
{// load this node from File into a new BTreeNode
	int result;
	BTNode * newNode = new BTNode(Order);
	result = BTreeFile.Read (*newNode, recaddr);
	if (result == -1) return NULL;
	newNode -> RecAddr = result;
	return newNode;
}

template <class keyType>
int BTree<keyType>::Store (BTreeNode<keyType> * thisNode)
{
	return BTreeFile.Write(*thisNode, thisNode->RecAddr);
}
