#include <array>
#include <stdint.h>

#include "registerInterface.h"

#ifndef INC_REGISTER_H_
#define INC_REGISTER_H_
class REGISTER: public REGISTER_INTERFACE
{
public:
	virtual void set_value_integer(unsigned int register_index, int32_t value) override;
	virtual int32_t get_value_integer(unsigned int register_index) override;

	virtual void set_pc(uint32_t value) override;
	virtual uint32_t get_pc() override;

private:
	std::array<int32_t, 32> register_bank_integer;
	uint32_t register_pc;
};
#endif //INC_REGISTER_H_
