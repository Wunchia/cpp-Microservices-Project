为什么listenfd放进epoll_event节点里了还要在epoll_ctl的参数列表里给内核传一下？
因为内核**不信任** `evt.data.fd` 里的值。

`epoll_ctl` 的函数签名：

```c
int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
```

内核把这三个独立参数用于不同的内核操作，各司其职：

---

## 两个 `listenfd` 的去向完全不同

```cpp
epoll_ctl(epfd, EPOLL_CTL_ADD, listenfd, &evt);
//                    ③ 内核用它做三件事        ④ 原样存下来，将来还你
```

| 参数 | 内核拿它干什么 |
|---|---|
| `epfd`（参数1） | 找到是**哪个 epoll 实例**的红黑树 |
| `listenfd`（参数3） | ① 作为红黑树的 **key** 插入节点 ② 找到这个 fd 对应的内核 `struct file` ③ 往 `file` 上**注册回调**："你有事件了叫我" |
| `evt`（参数4） | **原封不动存下来**，事件触发时拷贝回用户态，给你当标记用 |

---

## 为什么内核不直接从 `evt.data.fd` 读？

两步完全独立的操作：

```
epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &evt)
          │                     │       │
          │                     │       └── 用户数据，存下来将来还你（捎带机制）
          │                     └── 真正的监控对象，内核要操作它的 file 结构
          └── epoll 实例
```

- **参数3 `fd`**：是真实的**文件描述符**整数，内核用它在进程的 fd 表中查到 `struct file`，然后注册回调。内核必须信它自己查到的——这是**安全边界**。
- **`evt.data.fd`**：你随便填什么内核都不管，它只是一个 **cookie**（捎带字段），事件触发时原样返回，**内核不看它语义**。

---

## 举个反例你就懂了

```cpp
evt.data.fd = 999;                    // 乱写
epoll_ctl(epfd, EPOLL_CTL_ADD, listenfd, &evt);  // 实际监控 listenfd
```

内核：你用参数3告诉我监控 `listenfd`，没问题。`evt.data.fd=999`？不关我事，存下来，将来还你。

事件来了：
```cpp
events[i].data.fd  // → 999   内核如实返回你写的值
// 你拿 999 去 recv(999, ...) → -1 EBADF，炸了
```

所以 `evt.data.fd` 只是一个**透明的用户标记**，内核不拿它做任何文件描述符的操作。真正的文件描述符操作全靠参数3那个 `fd`。
