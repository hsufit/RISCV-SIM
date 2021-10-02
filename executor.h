#include "executorInterface.h"

#ifndef INC_EXECUTOR_H_
#define INC_EXECUTOR_H_
class EXECUTOR: public EXECUTOR_INTERFACE
{
public:
	virtual void execute() override;
private:
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

	uint32_t new_pc; //write back to register when execute finished
};
#endif //INC_EXECUTOR_H_
