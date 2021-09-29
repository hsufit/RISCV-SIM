#include <vector>

#include "systemc.h"

#include "tlm_utils/simple_initiator_socket.h"
#include "tlm_utils/simple_target_socket.h"

#ifndef INC_MEMORY_H_
#define INC_MEMORY_H_
class MEMORY : public sc_module
{
public:
	MEMORY(sc_module_name name);

	tlm_utils::simple_target_socket<MEMORY> memory_socket;
private:
	void b_transport(tlm::tlm_generic_payload &trans, sc_core::sc_time &delay);


	std::vector<uint8_t> dataMemory;
	void programLoader(std::array<uint32_t, 4096> &binary);
};
#endif //INC_MEMORY_H_
