LIB_DIR=-L/usr/local/systemc-2.3.3/lib-linux64
INC_DIR=-I/usr/local/systemc-2.3.3/include
LIB=-lsystemc

export SYSTEMC_HOME=/usr/local/systemc-2.3.3
export LD_LIBRARY_PATH=$(SYSTEMC_HOME)/lib-linux64

HEADERS=cpu memory register registerInterface
SRC=main cpu memory register
APP=hello

hello: $(addsuffix .cpp, $(SRC)) $(addsuffix .h, $(HEADERS))
	g++ -o $(APP) $(^) $(LIB_DIR) $(INC_DIR) $(LIB) -std=c++14

clean:
	rm -rf $(APP)

format:
	astyle --style=linux --indent=tab --indent-switches --suffix=none *.cpp *.h

run: $(APP)
	./$(APP)
