#include <stdint.h>

#ifndef INC_ADDRESS_SPACE_INTERFACE_H_
#define INC_ADDRESS_SPACE_INTERFACE_H_
class ADDRESS_SPACE_INTERFACE
{
public:
	virtual int32_t read(uint32_t addr, uint32_t size) =0;
	virtual void write(uint32_t addr, uint32_t data, uint32_t size)=0;
};
#endif //INC_ADDRESS_SPACE_INTERFACE_H_
