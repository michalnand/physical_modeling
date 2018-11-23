RYSY_LIBS_PATH=$(HOME)/libs/rysy

export RYSY_LIBS_PATH

all:
	cd libs_common && make -j4
	cd libs_load && make -j4
	cd load_test && make -j4
	cd regression_test && make -j4


clean:
	cd libs_common && make clean
	cd libs_load && make clean
	cd load_test && make clean
	cd regression_test && make clean
