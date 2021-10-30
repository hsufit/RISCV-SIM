#include "instructionDecoderInterface.h"

#ifndef INC_INSTRUCTION_H_
#define INC_INSTRUCTION_H_
class INSTRUCTION_DECODER: public INSTRUCTION_DECODER_INTERFACE
{
public:
	virtual INSTRUCTION_DECODER_INTERFACE::Instruction get_instruction() override;
	INSTRUCTION_DECODER_INTERFACE::Instruction cmmand_dispatch();
	INSTRUCTION_DECODER_INTERFACE::Instruction imm_dispatch();
	INSTRUCTION_DECODER_INTERFACE::Instruction load_dispatch();
	INSTRUCTION_DECODER_INTERFACE::Instruction store_dispatch();
	INSTRUCTION_DECODER_INTERFACE::Instruction jalr_dispatch();
	INSTRUCTION_DECODER_INTERFACE::Instruction branch_dispatch();
	INSTRUCTION_DECODER_INTERFACE::Instruction fence_dispatch();
	INSTRUCTION_DECODER_INTERFACE::Instruction system_dispatch();
	INSTRUCTION_DECODER_INTERFACE::Instruction reg_dispatch();
	virtual void log_instruction(uint32_t current_pc, uint32_t target_pc, uint32_t rs1Value, uint32_t rs2Value, uint32_t rdValue,int32_t immValue) override;
	virtual uint32_t get_opcode() override;
	virtual uint32_t get_func3() override;
	virtual uint32_t get_func7() override;
	virtual uint32_t get_func12() override;

	virtual uint32_t get_rs1() override;
	virtual uint32_t get_rs2() override;
	virtual uint32_t get_rd() override;

	virtual int32_t get_imm(uint32_t start, uint32_t end) override;
	virtual int32_t get_imm_j() override;
	virtual int32_t get_imm_b() override;
	virtual uint32_t get_imm_fence_fm() override;
};
#endif //INSTRUCTION_INTERFAC
