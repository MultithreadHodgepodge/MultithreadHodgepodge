OBJECTS?= all_test
OBJECTS_LIST=test_list.o
OBJECTS_STACK=test_stack.o
OBJECTS_QUEUE=test_queue.o
OBJECTS_RB=test_RB.o
CC = gcc
.PHONY: clean
CFLAGS= -pthread -g -O0 -o
LIST_DIR=list/
STACK_DIR=stack/
OBSERVER_DIR=Observer/
QUEUE_DIR=queue/
RB_DIR=RingBuffer/
TEST_LIST_FILE= $(LIST_DIR)test_list.c
LIST_SOURCE:= $(shell find $(LIST_DIR) -name '*.c')
STACK_SOURCE:= $(shell find $(STACK_DIR) -name '*.c')
QUEUE_SOURCE:= $(shell find $(QUEUE_DIR) -name '*.c') 
RB_SOURCE:= $(shell find $(RB_DIR) -name '*.c')
COMMON_SOURCE:=$(filter-out $(TEST_LIST_FILE),$(LIST_SOURCE))
OBJ_DIR=build/
#all: $(OBJ_DIR)$(OBJECTS)
#$(OBJ_DIR)$(OBJECTS): $(OBJ_DIR)$(OBJECTS_LIST) $(COMMON_SOURCE) $(STACK_SOURCE)
#	mkdir -p $(@D)
#	$(CC) $(CFLAGS) $@ $^
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
rb: $(OBJ_DIR)$(OBJECTS_RB)
$(OBJ_DIR)$(OBJECTS_RB): $(COMMON_SOURCE) $(RB_SOURCE)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $@ $^
clean:
	rm -rf ./$(OBJ_DIR)*.o
