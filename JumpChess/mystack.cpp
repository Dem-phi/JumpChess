#include "mystack.h"

myStack::myStack(){
    head=NULL;
    num = 0;
}
//压栈操作
void myStack::push(Change* p){
    Node* node=new Node();
    node->step =p;
    if(head==NULL){
        head=node;
        node->next=NULL;
    }
    else{
        Node* end=head;
        node->next=end;
        head=node;
    }
    num++;
}
//弹栈操作
Change* myStack::pop(){
    if(head==NULL){
        return 0;
    }
    else{
        Change* p=head->step;
        Node* node=head;
        head=head->next;
        num--;
        delete node;
        return p;
    }

}
//获取栈顶元素
Change* myStack::front()
{
    return head->step;
}
