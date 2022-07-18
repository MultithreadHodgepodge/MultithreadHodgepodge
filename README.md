# Multithread-Hodgepodge

Multithread-Hodgepodge is an open-source project which implements thread-safe data structures in CS.
Multithread-Hodgepodge is written in C language. It utilizes object-oriented concept to make the code structured.
Multithread-Hodgepodge is expected to be library of system software(device driver) with variety of thread-safe data structure and function.


# Multithread-Hodgepodge Architecture
- common: Macro used commonly across different data strucrture.
- drivers: Some praticing drivers
- list: The kernel implementation of Multithread-Hodgepodge Architecture. This struture includes almost all implementation details of function and other structure utilize the implemetation in list.
    - stack: Implementation of thread-safe stack structure based on list_t.
    - queue: Implementation of thread-safe queue structure based on list_t.
    - RingBuffer: Implementation of thread-safe Ring Buffer based on list_t.
- Tree:  Implementation of Tree including different types of tree. Leverage function pointer to implement different tree, tree is only interface!!!(Same tree different implementation)
    - binary_tree: only contain testing of binary tree and specific function
    - binary_search_tree: only contain testing of binary search tree and specific function
- simpleThreadpool: Implementation of threadpool maintained by list
# Multithread-Hodgepodge Advantages
- Object-Oriented C Programming Style.
- Tidy Coding style.
- Implemetation of many household data structures.
- Thread-safe data structures.

## Collaborators
Created by:

[**Chung Hsuan Chen**](https://github.com/ChungHsuanChen)

[**Peter Kung**](https://github.com/Peter-Kung)

## Contribution
Please feel free to make a pull request to Multithread-Hodgepodge or leave a star for the project!!