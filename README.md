# RISCV-SIM
A risc-v simulator based on SystrmC.
Support RV32I instruction set, and will add more extension in future.

## Prerequest
SystemC Library, C++ Compiler, RISC-V Cross Compiler

## How to Use
To Run the simple hello world.
```
//cpu.cpp
void CPU::cpu_thread(void)
{
        register_file->set_pc(0x10b8);                                       <---add this line to set program counter
        register_file->set_value_integer(REGISTER_INTERFACE::x2, 0x40000);   <---add this line to set stack pointer
        while(true) {
                step();
                wait(delay);
        }
}
```
```
$ make run
//compile
...
00 address: 0x10f7 value: 0x21
00 address: 0x10f8 value: 0x0
03 program counter should be: 0x10b8
current_pc: 0x10b8 target_pc: 0x10bc ADDI 2 16 2 rs1Value: 0x3fff0 rs2Value: 0x0 rdValue: 0x3fff0 immValue: 0xfffffff0
current_pc: 0x10bc target_pc: 0x10c0 SW 2 1 12 rs1Value: 0x3fff0 rs2Value: 0x0 rdValue: 0x0 immValue: 0xc
...
console: h
...
console: e
...
console: l
...
console: l
...
console: o
...
console:  
...
console: w
...
console: o
...
console: r
...
console: l
...
console: d
...
console: !
...
current_pc: 0x10dc target_pc: 0x10e0 LW 2 12 1 rs1Value: 0x3fff0 rs2Value: 0x0 rdValue: 0x0 immValue: 0xc
current_pc: 0x10e0 target_pc: 0x10e4 LW 2 8 8 rs1Value: 0x3fff0 rs2Value: 0x0 rdValue: 0x0 immValue: 0x8
current_pc: 0x10e4 target_pc: 0x10e8 ADDI 2 16 2 rs1Value: 0x40000 rs2Value: 0x0 rdValue: 0x40000 immValue: 0x10
current_pc: 0x10e8 target_pc: 0x0 JALR 1 0 0 rs1Value: 0x0 rs2Value: 0x0 rdValue: 0x0 immValue: 0x0
INVALID: Opcode :0
Illegal Instruction, end simulation!
exception!

Info: /OSCI/SystemC: Simulation stopped by user.
```

or run your hex file by replace `binary.hex` in RISCV-SIM folder.

## Set Up Cross Compiler
Read the README in https://github.com/riscv/riscv-gnu-toolchain
User can decide where to install, use /home/user/Desktop/code/rv32i-ilp32-gnu-toolchain in thins example.
This project support RV32i instrucetion set only, so sonfigure with --with-arch=rv32i (I instruction set) and
--with-abi=ilp32 (soft floating point) options
```
$sudo apt-get install autoconf automake autotools-dev curl python3 libmpc-dev libmpfr-dev libgmp-dev gawk build-essential bison flex texinfo gperf libtool patchutils bc zlib1g-dev libexpat-dev
$git clone https://github.com/riscv/riscv-gnu-toolchain
$cd riscv-gnu-toolchain && git submodule update -i -r
$./configure --prefix=/home/user/Desktop/code/rv32i-ilp32-gnu-toolchain --with-arch=rv32i --with-abi=ilp32
$make
```

## How to Generate binary.hex and Run Simulation With It
If you change the install path, please remember to modify the Makefile.
```
$ cd test
//modify hello.c
$ make
$ cd ..
$ make run
...
03 program counter should be: 0x10b8
...
//modify program counter to 0x10b8
$ make run
```
## TODO
- Simplify simulation run step
  - Build and simulate specified binary file from source file automatically
  - Get program counter autometically from program loader
- Add more example
- Fix Logger message bug cause by same source and target register
- Refine Logger by replace unused rs1, rs2, rd with x0
- Add unittest
- Add branch prediction analyzer
- Add memory access analyzer
- Extend external device
  - More generalized console
  - External timer
  - Deep learning acclerator
- support more standard instruction set extension
  - M, A, F, D Extensions
  - Compress Extension
  - Vector Extension

### Advanced Topics
- Extend Logger to support Out Of Order Execution analysis.
