#include <memory>

#include "systemc.h"

#include "tlm_utils/simple_initiator_socket.h"
#include "tlm_utils/simple_target_socket.h"

#include "registerInterface.h"
#include "addressSpaceInterface.h"

#ifndef INC_CPU_H_
#define INC_CPU_H_
class CPU : public sc_module
{
public:
	CPU(sc_module_name name);
	void set_register_file(const std::shared_ptr<REGISTER_INTERFACE> &instance);
	void set_address_space(const std::shared_ptr<ADDRESS_SPACE_INTERFACE> &instance);

	tlm_utils::simple_initiator_socket<CPU> memory_socket;
private:
	void hello_thread(void);
	void step();

	sc_core::sc_time  delay = sc_core::sc_time(1, sc_core::SC_NS);
	uint32_t pc = 0;

	std::shared_ptr<REGISTER_INTERFACE> register_file;
	std::shared_ptr<ADDRESS_SPACE_INTERFACE> address_space;
};
#endif //INC_CPU_H_
