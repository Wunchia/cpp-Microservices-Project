#include "linklist.h"

int main() {
    // 1. 测试创建
    printf("--- 1. Testing Create ---\n");
    Linklist* list = create_linked_list();
    if (list) printf("List created successfully. Size: %d\n", list->size);

    // 2. 测试头插法 (add_before_head)
    printf("\n--- 2. Testing Head Insertion ---\n");
    add_before_head(list, 10); // 第一个节点
    add_before_head(list, 5);  // 头部插入
    print_list(list); // 预期: 5 -> 10

    // 3. 测试尾插法 (add_behind_tail)
    printf("\n--- 3. Testing Tail Insertion ---\n");
    add_behind_tail(list, 20);
    add_behind_tail(list, 30);
    print_list(list); // 预期: 5 -> 10 -> 20 -> 30

    // 4. 测试索引插入 (add_by_idx)
    printf("\n--- 4. Testing Insertion by Index ---\n");
    add_by_idx(list, 0, 1);   // 头部插入
    add_by_idx(list, 5, 40);  // 尾部插入
    add_by_idx(list, 2, 8);   // 中间插入
    add_by_idx(list, 10, 99); // 非法索引测试
    print_list(list); // 预期: 1 -> 5 -> 8 -> 10 -> 20 -> 30 -> 40

    // 5. 测试搜索 (search_by_idx & search_by_data)
    printf("\n--- 5. Testing Search ---\n");
    Node* node_idx = search_by_idx(list, 3);
    if (node_idx) printf("Data at index 3: %d\n", node_idx->data); // 预期: 10

    Node* node_data = search_by_data(list, 20);
    if (node_data) printf("Found data 20 at address: %p\n", (void*)node_data);
    search_by_data(list, 100); // 搜索不存在的数据

    // 6. 测试根据索引删除 (delete_by_idx)
    printf("\n--- 6. Testing Deletion by Index ---\n");
    delete_by_idx(list, 0); // 删除头 (1)
    delete_by_idx(list, list->size - 1); // 删除尾 (40)
    delete_by_idx(list, 2); // 删除中间 (10)
    print_list(list); // 预期: 5 -> 8 -> 20 -> 30

    // 7. 测试根据数据删除 (delete_by_data)
    printf("\n--- 7. Testing Deletion by Data ---\n");
    delete_by_data(list, 5);  // 删除头
    delete_by_data(list, 30); // 删除尾
    delete_by_data(list, 8);  // 删除中间
    print_list(list); // 预期: 20

    delete_by_data(list, 20); // 删除最后一个节点
    printf("List after deleting last element: ");
    print_list(list); // 预期: 空行
    printf("Current Size: %d, Head: %p, Rear: %p\n", list->size, (void*)list->head, (void*)list->rear);

    // 8. 测试销毁
    printf("\n--- 8. Testing Destroy ---\n");
    destroy_linked_list(list);
    printf("Memory freed.\n");

    return 0;
}