OUTPUT_NAME = pyphy

PHYSICAL_MODELING_LIBS_PATH=..

INC+= -I.
INC+= -I$(RYSY_LIBS_PATH)/libs_common
INC+= -I$(RYSY_LIBS_PATH)/libs_dataset
INC+= -I$(RYSY_LIBS_PATH)/libs_experiment
INC+= -I$(RYSY_LIBS_PATH)/libs_nn
INC+= -I$(PHYSICAL_MODELING_LIBS_PATH)/libs_common

# LIBS+= $(PHYSICAL_MODELING_LIBS_PATH)/libs_dataset/libs_dataset_pm.a
# LIBS+= $(PHYSICAL_MODELING_LIBS_PATH)/libs_common/libs_common_pm.a
# LIBS+= $(RYSY_LIBS_PATH)/libs_dataset/libs_dataset.a
# LIBS+= $(RYSY_LIBS_PATH)/libs_experiment/libs_experiment.a
# LIBS+= $(RYSY_LIBS_PATH)/libs_nn/libs_nn.a
# LIBS+= $(RYSY_LIBS_PATH)/libs_common/libs_common.a

SRCS+= $(shell find . -name '*.cpp')




SRCS_SWIG+= $(shell find . -name '*.i')

# CUDA_PATH = /usr/local/cuda-9.1/bin/

CC = g++
CU = nvcc
LD = g++
SWIG = swig3.0
OBJCOPY = objcopy
OBJDUMP = objdump
SIZE = size
ARCHIVE = ar


PYTHONI = $(shell python3-config --cflags)
PYTHONL = $(shell python3-config --ldflags)

CFLAGS+= -O2 -Os -fPIC -s -Wall -Wextra -pedantic -std=c++17 $(INC)

LD_OPENGLFLAGS = -lglut -lGL -lGLU -lX11
LD_CUDAFLAGS 	 = -L/usr/local/cuda/lib64 -lcuda -lcudart
LD_COMMONFLAGS = -ljsoncpp

LDFLAGS = $(LD_OPENGLFLAGS) $(LD_COMMONFLAGS) $(LD_CUDAFLAGS) -lm -lpthread -pthread -std=c++17 -lstdc++fs


OBJS 				= $(SRCS:.cpp=.o)
OBJS_CUDA 	= $(SRCS_CUDA:.cu=.oc)
OBJS_CSWIG  = $(SRCS_SWIG:.i=.cxx)
OBJS_SWIG 	= $(OBJS_CSWIG:.cxx=.oswig)



OBJS_EXTERN+= $(shell find ~/libs/rysy/libs_common -name '*.o')
OBJS_EXTERN+= $(shell find ~/libs/rysy/libs_dataset -name '*.o')
OBJS_EXTERN+= $(shell find ~/libs/rysy/libs_experiment -name '*.o')
OBJS_EXTERN+= $(shell find ~/libs/rysy/libs_nn -name '*.o')
OBJS_EXTERN+= $(shell find ~/libs/rysy/libs_preprocessing -name '*.o')
OBJS_EXTERN+= $(shell find ~/libs/rysy -name '*.oc')


OBJS_EXTERN+= $(shell find ../libs_common -name '*.o')



all: $(OBJS) $(OBJS_CUDA) $(OBJS_SWIG)
	 $(ARCHIVE) rc $(OUTPUT_NAME).a $(OBJS) $(OBJS_CUDA)
	 $(CC) -shared -fPIC $(PYTHONL) -o _$(OUTPUT_NAME).so $(OBJS_EXTERN) $(OBJS)  $(OBJS_SWIG) $(LDFLAGS)



%.o: %.cpp
	$(CC) -c $(CFLAGS) $< -o $@

%.oc: %.cu
	$(CUDA_PATH)$(CU) -c $(CUDAFLAGS) $< -o $@


%.cxx: %.i
	$(SWIG) -c++ -python $(INC) -o $@ $<

%.oswig: %.cxx
	$(CC) -c -fPIC $(INC) $(PYTHONI) $< -o $@

clean:
	rm $(OBJS) -f
	rm $(OBJS_CSWIG) -f
	rm $(OBJS_SWIG) -f
	rm $(OUTPUT_NAME).a -f
	rm _$(OUTPUT_NAME).so -f
	rm $(OUTPUT_NAME).py -f
	rm $(OUTPUT_NAME).pyc -f
