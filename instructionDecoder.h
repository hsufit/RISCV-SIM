#include "instructionDecoderInterface.h"

#ifndef INC_INSTRUCTION_H_
#define INC_INSTRUCTION_H_
class INSTRUCTION_DECODER: public INSTRUCTION_DECODER_INTERFACE
{
public:
	virtual uint32_t get_opcode() override;
	virtual uint32_t get_func3() override;
	virtual uint32_t get_func7() override;

	virtual uint32_t get_rs1() override;
	virtual uint32_t get_rs2() override;
	virtual uint32_t get_rd() override;

	virtual int32_t get_imm(uint32_t start, uint32_t end) override;
	virtual int32_t get_imm_j() override;
};
#endif //INSTRUCTION_INTERFAC
