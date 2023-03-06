TARGETS=dec2rom caesar teststack grading_tasks crack_passwd

all: $(TARGETS)

istack.o: istack.c istack.h
	$(CC) -c -o $@ $<

teststack: teststack.c istack.o
	$(CC) -o $@ $^

grading_table.o: grading_table.c grading_table.h
	$(CC) -c -o $@ $<

grading_tasks: grading_tasks.c grading_table.o
	$(CC) -o $@ $^

sha256.o: sha256.c sha256.h
	$(CC) -c -o $@ $<

dictionary_attack.o: dictionary_attack.c dictionary_attack.h
	$(CC) -c -o $@ $<

crack_passwd: crack_passwd.c dictionary_attack.o sha256.o
	$(CC) -o $@ $^

clean:
	$(RM) $(TARGETS) istack.o grading_table.o sha256.o dictionary_attack.o

.PHONY: all clean
