all: runner.out

CC := g++ -std=c++11

CFLAGS := \
	-MMD \
	-Wall \
	-Wextra \
	-Wnon-virtual-dtor

INCLUDE := -I..

LIBS := \
	-lgtest \
	-lpthread

SRCS := $(shell find .. -name '*.cpp')
OBJS := $(SRCS:%.cpp=%.o)
DEPS := $(OBJS:%.o=%.d)

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<

runner.out: $(OBJS)
	$(CC) $(OBJS) -o runner.out $(LIBS)

clean:
	rm runner.out
	rm $(OBJS)
	rm $(DEPS)

-include $(OBJS:.o=.d)
