all: runner.out

CPP = g++ -std=c++11

CPPFLAGS = -MMD

INCLUDE = \
	-I../binary_tree \
	-I../binary_search_tree \
	-I../../../common

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
