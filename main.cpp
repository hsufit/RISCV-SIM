#include <vector>

#include "systemc.h"
#include "tlm.h"
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

class MOON : public sc_module{
public:
	MOON(sc_module_name name) : sc_module(name){
		moon_access_socket.register_b_transport(this, &MOON::b_transport);
	}
	
	tlm_utils::simple_target_socket<MOON> moon_access_socket;

private:
	std::vector<char> dataMemory{'M', 'o', 'o', 'n', '!',
					',', ' ', '3', '.', '1',
					'4', '1', '5', '9', '2',
					'6', '5', '3', '5', '8',
					'9', '7', '9', '3', '2',
					'3', '8', '4', '6', '2'};

	void b_transport(tlm::tlm_generic_payload &trans, sc_core::sc_time &delay){
		delay = sc_core::SC_ZERO_TIME;
		tlm::tlm_command cmd = trans.get_command();
		sc_dt::uint64 adr = trans.get_address();
		unsigned char *ptr = trans.get_data_ptr();
		unsigned int len = trans.get_data_length();

		if(adr < dataMemory.size())
		{
			*(char*)ptr = dataMemory[adr];
			std::cout << "time " << sc_core::sc_time_stamp() << ":" << "moon response!!" << dataMemory[adr] << std::endl;
			trans.set_response_status(tlm::TLM_OK_RESPONSE);
		}
		else
		{
			trans.set_response_status(tlm::TLM_BURST_ERROR_RESPONSE);
			std::cout << "error an address " << adr << "!!" << std::endl;
		}
	}
};

int sc_main(int argc,char** argv){
	
        HELLO hello("hello");
	MOON moon("moon");
	hello.moon_access_socket.bind(moon.moon_access_socket);
	sc_core::sc_start();
        return 0;
}




