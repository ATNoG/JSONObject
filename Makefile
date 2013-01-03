TARGET  := main
SRCS    := ${wildcard *.cpp} 
OBJS    := ${SRCS:.cpp=.o} 

CFLAGS= -O0 -g -pipe -ansi -pedantic
CXXFLAGS=${CFLAGS}
LDFLAGS=
LIBS=-lboost_regex -lboost_thread
CC=g++

.PHONY: all clean distclean 
all:: ${TARGET} 

${TARGET}: ${OBJS} 
	${CC} ${LDFLAGS} -o $@ $^ ${LIBS} 
	
${OBJS}:  %.o: %.cpp
	${CC} ${CFLAGS} -o $@ -c $< 
	
clean::
	-rm -f *~ *.o ${TARGET}

distclean:: clean
