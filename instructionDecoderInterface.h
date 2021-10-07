#include <stdint.h>

#include "systemc.h"

#ifndef INC_INSTRUCTION_DECODER_INTERFACE_H_
#define INC_INSTRUCTION_DECODER_INTERFACE_H_
class INSTRUCTION_DECODER_INTERFACE
{
public:
	enum ExtensionType {
		BASE_RV32I,
		UNSUPPORTED,
	};

	enum Opcode {
		IMM_OP = 0b0010011,
		LUI_OP = 0b0110111,
		AUIPC_OP = 0b0010111,
		LOAD_OP = 0b0000011,
		STORE_OP = 0b0100011,
		JAL_OP = 0b1101111,
		JALR_OP = 0b1100111,
		BRANCH_OP = 0b1100011,
		MISC_MEM_OP = 0b0001111,
		SYSTEM_OP = 0b1110011,
		REG_OP = 0b0110011,
	};

	enum Func3 {
		//IMM_OP
		ADDI_FN3 = 0b000,
		ANDI_FN3 = 0b111,
		ORI_FN3 = 0b110,
		XORI_FN3 = 0b100,
		SLTI_FN3 = 0b010,
		SLTIU_FN3 = 0b011,
		SLLI_FN3 = 0b001,
		SRLI_FN3 = 0b101,
		SRAI_FN3 = 0b101,
		LB_FN3 = 0b000,
		LH_FN3 = 0b001,
		LW_FN3 = 0b010,
		LBU_FN3 = 0b100,
		LHU_FN3 = 0b101,
		SB_FN3 = 0b000,
		SH_FN3 = 0b001,
		SW_FN3 = 0b010,
		JALR_FN3 = 0b000,
		BEQ_FN3 = 0b000,
		BNE_FN3 = 0b001,
		BLT_FN3 = 0b100,
		BGE_FN3 = 0b101,
		BLTU_FN3 = 0b110,
		BGEU_FN3 = 0b111,
		FENCE_FN3 = 0b000,
		ADD_FN3 = 0b000,
		SUB_FN3 = 0b000,
		AND_FN3 = 0b111,
		OR_FN3 = 0b110,
		XOR_FN3 = 0b100,
	};

	enum Func7 {
		ADD_FN7 = 0b0000000,
		SUB_FN7 = 0b0100000,
		AND_FN7 = 0b0000000,
		OR_FN7 = 0b0000000,
		XOR_FN7 = 0b0000000,
	};

	enum Func12 {
		ECALL_FN12 = 0b0,
		EBREAK_FN12 = 0b1,
	};

	void set_instruction(uint32_t value)
	{
		instruction_value = sc_dt::sc_uint<32>(value);
	}

	INSTRUCTION_DECODER_INTERFACE::ExtensionType extension()
	{
		if ((instruction_value & 0x00000003) == 0b11) {
			return INSTRUCTION_DECODER_INTERFACE::BASE_RV32I;
		}
		return INSTRUCTION_DECODER_INTERFACE::UNSUPPORTED;
	}

	virtual uint32_t get_opcode() = 0;
	virtual uint32_t get_func3() = 0;
	virtual uint32_t get_func7() = 0;
	virtual uint32_t get_func12() = 0;

	virtual uint32_t get_rs1() = 0;
	virtual uint32_t get_rs2() = 0;
	virtual uint32_t get_rd() = 0;

	virtual int32_t get_imm(uint32_t start, uint32_t end) = 0;
	virtual int32_t get_imm_j() = 0;
	virtual int32_t get_imm_b() = 0;
	virtual uint32_t get_imm_fence_fm() = 0;

protected:
	sc_dt::sc_uint<32> instruction_value;
};

#endif //INC_INSTRUCTION_DECODER_INTERFACE_H_

