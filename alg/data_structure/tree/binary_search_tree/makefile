all: runner.out

CPP = g++

CPPFLAGS = -MMD

INCLUDE = \
	-I../binary_tree \
	-I../traversal \
	-I../../../common \
	-I../../stack

LIBS = \
	-lgtest \
	-lpthread

OBJS = main.o

%.o: %.cpp
	$(CPP) $(CPPFLAGS) $(INCLUDE) -c -o $@ $<

runner.out: $(OBJS)
	$(CPP) $(OBJS) -o runner.out $(LIBS)

clean:
	rm runner.out
	rm $(OBJS)
	rm *.d

-include $(OBJS:.o=.d)
