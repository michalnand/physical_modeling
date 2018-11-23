OUTPUT_NAME = libs_common_pm
PHYSICAL_MODELING_LIBS_PATH=..

INC+= -I.
INC+= -I$(RYSY_LIBS_PATH)/libs_common
INC+= -I$(RYSY_LIBS_PATH)/libs_dataset
INC+= -I$(RYSY_LIBS_PATH)/libs_experiment
INC+= -I$(RYSY_LIBS_PATH)/libs_nn
INC+= -I$(PHYSICAL_MODELING_LIBS_PATH)/libs_common
INC+= -I$(PHYSICAL_MODELING_LIBS_PATH)/libs_load

SRCS+= $(shell find . -name '*.cpp')

CC = g++
CU = nvcc
LD = g++
OBJCOPY = objcopy
OBJDUMP = objdump
SIZE = size
ARCHIVE = ar

# DEGUBFLAGS = -g -pg

CFLAGS = $(DEGUBFLAGS) -O2 -Os -fPIC -s -Wall -Wextra -pedantic -std=c++17 $(INC)

OBJS = $(SRCS:.cpp=.o)

all: $(OBJS)
	$(ARCHIVE) rc $(OUTPUT_NAME).a $(OBJS)
	$(CC) -shared -fPIC -o $(OUTPUT_NAME).so $(OBJS)

%.o: %.cpp
	$(CC) -c $(CFLAGS) $< -o $@


clean:
	rm $(OBJS) -rf
	rm $(OUTPUT_NAME).* -rf
