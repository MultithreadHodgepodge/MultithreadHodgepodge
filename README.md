# Multithread-Hodgepodge

Multithread-Hodgepodge is an open-source project which implements thread-safe data structures in CS. \
Multithread-Hodgepodge is written in C language. It utilizes object-oriented concept to make the code structured. \
Multithread-Hodgepodge is expected to be library of both kernel space/user space application \
Currently support Linux and IOS platform, other platform TBD.


## How to use
Add the data structure be an element of your own structure.
For example if you want to use list_t:
```
struct mystruct{
    int data;
    list_t list;
}
```

# Multithread-Hodgepodge Architecture
- list: The kernel implementation of Multithread-Hodgepodge Architecture. This struture includes almost all implementation details of function and other structure utilize the implemetation in list.
    - stack: Implementation of thread-safe stack structure based on list_t.
    - queue: Implementation of thread-safe queue structure based on list_t.
    - hashtable: Implementation of thread-safe hashtable utilized list_t to maintain entry in hashtable. 
- Tree:  Implementation of Tree including different types of tree. Leverage function pointer to implement different tree, tree is only interface!!!(Same tree different implementation)
    - binary_tree: only contain testing of binary tree and specific function
    - binary_search_tree: only contain testing of binary search tree and specific function
- simpleThreadpool: Implementation of threadpool maintained by list

# Multithread-Hodgepodge Advantages
- Object-Oriented C Programming.
- Tidy Coding style.
- Implemetation of many household data structures.
- Thread-safe data structures.

## Contributors
Created by:

[**Chung Hsuan Chen**](https://github.com/ChungHsuanChen)

[**Peter Kung**](https://github.com/Peter-Kung)

## Contribution
Please feel free to make a pull request to MultithreadHodgepodge or leave a star for the project!!