#include "systemc.h"

#include "tlm_utils/simple_initiator_socket.h"
#include "tlm_utils/simple_target_socket.h"

class CPU : public sc_module
{
public:
	CPU(sc_module_name name);

	tlm_utils::simple_initiator_socket<CPU> memory_socket;
private:
	void hello_thread(void);
	void step();

	sc_core::sc_time  delay = sc_core::sc_time(1, sc_core::SC_NS);
	uint32_t pc = 0;
};
