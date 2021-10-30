run: test/binary.hex simulator/simulator
	cp test/binary.hex ./bin
	cp simulator/simulator ./bin
	make -C bin/

test/binary.hex:
	make -C test/

simulator/simulator:
	make -C simulator/

clean:
	make -C test/ -f Makefile clean
	make -C bin/ -f Makefile clean
	make -C simulator/ -f Makefile clean

