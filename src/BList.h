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
			//this->mNode = (BLNode*)((long)node | 1);
			this->mNode = node;
		}
		BLNode *getNode()
		{
			//return (BLNode*)((long)this->mNode & 0xFFFFFFFFFFFFFFF0);
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

	void checkNeedAddKeyNode(size_t idx, BLNode *node)
	{
		if (this->mKeyNodes[idx]->mNodeNum >= this->mStep)
		{
			this->mKeyNodeNum++;
			if (this->mKeyNodeNum > this->mCap)
			{
				this->mCap++;
				this->mKeyNodes = (KeyNode**)realloc(this->mKeyNodes, sizeof(KeyNode*) * this->mCap);	
			}
			if (idx < (this->mKeyNodeNum - 2))
			{
				memmove(this->mKeyNodes + 1, this->mKeyNodes + 2, sizeof(KeyNode*)* (this->mKeyNodeNum - idx - 2));
			}
			this->mKeyNodes[idx + 1] = new KeyNode(node);
			this->mKeyNodes[idx]->mNodeNum--;
			
		}

	}

	TV *get(TK &k)
	{

	}

	void set(TK &&k, TV &&v)
	{
		if (this->mLen > 0)
		{
			BLNode *node = 0;
			size_t preBeginIdx = 0;
			size_t preEndIdx = this->mKeyNodeNum - 1;
			size_t idx = this->mKeyNodeNum / 2;
			while (preBeginIdx <= preEndIdx)
			{
				node = this->mKeyNodes[idx]->getNode();
				if (k < node->mKey)
				{
					if (idx > 0)
					{
						node = this->mKeyNodes[idx - 1]->getNode();
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
							this->checkNeedAddKeyNode(idx, newNode);
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
						this->checkNeedAddKeyNode(idx, newNode);
						break;
					}
					
				}
				else if (k > node->mKey)
				{
					if (idx < (this->mKeyNodeNum - 1))
					{
						if (k < this->mKeyNodes[idx + 1]->getNode()->mKey)
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
							this->checkNeedAddKeyNode(idx, newNode);
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
						this->checkNeedAddKeyNode(idx, newNode);
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
			this->mKeyNodeNum++;
			this->mHead = this->mTail = newNode;
		}
	}

	void foreach(bool (*cb)(TV *v))
	{
		printf("*********************************\n");
		size_t kNodeIdx = 0;
		BLNode *curr = this->mHead;
		while (curr)
		{
			if ((kNodeIdx+1 < this->mKeyNodeNum) && curr == this->mKeyNodes[kNodeIdx + 1]->getNode())
			{
				kNodeIdx++;
			}
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
					this->mTail = 0;
				}
				delete tmp;
				this->mKeyNodes[kNodeIdx]->mNodeNum--;
				if (this->mKeyNodes[kNodeIdx]->mNodeNum == 0)
				{
					delete this->mKeyNodes[kNodeIdx];
					memmove(this->mKeyNodes + kNodeIdx, this->mKeyNodes + kNodeIdx + 1, sizeof(KeyNode*)*(this->mKeyNodeNum - kNodeIdx - 1));
					this->mKeyNodeNum--;
					kNodeIdx--;
				}
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

	size_t mLen; 
	size_t mCap;
	size_t mStep;
	BLNode *mHead;
	BLNode *mTail;
	size_t mKeyNodeNum;
	KeyNode **mKeyNodes;
	
};




#endif // _BList_H_
