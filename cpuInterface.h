#include <inttypes.h>

#ifndef INC_CPU_INTERFACE_H_
#define INC_CPU_INTERFACE_H_
class CPU_INTERFACE
{
public:
	virtual void raise_exception(uint32_t cause) = 0;
	virtual void raise_interrupt(uint32_t cause) = 0;
};
#endif //INC_CPU_INTERFACE_H_
