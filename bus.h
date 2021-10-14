#include <stdint.h>

#include "tlm_utils/simple_initiator_socket.h"
#include "tlm_utils/simple_target_socket.h"

#include "addressSpaceInterface.h"
#include "memory.h"

#ifndef INC_BUS_H_
#define INC_BUS_H_
class BUS: public ADDRESS_SPACE_INTERFACE, public sc_module
{
	enum memoryMapp {
		MEMORY_BASE = 0x000000,
		CONSOLE_BASE = 0x400000,
	};
public:
	BUS(sc_module_name name);

	virtual int32_t read(uint32_t addr, uint32_t size) override;
	virtual void write(uint32_t addr, uint32_t data, uint32_t size) override;
private:
	MEMORY memory;
	tlm_utils::simple_initiator_socket<BUS> memory_socket;
};

#endif //INC_BUS_H_



