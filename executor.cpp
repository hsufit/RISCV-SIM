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
	command_dispatch();
	register_file->set_pc(new_pc);
}

void EXECUTOR::command_dispatch()
{
	switch (instruction_decoder->get_instruction()) {
		case INSTRUCTION_DECODER_INTERFACE::ADDI_INSTRUCTION_ENUM:
			ADDI_E();
			break;
		case INSTRUCTION_DECODER_INTERFACE::ANDI_INSTRUCTION_ENUM:
			ANDI_E();
			break;
		case INSTRUCTION_DECODER_INTERFACE::ORI_INSTRUCTION_ENUM:
			ORI_E();
			break;
		case INSTRUCTION_DECODER_INTERFACE::XORI_INSTRUCTION_ENUM:
			XORI_E();
			break;
		case INSTRUCTION_DECODER_INTERFACE::SLTI_INSTRUCTION_ENUM:
			SLTI_E();
			break;
		case INSTRUCTION_DECODER_INTERFACE::SLTIU_INSTRUCTION_ENUM:
			SLTIU_E();
			break;
		case INSTRUCTION_DECODER_INTERFACE::SLLI_INSTRUCTION_ENUM:
			SLLI_E();
			break;
		case INSTRUCTION_DECODER_INTERFACE::SRLI_INSTRUCTION_ENUM:
			SRLI_E();
			break;
		case INSTRUCTION_DECODER_INTERFACE::SRAI_INSTRUCTION_ENUM:
			SRAI_E();
			break;
		case INSTRUCTION_DECODER_INTERFACE::LUI_INSTRUCTION_ENUM:
			LUI_E();
			break;
		case INSTRUCTION_DECODER_INTERFACE::AUIPC_INSTRUCTION_ENUM:
			AUIPC_E();
			break;
		case INSTRUCTION_DECODER_INTERFACE::LB_INSTRUCTION_ENUM:
			LB_E();
			break;
		case INSTRUCTION_DECODER_INTERFACE::LH_INSTRUCTION_ENUM:
			LH_E();
			break;
		case INSTRUCTION_DECODER_INTERFACE::LW_INSTRUCTION_ENUM:
			LW_E();
			break;
		case INSTRUCTION_DECODER_INTERFACE::LBU_INSTRUCTION_ENUM:
			LBU_E();
			break;
		case INSTRUCTION_DECODER_INTERFACE::LHU_INSTRUCTION_ENUM:
			LHU_E();
			break;
		case INSTRUCTION_DECODER_INTERFACE::SB_INSTRUCTION_ENUM:
			SB_E();
			break;
		case INSTRUCTION_DECODER_INTERFACE::SH_INSTRUCTION_ENUM:
			SH_E();
			break;
		case INSTRUCTION_DECODER_INTERFACE::SW_INSTRUCTION_ENUM:
			SW_E();
			break;
		case INSTRUCTION_DECODER_INTERFACE::JAL_INSTRUCTION_ENUM:
			JAL_E();
			break;
		case INSTRUCTION_DECODER_INTERFACE::JALR_INSTRUCTION_ENUM:
			JALR_E();
			break;
		case INSTRUCTION_DECODER_INTERFACE::BEQ_INSTRUCTION_ENUM:
			BEQ_E();
			break;
		case INSTRUCTION_DECODER_INTERFACE::BNE_INSTRUCTION_ENUM:
			BNE_E();
			break;
		case INSTRUCTION_DECODER_INTERFACE::BLT_INSTRUCTION_ENUM:
			BLT_E();
			break;
		case INSTRUCTION_DECODER_INTERFACE::BGE_INSTRUCTION_ENUM:
			BGE_E();
			break;
		case INSTRUCTION_DECODER_INTERFACE::BLTU_INSTRUCTION_ENUM:
			BLTU_E();
			break;
		case INSTRUCTION_DECODER_INTERFACE::BGEU_INSTRUCTION_ENUM:
			BGEU_E();
			break;
		case INSTRUCTION_DECODER_INTERFACE::FENCE_INSTRUCTION_ENUM:
			FENCE_E();
			break;
		case INSTRUCTION_DECODER_INTERFACE::FENCE_TSO_INSTRUCTION_ENUM:
			FENCE_TSO_E();
			break;
		case INSTRUCTION_DECODER_INTERFACE::ECALL_INSTRUCTION_ENUM:
			ECALL_E();
			break;
		case INSTRUCTION_DECODER_INTERFACE::EBREAK_INSTRUCTION_ENUM:
			EBREAK_E();
			break;
		case INSTRUCTION_DECODER_INTERFACE::ADD_INSTRUCTION_ENUM:
			ADD_E();
			break;
		case INSTRUCTION_DECODER_INTERFACE::SUB_INSTRUCTION_ENUM:
			SUB_E();
			break;
		case INSTRUCTION_DECODER_INTERFACE::AND_INSTRUCTION_ENUM:
			AND_E();
			break;
		case INSTRUCTION_DECODER_INTERFACE::OR_INSTRUCTION_ENUM:
			OR_E();
			break;
		case INSTRUCTION_DECODER_INTERFACE::XOR_INSTRUCTION_ENUM:
			XOR_E();
			break;
		case INSTRUCTION_DECODER_INTERFACE::SLT_INSTRUCTION_ENUM:
			SLT_E();
			break;
		case INSTRUCTION_DECODER_INTERFACE::SLTU_INSTRUCTION_ENUM:
			SLTU_E();
			break;
		case INSTRUCTION_DECODER_INTERFACE::SLL_INSTRUCTION_ENUM:
			SLL_E();
			break;
		case INSTRUCTION_DECODER_INTERFACE::SRL_INSTRUCTION_ENUM:
			SRL_E();
			break;
		case INSTRUCTION_DECODER_INTERFACE::SRA_INSTRUCTION_ENUM:
			SRA_E();
			break;
		default:
			cpu->raise_exception(CPU_INTERFACE::ILLEGAL_INSTRUCTION_EXCEPTION_CAUSE);
			break;
	}
}

