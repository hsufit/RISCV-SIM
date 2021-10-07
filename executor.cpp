#include <iostream>

#include "executor.h"

#define INSTRUCTION_ALIGNMENT 4
#define LOAD_STORE_ALIGNMENT_W 4
#define LOAD_STORE_ALIGNMENT_HW 4

bool isAlignment(uint32_t address, unsigned int baseNumber)
{
	if(0 == address % baseNumber) {
		return true;
	} else {
		return false;
	}
}


void EXECUTOR::execute()
{
	new_pc = register_file->get_pc() + 4;
	cmmand_dispatch();
	register_file->set_pc(new_pc);
}

void EXECUTOR::cmmand_dispatch()
{
	switch (instruction_decoder->get_opcode()) {
		case INSTRUCTION_DECODER_INTERFACE::IMM_OP:
			imm_dispatch();
			break;
		case INSTRUCTION_DECODER_INTERFACE::LUI_OP:
			LUI_E();
			break;
		case INSTRUCTION_DECODER_INTERFACE::AUIPC_OP:
			AUIPC_E();
			break;
		case INSTRUCTION_DECODER_INTERFACE::LOAD_OP:
			load_dispatch();
			break;
		case INSTRUCTION_DECODER_INTERFACE::STORE_OP:
			store_dispatch();
			break;
		case INSTRUCTION_DECODER_INTERFACE::JAL_OP:
			JAL_E();
			break;
		case INSTRUCTION_DECODER_INTERFACE::JALR_OP:
			jalr_dispatch();
			break;
		case INSTRUCTION_DECODER_INTERFACE::BRANCH_OP:
			branch_dispatch();
			break;
		case INSTRUCTION_DECODER_INTERFACE::MISC_MEM_OP:
			fence_dispatch();
			break;
		case INSTRUCTION_DECODER_INTERFACE::SYSTEM_OP:
			system_dispatch();
			break;
		case INSTRUCTION_DECODER_INTERFACE::REG_OP:
			reg_dispatch();
			break;
		default:
			std::cout << "INVALID: Opcode :" << instruction_decoder->get_opcode() << std::endl;
			break;
	}
}

void EXECUTOR::imm_dispatch()
{
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
			if(instruction_decoder->get_imm(30, 30) == 0) {
				SRLI_E();
			} else {
				SRAI_E();
			}
			break;
		default:
			std::cout << "INVALID: Func3 in IMM_OP :" << instruction_decoder->get_func3() << std::endl;
			break;
	}
}

void EXECUTOR::load_dispatch()
{
	switch (instruction_decoder->get_func3()) {
		case INSTRUCTION_DECODER_INTERFACE::LB_FN3:
			LB_E();
			break;
		case INSTRUCTION_DECODER_INTERFACE::LH_FN3:
			LH_E();
			break;
		case INSTRUCTION_DECODER_INTERFACE::LW_FN3:
			LW_E();
			break;
		case INSTRUCTION_DECODER_INTERFACE::LBU_FN3:
			LBU_E();
			break;
		case INSTRUCTION_DECODER_INTERFACE::LHU_FN3:
			LHU_E();
			break;
		default:
			std::cout << "INVALID: Func3 in LOAD_OP :" << instruction_decoder->get_func3() << std::endl;
			break;
	}
}

void EXECUTOR::store_dispatch()
{
	switch (instruction_decoder->get_func3()) {
		case INSTRUCTION_DECODER_INTERFACE::SB_FN3:
			SB_E();
			break;
		case INSTRUCTION_DECODER_INTERFACE::SH_FN3:
			SH_E();
			break;
		case INSTRUCTION_DECODER_INTERFACE::SW_FN3:
			SW_E();
			break;
		default:
			std::cout << "INVALID: Func3 in STORE_OP :" << instruction_decoder->get_func3() << std::endl;
			break;
	}
}

void EXECUTOR::jalr_dispatch()
{
	switch (instruction_decoder->get_func3()) {
		case INSTRUCTION_DECODER_INTERFACE::JALR_FN3:
			JALR_E();
			break;
		default:
			std::cout << "INVALID: Func3 in JALR_OP :" << instruction_decoder->get_func3() << std::endl;
			break;
	}
}

