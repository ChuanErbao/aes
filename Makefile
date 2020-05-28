objects = aes.o test.o aes_cbc.o

test : $(objects)
	cc -o test $(objects)

aes.o : aes.h
aes_cbc.o : aes.h
test.o : aes.h

.PHONY:clean
clean :
	-rm $(objects) test