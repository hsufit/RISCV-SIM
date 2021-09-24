#include <memory>

#include "instructionDecoderInterface.h"
#include "registerInterface.h"

#ifndef INC_EXECUTOR_INTERFACE_H_
#define INC_EXECUTOR_INTERFACE_H_
class EXECUTOR_INTERFACE
{
public:
	virtual void execute() = 0;
	void set_instruction_decoder(const std::shared_ptr<INSTRUCTION_DECODER_INTERFACE> &instance)
	{

		instruction_decoder = instance;
	}
	void set_register_file(const std::shared_ptr<REGISTER_INTERFACE> &instance)
	{
		register_file = instance;
	}

protected:
	std::shared_ptr<INSTRUCTION_DECODER_INTERFACE> instruction_decoder;
	std::shared_ptr<REGISTER_INTERFACE> register_file;
};
#endif //INC_EXECUTOR_INTERFACE_H_
