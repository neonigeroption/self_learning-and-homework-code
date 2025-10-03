//
// Created by neo niger on 25-9-27.
//

#ifndef 线性表函数_H
#define 线性表函数_H
#include <iostream>
using namespace std;
typedef struct Node{
    int data;
    Node* next;
}Node,*LinkList;

void InitList(LinkList &L) {
    L = new Node;
    L -> next = nullptr;
}

void CreateListtail(LinkList &L,int arr[],int n) {
    Node *r = L;
    for (int i=0;i<n;i++) {
        Node *p = new Node;
        p->data = arr[i];
        p->next = nullptr;
        r->next = p;
        r = p;
    }
}

void PrintList(LinkList L) {
    Node *p = L->next;
    while (p!=nullptr) {
        cout<<p->data<<" ";
        p = p->next;
    }
    cout<<endl;
}

void DeleteList(LinkList &L) {
    Node*  cur = L;
    Node*  nextnode = nullptr;
    while (cur!=nullptr) {
        nextnode = cur->next;
        delete cur;
        cur = nextnode;
    }

    L = nullptr;
}

#endif //线性表函数_H
