#include <vector>

#include "systemc.h"

#include "tlm_utils/simple_initiator_socket.h"
#include "tlm_utils/simple_target_socket.h"

class MOON : public sc_module{
public:
	MOON(sc_module_name name);
	
	tlm_utils::simple_target_socket<MOON> moon_access_socket;
private:
	void b_transport(tlm::tlm_generic_payload &trans, sc_core::sc_time &delay);

	std::vector<char> dataMemory{'M', 'o', 'o', 'n', '!',
					',', ' ', '3', '.', '1',
					'4', '1', '5', '9', '2',
					'6', '5', '3', '5', '8',
					'9', '7', '9', '3', '2',
					'3', '8', '4', '6', '2'};
};
