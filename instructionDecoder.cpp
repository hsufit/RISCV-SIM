#include "instructionDecoder.h"

INSTRUCTION_DECODER_INTERFACE::Instruction INSTRUCTION_DECODER::get_instruction()
{
	return cmmand_dispatch();
}

INSTRUCTION_DECODER_INTERFACE::Instruction INSTRUCTION_DECODER::cmmand_dispatch()
{
	switch (get_opcode()) {
		case INSTRUCTION_DECODER_INTERFACE::IMM_OP:
			return imm_dispatch();

		case INSTRUCTION_DECODER_INTERFACE::LUI_OP:
			return LUI_INSTRUCTION_ENUM;

		case INSTRUCTION_DECODER_INTERFACE::AUIPC_OP:
			return AUIPC_INSTRUCTION_ENUM;

		case INSTRUCTION_DECODER_INTERFACE::LOAD_OP:
			return load_dispatch();

		case INSTRUCTION_DECODER_INTERFACE::STORE_OP:
			return store_dispatch();

		case INSTRUCTION_DECODER_INTERFACE::JAL_OP:
			return JAL_INSTRUCTION_ENUM;

		case INSTRUCTION_DECODER_INTERFACE::JALR_OP:
			return jalr_dispatch();

		case INSTRUCTION_DECODER_INTERFACE::BRANCH_OP:
			return branch_dispatch();

		case INSTRUCTION_DECODER_INTERFACE::MISC_MEM_OP:
			return fence_dispatch();

		case INSTRUCTION_DECODER_INTERFACE::SYSTEM_OP:
			return system_dispatch();

		case INSTRUCTION_DECODER_INTERFACE::REG_OP:
			return reg_dispatch();

		default:
			std::cout << "INVALID: Opcode :" << get_opcode() << std::endl;
			return INVALID_INSTRUCTION_ENUM;

	}
}

INSTRUCTION_DECODER_INTERFACE::Instruction INSTRUCTION_DECODER::imm_dispatch()
{
	switch (get_func3()) {
		case INSTRUCTION_DECODER_INTERFACE::ADDI_FN3:
			return ADDI_INSTRUCTION_ENUM;

		case INSTRUCTION_DECODER_INTERFACE::ANDI_FN3:
			return ANDI_INSTRUCTION_ENUM;

		case INSTRUCTION_DECODER_INTERFACE::XORI_FN3:
			return ORI_INSTRUCTION_ENUM;

		case INSTRUCTION_DECODER_INTERFACE::ORI_FN3:
			return XORI_INSTRUCTION_ENUM;

		case INSTRUCTION_DECODER_INTERFACE::SLTI_FN3:
			return SLTI_INSTRUCTION_ENUM;

		case INSTRUCTION_DECODER_INTERFACE::SLTIU_FN3:
			return SLTIU_INSTRUCTION_ENUM;

		case INSTRUCTION_DECODER_INTERFACE::SLLI_FN3:
			return SLLI_INSTRUCTION_ENUM;

		case INSTRUCTION_DECODER_INTERFACE::SRLI_FN3://same as INSTRUCTION_DECODER_INTERFACE::SRAI_FN3
			if(get_imm(30, 30) == 0) {
				return SRLI_INSTRUCTION_ENUM;
			} else {
				return SRAI_INSTRUCTION_ENUM;
			}

		default:
			std::cout << "INVALID: Func3 in IMM_OP :" << get_func3() << std::endl;
			return INVALID_INSTRUCTION_ENUM;

	}
}

