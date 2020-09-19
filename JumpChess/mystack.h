#ifndef MYSTACK_H
#define MYSTACK_H
#include<iostream>
#include"piece.h"
#include "change.h"
//栈用来存储游戏中所有的走棋坐标
struct Node{
    Change* step;   //Change类
    Node* next;     //下一个节点坐标
};
class myStack{
public:
    myStack();
    void push(Change* p);   //压栈
    Change* pop();          //弹栈
    Change* front();        //获取栈顶元素
    int num;
protected:
    Node* head;


};
#endif // MYSTACK_H
