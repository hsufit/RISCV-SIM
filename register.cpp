#include "register.h"

void REGISTER::set_pc(uint32_t value)
{
	register_pc=value;
}

uint32_t REGISTER::get_pc()
{
	return register_pc;
}

void REGISTER::set_value_integer(unsigned int register_index, int32_t value)
{
	register_bank_integer[register_index] = value;
}

int32_t REGISTER::get_value_integer(unsigned int register_index)
{
	return register_bank_integer[register_index];
}
