/**
 * main.cpp —— 顺序表基本操作（单文件版，直接运行）
 *
 * 对应教材：王道《数据结构》第2章 2.2 线性表的顺序表示
 *
 * 编译运行：
 *   g++ main.cpp -o main && ./main
 */

#include <cstdio>

// ════════════════════════════════════════════════════════════
//  一、类型定义  （对应教材 2.2.1 顺序表的定义）
// ════════════════════════════════════════════════════════════

typedef int ElemType;    // 元素类型，学习时统一用 int

#define MaxSize 50       // 顺序表的最大长度（静态分配）

/**
 * 静态分配顺序表
 *   教材原文：
 *     typedef struct {
 *         ElemType data[MaxSize];
 *         int length;
 *     } SqList;
 */
typedef struct {
    ElemType data[MaxSize]; // 存放数据元素的数组
    int length;             // 顺序表当前有效长度
} SqList;


// ════════════════════════════════════════════════════════════
//  二、基本操作  （对应教材 2.2.2 顺序表上基本操作的实现）
// ════════════════════════════════════════════════════════════

// ──────────────────────────────────────────────
//  1. 初始化
//  教材原文：
//    void InitList(SqList &L) {
//        L.length = 0;
//    }
// ──────────────────────────────────────────────
void InitList(SqList &L) {
    L.length = 0;  // 静态分配数组空间已自动开好，只需把长度置 0
}

// ──────────────────────────────────────────────
//  2. 插入操作
//  教材原文：
//    bool ListInsert(SqList &L, int i, ElemType e) {
//        if (i < 1 || i > L.length + 1) return false;
//        if (L.length >= MaxSize)        return false;
//        for (int j = L.length; j >= i; j--)
//            L.data[j] = L.data[j-1];
//        L.data[i-1] = e;
//        L.length++;
//        return true;
//    }
//
//  关键点：
//    • 位序 i 从 1 开始，数组下标从 0 开始，"第 i 位" → data[i-1]
//    • 允许 i = length+1（在表尾追加），所以越界判断是 length+1
//    • 移位必须从后往前，防止覆盖未移动的元素
// ──────────────────────────────────────────────
bool ListInsert(SqList &L, int i, ElemType e) {
    if (i < 1 || i > L.length + 1) return false; // 位序越界
    if (L.length >= MaxSize)        return false; // 存储空间已满

    // 第 i 个元素及其后的所有元素依次后移一位
    for (int j = L.length; j >= i; j--)
        L.data[j] = L.data[j - 1];

    L.data[i - 1] = e; // 在位置 i（下标 i-1）放入新元素
    L.length++;
    return true;
}

// ──────────────────────────────────────────────
//  3. 删除操作
//  教材原文：
//    bool ListDelete(SqList &L, int i, ElemType &e) {
//        if (i < 1 || i > L.length) return false;
//        e = L.data[i-1];
//        for (int j = i; j < L.length; j++)
//            L.data[j-1] = L.data[j];
//        L.length--;
//        return true;
//    }
//
//  关键点：
//    • 先用 e 保存被删值，再移位覆盖
//    • 移位从前往后（与插入方向相反）
// ──────────────────────────────────────────────
bool ListDelete(SqList &L, int i, ElemType &e) {
    if (i < 1 || i > L.length) return false; // 位序越界

    e = L.data[i - 1]; // 保存被删元素的值

    // 第 i+1 个元素及其后的所有元素依次前移一位
    for (int j = i; j < L.length; j++)
        L.data[j - 1] = L.data[j];

    L.length--;
    return true;
}

// ──────────────────────────────────────────────
//  4. 按值查找（顺序查找）
//  教材原文：
//    int LocateElem(SqList L, ElemType e) {
//        for (int i = 0; i < L.length; i++)
//            if (L.data[i] == e)
//                return i + 1;
//        return 0;
//    }
//
//  返回：第一个值等于 e 的元素的位序（从 1 开始），未找到返回 0
// ──────────────────────────────────────────────
int LocateElem(SqList L, ElemType e) {
    for (int i = 0; i < L.length; i++)
        if (L.data[i] == e)
            return i + 1; // 下标 i → 位序 i+1
    return 0;
}

