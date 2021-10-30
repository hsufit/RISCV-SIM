CXX = g++
CXXFLAGS = -std=c++14

LIB_DIR=-L/usr/local/systemc-2.3.3/lib-linux64
INC_DIR=-I/usr/local/systemc-2.3.3/include
LIB=-lsystemc

export SYSTEMC_HOME=/usr/local/systemc-2.3.3
export LD_LIBRARY_PATH=$(SYSTEMC_HOME)/lib-linux64

INC_INTERFACE=addressSpaceInterface registerInterface instructionDecoderInterface executorInterface cpuInterface
SRC=main cpu memory register bus instructionDecoder executor
APP=simulator

$(APP): $(addsuffix .o, $(SRC))
	$(CXX) -o $(APP) $(^) $(LIB_DIR) $(INC_DIR) $(LIB) $(CXXFLAGS)

clean:
	rm -rf ./*.o
	rm -rf $(APP)

main.o: main.cpp
	$(CXX) -c $(CXXFLAGS) $(<) $(INC_DIR) -o $@

%.o: %.cpp %.h $(addsuffix .h,$(INC_INTERFACE))
	$(CXX) -c $(CXXFLAGS) $(<) $(INC_DIR) -o $@

format:
	astyle --style=linux --indent=tab --indent-switches --suffix=none *.cpp *.h

run: $(APP)
	./$(APP)
