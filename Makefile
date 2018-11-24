RYSY_LIBS_PATH=$(HOME)/libs/rysy

export RYSY_LIBS_PATH

all:
	cd libs_common && make -j4
	cd libs_load && make -j4
	cd libs_python && make -j4

	cd trajectory_learn && make -j4


clean:
	cd libs_common && make clean
	cd libs_load && make clean
	cd libs_python && make clean

	cd trajectory_learn && make clean
