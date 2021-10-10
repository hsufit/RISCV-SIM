#include "cpu.h"

CPU::CPU(sc_module_name name) : sc_module(name)
{
	SC_HAS_PROCESS(CPU);
	SC_THREAD(cpu_thread);
}

void CPU::cpu_thread(void)
{
	while(true) {
		step();
		wait(delay);
	}
}

void CPU::step()
{
	uint32_t instruction = address_space->read(register_file->get_pc(), 4);

	instruction_decoder->set_instruction(instruction);
	executor->execute();
}

void CPU::set_register_file(const std::shared_ptr<REGISTER_INTERFACE> &instance)
{
	register_file = instance;
	if(executor != nullptr) {
		executor->set_register_file(register_file);
	}
}

void CPU::set_address_space(const std::shared_ptr<ADDRESS_SPACE_INTERFACE> &instance)
{
	address_space = instance;
	if(executor != nullptr) {
		executor->set_address_space(address_space);
	}
}

void CPU::set_instruction_decoder(const std::shared_ptr<INSTRUCTION_DECODER_INTERFACE> &instance)
{
	instruction_decoder = instance;
	if(executor != nullptr) {
		executor->set_instruction_decoder(instruction_decoder);
	}
}

void CPU::set_executor(const std::shared_ptr<EXECUTOR_INTERFACE> &instance)
{
	executor = instance;

	executor->set_cpu(std::shared_ptr<CPU_INTERFACE>(this, [](CPU *p) {}));

	if(instruction_decoder != nullptr) {
		executor->set_instruction_decoder(instruction_decoder);
	}

	if(register_file != nullptr) {
		executor->set_register_file(register_file);
	}

	if(address_space != nullptr) {
		executor->set_address_space(address_space);
	}

}

void CPU::raise_exception(uint32_t cause)
{
	switch(cause) {
		case CPU_INTERFACE::INSTRUCTION_ADDRESS_MISALIGNED_EXCEPTION_CAUSE:
			std::cout << "Address Misalignment, end simulation!" << std::endl;
			break;
		case CPU_INTERFACE::INSTRUCTION_ACCESS_FAULT_EXCEPTION_CAUSE:
			break;
		case CPU_INTERFACE::ILLEGAL_INSTRUCTION_EXCEPTION_CAUSE:
			std::cout << "Illegal Instruction, end simulation!" << std::endl;
			break;
		case CPU_INTERFACE::BREAKPOINT_EXCEPTION_CAUSE:
			std::cout << "EBREAK, end simulation!" << std::endl;
			break;
		case CPU_INTERFACE::LOAD_ADDRESS_MISALIGNED_EXCEPTION_CAUSE:
			std::cout << "Load Address Misalignment, end simulation!" << std::endl;
			break;
		case CPU_INTERFACE::LOAD_ACCESS_FAULT_EXCEPTION_CAUSE:
			std::cout << "Access Fault, end simulation!" << std::endl;
			break;
		case CPU_INTERFACE::STORE_AMO_ADDRESS_MISALIGNED_EXCEPTION_CAUSE:
			std::cout << "Store and AMO Address Misalignment, end simulation!" << std::endl;
			break;
		case CPU_INTERFACE::STORE_AMO_ACCESS_FAULT_EXCEPTION_CAUSE:
			std::cout << "Store and AMO Access Fault, end simulation!" << std::endl;
			break;
		case CPU_INTERFACE::ENVIRONMENT_CALL_FROM_U_MODE_EXCEPTION_CAUSE:
			break;
		case CPU_INTERFACE::ENVIRONMENT_CALL_FROM_S_MODE_EXCEPTION_CAUSE:
			break;
		case CPU_INTERFACE::RESERVED_EXCEPTION_CAUSE:
			break;
		case CPU_INTERFACE::ENVIRONMENT_CALL_FROM_M_MODE_EXCEPTION_CAUSE:
			std::cout << "ECALL, end simulation!" << std::endl;
			break;
		case CPU_INTERFACE::INSTRUCTION_PAGE_FAULT_EXCEPTION_CAUSE:
			break;
		case CPU_INTERFACE::LOAD_PAGE_FAULT_EXCEPTION_CAUSE:
			break;
		case CPU_INTERFACE::RESERVED_FOR_FUTURE_STANDARD_USE_EXCEPTION_CAUSE:
			break;
		case CPU_INTERFACE::STORE_AMO_PAGE_FAULT_EXCEPTION_CAUSE:
			break;
		default:
			std::cout << "unsupported exception cause: " << cause << std::endl;
			break;
	}

	std::cout << "exception!" << std::endl;
	sc_core::sc_stop();
}

void CPU::raise_interrupt(uint32_t cause)
{
	switch (cause) {
		case CPU_INTERFACE::USER_SOFTWARE_INTERRUPT_INTERRUPT_CAUSE:
			break;
		case CPU_INTERFACE::SUPERVISOR_SOFTWARE_INTERRUPT_INTERRUPT_CAUSE:
			break;
		//case CPU_INTERFACE::RESERVED_FOR_FUTURE_STANDARD_USE_INTERRUPT_CAUSE:
		//	break;
		case CPU_INTERFACE::MACHINE_SOFTWARE_INTERRUPT_INTERRUPT_CAUSE:
			break;
		case CPU_INTERFACE::USER_TIMER_INTERRUPT_INTERRUPT_CAUSE:
			break;
		case CPU_INTERFACE::SUPERVISOR_TIMER_INTERRUPT_INTERRUPT_CAUSE:
			break;
		//case CPU_INTERFACE::RESERVED_FOR_FUTURE_STANDARD_USE_INTERRUPT_CAUSE:
		//	break;
		case CPU_INTERFACE::MACHINE_TIMER_INTERRUPT_INTERRUPT_CAUSE:
			break;
		case CPU_INTERFACE::USER_EXTERNAL_INTERRUPT_INTERRUPT_CAUSE:
			break;
		case CPU_INTERFACE::SUPERVISOR_EXTERNAL_INTERRUPT_INTERRUPT_CAUSE:
			break;
		//case CPU_INTERFACE::RESERVED_FOR_FUTURE_STANDARD_USE_INTERRUPT_CAUSE:
		//	break;
		case CPU_INTERFACE::MACHINE_EXTERNAL_INTERRUPT_INTERRUPT_CAUSE:
			break;
		default:
			std::cout << "unsupported interrupt cause: " << cause << std::endl;
			break;
	}
	std::cout << "interrupt!" << std::endl;
	sc_core::sc_stop();
}