INSTRUCTION_DECODER_INTERFACE::Instruction INSTRUCTION_DECODER::load_dispatch()
{
	switch (get_func3()) {
		case INSTRUCTION_DECODER_INTERFACE::LB_FN3:
			return LB_INSTRUCTION_ENUM;

		case INSTRUCTION_DECODER_INTERFACE::LH_FN3:
			return LH_INSTRUCTION_ENUM;

		case INSTRUCTION_DECODER_INTERFACE::LW_FN3:
			return LW_INSTRUCTION_ENUM;

		case INSTRUCTION_DECODER_INTERFACE::LBU_FN3:
			return LBU_INSTRUCTION_ENUM;

		case INSTRUCTION_DECODER_INTERFACE::LHU_FN3:
			return LHU_INSTRUCTION_ENUM;

		default:
			std::cout << "INVALID: Func3 in LOAD_OP :" << get_func3() << std::endl;
			return INVALID_INSTRUCTION_ENUM;

	}
}

INSTRUCTION_DECODER_INTERFACE::Instruction INSTRUCTION_DECODER::store_dispatch()
{
	switch (get_func3()) {
		case INSTRUCTION_DECODER_INTERFACE::SB_FN3:
			return SB_INSTRUCTION_ENUM;

		case INSTRUCTION_DECODER_INTERFACE::SH_FN3:
			return SH_INSTRUCTION_ENUM;

		case INSTRUCTION_DECODER_INTERFACE::SW_FN3:
			return SW_INSTRUCTION_ENUM;

		default:
			std::cout << "INVALID: Func3 in STORE_OP :" << get_func3() << std::endl;
			return INVALID_INSTRUCTION_ENUM;

	}
}

INSTRUCTION_DECODER_INTERFACE::Instruction INSTRUCTION_DECODER::jalr_dispatch()
{
	switch (get_func3()) {
		case INSTRUCTION_DECODER_INTERFACE::JALR_FN3:
			return JALR_INSTRUCTION_ENUM;

		default:
			std::cout << "INVALID: Func3 in JALR_OP :" << get_func3() << std::endl;
			return INVALID_INSTRUCTION_ENUM;

	}
}

INSTRUCTION_DECODER_INTERFACE::Instruction INSTRUCTION_DECODER::branch_dispatch()
{
	switch (get_func3()) {
		case INSTRUCTION_DECODER_INTERFACE::BEQ_FN3:
			return BEQ_INSTRUCTION_ENUM;

		case INSTRUCTION_DECODER_INTERFACE::BNE_FN3:
			return BNE_INSTRUCTION_ENUM;

		case INSTRUCTION_DECODER_INTERFACE::BLT_FN3:
			return BLT_INSTRUCTION_ENUM;

		case INSTRUCTION_DECODER_INTERFACE::BGE_FN3:
			return BGE_INSTRUCTION_ENUM;

		case INSTRUCTION_DECODER_INTERFACE::BLTU_FN3:
			return BLTU_INSTRUCTION_ENUM;

		case INSTRUCTION_DECODER_INTERFACE::BGEU_FN3:
			return BGEU_INSTRUCTION_ENUM;

		default:
			std::cout << "INVALID: Func3 in BRANCH_OP :" << get_func3() << std::endl;
			return INVALID_INSTRUCTION_ENUM;

	}
}

INSTRUCTION_DECODER_INTERFACE::Instruction INSTRUCTION_DECODER::fence_dispatch()
{
	switch (get_func3()) {
		case INSTRUCTION_DECODER_INTERFACE::FENCE_FN3:
			if(0b000 == get_imm_fence_fm()) {
				return FENCE_INSTRUCTION_ENUM;
			} else if(0b100 == get_imm_fence_fm()) {
				return FENCE_TSO_INSTRUCTION_ENUM;
			} else {
				std::cout << "INVALID: fm in MISC_MEM_OP :" << get_func3() << std::endl;
				return INVALID_INSTRUCTION_ENUM;
			}

		default:
			std::cout << "INVALID: Func3 in MISC_MEM_OP :" << get_func3() << std::endl;
			return INVALID_INSTRUCTION_ENUM;

	}
}

