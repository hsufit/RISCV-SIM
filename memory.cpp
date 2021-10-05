#include "memory.h"

MEMORY::MEMORY(sc_module_name name) : sc_module(name)
{
	auto binary = std::array<uint32_t, 4096> {
		0b000000000001'00000'000'00001'0010011, //ADDI x1 = x0 + 1
		0b111111111111'00001'000'00010'0010011, //ADDI x2 = x1 + (-1)
		0b000000000000'00000'000'00000'0010011, //NOP
		0b100000000000'00001'010'00000'0010011, //SLTI x1 = x0 < negativeNum
		0b100000000000'00010'011'00010'0010011, //SLTU x2 = x0 < PositiveNum
		0b0000000'11111'00010'001'00011'0010011, //SLLI x3 = x2 << 31
		0b0000000'00001'00011'101'00100'0010011, //SRLI x4 = x2 >> 1
		0b0100000'00001'00011'101'00101'0010011, //SRAI x5 = x2 >> 1
		0b00000000000000000001'00110'0110111, //LUI x6 = 1 << 12
		0b00000000000000000001'00110'0010111, //AUIPC x6 = pc + (1 << 12)
		0b000000000100'00000'001'00111'0000011, //LH x7 = sign_ext(read(4, 2))
		0b000000000100'00000'101'01000'0000011, //LHU x8 = read(4, 2)
		0b0100000'00111'00000'001'00000'0100011, //SH write( 1024, x7, 2))
		0b00000000100000000000'01001'1101111, //JAL x9 = pc + 4; pc = pc + 8
		0b0000000'00000'00000'000'01000'1100011, //BEQ pc = current_pc + (x0 == x0 ? imm : 4) <--bad guy that ISA manual talk about
		0b000000000000'01001'000'00000'1100111, //JALR x0 = pc + 4; pc = x9 + 0
		0b000000000000'00000'000'00000'1110011, //ECALL

	};
	programLoader(binary);
	memory_socket.register_b_transport(this, &MEMORY::b_transport);
}
void MEMORY::programLoader(std::array<uint32_t, 4096> &binary)
{
	for(auto instruction: binary) {
		dataMemory.push_back(instruction & 0xFF);
		dataMemory.push_back(instruction >> 8 & 0xFF);
		dataMemory.push_back(instruction >> 16 & 0xFF);
		dataMemory.push_back(instruction >> 24 & 0xFF);

		if(instruction != 0)
			std::cout << "inst: " << instruction << std::endl;
	}
}

void MEMORY::b_transport(tlm::tlm_generic_payload &trans, sc_core::sc_time &delay)
{
	delay = sc_core::SC_ZERO_TIME;
	tlm::tlm_command cmd = trans.get_command();
	sc_dt::uint64 adr = trans.get_address();
	unsigned char *ptr = trans.get_data_ptr();
	unsigned int len = trans.get_data_length();

	trans.set_response_status(tlm::TLM_OK_RESPONSE);

	for(int i =  0; i < len; i++) {
		if(adr < dataMemory.size()) {
			if(cmd == tlm::TLM_READ_COMMAND) {
				((char *)ptr)[i] = dataMemory[adr + i];
				//std::cout << "addr: " << adr + i << "--" << (int)dataMemory[adr + i] << std::endl;
			} else if(cmd == tlm::TLM_WRITE_COMMAND) {
				dataMemory[adr + i] = ((char *)ptr)[i];
				//std::cout << "addr: " << adr + i << "--" << (int)dataMemory[adr + i] << std::endl;
			} else {
				std::cout << "unsupported operation" << adr << "!!" << std::endl;
			}
		} else {
			trans.set_response_status(tlm::TLM_BURST_ERROR_RESPONSE);
			std::cout << "error an address " << adr << "!!" << std::endl;
			return;
		}
	}
}
