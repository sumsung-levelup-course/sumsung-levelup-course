#include "pch.h"
#include <stdio.h>
const int SIZE = 30100;
const int HASH_SIZE = 5000;
int wantFind[SIZE][4];//각 블록마다 맞는 4가지의 모양을 저장

void rotate(int org[4][4], int made[4][4])
{
	made[0][3] = org[0][0];
	made[1][3] = org[0][1];
	made[2][3] = org[0][2];
	made[3][3] = org[0][3];
//------------------------------
	made[0][2] = org[1][0];
	made[1][2] = org[1][1];
	made[2][2] = org[1][2];
	made[3][2] = org[1][3];
//------------------------------
	made[0][1] = org[2][0];
	made[1][1] = org[2][1];
	made[2][1] = org[2][2];
	made[3][1] = org[2][3];
//------------------------------
	made[0][0] = org[3][0];
	made[1][0] = org[3][1];
	made[2][0] = org[3][2];
	made[3][0] = org[3][3];
//------------------------------
}
void make_Findlist(int block_idx, int minus_base[4][4])
{
	int made[4][4];
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			made[i][j] = heightof_[block_idx]-minus_base[i][3-j];
		}
	}
	for (int i = 0; i < 4; i++)
	{
		int tmp[4][4];
		for (int a = 0; a < 4; a++)
		{
			for (int b = 0; b < 4; b++)
			{
				tmp[a][b] = made[a][b];
			}
		}
		rotate(tmp, made);
		int hash = 0;
		for (int a = 0; a < 4; a++)
		{
			for (int b = 0; b < 4; b++)
			{
				hash = hash * 3 + made[a][b];
			}
		}
		wantFind[block_idx][i] = hash;
	}

}
struct Node {
	int base;
	int block_idx;
	int value; // 1~3^16;
	Node* next;
};
int baseof_[SIZE];
int heightof_[SIZE];
Node node[SIZE];
int node_idx = 0;
struct List {
	Node* head;
	int size;
	void add(int value, int idx)
	{
		Node* tmp = head;
		head = &node[node_idx++];
		head->next = tmp;
		head->value = value;
		head->block_idx = idx;
		size++;
	}
};
bool check[SIZE];
List hashTable[6][HASH_SIZE]; //base-1, hash값
struct mystruc {
	int hash;
	int base;
};
mystruc hashF(int block_idx,int mod[4][4])
{
	int base = 10;
	int minus_base[4][4];
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (mod[i][j] < base) base = mod[i][j];
		}
	}
	int hash = 0;
	int height = -1;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			minus_base[i][j] = mod[i][j] - base;
			if (height < minus_base[i][j]) height = minus_base[i][j];
			hash = hash * 3 + minus_base[i][j];
		}
	}
	heightof_[block_idx] = height;
	baseof_[block_idx] = base;
	make_Findlist(block_idx, minus_base);//wannaFind[blockidx][4]완성
	return { hash,base };
}
void init()
{
	node_idx = 0;
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < HASH_SIZE; j++)
		{
			hashTable[i][j].size = 0;
			hashTable[i][j].head = 0;
		}
	}
	for (int i = 0; i < SIZE; i++)
	{
		check[i] = false;
	}
}

int isEx(int k, int start, int hash_val) // 없으면 0 리턴, 있으면 사이즈리턴
{
	List address = hashTable[k][hash_val%HASH_SIZE];
	int s = address.size;
	if (s != 0)
	{
		Node* itr = address.head;
		if (itr->value == hash_val && itr->block_idx!=start)
		{
			if (!check[itr->block_idx])
			{
				check[itr->block_idx] = true;
				//printf("[%d] matched with ", itr->block_idx);
				return baseof_[itr->block_idx];
			}
		}
		for (int j = 1; j < s; j++)
		{
			itr = itr->next;
			if (itr->value == hash_val && itr->block_idx != start)
			{
				if (!check[itr->block_idx])
				{
					check[itr->block_idx] = true;
					//printf("[%d] matched with ", itr->block_idx); 
					return baseof_[itr->block_idx];
				}
			}
		}
	}
		
	return 0;
}
int makeBlock(int module[][4][4])
{//블록을 입력받아 완성품들의 높이의 최대합을 리턴
	init();
	int sum = 0;

	for (int i = 0; i < 30000; i++)
	{
		mystruc tmp = hashF(i,module[i]);
		hashTable[tmp.base-1][tmp.hash % HASH_SIZE].add(tmp.hash, i);

	}//해쉬테이블에 입력완료, wannafind완성
	//printf("해쉬테이블 입력완료, wannafind완성\n");
	for (int i = 0; i < 30000; i++)
	{
		if (!check[i])
		{
			for (int k = 5; k >= 0; k--)
			{
				bool find = false;

				for (int j = 0; j < 4; j++)
				{
					int before = sum;
					sum += isEx(k, i, wantFind[i][j]); // 없으면 0 리턴, 있으면 베이스리턴
					if (sum != before)
					{
						check[i] = true;
						sum += baseof_[i] + heightof_[i]; //높이더하기
						find = true;
						break;
						//printf("[%d]\n", i);
					}	

				}
				if (find) break;
			}
		}
	}
	return sum;
}