INSTRUCTION_DECODER_INTERFACE::Instruction INSTRUCTION_DECODER::system_dispatch()
{
	switch (get_func12()) {
		case INSTRUCTION_DECODER_INTERFACE::ECALL_FN12:
			return ECALL_INSTRUCTION_ENUM;

		case INSTRUCTION_DECODER_INTERFACE::EBREAK_FN12:
			return EBREAK_INSTRUCTION_ENUM;

		default:
			std::cout << "INVALID: Func3 in MISC_MEM_OP :" << get_func3() << std::endl;
			return INVALID_INSTRUCTION_ENUM;

	}
}

INSTRUCTION_DECODER_INTERFACE::Instruction INSTRUCTION_DECODER::reg_dispatch()
{
	switch (get_func3()) {
		case INSTRUCTION_DECODER_INTERFACE::ADDI_FN3: //SUB_FN3 is the same
			switch (get_func7()) {
				case INSTRUCTION_DECODER_INTERFACE::ADD_FN7:
					return ADD_INSTRUCTION_ENUM;

				case INSTRUCTION_DECODER_INTERFACE::SUB_FN7:
					return SUB_INSTRUCTION_ENUM;

				default:
					std::cout << "INVALID: Func7 in REG_OP :" << get_func3() << std::endl;
					return INVALID_INSTRUCTION_ENUM;

			}

		case INSTRUCTION_DECODER_INTERFACE::AND_FN3:
			return AND_INSTRUCTION_ENUM;
		//do not check FN7 for readibility, refactor in future

		case INSTRUCTION_DECODER_INTERFACE::OR_FN3:
			return OR_INSTRUCTION_ENUM;
		//do not check FN7 for readibility, refactor in future

		case INSTRUCTION_DECODER_INTERFACE::XOR_FN3:
			return XOR_INSTRUCTION_ENUM;
		//do not check FN7 for readibility, refactor in future

		case INSTRUCTION_DECODER_INTERFACE::SLT_FN3:
			return SLT_INSTRUCTION_ENUM;
		//do not check FN7 for readibility, refactor in future

		case INSTRUCTION_DECODER_INTERFACE::SLTU_FN3:
			return SLTU_INSTRUCTION_ENUM;
		//do not check FN7 for readibility, refactor in future

		case INSTRUCTION_DECODER_INTERFACE::SLL_FN3:
			return SLL_INSTRUCTION_ENUM;
		//do not check FN7 for readibility, refactor in future

		case INSTRUCTION_DECODER_INTERFACE::SRL_FN3:
			switch (get_func7()) {
				case INSTRUCTION_DECODER_INTERFACE::SRL_FN7:
					return SRL_INSTRUCTION_ENUM;

				case INSTRUCTION_DECODER_INTERFACE::SRA_FN7:
					return SRA_INSTRUCTION_ENUM;

				default:
					std::cout << "INVALID: Func7 in REG_OP :" << get_func3() << std::endl;
					return INVALID_INSTRUCTION_ENUM;

			}

		default:
			std::cout << "INVALID: Func3 in REG_OP :" << get_func3() << std::endl;
			return INVALID_INSTRUCTION_ENUM;

	}

}

void INSTRUCTION_DECODER::log_instruction(uint32_t current_pc, uint32_t target_pc, uint32_t rs1Value, uint32_t rs2Value, uint32_t rdValue,int32_t immValue)
{

	auto instructionName = instruction_name_map[get_instruction()];
	auto rd = get_rd();
	auto rs1 = get_rs1();
	auto rs2 = get_rs2();

	std::cout << "current_pc: 0x" << std::hex << current_pc
	          << " target_pc: 0x" << std::hex << target_pc
		  << " " << instructionName
		  << " " << std::dec  << rs1
		  << " " << std::dec  << rs2
		  << " " << std::dec  << rd
	          << " rs1Value: 0x" << std::hex << rs1Value
	          << " rs2Value: 0x" << std::hex << rs2Value
	          << " rdValue: 0x" << std::hex << rdValue
	          << " immValue: 0x" << std::hex << immValue
		  << std::endl;
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
