all: q1 q2


q1: mysort.c mysort_ptest.c
	gcc mysort.c mysort_ptest.c -o q1

q2: myrecord.c myrecord_ptest.c
	gcc myrecord.c myrecord_ptest.c -o q2

run_q1: q1
	./q1

run_q2: q2
	./q2

clean: 
	rm -f q1 q2 *.o

.PHONY: all run_q1 run_q2 clean