LIB_DIR=-L/usr/local/systemc-2.3.3/lib-linux64
INC_DIR=-I/usr/local/systemc-2.3.3/include
LIB=-lsystemc

export SYSTEMC_HOME=/usr/local/systemc-2.3.3
export LD_LIBRARY_PATH=$(SYSTEMC_HOME)/lib-linux64

SRC=main memory
APP=hello

hello: $(addsuffix .cpp, $(SRC))
	g++ -o $(APP) $(^) $(LIB_DIR) $(INC_DIR) $(LIB) -std=c++14

clean:
	rm -rf $(APP)

run: $(APP)
	./$(APP)
