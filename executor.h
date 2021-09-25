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
};
#endif //INC_EXECUTOR_H_
