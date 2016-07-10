all: runner.out

CPP = g++

CPPFLAGS = -MMD

LIBS = \
	-lgtest \
	-lpthread

OBJS = main.o

%.o: %.cpp
	$(CPP) $(CPPFLAGS) -c -o $@ $<

runner.out: $(OBJS)
	$(CPP) $(OBJS) -o runner.out $(LIBS)

clean:
	rm runner.out
	rm $(OBJS)
	rm *.d

-include $(OBJS:.o=.d)
