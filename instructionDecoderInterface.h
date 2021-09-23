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

	virtual uint32_t get_rs1() = 0;
	virtual uint32_t get_rs2() = 0;
	virtual uint32_t get_rd() = 0;

	virtual uint32_t get_imm(uint32_t start, uint32_t end) = 0;

protected:
	sc_dt::sc_uint<32> instruction_value;
};

#endif //INC_INSTRUCTION_DECODER_INTERFACE_H_

