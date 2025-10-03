//
// Created by neo niger on 25-9-28.
//

#ifndef 实验一函数_H
#define 实验一函数_H
#include <iostream>
#include <string.h>
using namespace std;
typedef struct HNode
{
    char roomN[7];	//客房名称
    float Price;		//标准价格
    float PriceL;	//入住价格(默认值=标准价格*80%)
    int	Beds;		//床位数Beds
    char State[5];	//入住状态(值域："空闲"、"入住"、"预订"，默认值为"空闲")
    HNode  *next;//指针域
}Hotel, *HLink;
void Build(HLink &H){
    H = new HNode;
    H->next = nullptr;
    HNode* tail = H;
    FILE *fp = fopen("data.txt","r");
    HNode* cur_node = new HNode;
    while (fscanf(fp,"%s %f %d",cur_node->roomN,&cur_node->Price,&cur_node->Beds) == 3) {
        cur_node->PriceL = 0.8*cur_node->Price;
        strcpy(cur_node->State,"空闲");
        tail->next = cur_node;
        tail = cur_node;
        cur_node = new HNode;
    }
    delete cur_node;
    tail->next = nullptr;//转垃圾值为空，防止沿着H继续访问到内存崩溃！
    fclose(fp);
}
void Exp(HLink H) {
    HNode *p = H->next;
    while (p!=nullptr) {
        cout<<"客房名称"<<p->roomN<<endl;
        cout<<"标准价格"<<p->Price<<endl;
        cout<<"入住价格"<<p->PriceL<<endl;
        cout<<"床位数"<<p->Beds<<endl;
        cout<<"入住状态"<<p->State<<endl;
        cout<<endl;
        p = p->next;
    }
}
int Find(HLink &H, char *roomN) {
    HNode *f = H->next;
    int pos = 1;
    while (f!=nullptr&&strcmp(f->roomN,roomN)!=0) {
        pos++;
        f=f->next;
    }
    if (f == nullptr) return 0;
    else return pos;
}
void updateH(HLink &H, int beds, char *state) {
    HNode *u = H->next;
    while (u!=nullptr) {
        if (u->Beds == beds) {
            strcpy(u->State,state);
        }
        u=u->next;
    }
}
void Add(HLink &H) {
    HNode *a = H->next;
    while (a!=nullptr) {
        if (strcmp(a->State,"空闲") == 0) {
            a->PriceL *= 1.2;
        }
        a=a->next;
    }
}
/*
HLink FirstH(HLink &H) {
    if (H->next == nullptr) return nullptr;
    float maxprice = -1;
    HNode *h = H->next;
    while (h!=nullptr) {
        maxprice = max(maxprice,h->PriceL);
        h=h->next;
    }
    HNode *rh = H;
    while (rh->next!=nullptr) {
        if (rh->next->PriceL == maxprice) {
            HNode* target = rh->next;
            rh->next = target->next;//是断链不是删内存
            target->next = nullptr;//完全切断是好习惯
            return target;
        }
        rh=rh->next;
    }
}
*/
HLink FirstH(HLink &H) {
    if (H->next == nullptr) return nullptr;
    HNode *max = H->next;
    HNode *prv_max = H;
    HNode *fmax = H->next->next;
    HNode *prv_fmax = H->next;
    while (fmax!=nullptr) {
        if (fmax->PriceL>max->PriceL) {
            max = fmax;
            prv_max = prv_fmax;
        }
        prv_fmax = fmax;
        fmax = fmax->next;
    }
    prv_max->next = max->next;
    max->next = nullptr;
    return max;
}//指针记忆max,两次遍历变一次O(2*n)->O(n);
void MoveK1(HLink &H, int k) {
    HNode *tar = H;
    HNode *tar_plus_k = H;
    HNode *tail = H;
    while (tail->next!=nullptr) tail = tail->next;
    for (int i=0;i<k;i++) {
        tar_plus_k = tar_plus_k->next;
    }
    while (tar_plus_k->next!=nullptr) {
        tar_plus_k = tar_plus_k->next;
        tar = tar->next;
    }
    HNode *ori_head_next = H->next;
    HNode *mov_head_next = tar->next;
    tar->next = nullptr;//先断后连,简单清晰;
    H->next = mov_head_next;
    tail->next = ori_head_next;
}
void ReverseN2(HLink &H) {
    HNode *p = H;
    HNode *tar= H;
    while (p->next!=nullptr&&p->next->next!=nullptr) {
        p = p->next->next;
        tar = tar->next;
    }
    HNode *Half_head = tar->next;
    tar->next = nullptr;
    HNode *prv = nullptr;
    HNode *cur = Half_head;
    while (cur!=nullptr) {
        HNode* temp = cur->next;
        cur->next = prv;
        prv = cur;
        cur = temp;
    }
    tar->next = prv;
}
void SortPriceL(HLink &H) {
    HNode* sorted_H = new HNode;
    sorted_H->next = nullptr;
    HNode* tail = sorted_H;
    while (H->next != nullptr) {
        HNode* min = H->next;
        HNode* prv_min = H;
        HNode *fmin = H->next->next;
        HNode *prv_fmin = H->next;
        while (fmin != nullptr) {
            if (fmin->PriceL<min->PriceL||
                fmin->PriceL == min->PriceL&&
                strcmp(fmin->roomN,min->roomN)<0) {
                min = fmin;
                prv_min = prv_fmin;
            }
            prv_fmin = fmin;
            fmin = fmin->next;
        }
        prv_min->next = min->next;
        min->next = nullptr;
        tail->next = min;
        tail = min;
    }
    H->next = sorted_H->next;
    delete sorted_H;
}
void upBed(HLink &H,int beds) {
    HNode* node = new HNode;
    node->Beds = beds;
    cout<<"输入客房名称"<<endl;
    cin>>node->roomN;
    cout<<"输入标准价格"<<endl;
    cin>>node->Price;
    cout<<"输入入住价格"<<endl;
    cin>>node->PriceL;
    cout<<"输入入住状态"<<endl;
    cin>>node->State;

    HNode* grt_H = new HNode;
    grt_H->next = nullptr;
    HNode* grt_tail = grt_H;

    HNode* les_H = new HNode;
    les_H->next = nullptr;
    HNode* les_tail = les_H;
    while (H->next!=nullptr) {
        HNode* cur = H->next;
        H->next = cur->next;
        cur->next = nullptr;
        if (cur->Beds>beds) {
            grt_tail->next = cur;
            grt_tail = cur;
        }else {
            les_tail->next = cur;
            les_tail = cur;
        }
    }
    node->next = les_H->next;
    if (grt_H->next!=nullptr) {
        H->next = grt_H->next;
        grt_tail->next = node;
    }else {
        H->next = node;
    }
    delete grt_H;
    delete les_H;
}
void Merge(HLink &H1, HLink &H2) {
    HNode *pa = H1->next;
    HNode *pb = H2->next;
    HNode *temp;
    H1->next = nullptr;
    while (pa != nullptr&&pb != nullptr) {
        if (pa->PriceL<=pb->PriceL) {
            temp = pa->next;
            pa->next = H1->next;
            H1->next = pa;
            pa = temp;
        }else {
            temp = pb->next;
            pb->next = H1->next;
            H1->next = pb;
            pb = temp;
        }
    }

    while (pa != nullptr) {
        temp = pa->next;
        pa->next = H1->next;
        H1->next = pa;
        pa = temp;
    }

    while (pb != nullptr) {
        temp = pb->next;
        pb->next = H1->next;
        H1->next = pb;
        pb = temp;
    }
    H2->next = nullptr;
    delete H2;
}
#endif //实验一函数_H
