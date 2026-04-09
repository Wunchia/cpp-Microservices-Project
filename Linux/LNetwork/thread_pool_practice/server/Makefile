# 定义最终要生成的可执行文件名
TARGET := server
# 找到所有的 .c 源文件
SRCS := $(wildcard *.c)
# 将所有的 .c 对应的 .o 目标文件列出来
OBJS := $(patsubst %.c,%.o,$(SRCS))

CC := gcc
CFLAGS := -Wall -g

.PHONY: clean rebuild all

# 默认目标：编译最终的 TARGET
all: $(TARGET)

# 链接阶段：把所有的 .o 文件链接成一个可执行文件
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(CFLAGS)

# 编译阶段：把每个 .c 文件编译成 .o 文件
%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	$(RM) $(TARGET) $(OBJS)

rebuild: clean all