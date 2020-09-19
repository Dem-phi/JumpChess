#include "mystack.h"

mystack::mystack()
{
    head = NULL;
    num = 0;
}

void mystack::push(change* p){
    Node* node=new Node();
    node->step = p;
    if(head == NULL){
        head = node;
        node->next = NULL;
    }
    else{
        Node* end = head;
        node->next = end;
        head = node;
    }
    num++;
}

change* mystack::pop(){
    if(head==NULL){
        return 0;
    }
    else {
        change* p = head->step;
        Node* node=head;
        head = head->next;
        num--;
        delete node;
        return p;
    }
}

change* mystack::front(){
    return head->step;
}

