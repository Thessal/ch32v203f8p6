# ch32v20xevt with gcc and makefile support

This is pre-converted ch32v20x firmware library with gcc and makefile support from WCH official CH32V20xEVT.ZIP. 

It is converted by '[ch32v_evt_makefile_gcc_project_template](https://github.com/cjacker/ch32v_evt_makefile_gcc_project_template)'

This firmware library support below parts from WCH:

- ch32v203f6p6
- ch32v203g6u6
- ch32v203k6t6
- ch32v203c6t6
- ch32v203f8p6
- ch32v203f8u6
- ch32v203g8r6
- ch32v203k8t6
- ch32v203c8t6
- ch32v203c8u6
- ch32v203rbt6
- ch32v208gbu6
- ch32v208cbu6
- ch32v208rbt6
- ch32v208wbu6

The default part is set to 'ch32v203g6u6'(FlappyBoard), you can change it with `./setpart.sh <part>`, it will setup correct flash/ram size, linker script and startup file automatically.

All examples shipped in original EVT package provided in 'Examples' dir.

The default 'User' codes is 'GPIO_Toggle' example, the default system frequency is set to 'SYSCLK_FREQ_96MHz_HSI' in 'User/system_ch32v20x.c'.


To build the project, type `make`.


https://github.com/xpack-dev-tools/riscv-none-embed-gcc-xpack/releases/download/v10.2.0-1.2/xpack-riscv-none-embed-gcc-10.2.0-1.2-linux-arm64.tar.gz

wlink flash build/ch32v203f8p6.bin
make; wlink reset; wlink erase; wlink reset; wlink flash build/ch32v203f8p6.bin
