CC:=gcc
CP=g++
CFLAG := -DMUL_HOD_UT=1 -pthread -o
CPFLAG:= -std=c++14 
.PHONY: clean
OBJECT:= gtest.out
OBJECTS_LIST:= list.o
OBJECTS_STACK:= stack.o
OBJECTS_QUEUE:= queue.o
OBJECTS_HASH:= hashtable.o
OBJECTS_TREE:= tree.o 
GTEST_FILE:=mul_hod_ut.cc
GTEST_MAIN_FILE:=mul_hod_ut_main.cc
LIST_FILE:= ../list/list.c
STACK_FILE:= ../list/stack/stack.c
QUEUE_FILE:= ../list/queue/queue.c
HASH_FILE:= ../list/hashtable/hashtable.c
TREE_FILE:= ../tree/tree.c

all: build_list build_stack build_queue build_hash build_ut 
build_ut: $(OBJECT)
$(OBJECT):$(OBJECTS_LIST) $(OBJECTS_STACK) $(OBJECTS_QUEUE) $(OBJECTS_HASH) $(OBJECTS_TREE) $(GTEST_FILE) $(GTEST_MAIN_FILE) 
	$(CP) $(CPFLAG) -o $@ $^ -lgtest -lpthread
build_list:$(OBJECTS_LIST)
$(OBJECTS_LIST):$(LIST_FILE)
	$(CC) $(CFLAG) $@ -c $^
build_stack:$(OBJECTS_STACK) 
$(OBJECTS_STACK): $(STACK_FILE) 
	$(CC) $(CFLAG) $@ -c $^
build_queue: $(OBJECTS_QUEUE)
$(OBJECTS_QUEUE): $(QUEUE_FILE)
	$(CC) $(CFLAG) $@ -c $^
build_hash: $(OBJECTS_HASH)
$(OBJECTS_HASH): $(HASH_FILE)
	$(CC) $(CFLAG) $@ -c $^
build_tree: $(OBJECTS_TREE)
$(OBJECTS_TREE): $(TREE_FILE)
	$(CC) $(CFLAG) $@ -c $^
clean:
	rm *.o
	rm *.out