## Object File
OBJECTS_LIST=test_list.o
OBJECTS_STACK=test_stack.o
OBJECTS_QUEUE=test_queue.o
OBJECTS_PRIORITYQUEUE=test_priorityqueue.o
OBJECTS_RB=test_RB.o
OBJECTS_BINARYTREE=test_binary_tree.o

## GCC argument
CC = gcc
.PHONY: clean
CFLAGS= -pthread -g -O0 -o

## Source DIR
LIST_DIR=list/
STACK_DIR=stack/
QUEUE_DIR=queue/
PRIORITYQUEUE_DIR=priority_queue/
RB_DIR=ringbuffer/
TREE_DIR=tree/
BINARY_TREE_DIR=tree/binary_tree/

## Source .c file
TEST_LIST_FILE= $(LIST_DIR)test_list.c
LIST_SOURCE:= $(shell find $(LIST_DIR) -name '*.c')
STACK_SOURCE:= $(shell find $(STACK_DIR) -name '*.c')
QUEUE_SOURCE:= $(shell find $(QUEUE_DIR) -name '*.c') 
PRIORITYQUEUE_SOURCE:= $(shell find $(PRIORITYQUEUE_DIR) -name '*.c') 
RB_SOURCE:= $(shell find $(RB_DIR) -name '*.c')
COMMON_SOURCE:=$(filter-out $(TEST_LIST_FILE),$(LIST_SOURCE))
TREE_SOURCE:=$(shell find $(TREE_DIR) -name '*.c')
BINARY_TREE_SOURCE:=$(shell find $(BINARY_TREE_DIR) -name '*.c')

## Target DIR
OBJ_DIR=build/

## Main Makefile
list: $(OBJ_DIR)$(OBJECTS_LIST) 
$(OBJ_DIR)$(OBJECTS_LIST): $(LIST_SOURCE)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $@ $^
stack: $(OBJ_DIR)$(OBJECTS_STACK)
$(OBJ_DIR)$(OBJECTS_STACK): $(COMMON_SOURCE) $(STACK_SOURCE)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $@ $^
queue: $(OBJ_DIR)$(OBJECTS_QUEUE)
$(OBJ_DIR)$(OBJECTS_QUEUE): $(COMMON_SOURCE) $(QUEUE_SOURCE)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $@ $^
priorityqueue: $(OBJ_DIR)$(OBJECTS_PRIORITYQUEUE)
$(OBJ_DIR)$(OBJECTS_PRIORITYQUEUE): $(COMMON_SOURCE) $(PRIORITYQUEUE_SOURCE)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $@ $^
rb: $(OBJ_DIR)$(OBJECTS_RB)
$(OBJ_DIR)$(OBJECTS_RB): $(COMMON_SOURCE) $(RB_SOURCE)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $@ $^
binarytree: $(OBJ_DIR)$(OBJECTS_BINARYTREE)
$(OBJ_DIR)$(OBJECTS_BINARYTREE): $(TREE_SOURCE) $(BINARY_TREE_SOURCE)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $@ $^
clean:
	rm -rf ./$(OBJ_DIR)*.o
	rm -d $(OBJ_DIR)