void EXECUTOR::ADDI_E()
{
	auto rs1 = instruction_decoder->get_rs1();
	auto rd = instruction_decoder->get_rd();
	auto imm = instruction_decoder->get_imm(31, 20);

	auto value = register_file->get_value_integer(rs1) + imm;
	register_file->set_value_integer(rd, value);

	instruction_decoder->log_instruction(
	    register_file->get_pc(),
	    new_pc,
	    register_file->get_value_integer(rs1),
	    0,
	    register_file->get_value_integer(rd),
	    imm);
}

void EXECUTOR::ANDI_E()
{
	auto rs1 = instruction_decoder->get_rs1();
	auto rd = instruction_decoder->get_rd();
	auto imm = instruction_decoder->get_imm(31, 20);

	auto value = register_file->get_value_integer(rs1) & imm;
	register_file->set_value_integer(rd, value);

	instruction_decoder->log_instruction(
	    register_file->get_pc(),
	    new_pc,
	    register_file->get_value_integer(rs1),
	    0,
	    register_file->get_value_integer(rd),
	    imm);
}

void EXECUTOR::ORI_E()
{
	auto rs1 = instruction_decoder->get_rs1();
	auto rd = instruction_decoder->get_rd();
	auto imm = instruction_decoder->get_imm(31, 20);

	auto value = register_file->get_value_integer(rs1) | imm;
	register_file->set_value_integer(rd, value);

	instruction_decoder->log_instruction(
	    register_file->get_pc(),
	    new_pc,
	    register_file->get_value_integer(rs1),
	    0,
	    register_file->get_value_integer(rd),
	    imm);
}

void EXECUTOR::XORI_E()
{
	auto rs1 = instruction_decoder->get_rs1();
	auto rd = instruction_decoder->get_rd();
	auto imm = instruction_decoder->get_imm(31, 20);

	auto value = register_file->get_value_integer(rs1) ^ imm;
	register_file->set_value_integer(rd, value);

	instruction_decoder->log_instruction(
	    register_file->get_pc(),
	    new_pc,
	    register_file->get_value_integer(rs1),
	    0,
	    register_file->get_value_integer(rd),
	    imm);
}

void EXECUTOR::SLTI_E()
{
	auto rs1 = instruction_decoder->get_rs1();
	auto rd = instruction_decoder->get_rd();
	auto imm = instruction_decoder->get_imm(31, 20);

	auto value = register_file->get_value_integer(rs1) < imm;
	register_file->set_value_integer(rd, value);

	instruction_decoder->log_instruction(
	    register_file->get_pc(),
	    new_pc,
	    register_file->get_value_integer(rs1),
	    0,
	    register_file->get_value_integer(rd),
	    imm);
}

