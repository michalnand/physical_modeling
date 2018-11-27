ELF = bin/trajectory_learn.elf

PHYSICAL_MODELING_LIBS_PATH=..

INC+= -I.
INC+= -I$(RYSY_LIBS_PATH)/libs_common
INC+= -I$(RYSY_LIBS_PATH)/libs_dataset
INC+= -I$(RYSY_LIBS_PATH)/libs_experiment
INC+= -I$(RYSY_LIBS_PATH)/libs_nn
INC+= -I$(PHYSICAL_MODELING_LIBS_PATH)/libs_common
INC+= -I$(PHYSICAL_MODELING_LIBS_PATH)/libs_load

LIBS+= $(PHYSICAL_MODELING_LIBS_PATH)/libs_load/libs_load.a
LIBS+= $(PHYSICAL_MODELING_LIBS_PATH)/libs_common/libs_common_pm.a
LIBS+= $(RYSY_LIBS_PATH)/libs_dataset/libs_dataset.a
LIBS+= $(RYSY_LIBS_PATH)/libs_experiment/libs_experiment.a
LIBS+= $(RYSY_LIBS_PATH)/libs_nn/libs_nn.a
LIBS+= $(RYSY_LIBS_PATH)/libs_common/libs_common.a



CC = g++
CU = nvcc
LD = g++
OBJCOPY = objcopy
OBJDUMP = objdump
SIZE = size

# DEGUBFLAGS = -g -pg

CFLAGS = $(DEGUBFLAGS) -O2 -Os -s -Wall -Wextra -pedantic -std=c++11 $(INC)
CUDAFLAGS = -O3 -D_FORCE_INLINES -ccbin=$(CXX) -Xcompiler -fPIC -std=c++11 $(INC)

LDFLAGS = $(DEGUBFLAGS) -lm -lpthread -pthread -std=c++11 -lglut -lGL -lGLU -lX11 -ljsoncpp -L/usr/local/cuda/lib64 -lcuda -lcudart


SRCS+= $(shell find -name '*.cpp')
SRCS_CUDA+= $(shell find -name '*.cu')


OBJS = $(SRCS:.cpp=.o)
OBJS_CUDA = $(SRCS_CUDA:.cu=.oc)

all: $(ELF)
	$(SIZE) $(ELF)

$(ELF): $(LIBS) $(OBJS) $(OBJS_CUDA)
	$(LD) -o $@ $(OBJS) $(OBJS_CUDA) $(LIBS) $(LDFLAGS)

%.o: %.cpp
	$(CC) -c $(CFLAGS) $< -o $@

%.oc: %.cu
	$(CU) -c $(CUDAFLAGS) $< -o $@

clean:
	rm $(OBJS) -rf
	rm $(OBJS_CUDA) -rf
	rm $(ELF) -rf
