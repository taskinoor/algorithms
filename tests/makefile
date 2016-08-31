all: runner.out

CC := g++ -std=c++11

CFLAGS := \
	-MMD \
	-Wall \
	-Wextra

INCLUDE := $(shell find ../alg -type d | sed s/^/-I/)

LIBS := \
	-lgtest \
	-lpthread

SRCS := $(shell find .. -name '*.cpp')
OBJS := $(SRCS:%.cpp=%.o)

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<

runner.out: $(OBJS)
	$(CC) $(OBJS) -o runner.out $(LIBS)

clean:
	rm runner.out
	rm $(OBJS)
	rm *.d

-include $(OBJS:.o=.d)