void EXECUTOR::SLTIU_E()
{
	auto rs1 = instruction_decoder->get_rs1();
	auto rd = instruction_decoder->get_rd();
	auto imm = (uint32_t) instruction_decoder->get_imm(31, 20);

	auto value = register_file->get_value_integer(rs1) < imm;
	register_file->set_value_integer(rd, value);

	instruction_decoder->log_instruction(
	    register_file->get_pc(),
	    new_pc,
	    register_file->get_value_integer(rs1),
	    0,
	    register_file->get_value_integer(rd),
	    imm);
}

void EXECUTOR::SLLI_E()
{
	auto rs1 = instruction_decoder->get_rs1();
	auto rd = instruction_decoder->get_rd();
	auto imm = (uint32_t) instruction_decoder->get_imm(24, 20);

	auto value = register_file->get_value_integer(rs1) << imm;
	register_file->set_value_integer(rd, value);

	instruction_decoder->log_instruction(
	    register_file->get_pc(),
	    new_pc,
	    register_file->get_value_integer(rs1),
	    0,
	    register_file->get_value_integer(rd),
	    imm);
}

void EXECUTOR::SRLI_E()
{
	auto rs1 = instruction_decoder->get_rs1();
	auto rd = instruction_decoder->get_rd();
	auto imm = (uint32_t) instruction_decoder->get_imm(24, 20);

	auto value = (uint32_t) register_file->get_value_integer(rs1) >> imm;
	register_file->set_value_integer(rd, value);

	instruction_decoder->log_instruction(
	    register_file->get_pc(),
	    new_pc,
	    register_file->get_value_integer(rs1),
	    0,
	    register_file->get_value_integer(rd),
	    imm);
}

void EXECUTOR::SRAI_E()
{
	auto rs1 = instruction_decoder->get_rs1();
	auto rd = instruction_decoder->get_rd();
	auto imm = (uint32_t) instruction_decoder->get_imm(24, 20);

	auto value = register_file->get_value_integer(rs1) >> imm;
	register_file->set_value_integer(rd, value);

	instruction_decoder->log_instruction(
	    register_file->get_pc(),
	    new_pc,
	    register_file->get_value_integer(rs1),
	    0,
	    register_file->get_value_integer(rd),
	    imm);
}

void EXECUTOR::LUI_E()
{
	auto rd = instruction_decoder->get_rd();
	auto imm = instruction_decoder->get_imm(31, 12);

	auto value = (imm << 12);
	register_file->set_value_integer(rd, value);

	instruction_decoder->log_instruction(
	    register_file->get_pc(),
	    new_pc,
	    0,
	    0,
	    register_file->get_value_integer(rd),
	    imm);
}

void EXECUTOR::AUIPC_E()
{
	auto rd = instruction_decoder->get_rd();
	auto imm = instruction_decoder->get_imm(31, 12);

	auto value = register_file->get_pc() + (imm << 12);
	register_file->set_value_integer(rd, value);

	instruction_decoder->log_instruction(
	    register_file->get_pc(),
	    new_pc,
	    0,
	    0,
	    register_file->get_value_integer(rd),
	    imm);
}


void EXECUTOR::LB_E()
{
	auto rs1 = instruction_decoder->get_rs1();
	auto rd = instruction_decoder->get_rd();
	auto imm = (uint32_t) instruction_decoder->get_imm(31, 20);

	auto addr = register_file->get_value_integer(rs1) + imm;
	auto value = address_space->read(addr, 1) << 24 >> 24;
	register_file->set_value_integer(rd, value);

	instruction_decoder->log_instruction(
	    register_file->get_pc(),
	    new_pc,
	    register_file->get_value_integer(rs1),
	    0,
	    register_file->get_value_integer(rd),
	    imm);
}

void EXECUTOR::LH_E()
{
	auto rs1 = instruction_decoder->get_rs1();
	auto rd = instruction_decoder->get_rd();
	auto imm = (uint32_t) instruction_decoder->get_imm(31, 20);

	auto addr = register_file->get_value_integer(rs1) + imm;
	if(!isAlignment(addr, LOAD_STORE_ALIGNMENT_HW)) {
		cpu->raise_exception(CPU_INTERFACE::LOAD_ADDRESS_MISALIGNED_EXCEPTION_CAUSE);
	}
	auto value = address_space->read(addr, 2) << 16 >> 16;
	register_file->set_value_integer(rd, value);

	instruction_decoder->log_instruction(
	    register_file->get_pc(),
	    new_pc,
	    register_file->get_value_integer(rs1),
	    0,
	    register_file->get_value_integer(rd),
	    imm);
}

