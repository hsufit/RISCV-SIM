#include "instructionDecoder.h"

INSTRUCTION_DECODER_INTERFACE::Instruction INSTRUCTION_DECODER::get_instruction()
{
}

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
uint32_t INSTRUCTION_DECODER::get_func12()
{
	return instruction_value.range(31, 20);
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
	value(10, 1) = instruction_value(30, 21);
	value <<= 11;
	value >>= 11;
	return value;
}

int32_t INSTRUCTION_DECODER::get_imm_b()
{
	auto value = sc_dt::sc_int<32>();
	value(12, 12) = instruction_value(31, 31);
	value(11, 11) = instruction_value(7, 7);
	value(10, 5) = instruction_value(30, 25);
	value(4, 1) = instruction_value(11, 8);
	value <<= 19;
	value >>= 19;
	return value;
}

uint32_t INSTRUCTION_DECODER::get_imm_fence_fm()
{
	return instruction_value.range(31, 28);
}
