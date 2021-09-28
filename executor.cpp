#include <iostream>

#include "executor.h"

void EXECUTOR::execute()
{
	new_pc = register_file->get_pc() + 4;

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
				case INSTRUCTION_DECODER_INTERFACE::SLTI_FN3:
					SLTI_E();
					break;
				case INSTRUCTION_DECODER_INTERFACE::SLTIU_FN3:
					SLTIU_E();
					break;
				case INSTRUCTION_DECODER_INTERFACE::SLLI_FN3:
					SLLI_E();
					break;
				case INSTRUCTION_DECODER_INTERFACE::SRLI_FN3://same as INSTRUCTION_DECODER_INTERFACE::SRAI_FN3
					if(instruction_decoder->get_imm(30, 30) == 0)
					{
						SRLI_E();
					}
					else
					{
						SRAI_E();
					}
					break;
				default:
					std::cout << "INVALID: Func3 in IMM_OP :" << instruction_decoder->get_func3() << std::endl;
					break;
			}
			break;
		case INSTRUCTION_DECODER_INTERFACE::LUI_OP:
			LUI_E();
			break;
		case INSTRUCTION_DECODER_INTERFACE::AUIPC_OP:
			AUIPC_E();
			break;
		default:
			std::cout << "INVALID: Opcode :" << instruction_decoder->get_opcode() << std::endl;
			break;
	}

	register_file->set_pc(new_pc);
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

void EXECUTOR::SLTI_E()
{
	auto rs1 = instruction_decoder->get_rs1();
	auto rd = instruction_decoder->get_rd();

	auto value = register_file->get_value_integer(rs1) < instruction_decoder->get_imm(31, 20);
	register_file->set_value_integer(rd, value);
	//TODO: just for test, move these to decoder and logger in future
	std::cout << "SLTI" << std::endl;
	std::cout << "rs1: " << rs1 << std::endl;
	std::cout << "rd: " << rd << std::endl;
	std::cout << "value: " << value << std::endl;
}

void EXECUTOR::SLTIU_E()
{
	auto rs1 = instruction_decoder->get_rs1();
	auto rd = instruction_decoder->get_rd();

	auto value = register_file->get_value_integer(rs1) < (uint32_t) instruction_decoder->get_imm(31, 20);
	register_file->set_value_integer(rd, value);
	//TODO: just for test, move these to decoder and logger in future
	std::cout << "SLTIU" << std::endl;
	std::cout << "rs1: " << rs1 << std::endl;
	std::cout << "rd: " << rd << std::endl;
	std::cout << "value: " << value << std::endl;
}

void EXECUTOR::SLLI_E()
{
	auto rs1 = instruction_decoder->get_rs1();
	auto rd = instruction_decoder->get_rd();

	auto value = register_file->get_value_integer(rs1) << (uint32_t) instruction_decoder->get_imm(24, 20);
	register_file->set_value_integer(rd, value);
	//TODO: just for test, move these to decoder and logger in future
	std::cout << "SLLI" << std::endl;
	std::cout << "rs1: " << rs1 << std::endl;
	std::cout << "rd: " << rd << std::endl;
	std::cout << "value: " << value << std::endl;
}
void EXECUTOR::SRLI_E()
{
	auto rs1 = instruction_decoder->get_rs1();
	auto rd = instruction_decoder->get_rd();

	auto value = (uint32_t) register_file->get_value_integer(rs1) >> (uint32_t) instruction_decoder->get_imm(24, 20);
	register_file->set_value_integer(rd, value);
	//TODO: just for test, move these to decoder and logger in future
	std::cout << "SRLI" << std::endl;
	std::cout << "rs1: " << rs1 << std::endl;
	std::cout << "rd: " << rd << std::endl;
	std::cout << "value: " << value << std::endl;
}
void EXECUTOR::SRAI_E()
{
	auto rs1 = instruction_decoder->get_rs1();
	auto rd = instruction_decoder->get_rd();

	auto value = register_file->get_value_integer(rs1) >> (uint32_t) instruction_decoder->get_imm(24, 20);
	register_file->set_value_integer(rd, value);
	//TODO: just for test, move these to decoder and logger in future
	std::cout << "SRAI" << std::endl;
	std::cout << "rs1: " << rs1 << std::endl;
	std::cout << "rd: " << rd << std::endl;
	std::cout << "value: " << value << std::endl;
}
void EXECUTOR::LUI_E()
{
	auto rd = instruction_decoder->get_rd();

	auto value = (instruction_decoder->get_imm(31, 12) << 12);
	register_file->set_value_integer(rd, value);
	//TODO: just for test, move these to decoder and logger in future
	std::cout << "LUI" << std::endl;
	std::cout << "rd: " << rd << std::endl;
	std::cout << "value: " << value << std::endl;
}
void EXECUTOR::AUIPC_E()
{
	auto rd = instruction_decoder->get_rd();

	auto value = register_file->get_pc() + (instruction_decoder->get_imm(31, 12) << 12);
	register_file->set_value_integer(rd, value);
	//TODO: just for test, move these to decoder and logger in future
	std::cout << "AUIPC" << std::endl;
	std::cout << "rd: " << rd << std::endl;
	std::cout << "value: " << value << std::endl;
}