// ──────────────────────────────────────────────
//  5. 按位查找（随机存取 O(1)）
//  教材："顺序表的按序号查找非常简单，直接根据数组下标访问，
//         时间复杂度 O(1)"
// ──────────────────────────────────────────────
bool GetElem(SqList L, int i, ElemType &e) {
    if (i < 1 || i > L.length) return false;
    e = L.data[i - 1]; // 随机存取，O(1)
    return true;
}

// ──────────────────────────────────────────────
//  辅助函数：打印 / 求表长 / 判空
// ──────────────────────────────────────────────
void PrintList(SqList L) {
    printf("[ ");
    for (int i = 0; i < L.length; i++) {
        printf("%d", L.data[i]);
        if (i < L.length - 1) printf(", ");
    }
    printf(" ]  (length = %d)\n", L.length);
}

int  Length(SqList L) { return L.length; }
bool Empty(SqList L)  { return L.length == 0; }


// ════════════════════════════════════════════════════════════
//  三、演示主程序
// ════════════════════════════════════════════════════════════

static void divider(const char *title) {
    printf("\n══════════════════════════════\n");
    printf("  %s\n", title);
    printf("══════════════════════════════\n");
}

int main() {
    SqList L;

    // ── 初始化 ─────────────────────────────────
    divider("【操作1】初始化 InitList");
    InitList(L);
    printf("是否为空：%s，表长：%d\n", Empty(L) ? "是" : "否", Length(L));
    PrintList(L);

    // ── 插入 ───────────────────────────────────
    divider("【操作2】插入 ListInsert");

    for (int v = 10; v <= 50; v += 10)
        ListInsert(L, L.length + 1, v); // 表尾追加（最好情况 O(1)）
    printf("追加 10~50：");
    PrintList(L);

    ListInsert(L, 3, 99);               // 在位序 3 插入 99
    printf("位序3插入99：");
    PrintList(L);

    if (!ListInsert(L, 0, 999))         // 非法：位序 0
        printf("位序0插入 —— 失败（位序非法 ✓）\n");
    if (!ListInsert(L, L.length + 2, 999)) // 非法：越界
        printf("位序%d插入 —— 失败（位序非法 ✓）\n", L.length + 2);

    // ── 删除 ───────────────────────────────────
    divider("【操作3】删除 ListDelete");

    ElemType del;
    ListDelete(L, 3, del);
    printf("删除位序3（值=%d）后：", del);
    PrintList(L);

    ListDelete(L, 1, del);              // 删表头（最坏情况 O(n)）
    printf("删除位序1（值=%d）后：", del);
    PrintList(L);

    ListDelete(L, L.length, del);       // 删表尾（最好情况 O(1)）
    printf("删除位序%d（值=%d）后：", L.length + 1, del);
    PrintList(L);

    if (!ListDelete(L, 0, del))
        printf("删除位序0 —— 失败（位序非法 ✓）\n");

    // ── 按值查找 ───────────────────────────────
    divider("【操作4】按值查找 LocateElem");
    printf("当前表："); PrintList(L);

    int pos = LocateElem(L, 30);
    if (pos) printf("查找 30：找到，位序 %d\n", pos);
    else     printf("查找 30：未找到\n");

    pos = LocateElem(L, 999);
    printf("查找 999：%s（预期 ✓）\n", pos == 0 ? "未找到" : "找到");

    // ── 按位查找 ───────────────────────────────
    divider("【操作5】按位查找 GetElem（随机存取 O(1)）");
    printf("当前表："); PrintList(L);

    ElemType val;
    for (int i = 1; i <= L.length; i++) {
        GetElem(L, i, val);
        printf("  GetElem(L, %d) = %d\n", i, val);
    }
    if (!GetElem(L, L.length + 1, val))
        printf("GetElem(L, %d) —— 越界，失败（预期 ✓）\n", L.length + 1);

    // ── 复杂度小结 ─────────────────────────────
    divider("复杂度小结（教材 2.2.2 节）");
    printf("  InitList   ：O(1)\n");
    printf("  ListInsert ：平均 O(n)  [平均后移 n/2 个元素]\n");
    printf("  ListDelete ：平均 O(n)  [平均前移 (n-1)/2 个元素]\n");
    printf("  LocateElem ：平均 O(n)  [平均比较 (n+1)/2 次]\n");
    printf("  GetElem    ：O(1)  ← 随机存取，顺序表核心优势\n\n");

    return 0;
}
