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
	return sc_dt::sc_int<32>(instruction_value) << (31-end) >> (31 - end + start);
}

