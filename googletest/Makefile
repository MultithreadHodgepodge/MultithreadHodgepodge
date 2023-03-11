CC:=gcc
CP=g++
CFLAG := -DMUL_HOD_UT=1 -pthread -o
CPFLAG:= -std=c++14 
.PHONY: clean
OBJECT:= gtest.out
OBJECTS_LIST:=list.o
OBJECTS_STACK:=stack.o
GTEST_FILE:=mul_hod_ut.cc
GTEST_MAIN_FILE:=mul_hod_ut_main.cc
LIST_FILE:= ../list/list.c
STACK_FILE:= ../list/stack/stack.c
all: build_list build_stack build_ut 
build_ut: $(OBJECT)
$(OBJECT):$(OBJECTS_LIST) $(OBJECTS_STACK) $(GTEST_FILE) $(GTEST_MAIN_FILE) 
	$(CP) $(CPFLAG) -o $@ $^ -lgtest -lpthread
build_list:$(OBJECTS_LIST)
$(OBJECTS_LIST):$(LIST_FILE)
	$(CC) $(CFLAG) $@ -c $^
build_stack:$(OBJECTS_STACK) 
$(OBJECTS_STACK): $(STACK_FILE) 
	$(CC) $(CFLAG) $@ -c $^
clean:
	rm *.o
	rm *.out