# Simple Threadpool

Demonstrate threadpool concept using C. There are four thread will be create in init();

t1 t2 t3 t4 t5 -----
					|
					|    assign
					|
          		work1()   work2() work3()  work4()
					|
					|    finished
					| 
					|
t1 t2 t3 t4 t5------



and we will maintain a ringbuffer to store task from application, and thread worker will take task from ringbuffer.
This action must be taken under sychronization, or will fail because of race.


There are many tasks in queue originally, you can use command via crtl+c to add task:

add new task

	a 1 
or
	
	a 2
	
or
	
	a 3
	
	
task_number only has three types function to use.

continue

	c

exit

	e


