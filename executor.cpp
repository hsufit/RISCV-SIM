#include <iostream>

#include "executor.h"

void EXECUTOR::execute()
{

	switch (instruction_decoder->get_opcode()) {
		case INSTRUCTION_DECODER_INTERFACE::IMM_OP:
			switch (instruction_decoder->get_func3()) {
				case INSTRUCTION_DECODER_INTERFACE::ADDI_FN3:
					ADDI_E();
					break;
				case INSTRUCTION_DECODER_INTERFACE::ANDI_FN3:
					ANDI_E();
					break;
				case INSTRUCTION_DECODER_INTERFACE::XORI_FN3:
					ORI_E();
					break;
				case INSTRUCTION_DECODER_INTERFACE::ORI_FN3:
					XORI_E();
					break;
				default:
					std::cout << "INVALID: Func3 in IMM_OP :" << instruction_decoder->get_func3() << std::endl;
					break;
			}
			break;
		default:
			std::cout << "INVALID: Opcode :" << instruction_decoder->get_opcode() << std::endl;
			break;
	}
}

void EXECUTOR::ADDI_E()
{
	auto rs1 = instruction_decoder->get_rs1();
	auto rd = instruction_decoder->get_rd();

	auto value = register_file->get_value_integer(rs1) + instruction_decoder->get_imm(31, 20);
	register_file->set_value_integer(rd, value);
	//TODO: just for test, move these to decoder and logger in future
	std::cout << "ADDI" << std::endl;
	std::cout << "rs1: " << rs1 << std::endl;
	std::cout << "rd: " << rd << std::endl;
	std::cout << "value: " << value << std::endl;
}

void EXECUTOR::ANDI_E()
{
	auto rs1 = instruction_decoder->get_rs1();
	auto rd = instruction_decoder->get_rd();

	auto value = register_file->get_value_integer(rs1) & instruction_decoder->get_imm(31, 20);
	register_file->set_value_integer(rd, value);
}

void EXECUTOR::ORI_E()
{
	auto rs1 = instruction_decoder->get_rs1();
	auto rd = instruction_decoder->get_rd();

	auto value = register_file->get_value_integer(rs1) | instruction_decoder->get_imm(31, 20);
	register_file->set_value_integer(rd, value);
}

void EXECUTOR::XORI_E()
{
	auto rs1 = instruction_decoder->get_rs1();
	auto rd = instruction_decoder->get_rd();

	auto value = register_file->get_value_integer(rs1) ^ instruction_decoder->get_imm(31, 20);
	register_file->set_value_integer(rd, value);
}
