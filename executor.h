#include "executorInterface.h"

#ifndef INC_EXECUTOR_H_
#define INC_EXECUTOR_H_
class EXECUTOR: public EXECUTOR_INTERFACE
{
public:
	virtual void execute() override;
private:
	void cmmand_dispatch();
	void imm_dispatch();
	void load_dispatch();
	void store_dispatch();
	void jalr_dispatch();
	void branch_dispatch();
	void fence_dispatch();
	void system_dispatch();
	void reg_dispatch();


	void ADDI_E();
	void ANDI_E();
	void ORI_E();
	void XORI_E();
	void SLTI_E();
	void SLTIU_E();
	void SLLI_E();
	void SRLI_E();
	void SRAI_E();
	void LUI_E();
	void AUIPC_E();
	void LB_E();
	void LH_E();
	void LW_E();
	void LBU_E();
	void LHU_E();
	void SB_E();
	void SH_E();
	void SW_E();
	void JAL_E();
	void JALR_E();
	void BEQ_E();
	void BNE_E();
	void BLT_E();
	void BGE_E();
	void BLTU_E();
	void BGEU_E();
	void FENCE_E();
	void FENCE_TSO_E();
	void ECALL_E();
	void EBREAK_E();
	void ADD_E();
	void SUB_E();
	void AND_E();
	void OR_E();
	void XOR_E();
	void SLT_E();
	void SLTU_E();

	uint32_t new_pc; //write back to register when execute finished
};
#endif //INC_EXECUTOR_H_
