#include "systemc.h"

class HELLO : public sc_module{ 
public: 
        HELLO(sc_module_name name) : sc_module(name){ 
                cout<<"Hello, SystemC!"<<endl; 
        }
};

int sc_main(int argc,char** argv){
        HELLO hello("hello");
        return 0;
}




