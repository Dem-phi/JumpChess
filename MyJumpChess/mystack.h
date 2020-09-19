#ifndef MYSTACK_H
#define MYSTACK_H
#include <iostream>
#include <piece.h>
#include "change.h"
//用来存储游戏中所有的走棋坐标
struct Node{
    change* step;   //change类
    Node* next;
};

class mystack
{
public:
    mystack();
    void push(change* p);   //压栈
    change* pop();          //弹栈
    change* front();        //获取栈顶元素
    int num;

protected:
    Node* head;
};

#endif // MYSTACK_H
