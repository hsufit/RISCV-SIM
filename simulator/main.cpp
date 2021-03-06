#include "systemc.h"

#include "cpu.h"
#include "register.h"
#include "bus.h"
#include "instructionDecoder.h"
#include "executor.h"

int sc_main(int argc,char** argv)
{
	CPU cpu("cpu");
	cpu.set_register_file(std::make_shared<REGISTER>());
	cpu.set_address_space(std::make_shared<BUS>("bus"));
	cpu.set_instruction_decoder(std::make_shared<INSTRUCTION_DECODER>());
	cpu.set_executor(std::make_shared<EXECUTOR>());
	sc_core::sc_start();
	return 0;
}




