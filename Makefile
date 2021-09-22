CXX = g++
CXXFLAGS = -std=c++14

LIB_DIR=-L/usr/local/systemc-2.3.3/lib-linux64
INC_DIR=-I/usr/local/systemc-2.3.3/include
LIB=-lsystemc

export SYSTEMC_HOME=/usr/local/systemc-2.3.3
export LD_LIBRARY_PATH=$(SYSTEMC_HOME)/lib-linux64

SRC=main cpu memory register bus
APP=simulator

$(APP): $(addsuffix .o, $(SRC))
	$(CXX) -o $(APP) $(^) $(LIB_DIR) $(INC_DIR) $(LIB) $(CXXFLAGS)

clean:
	rm -rf $(APP)

%.o: %.cpp %.h
	$(CXX) -c $(CXXFLAGS) $(<) $(INC_DIR) -o $@

format:
	astyle --style=linux --indent=tab --indent-switches --suffix=none *.cpp *.h

run: $(APP)
	./$(APP)
