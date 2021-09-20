#include "systemc.h"

#include "tlm_utils/simple_initiator_socket.h"
#include "tlm_utils/simple_target_socket.h"

class HELLO : public sc_module{ 
public: 
        HELLO(sc_module_name name) : sc_module(name){ 
		SC_HAS_PROCESS(HELLO);
		SC_THREAD(hello_thread);
        }

	tlm_utils::simple_initiator_socket<HELLO> moon_access_socket;
private:
	sc_core::sc_time  delay = sc_core::sc_time(1, sc_core::SC_NS);
	uint32_t pc = 0;


	void hello_thread(void)
	{
		for(int i = 0; i < 30; i++)
		{
			step();
			wait(delay);
		}
	}

	void step()
	{
		char data;
		sc_dt::uint64 addr = pc;
		int size = 1;
		tlm::tlm_generic_payload trans;
		trans.set_command(tlm::TLM_READ_COMMAND);
		trans.set_data_ptr(reinterpret_cast<unsigned char*>(&data));
		trans.set_data_length(size);
		trans.set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);
		trans.set_address(addr);
		sc_core::sc_time delay = sc_core::SC_ZERO_TIME;

		moon_access_socket->b_transport(trans, delay);
		std::cout << "time " << sc_core::sc_time_stamp() << ":" << "hello received!!" << data << std::endl;

		pc++;
	}
};
