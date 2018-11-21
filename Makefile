RYSY_LIBS_PATH=$(HOME)/libs/rysy

export RYSY_LIBS_PATH

all:
	cd libs_load && make -j4
	cd libs_model && make -j4
	cd load_test && make -j4
	cd lorenz_test && make -j4

	cd regression_test && make -j4


clean:
	cd libs_load && make clean
	cd libs_model && make clean
	cd load_test && make clean
	cd lorenz_test && make -j4

	cd regression_test && make clean