void EXECUTOR::LW_E()
{
	auto rs1 = instruction_decoder->get_rs1();
	auto rd = instruction_decoder->get_rd();
	auto imm = (uint32_t) instruction_decoder->get_imm(31, 20);

	auto addr = register_file->get_value_integer(rs1) + imm;
	if(!isAlignment(addr, LOAD_STORE_ALIGNMENT_W)) {
		cpu->raise_exception(CPU_INTERFACE::LOAD_ADDRESS_MISALIGNED_EXCEPTION_CAUSE);
	}
	auto value = address_space->read(addr, 4);
	register_file->set_value_integer(rd, value);

	instruction_decoder->log_instruction(
	    register_file->get_pc(),
	    new_pc,
	    register_file->get_value_integer(rs1),
	    0,
	    register_file->get_value_integer(rd),
	    imm);
}

void EXECUTOR::LBU_E()
{
	auto rs1 = instruction_decoder->get_rs1();
	auto rd = instruction_decoder->get_rd();
	auto imm = (uint32_t) instruction_decoder->get_imm(31, 20);

	auto addr = register_file->get_value_integer(rs1) + imm;
	auto value = address_space->read(addr, 1);
	register_file->set_value_integer(rd, value);

	instruction_decoder->log_instruction(
	    register_file->get_pc(),
	    new_pc,
	    register_file->get_value_integer(rs1),
	    0,
	    register_file->get_value_integer(rd),
	    imm);
}

void EXECUTOR::LHU_E()
{
	auto rs1 = instruction_decoder->get_rs1();
	auto rd = instruction_decoder->get_rd();
	auto imm = (uint32_t) instruction_decoder->get_imm(31, 20);

	auto addr = register_file->get_value_integer(rs1) + imm;
	if(!isAlignment(addr, LOAD_STORE_ALIGNMENT_HW)) {
		cpu->raise_exception(CPU_INTERFACE::LOAD_ADDRESS_MISALIGNED_EXCEPTION_CAUSE);
	}
	auto value = address_space->read(addr, 2);
	register_file->set_value_integer(rd, value);

	instruction_decoder->log_instruction(
	    register_file->get_pc(),
	    new_pc,
	    register_file->get_value_integer(rs1),
	    0,
	    register_file->get_value_integer(rd),
	    imm);
}

void EXECUTOR::SB_E()
{
	auto rs1 = instruction_decoder->get_rs1();
	auto rs2 = instruction_decoder->get_rs2();
	auto offset =  (instruction_decoder->get_imm(31, 25) << 5) |
	               (instruction_decoder->get_imm(11, 7) & 0x1F);

	auto addr = register_file->get_value_integer(rs1) + offset;
	address_space->write(addr, register_file->get_value_integer(rs2), 1);

	instruction_decoder->log_instruction(
	    register_file->get_pc(),
	    new_pc,
	    register_file->get_value_integer(rs1),
	    register_file->get_value_integer(rs2),
	    0,
	    offset);
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

	instruction_decoder->log_instruction(
	    register_file->get_pc(),
	    new_pc,
	    register_file->get_value_integer(rs1),
	    register_file->get_value_integer(rs2),
	    0,
	    offset);
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

	instruction_decoder->log_instruction(
	    register_file->get_pc(),
	    new_pc,
	    register_file->get_value_integer(rs1),
	    register_file->get_value_integer(rs2),
	    0,
	    offset);
}

void EXECUTOR::JAL_E()
{
	auto rd = instruction_decoder->get_rd();
	auto offset = instruction_decoder->get_imm_j();

	auto addr = register_file->get_pc() + offset;
	if(!isAlignment(addr, INSTRUCTION_ALIGNMENT)) {
		cpu->raise_exception(CPU_INTERFACE::INSTRUCTION_ADDRESS_MISALIGNED_EXCEPTION_CAUSE);
	}
	register_file->set_value_integer(rd, new_pc);
	new_pc = addr;

	instruction_decoder->log_instruction(
	    register_file->get_pc(),
	    new_pc,
	    0,
	    0,
	    register_file->get_value_integer(rd),
	    offset);
}

