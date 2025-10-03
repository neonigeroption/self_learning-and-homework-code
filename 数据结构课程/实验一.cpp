#include "实验一函数.h"
#include <iostream>
#include <limits>

using namespace std;
void PrintSingleNode(HLink node, const char* message) {
    if (node != nullptr) {
        cout << message << endl;

        printf("房名:%-7s, 标价:%-8.1f, 入住价:%-8.1f, 床位数:%d, 状态:%s\n",
               node->roomN, node->Price, node->PriceL, node->Beds, node->State);
    } else {
        cout << "操作返回了一个空节点指针!" << endl;
    }
}


void DestroyList(HLink &H) {
    if (H == nullptr) return;
    HNode* p = H->next;
    while (p != nullptr) {
        HNode* temp = p;
        p = p->next;
        delete temp;
    }
    delete H;
    H = nullptr;
}


void showMenu() {
    cout << "\n========== 客房管理系统 ==========" << endl;
    cout << "1.  (重新)创建客房链表 (Build)" << endl;
    cout << "2.  显示所有客房信息 (Exp)" << endl;
    cout << "3.  查找指定客房 (Find)" << endl;
    cout << "4.  修改客房状态 (updateH)" << endl;
    cout << "5.  给空闲客房加价 (Add)" << endl;
    cout << "6.  查找并移除最高价客房 (FirstH)" << endl;
    cout << "7.  移动链表后k个节点 (MoveK1)" << endl;
    cout << "8.  倒置链表后半部分 (ReverseN2)" << endl;
    cout << "9.  排序客房 (SortPriceL)" << endl;
    cout << "10. 按床位插入新客房 (upBed)" << endl;
    cout << "11. 合并两个有序链表 (Merge)" << endl;
    cout << "0.  退出程序" << endl;
    cout << "==================================" << endl;
    cout << "请输入你的选择: ";
}

int main() {
    HLink H1 = nullptr, H2 = nullptr;
    int choice;

    cout << "程序初始化：从文件 data.txt 创建主链表 H1..." << endl;
    Build(H1);
    Exp(H1);

    do {
        showMenu();


        while (!(cin >> choice)) {
            cout << "输入无效，请输入一个数字: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1: {
                cout << "\n--- 1. (重新)创建客房链表 ---" << endl;
                DestroyList(H1); // 重新创建前先销毁旧的链表，防止内存泄漏
                Build(H1);
                cout << "链表 H1 已重新创建。" << endl;
                Exp(H1);
                break;
            }
            case 2: {
                cout << "\n--- 2. 显示所有客房信息 ---" << endl;
                Exp(H1);
                break;
            }
            case 3: {
                cout << "\n--- 3. 查找指定客房 ---" << endl;
                char room_to_find[7];
                cout << "请输入要查找的客房名称: ";
                cin >> room_to_find;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 清空缓冲区

                int pos = Find(H1, room_to_find);
                if (pos > 0) {
                    cout << "结果: 客房 " << room_to_find << " 找到了, 位置在: " << pos << endl;
                } else {
                    cout << "结果: 客房 " << room_to_find << " 不存在。" << endl;
                }
                break;
            }
            case 4: {
                cout << "\n--- 4. 修改客房状态 ---" << endl;
                int beds;
                char state[5];
                cout << "请输入要修改的客房床位数: ";
                cin >> beds;
                cout << "请输入新的状态 (如: 预订): ";
                cin >> state;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                updateH(H1, beds, state);
                cout << "修改后的链表内容：" << endl;
                Exp(H1);
                break;
            }
            case 5: {
                cout << "\n--- 5. 给空闲客房加价 ---" << endl;
                Add(H1);
                cout << "加价后的链表内容：" << endl;
                Exp(H1);
                break;
            }
            case 6: {
                cout << "\n--- 6. 查找并移除最高价客房 ---" << endl;
                HLink highest_node = FirstH(H1);
                PrintSingleNode(highest_node, "找到并移除了入住价格最高的客房:");
                cout << "\n处理后的链表内容：" << endl;
                Exp(H1);
                delete highest_node;
                break;
            }
            case 7: {
                cout << "\n--- 7. 移动链表后k个节点 ---" << endl;
                int k;
                cout << "请输入要移动的 k 值: ";
                cin >> k;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                MoveK1(H1, k);
                cout << "移动后的链表内容：" << endl;
                Exp(H1);
                break;
            }
            case 8: {
                cout << "\n--- 8. 倒置链表后半部分 ---" << endl;
                ReverseN2(H1);
                cout << "倒置后的链表内容：" << endl;
                Exp(H1);
                break;
            }
            case 9: {
                cout << "\n--- 9. 排序客房 ---" << endl;
                SortPriceL(H1);
                cout << "排序后的链表内容：" << endl;
                Exp(H1);
                break;
            }
            case 10: {
                cout << "\n--- 10. 按床位插入新客房 ---" << endl;
                int new_beds;
                cout << "请输入新客房的床位数: ";
                cin >> new_beds;
                upBed(H1, new_beds);
                cout << "插入并重组后的链表内容：" << endl;
                Exp(H1);
                break;
            }
            case 11: {
                cout << "\n--- 11. 合并两个有序链表 ---" << endl;
                cout << "创建一个新的链表 H2 用于合并..." << endl;
                Build(H2);
                cout << "为了满足合并前提，先对 H1 和 H2 分别排序：" << endl;
                SortPriceL(H1);
                SortPriceL(H2);
                cout << "排序后的 H1:" << endl; Exp(H1);
                cout << "排序后的 H2:" << endl; Exp(H2);
                cout << "\n执行合并操作 Merge(H1, H2)..." << endl;
                Merge(H1, H2);
                cout << "合并后 (非递增排序) 的 H1 内容：" << endl;
                Exp(H1);
                H2 = nullptr; // H2的头结点已在Merge中释放, 将指针置空
                break;
            }
            case 0: {
                cout << "感谢使用，程序退出。" << endl;
                break;
            }
            default: {
                cout << "无效的选项，请重新输入。" << endl;
                break;
            }
        }
    } while (choice != 0);

    DestroyList(H1);
    DestroyList(H2);

    return 0;
}