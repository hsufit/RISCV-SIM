#include <vector>

#include "systemc.h"

class HELLO : public sc_module{ 
public: 
        HELLO(sc_module_name name) : sc_module(name){ 
		SC_HAS_PROCESS(HELLO);
		SC_THREAD(hello_thread);
        }

private:
	sc_core::sc_time  delay = sc_core::sc_time(1, sc_core::SC_NS);
	uint32_t pc = 0;

	std::vector<char> dataMemory{'H', 'e', 'l', 'l', 'o', ',', ' ', 'S', 'y', 's', 't', 'e', 'm', 'C', '!'};
	void hello_thread(void)
	{
		for(int i = 0; i<dataMemory.size()*2; i++)
		{
			step();
			wait(delay);
		}
	}

	void step()
	{
		std::cout << "time " << sc_core::sc_time_stamp() << ":" << dataMemory[pc % dataMemory.size()] << std::endl;
		pc++;
	}
};

int sc_main(int argc,char** argv){
	
        HELLO hello("hello");
	sc_core::sc_start();
        return 0;
}