void EXECUTOR::JALR_E()
{
	auto rs1 = instruction_decoder->get_rs1();
	auto rd = instruction_decoder->get_rd();
	auto offset = instruction_decoder->get_imm(31, 20);

	auto addr = (register_file->get_value_integer(rs1) + offset) & ~0x1;
	if(!isAlignment(addr, INSTRUCTION_ALIGNMENT)) {
		cpu->raise_exception(CPU_INTERFACE::INSTRUCTION_ADDRESS_MISALIGNED_EXCEPTION_CAUSE);
	}
	register_file->set_value_integer(rd, new_pc);
	new_pc = addr;

	instruction_decoder->log_instruction(
	    register_file->get_pc(),
	    new_pc,
	    register_file->get_value_integer(rs1),
	    0,
	    register_file->get_value_integer(rd),
	    offset);
}

void EXECUTOR::BEQ_E()
{
	auto rs1 = instruction_decoder->get_rs1();
	auto rs2 = instruction_decoder->get_rs2();
	auto offset = instruction_decoder->get_imm_b();

	auto addr = register_file->get_pc() +
	            (register_file->get_value_integer(rs1) == register_file->get_value_integer(rs1) ?
	             offset : 4);
	if(!isAlignment(addr, INSTRUCTION_ALIGNMENT)) {
		cpu->raise_exception(CPU_INTERFACE::INSTRUCTION_ADDRESS_MISALIGNED_EXCEPTION_CAUSE);
	}
	new_pc = addr;

	instruction_decoder->log_instruction(
	    register_file->get_pc(),
	    new_pc,
	    register_file->get_value_integer(rs1),
	    register_file->get_value_integer(rs2),
	    0,
	    offset);
}

void EXECUTOR::BNE_E()
{
	auto rs1 = instruction_decoder->get_rs1();
	auto rs2 = instruction_decoder->get_rs2();
	auto offset = instruction_decoder->get_imm_b();

	auto addr = register_file->get_pc() +
	            (register_file->get_value_integer(rs1) != register_file->get_value_integer(rs1) ?
	             offset : 4);
	if(!isAlignment(addr, INSTRUCTION_ALIGNMENT)) {
		cpu->raise_exception(CPU_INTERFACE::INSTRUCTION_ADDRESS_MISALIGNED_EXCEPTION_CAUSE);
	}
	new_pc = addr;

	instruction_decoder->log_instruction(
	    register_file->get_pc(),
	    new_pc,
	    register_file->get_value_integer(rs1),
	    register_file->get_value_integer(rs2),
	    0,
	    offset);
}

void EXECUTOR::BLT_E()
{
	auto rs1 = instruction_decoder->get_rs1();
	auto rs2 = instruction_decoder->get_rs2();
	auto offset = instruction_decoder->get_imm_b();

	auto addr = register_file->get_pc() +
	            (register_file->get_value_integer(rs1) < register_file->get_value_integer(rs1) ?
	             offset : 4);
	if(!isAlignment(addr, INSTRUCTION_ALIGNMENT)) {
		cpu->raise_exception(CPU_INTERFACE::INSTRUCTION_ADDRESS_MISALIGNED_EXCEPTION_CAUSE);
	}
	new_pc = addr;

	instruction_decoder->log_instruction(
	    register_file->get_pc(),
	    new_pc,
	    register_file->get_value_integer(rs1),
	    register_file->get_value_integer(rs2),
	    0,
	    offset);
}

void EXECUTOR::BGE_E()
{
	auto rs1 = instruction_decoder->get_rs1();
	auto rs2 = instruction_decoder->get_rs2();
	auto offset = instruction_decoder->get_imm_b();

	auto addr = register_file->get_pc() +
	            (register_file->get_value_integer(rs1) >= register_file->get_value_integer(rs1) ?
	             offset : 4);
	if(!isAlignment(addr, INSTRUCTION_ALIGNMENT)) {
		cpu->raise_exception(CPU_INTERFACE::INSTRUCTION_ADDRESS_MISALIGNED_EXCEPTION_CAUSE);
	}
	new_pc = addr;

	instruction_decoder->log_instruction(
	    register_file->get_pc(),
	    new_pc,
	    register_file->get_value_integer(rs1),
	    register_file->get_value_integer(rs2),
	    0,
	    offset);
}

