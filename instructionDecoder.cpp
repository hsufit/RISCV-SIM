#include "instructionDecoder.h"

uint32_t INSTRUCTION_DECODER::get_opcode()
{
	return instruction_value.range(6, 0);
}

uint32_t INSTRUCTION_DECODER::get_func3()
{
	return instruction_value.range(14, 12);
}

uint32_t INSTRUCTION_DECODER::get_func7()
{
	return instruction_value.range(31,25);
}

uint32_t INSTRUCTION_DECODER::get_rs1()
{
	return instruction_value.range(19,15);
}

uint32_t INSTRUCTION_DECODER::get_rs2()
{
	return instruction_value.range(24, 20);
}

uint32_t INSTRUCTION_DECODER::get_rd()
{
	return instruction_value.range(11, 7);
}

int32_t INSTRUCTION_DECODER::get_imm(uint32_t end, uint32_t start)
{
	auto value = sc_dt::sc_int<32>(instruction_value);
	value <<= (31 - end);
	value >>= (31 - end + start);
	return value;
}

int32_t INSTRUCTION_DECODER::get_imm_j()
{
	auto value = sc_dt::sc_int<32>();
	value(20, 20) = instruction_value(31, 31);
	value(19, 12) = instruction_value(19, 12);
	value(11, 11) = instruction_value(20, 20);
	value(10, 1) = instruction_value(31, 21);
	value <<= 12;
	value >>= 12;
	return value;
}