void EXECUTOR::branch_dispatch()
{
	switch (instruction_decoder->get_func3()) {
		case INSTRUCTION_DECODER_INTERFACE::BEQ_FN3:
			BEQ_E();
			break;
		case INSTRUCTION_DECODER_INTERFACE::BNE_FN3:
			BNE_E();
			break;
		case INSTRUCTION_DECODER_INTERFACE::BLT_FN3:
			BLT_E();
			break;
		case INSTRUCTION_DECODER_INTERFACE::BGE_FN3:
			BGE_E();
			break;
		case INSTRUCTION_DECODER_INTERFACE::BLTU_FN3:
			BLTU_E();
			break;
		case INSTRUCTION_DECODER_INTERFACE::BGEU_FN3:
			BGEU_E();
			break;
		default:
			std::cout << "INVALID: Func3 in BRANCH_OP :" << instruction_decoder->get_func3() << std::endl;
			break;
	}
}

void EXECUTOR::fence_dispatch()
{
	switch (instruction_decoder->get_func3()) {
		case INSTRUCTION_DECODER_INTERFACE::FENCE_FN3:
			if(0b000 == instruction_decoder->get_imm_fence_fm()) {
				FENCE_E();
			} else if(0b100 == instruction_decoder->get_imm_fence_fm()) {
				FENCE_TSO_E();
			} else {
				std::cout << "INVALID: fm in MISC_MEM_OP :" << instruction_decoder->get_func3() << std::endl;
			}
			break;
		default:
			std::cout << "INVALID: Func3 in MISC_MEM_OP :" << instruction_decoder->get_func3() << std::endl;
			break;
	}
}

void EXECUTOR::system_dispatch()
{
	switch (instruction_decoder->get_func12()) {
		case INSTRUCTION_DECODER_INTERFACE::ECALL_FN12:
			ECALL_E();
			break;
		case INSTRUCTION_DECODER_INTERFACE::EBREAK_FN12:
			EBREAK_E();
			break;
		default:
			std::cout << "INVALID: Func3 in MISC_MEM_OP :" << instruction_decoder->get_func3() << std::endl;
			break;
	}
}