void EXECUTOR::BLTU_E()
{
	auto rs1 = instruction_decoder->get_rs1();
	auto rs2 = instruction_decoder->get_rs2();
	auto offset = instruction_decoder->get_imm_b();

	auto addr = register_file->get_pc() +
	            ((uint32_t) register_file->get_value_integer(rs1) < (uint32_t) register_file->get_value_integer(rs1) ?
	             offset : 4);
	if(!isAlignment(addr, INSTRUCTION_ALIGNMENT)) {
		cpu->raise_exception(CPU_INTERFACE::INSTRUCTION_ADDRESS_MISALIGNED_EXCEPTION_CAUSE);
	}
	new_pc = addr;

	instruction_decoder->log_instruction(
	    register_file->get_pc(),
	    new_pc,
	    register_file->get_value_integer(rs1),
	    register_file->get_value_integer(rs2),
	    0,
	    offset);
}

void EXECUTOR::BGEU_E()
{
	auto rs1 = instruction_decoder->get_rs1();
	auto rs2 = instruction_decoder->get_rs2();
	auto offset = instruction_decoder->get_imm_b();

	auto addr = register_file->get_pc() +
	            ((uint32_t) register_file->get_value_integer(rs1) >= (uint32_t) register_file->get_value_integer(rs1) ?
	             offset : 4);
	if(!isAlignment(addr, INSTRUCTION_ALIGNMENT)) {
		cpu->raise_exception(CPU_INTERFACE::INSTRUCTION_ADDRESS_MISALIGNED_EXCEPTION_CAUSE);
	}
	new_pc = addr;

	instruction_decoder->log_instruction(
	    register_file->get_pc(),
	    new_pc,
	    register_file->get_value_integer(rs1),
	    register_file->get_value_integer(rs2),
	    0,
	    offset);
}

void EXECUTOR::FENCE_E()
{
	instruction_decoder->log_instruction(
	    register_file->get_pc(),
	    new_pc,
	    0,
	    0,
	    0,
	    0);
}

void EXECUTOR::FENCE_TSO_E()
{
	instruction_decoder->log_instruction(
	    register_file->get_pc(),
	    new_pc,
	    0,
	    0,
	    0,
	    0);
}

void EXECUTOR::ECALL_E()
{
	cpu->raise_exception(CPU_INTERFACE::ENVIRONMENT_CALL_FROM_M_MODE_EXCEPTION_CAUSE);

	instruction_decoder->log_instruction(
	    register_file->get_pc(),
	    new_pc,
	    0,
	    0,
	    0,
	    0);
}

void EXECUTOR::EBREAK_E()
{
	cpu->raise_exception(CPU_INTERFACE::BREAKPOINT_EXCEPTION_CAUSE);

	instruction_decoder->log_instruction(
	    register_file->get_pc(),
	    new_pc,
	    0,
	    0,
	    0,
	    0);
}
void EXECUTOR::ADD_E()
{
	auto rs1 = instruction_decoder->get_rs1();
	auto rs2 = instruction_decoder->get_rs2();
	auto rd = instruction_decoder->get_rd();

	auto value = register_file->get_value_integer(rs1) + register_file->get_value_integer(rs2);
	register_file->set_value_integer(rd, value);

	instruction_decoder->log_instruction(
	    register_file->get_pc(),
	    new_pc,
	    register_file->get_value_integer(rs1),
	    register_file->get_value_integer(rs2),
	    register_file->get_value_integer(rd),
	    0);
}

void EXECUTOR::SUB_E()
{
	auto rs1 = instruction_decoder->get_rs1();
	auto rs2 = instruction_decoder->get_rs2();
	auto rd = instruction_decoder->get_rd();

	auto value = register_file->get_value_integer(rs1) - register_file->get_value_integer(rs2);
	register_file->set_value_integer(rd, value);

	instruction_decoder->log_instruction(
	    register_file->get_pc(),
	    new_pc,
	    register_file->get_value_integer(rs1),
	    register_file->get_value_integer(rs2),
	    register_file->get_value_integer(rd),
	    0);
}

void EXECUTOR::AND_E()
{
	auto rs1 = instruction_decoder->get_rs1();
	auto rs2 = instruction_decoder->get_rs2();
	auto rd = instruction_decoder->get_rd();

	auto value = register_file->get_value_integer(rs1) & register_file->get_value_integer(rs2);
	register_file->set_value_integer(rd, value);

	instruction_decoder->log_instruction(
	    register_file->get_pc(),
	    new_pc,
	    register_file->get_value_integer(rs1),
	    register_file->get_value_integer(rs2),
	    register_file->get_value_integer(rd),
	    0);
}

