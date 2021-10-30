export SYSTEMC_HOME=/usr/local/systemc-2.3.3
export LD_LIBRARY_PATH=$(SYSTEMC_HOME)/lib-linux64

run: simulator binary.hex
	./simulator

clean:
	rm -rf ./simulator ./binary.hex
