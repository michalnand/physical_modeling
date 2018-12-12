RYSY_LIBS_PATH=$(HOME)/libs/rysy

export RYSY_LIBS_PATH

all:
	cd libs_common && make -j4
	cd libs_dataset && make -j4
	cd libs_python && make -j4

	cd physics_test && make -j4

clean:
	cd libs_common && make clean
	cd libs_dataset && make clean
	cd libs_python && make clean
 
	cd physics_test && make clean