void EXECUTOR::OR_E()
{
	auto rs1 = instruction_decoder->get_rs1();
	auto rs2 = instruction_decoder->get_rs2();
	auto rd = instruction_decoder->get_rd();

	auto value = register_file->get_value_integer(rs1) | register_file->get_value_integer(rs2);
	register_file->set_value_integer(rd, value);

	instruction_decoder->log_instruction(
	    register_file->get_pc(),
	    new_pc,
	    register_file->get_value_integer(rs1),
	    register_file->get_value_integer(rs2),
	    register_file->get_value_integer(rd),
	    0);
}

void EXECUTOR::XOR_E()
{
	auto rs1 = instruction_decoder->get_rs1();
	auto rs2 = instruction_decoder->get_rs2();
	auto rd = instruction_decoder->get_rd();

	auto value = register_file->get_value_integer(rs1) ^ register_file->get_value_integer(rs2);
	register_file->set_value_integer(rd, value);

	instruction_decoder->log_instruction(
	    register_file->get_pc(),
	    new_pc,
	    register_file->get_value_integer(rs1),
	    register_file->get_value_integer(rs2),
	    register_file->get_value_integer(rd),
	    0);
}

void EXECUTOR::SLT_E()
{
	auto rs1 = instruction_decoder->get_rs1();
	auto rs2 = instruction_decoder->get_rs2();
	auto rd = instruction_decoder->get_rd();

	auto value = register_file->get_value_integer(rs1) < register_file->get_value_integer(rs2) ? 1 : 0;
	register_file->set_value_integer(rd, value);

	instruction_decoder->log_instruction(
	    register_file->get_pc(),
	    new_pc,
	    register_file->get_value_integer(rs1),
	    register_file->get_value_integer(rs2),
	    register_file->get_value_integer(rd),
	    0);
}

void EXECUTOR::SLTU_E()
{
	auto rs1 = instruction_decoder->get_rs1();
	auto rs2 = instruction_decoder->get_rs2();
	auto rd = instruction_decoder->get_rd();

	auto value = (uint32_t)register_file->get_value_integer(rs1) < (uint32_t)register_file->get_value_integer(rs2) ? 1 : 0;
	register_file->set_value_integer(rd, value);

	instruction_decoder->log_instruction(
	    register_file->get_pc(),
	    new_pc,
	    register_file->get_value_integer(rs1),
	    register_file->get_value_integer(rs2),
	    register_file->get_value_integer(rd),
	    0);
}

void EXECUTOR::SLL_E()
{
	auto rs1 = instruction_decoder->get_rs1();
	auto rs2 = instruction_decoder->get_rs2();
	auto rd = instruction_decoder->get_rd();

	auto value = register_file->get_value_integer(rs1) << register_file->get_value_integer(rs2);
	register_file->set_value_integer(rd, value);

	instruction_decoder->log_instruction(
	    register_file->get_pc(),
	    new_pc,
	    register_file->get_value_integer(rs1),
	    register_file->get_value_integer(rs2),
	    register_file->get_value_integer(rd),
	    0);
}

void EXECUTOR::SRL_E()
{
	auto rs1 = instruction_decoder->get_rs1();
	auto rs2 = instruction_decoder->get_rs2();
	auto rd = instruction_decoder->get_rd();

	auto value = (uint32_t)register_file->get_value_integer(rs1) >> register_file->get_value_integer(rs2);
	register_file->set_value_integer(rd, value);

	instruction_decoder->log_instruction(
	    register_file->get_pc(),
	    new_pc,
	    register_file->get_value_integer(rs1),
	    register_file->get_value_integer(rs2),
	    register_file->get_value_integer(rd),
	    0);
}

void EXECUTOR::SRA_E()
{
	auto rs1 = instruction_decoder->get_rs1();
	auto rs2 = instruction_decoder->get_rs2();
	auto rd = instruction_decoder->get_rd();

	auto value = register_file->get_value_integer(rs1) >> register_file->get_value_integer(rs2);
	register_file->set_value_integer(rd, value);

	instruction_decoder->log_instruction(
	    register_file->get_pc(),
	    new_pc,
	    register_file->get_value_integer(rs1),
	    register_file->get_value_integer(rs2),
	    register_file->get_value_integer(rd),
	    0);
}

