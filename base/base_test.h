#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

/*
c_test.cpp
*/
struct CNode
{
    CNode * next;
    CNode * pre;
    int value;
};

void sizoffunc(char str[100]);

void test_sizeof();
void test_strlen();

void get_memory1(char * p);
void get_memory2(char * p);
void get_memory3(char * p);
void get_memory4(char * p);

void test_memory();
void test_trans();
char * strcpy(char * strDest,const char * strSrc);
void test_strcpy();
void test_bubbleSort();
void test_chose();
CNode * cross_link(CNode *pHead1,CNode* pHead2);
bool cycle_link(CNode * pHead);
void test_link();


/*
c_puzzle.cpp
*/

void test_std_out();