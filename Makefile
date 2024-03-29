COMPILER = g++
CFLAGS = -Wall -std=c++11 -pthread
INCLUDES = -I./include
TARGET = dir_compare

all: $(TARGET)

$(TARGET): src/main.cpp src/DirectoryCmp.cpp src/FileCmp.cpp src/Extra.cpp
	$(COMPILER) $(CFLAGS) $(INCLUDES) $^ -o $@

clean:
	rm -f $(TARGET)
