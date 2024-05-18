## Object File
OBJECTS_LIST=test_list.o
OBJECTS_STACK=test_stack.o
OBJECTS_QUEUE=test_queue.o
OBJECTS_HASH=test_hashtable.o
OBJECTS_MINHEAP=test_minheap.o
OBJECTS_RB=test_RB.o
OBJECTS_BINARYTREE=test_binary_tree.o
OBJECTS_BINARYSEARCHTREE=test_binary_search_tree.o
OBJECTS_THPOOL = test_threadpool.o
OBJECTS_RWLOCK = test_rwlock.o
OBJECTS_SPEEDTEST = speedtest.o

## GCC argument
CC = gcc
.PHONY: clean
CFLAGS= -pthread -g -O0 -fsanitize=address -o
CONFIG_BPF_SYSCALL=y
## Source DIR
LIST_DIR=list/
STACK_DIR=$(LIST_DIR)stack/
QUEUE_DIR=$(LIST_DIR)queue/
HASH_DIR=$(LIST_DIR)hashtable/
MINHEAP_DIR= minheap/
TREE_DIR=tree/
BINARY_TREE_DIR=tree/binary_tree/
BINARY_SEARCH_TREE_DIR=tree/binary_search_tree/
THPOOL_DIR = simpleThreadpool/
RWLOCK_DIR = rwlock/
SPEEDTEST_DIR=speedtest/
## Target DIR
OBJ_DIR=build/

## Source .c file
TEST_LIST_FILE= $(shell find $(LIST_DIR) -maxdepth 1 -name 'test_list.c')
LIST_SOURCE:= $(shell find $(LIST_DIR) -maxdepth 1 -name '*.c')
STACK_SOURCE:= $(shell find $(STACK_DIR) -name '*.c')
QUEUE_SOURCE:= $(shell find $(QUEUE_DIR) -name '*.c') 
HASH_SOURCE:= $(shell find $(HASH_DIR) -name '*.c') 
MINHEAP_SOURCE:=$(shell find $(MINHEAP_DIR) -name '*.c') 
COMMON_SOURCE:= $(filter-out $(TEST_LIST_FILE),$(LIST_SOURCE))
TREE_SOURCE:=$(shell find $(TREE_DIR) -maxdepth 1 -name '*.c')
THPOOL_SOURCE := $(shell find $(THPOOL_DIR) -name '*.c')
RWLOCK_SOURCE := $(shell find $(RWLOCK_DIR) -name '*.c')
BINARY_TREE_SOURCE:=$(shell find $(BINARY_TREE_DIR) -name '*.c')
BINARY_SEARCH_TREE_SOURCE:=$(shell find $(BINARY_SEARCH_TREE_DIR) -name '*.c')
SPEEDTEST_SOURCE := $(shell find $(SPEEDTEST_DIR) -name '*.c')
## Main Makefile
all: list stack queue hash minheap binarytree bst thpool rwlock
list: clean $(OBJ_DIR)$(OBJECTS_LIST) 
$(OBJ_DIR)$(OBJECTS_LIST): $(LIST_SOURCE)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $@ $^
stack: clean $(OBJ_DIR)$(OBJECTS_STACK)
$(OBJ_DIR)$(OBJECTS_STACK): $(COMMON_SOURCE) $(STACK_SOURCE)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $@ $^
queue: clean $(OBJ_DIR)$(OBJECTS_QUEUE)
$(OBJ_DIR)$(OBJECTS_QUEUE): $(COMMON_SOURCE) $(QUEUE_SOURCE)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $@ $^
hash: clean $(OBJ_DIR)$(OBJECTS_HASH)
$(OBJ_DIR)$(OBJECTS_HASH): $(COMMON_SOURCE) $(HASH_SOURCE)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $@ $^
minheap: clean $(OBJ_DIR)$(OBJECTS_MINHEAP)
$(OBJ_DIR)$(OBJECTS_MINHEAP): $(MINHEAP_SOURCE)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $@ $^
binarytree: clean $(OBJ_DIR)$(OBJECTS_BINARYTREE)
$(OBJ_DIR)$(OBJECTS_BINARYTREE): $(TREE_SOURCE) $(BINARY_TREE_SOURCE) 
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $@  $^
bst: clean $(OBJ_DIR)$(OBJECTS_BINARYSEARCHTREE)
$(OBJ_DIR)$(OBJECTS_BINARYSEARCHTREE): $(TREE_SOURCE) $(BINARY_SEARCH_TREE_SOURCE) 
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $@  $^
thpool: clean $(OBJ_DIR)$(OBJECTS_THPOOL)
$(OBJ_DIR)$(OBJECTS_THPOOL): $(THPOOL_SOURCE) $(COMMON_SOURCE)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $@ $^
rwlock: clean $(OBJ_DIR)$(OBJECTS_RWLOCK)
$(OBJ_DIR)$(OBJECTS_RWLOCK): $(RWLOCK_SOURCE)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $@ $^ 
speedtest: clean $(OBJ_DIR)$(OBJECTS_SPEEDTEST)
$(OBJ_DIR)$(OBJECTS_SPEEDTEST): $(COMMON_SOURCE) list/stack/stack.c list/queue/queue.c $(SPEEDTEST_SOURCE)
	$(CC) $(CFLAGS) $@ $^
	./build/speedtest.o | tee speedtest_result.txt
clean:
	rm -rf ./$(OBJ_DIR)*.o >/dev/null 2>/dev/null || true
	rm -d $(OBJ_DIR)  >/dev/null 2>/dev/null || true
	rm *.o >/dev/null 2>/dev/null || true
