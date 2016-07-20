#ifndef _BList_H_
#define _BList_H_

#include <stdio.h>
#include<stdlib.h>
#include <stdint.h>


static const int moveCount = (sizeof(void*)-1)*8;

#define MAX_STEP ((size_t)0xff)

#define changeKeyNodeChildNum(ppNode, n) do{\
	void *tmp = *ppNode; \
	(*(void**)ppNode) = (void*)((long)(*ppNode) & ((long)tmp >> moveCount + n) << moveCount); \
}while (0)

//#define getNodeByKeyNode(pNode) ((pNode << 8) >> 8)
	

template<class TK, class TV>
class BList
{
public:
	
	class BLNode
	{
	public:
		BLNode(TK &k, TV &v, BLNode *pre, BLNode *next) : mKey(k), mData(v), mPre(pre), mNext(next)
		{
		}

		struct BLNode *mPre;
		struct BLNode *mNext;
		TK mKey;
		TV mData;
	};

	class KeyNode
	{
	public:
		KeyNode(BLNode *node) : mNode(node), mNodeNum(1)
		{

		}
		void setNode(BLNode *node)
		{
			this->mNode = node;
		}
		BLNode *getNode()
		{
			return this->mNode;
		}
		BLNode *mNode;
		size_t mNodeNum;
	};

	BList(size_t step) : mLen(0), mStep(step), mCap(0), mHead(0), mTail(0), mKeyNodeNum(0)
	{
		//this->mKeyNodes = (BLNode**)malloc(cap);
	}

	static BList *create(size_t step, size_t cap)
	{
		if (step > MAX_STEP)
		{
			return 0;
		}

		BList *p = new BList(step);
		return p;
	}

	TV *get(TK &k)
	{

	}

	BLNode *getNodeByKey(TK &k)
	{
		if (this->mLen == 0)
		{
			return 0;
		}
		else
		{
			BLNode *node = 0;
			size_t preBeginIdx = 0;
			size_t preEndIdx = this->mLen - 1;
			size_t idx = this->mLen / 2;
			while (preBeginIdx <= preEndIdx)
		}
	}

	void set(TK &&k, TV &&v)
	{
		if (this->mLen > 0)
		{
			BLNode *node = 0;
			size_t preBeginIdx = 0;
			size_t preEndIdx = this->mCap - 1;
			size_t idx = this->mCap / 2;
			while (preBeginIdx <= preEndIdx)
			{
				node = this->mKeyNodes[idx]->mNode;
				if (k < node->mKey)
				{
					if (idx > 0)
					{
						node = this->mKeyNodes[idx - 1]->mNode;
						if (k > node->mKey)
						{
							while (node->mNext && (k > node->mNext->mKey))
							{
								node = node->mNext;
							}
							BLNode *newNode = new BLNode(k, v, node, node->mNext);
							if (node->mNext)
							{
								node->mNext->mPre = newNode;
							}
							node->mNext = newNode;
							this->mLen++;
							break;
						}
						else
						{
							preEndIdx = idx;
							idx = (idx + preBeginIdx) / 2;
						}
					}
					else
					{
						BLNode *newNode = new BLNode(k, v, 0, node);
						node->mPre = newNode;
						this->mKeyNodes[0]->setNode(newNode);
						this->mKeyNodes[0]->mNodeNum++;
						this->mHead = newNode;
						this->mLen++;
						break;
					}
					
				}
				else if (k > node->mKey)
				{
					if (idx < (this->mCap - 1))
					{
						if (k < this->mKeyNodes[idx + 1]->mNode->mKey)
						{
							while (node->mNext && (k > node->mNext->mKey))
							{
								node = node->mNext;
							}
							BLNode *newNode = new BLNode(k, v, node, node->mNext);
							if (node->mNext)
							{
								node->mNext->mPre = newNode;
							}
							node->mNext = newNode;
							this->mLen++;
							break;
						}
						else
						{
							preBeginIdx = idx;
							idx = (idx + preEndIdx + 1) / 2;
						}
					}
					else
					{
						while (node->mNext && (k > node->mNext->mKey))
						{
							node = node->mNext;
						}
						BLNode *newNode = new BLNode(k, v, node, node->mNext);
						if (node->mNext)
						{
							node->mNext->mPre = newNode;
						}
						else
						{
							this->mTail = newNode;
						}
						node->mNext = newNode;
						this->mLen++;
						this->mKeyNodes[idx]->mNodeNum++;
						break;
					}
				}
				else if (k == node->mKey)
				{
					node->mData = v;
					break;
				}
			}
		}
		else
		{
			this->mLen++;
			this->mCap++; 
			BLNode *newNode = new BLNode(k, v, 0, 0);
			this->mKeyNodes = (KeyNode**)realloc(this->mKeyNodes, sizeof(KeyNode*) * this->mCap);
			this->mKeyNodes[0] = new KeyNode(newNode);
			this->mHead = this->mTail = newNode;
		}
	}

	void foreach(bool (*cb)(TV *v))
	{
		printf("*********************************\n");
		BLNode *curr = this->mHead;
		while (curr)
		{
			if (cb(&curr->mData))
			{
				if (curr->mNext)
				{
					curr->mNext->mPre = curr->mPre;
				}
				if (curr->mPre)
				{
					curr->mPre->mNext = curr->mNext;
				}
				BLNode *tmp = curr; 
				curr = curr->mNext;
				if (this->mHead == tmp)
				{
					this->mHead = curr;
				}
				if (this->mTail == tmp)
				{
					this->mTail = curr;
				}
				delete tmp;
			}
			else
			{
				curr = curr->mNext;
			}
		}
		printf("*********************************\n\n");
	}

	void deleByKey(TK &k)
	{

	}

	void deleByNode(BLNode &v)
	{

	}

	BLNode *head()
	{
		return this->mHead;
	}

	BLNode *tail()
	{
		return this->mTail;
	}

	void push(TK &k, TV &v)
	{

	}

	void pop()
	{

	}

	void resetKeyNode(BLNode **ppNode)
	{

	}

	BLNode *getNodeByKeyNode(BLNode *pNode)
	{
		return (BLNode*)(((long)pNode << 8) >> 8);
	}

	size_t mLen; 
	size_t mCap;
	size_t mStep;
	BLNode *mHead;
	BLNode *mTail;
	size_t mKeyNodeNum;
	KeyNode **mKeyNodes;
	
};




#endif // _BList_H_
