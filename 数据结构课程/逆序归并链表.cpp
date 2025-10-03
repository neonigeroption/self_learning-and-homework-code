#include "线性表函数.h"
void MergeDescending(LinkList& La,LinkList&Lb,LinkList &Lc) {
    Node* pa = La->next;
    Node* pb = Lb->next;
    Node* temp;

    Lc = La;
    Lc -> next = nullptr;
    while (pa!=nullptr&&pb!=nullptr) {
        if (pa->data <= pb->data) {//小数头插
            temp = pa->next;
            pa->next = Lc->next;
            Lc->next = pa;
            pa  = temp;
        }
        else{
            temp = pb->next;
            pb->next = Lc->next;
            Lc->next = pb;
            pb = temp;
        }
    }

    while (pa != nullptr) {
        temp = pa->next;
        pa->next = Lc->next;
        Lc->next = pa;
        pa  = temp;
    }
    while (pb != nullptr) {
        temp = pb->next;
        pb->next = Lc->next;
        Lc->next = pb;
        pb = temp;
    }

    delete Lb;
}//链表逆序归并
/*int main() {
    int arr1[] = {1,3,5};
    int arr2[] = {2,4,6};
    LinkList La,Lb;
    InitList(La);
    InitList(Lb);
    CreateListtail(La,arr1,sizeof(arr1)/sizeof(int));
    CreateListtail(Lb,arr2,sizeof(arr2)/sizeof(int));
    LinkList Lc;
    MergeDescending(La, Lb, Lc);
    cout << "合并后的降序链表 Lc: ";
    PrintList(Lc);
    DeleteList(Lc);
    PrintList(Lc);
}*/