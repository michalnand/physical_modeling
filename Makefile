RYSY_LIBS_PATH=$(HOME)/libs/rysy

export RYSY_LIBS_PATH

all:
	cd libs_common && make -j4
	cd libs_python && make -j4

	cd network_train && make -j4
	cd prediction && make -j4
	cd visualisation && make -j4
	#cd vtk_test && make -j4

clean:
	cd libs_common && make clean
	cd libs_python && make clean
	
	cd network_train && make clean
	cd prediction && make clean
	cd visualisation && make clean
	#cd vtk_test && make clean
