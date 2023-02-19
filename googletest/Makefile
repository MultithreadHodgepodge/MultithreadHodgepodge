CC:=gcc
CP=g++
CFLAG := -DMUL_HOD_UT=1 -pthread -o 
CPFLAG:= -std=c++14 
.PHONY: clean
OBJECT:= gtest.out
OBJECT_TEMP:= gtest_temp.o
OBJECTS_LIST:=list.o
GTEST_FILE:=mul_hod_ut.cc
GTEST_MAIN_FILE:=mul_hod_ut_main.cc
LIST_FILE:= ../list/list.c
all: build_list build_ut 
build_ut: $(OBJECT)
$(OBJECT):$(OBJECTS_LIST) $(GTEST_FILE) $(GTEST_MAIN_FILE) 
	$(CP) $(CPFLAG) -o $@ $^ -lgtest -lpthread
build_list:$(OBJECTS_LIST)
$(OBJECTS_LIST):$(LIST_FILE)
	$(CC) $(CFLAG) $@ -c $^
clean:
	rm *.o
	rm *.out