void EXECUTOR::reg_dispatch()
{
	switch (instruction_decoder->get_func3()) {
		case INSTRUCTION_DECODER_INTERFACE::ADDI_FN3: //SUB_FN3 is the same
			switch (instruction_decoder->get_func7()) {
				case INSTRUCTION_DECODER_INTERFACE::ADD_FN7:
					ADD_E();
					break;
				case INSTRUCTION_DECODER_INTERFACE::SUB_FN7:
					SUB_E();
					break;
				default:
					std::cout << "INVALID: Func7 in REG_OP :" << instruction_decoder->get_func3() << std::endl;
					break;
			}
			break;
		case INSTRUCTION_DECODER_INTERFACE::AND_FN3:
			AND_E();
			//do not check FN7 for readibility, refactor in future
			break;
		case INSTRUCTION_DECODER_INTERFACE::OR_FN3:
			OR_E();
			//do not check FN7 for readibility, refactor in future
			break;
		case INSTRUCTION_DECODER_INTERFACE::XOR_FN3:
			XOR_E();
			//do not check FN7 for readibility, refactor in future
			break;
		default:
			std::cout << "INVALID: Func3 in REG_OP :" << instruction_decoder->get_func3() << std::endl;
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


void EXECUTOR::LB_E()
{
	auto rs1 = instruction_decoder->get_rs1();
	auto rd = instruction_decoder->get_rd();
	auto addr = register_file->get_value_integer(rs1) + (uint32_t) instruction_decoder->get_imm(31, 20);

	auto value = address_space->read(addr, 1) << 24 >> 24;
	register_file->set_value_integer(rd, value);
}

void EXECUTOR::LH_E()
{
	auto rs1 = instruction_decoder->get_rs1();
	auto rd = instruction_decoder->get_rd();
	auto addr = register_file->get_value_integer(rs1) + (uint32_t) instruction_decoder->get_imm(31, 20);

	if(!isAlignment(addr, LOAD_STORE_ALIGNMENT_HW)) {
		cpu->raise_exception(CPU_INTERFACE::LOAD_ADDRESS_MISALIGNED_EXCEPTION_CAUSE);
	}

	auto value = address_space->read(addr, 2) << 16 >> 16;
	register_file->set_value_integer(rd, value);
	std::cout << "LH" << std::endl;
	std::cout << "rs1: " << rs1 << std::endl;
	std::cout << "rd: " << rd << std::endl;
	std::cout << "addr: " << addr << std::endl;
	std::cout << "value: " << value << std::endl;
}

void EXECUTOR::LW_E()
{
	auto rs1 = instruction_decoder->get_rs1();
	auto rd = instruction_decoder->get_rd();
	auto addr = register_file->get_value_integer(rs1) + (uint32_t) instruction_decoder->get_imm(31, 20);

	if(!isAlignment(addr, LOAD_STORE_ALIGNMENT_W)) {
		cpu->raise_exception(CPU_INTERFACE::LOAD_ADDRESS_MISALIGNED_EXCEPTION_CAUSE);
	}

	auto value = address_space->read(addr, 4);
	register_file->set_value_integer(rd, value);
}

void EXECUTOR::LBU_E()
{
	auto rs1 = instruction_decoder->get_rs1();
	auto rd = instruction_decoder->get_rd();
	auto addr = register_file->get_value_integer(rs1) + (uint32_t) instruction_decoder->get_imm(31, 20);

	auto value = address_space->read(addr, 1);
	register_file->set_value_integer(rd, value);
}

void EXECUTOR::LHU_E()
{
	auto rs1 = instruction_decoder->get_rs1();
	auto rd = instruction_decoder->get_rd();
	auto addr = register_file->get_value_integer(rs1) + (uint32_t) instruction_decoder->get_imm(31, 20);

	if(!isAlignment(addr, LOAD_STORE_ALIGNMENT_HW)) {
		cpu->raise_exception(CPU_INTERFACE::LOAD_ADDRESS_MISALIGNED_EXCEPTION_CAUSE);
	}

	auto value = address_space->read(addr, 2);
	register_file->set_value_integer(rd, value);
	std::cout << "LHU" << std::endl;
	std::cout << "rs1: " << rs1 << std::endl;
	std::cout << "rd: " << rd << std::endl;
	std::cout << "addr: " << addr << std::endl;
	std::cout << "value: " << value << std::endl;
}

void EXECUTOR::SB_E()
{
	auto rs1 = instruction_decoder->get_rs1();
	auto rs2 = instruction_decoder->get_rs2();

	auto offset =  (instruction_decoder->get_imm(31, 25) << 5) |
	               (instruction_decoder->get_imm(11, 7) & 0x1F);
	auto addr = register_file->get_value_integer(rs1) + offset;
	address_space->write(addr, register_file->get_value_integer(rs2), 1);
}

void EXECUTOR::SH_E()
{
	auto rs1 = instruction_decoder->get_rs1();
	auto rs2 = instruction_decoder->get_rs2();

	auto offset =  (instruction_decoder->get_imm(31, 25) << 5) |
	               (instruction_decoder->get_imm(11, 7) & 0x1F);
	auto addr = register_file->get_value_integer(rs1) + offset;

	if(!isAlignment(addr, LOAD_STORE_ALIGNMENT_HW)) {
		cpu->raise_exception(CPU_INTERFACE::STORE_AMO_ADDRESS_MISALIGNED_EXCEPTION_CAUSE);
	}

	address_space->write(addr, register_file->get_value_integer(rs2), 2);
	std::cout << "SH" << std::endl;
	std::cout << "rs1: " << rs1 << std::endl;
	std::cout << "rs2: " << rs2 << std::endl;
	std::cout << "addr: " << addr << std::endl;
}

void EXECUTOR::SW_E()
{
	auto rs1 = instruction_decoder->get_rs1();
	auto rs2 = instruction_decoder->get_rs2();

	auto offset =  (instruction_decoder->get_imm(31, 25) << 5) |
	               (instruction_decoder->get_imm(11, 7) & 0x1F);
	auto addr = register_file->get_value_integer(rs1) + offset;

	if(!isAlignment(addr, LOAD_STORE_ALIGNMENT_W)) {
		cpu->raise_exception(CPU_INTERFACE::STORE_AMO_ADDRESS_MISALIGNED_EXCEPTION_CAUSE);
	}

	address_space->write(addr, register_file->get_value_integer(rs2), 4);
}

void EXECUTOR::JAL_E()
{
	auto offset = instruction_decoder->get_imm_j();
	auto rd = instruction_decoder->get_rd();
	auto addr = register_file->get_pc() + offset;

	if(!isAlignment(addr, INSTRUCTION_ALIGNMENT)) {
		cpu->raise_exception(CPU_INTERFACE::INSTRUCTION_ADDRESS_MISALIGNED_EXCEPTION_CAUSE);
	}

	register_file->set_value_integer(rd, new_pc);
	new_pc = addr;
	std::cout << "JAL" << std::endl;
	std::cout << "rd: " << rd << std::endl;
	std::cout << "new_pc: " << new_pc << std::endl;
}

void EXECUTOR::JALR_E()
{
	auto offset = instruction_decoder->get_imm(31, 20);
	auto rs1 = instruction_decoder->get_rs1();
	auto rd = instruction_decoder->get_rd();
	auto addr = (register_file->get_value_integer(rs1) + offset) & ~0x1;

	if(!isAlignment(addr, INSTRUCTION_ALIGNMENT)) {
		cpu->raise_exception(CPU_INTERFACE::INSTRUCTION_ADDRESS_MISALIGNED_EXCEPTION_CAUSE);
	}

	register_file->set_value_integer(rd, new_pc);
	new_pc = addr;
	std::cout << "JALR" << std::endl;
	std::cout << "rs1: " << rs1 << std::endl;
	std::cout << "rd: " << rd << std::endl;
	std::cout << "new_pc: " << new_pc << std::endl;
}

void EXECUTOR::BEQ_E()
{
	auto offset = instruction_decoder->get_imm_b();
	auto rs1 = instruction_decoder->get_rs1();
	auto rs2 = instruction_decoder->get_rs2();
	auto addr = register_file->get_pc() +
	            (register_file->get_value_integer(rs1) == register_file->get_value_integer(rs1) ?
	             offset : 4);

	if(!isAlignment(addr, INSTRUCTION_ALIGNMENT)) {
		cpu->raise_exception(CPU_INTERFACE::INSTRUCTION_ADDRESS_MISALIGNED_EXCEPTION_CAUSE);
	}

	new_pc = addr;
	std::cout << "BEQ" << std::endl;
	std::cout << "rs1: " << rs1 << std::endl;
	std::cout << "rs2: " << rs2 << std::endl;
	std::cout << "offset: " << offset << std::endl;
	std::cout << "new_pc: " << new_pc << std::endl;
}

void EXECUTOR::BNE_E()
{
	auto offset = instruction_decoder->get_imm_b();
	auto rs1 = instruction_decoder->get_rs1();
	auto rs2 = instruction_decoder->get_rs2();
	auto addr = register_file->get_pc() +
	            (register_file->get_value_integer(rs1) != register_file->get_value_integer(rs1) ?
	             offset : 4);

	if(!isAlignment(addr, INSTRUCTION_ALIGNMENT)) {
		cpu->raise_exception(CPU_INTERFACE::INSTRUCTION_ADDRESS_MISALIGNED_EXCEPTION_CAUSE);
	}

	new_pc = addr;
}

void EXECUTOR::BLT_E()
{
	auto offset = instruction_decoder->get_imm_b();
	auto rs1 = instruction_decoder->get_rs1();
	auto rs2 = instruction_decoder->get_rs2();
	auto addr = register_file->get_pc() +
	            (register_file->get_value_integer(rs1) < register_file->get_value_integer(rs1) ?
	             offset : 4);

	if(!isAlignment(addr, INSTRUCTION_ALIGNMENT)) {
		cpu->raise_exception(CPU_INTERFACE::INSTRUCTION_ADDRESS_MISALIGNED_EXCEPTION_CAUSE);
	}

	new_pc = addr;
}

void EXECUTOR::BGE_E()
{
	auto offset = instruction_decoder->get_imm_b();
	auto rs1 = instruction_decoder->get_rs1();
	auto rs2 = instruction_decoder->get_rs2();
	auto addr = register_file->get_pc() +
	            (register_file->get_value_integer(rs1) >= register_file->get_value_integer(rs1) ?
	             offset : 4);

	if(!isAlignment(addr, INSTRUCTION_ALIGNMENT)) {
		cpu->raise_exception(CPU_INTERFACE::INSTRUCTION_ADDRESS_MISALIGNED_EXCEPTION_CAUSE);
	}

	new_pc = addr;
}

void EXECUTOR::BLTU_E()
{
	auto offset = instruction_decoder->get_imm_b();
	auto rs1 = instruction_decoder->get_rs1();
	auto rs2 = instruction_decoder->get_rs2();
	auto addr = register_file->get_pc() +
	            ((uint32_t) register_file->get_value_integer(rs1) < (uint32_t) register_file->get_value_integer(rs1) ?
	             offset : 4);

	if(!isAlignment(addr, INSTRUCTION_ALIGNMENT)) {
		cpu->raise_exception(CPU_INTERFACE::INSTRUCTION_ADDRESS_MISALIGNED_EXCEPTION_CAUSE);
	}

	new_pc = addr;
}

void EXECUTOR::BGEU_E()
{
	auto offset = instruction_decoder->get_imm_b();
	auto rs1 = instruction_decoder->get_rs1();
	auto rs2 = instruction_decoder->get_rs2();
	auto addr = register_file->get_pc() +
	            ((uint32_t) register_file->get_value_integer(rs1) >= (uint32_t) register_file->get_value_integer(rs1) ?
	             offset : 4);

	if(!isAlignment(addr, INSTRUCTION_ALIGNMENT)) {
		cpu->raise_exception(CPU_INTERFACE::INSTRUCTION_ADDRESS_MISALIGNED_EXCEPTION_CAUSE);
	}

	new_pc = addr;
}

void EXECUTOR::FENCE_E()
{
}

void EXECUTOR::FENCE_TSO_E()
{
}

void EXECUTOR::ECALL_E()
{
	cpu->raise_exception(CPU_INTERFACE::ENVIRONMENT_CALL_FROM_M_MODE_EXCEPTION_CAUSE);
}

void EXECUTOR::EBREAK_E()
{
	cpu->raise_exception(CPU_INTERFACE::BREAKPOINT_EXCEPTION_CAUSE);
}
void EXECUTOR::ADD_E()
{
	auto rd = instruction_decoder->get_rd();
	auto rs1 = instruction_decoder->get_rs1();
	auto rs2 = instruction_decoder->get_rs2();

	auto value = register_file->get_value_integer(rs1) + register_file->get_value_integer(rs2);
	register_file->set_value_integer(rd, value);
}

void EXECUTOR::SUB_E()
{
	auto rd = instruction_decoder->get_rd();
	auto rs1 = instruction_decoder->get_rs1();
	auto rs2 = instruction_decoder->get_rs2();

	auto value = register_file->get_value_integer(rs1) - register_file->get_value_integer(rs2);
	register_file->set_value_integer(rd, value);
}

void EXECUTOR::AND_E()
{
	auto rd = instruction_decoder->get_rd();
	auto rs1 = instruction_decoder->get_rs1();
	auto rs2 = instruction_decoder->get_rs2();

	auto value = register_file->get_value_integer(rs1) & register_file->get_value_integer(rs2);
	register_file->set_value_integer(rd, value);
}

void EXECUTOR::OR_E()
{
	auto rd = instruction_decoder->get_rd();
	auto rs1 = instruction_decoder->get_rs1();
	auto rs2 = instruction_decoder->get_rs2();

	auto value = register_file->get_value_integer(rs1) | register_file->get_value_integer(rs2);
	register_file->set_value_integer(rd, value);
}

void EXECUTOR::XOR_E()
{
	auto rd = instruction_decoder->get_rd();
	auto rs1 = instruction_decoder->get_rs1();
	auto rs2 = instruction_decoder->get_rs2();

	auto value = register_file->get_value_integer(rs1) ^ register_file->get_value_integer(rs2);
	register_file->set_value_integer(rd, value);
}

