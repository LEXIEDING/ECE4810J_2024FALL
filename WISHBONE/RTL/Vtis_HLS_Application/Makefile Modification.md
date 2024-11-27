Please modify the Makefiles of the following paths to:

PATH:

```PATH
D:\workspace\l2\s2_4\Zynq_CPU_wrapper_hw_platform_4\zynq_fsbl\zynq_fsbl_bsp\ps7_cortexa9_0\libsrc\rtl_multiplier_v1_0\src\Makefile
D:\workspace\l2\s2_4\Zynq_CPU_wrapper_hw_platform_4\ps7_cortexa9_0\standalone_ps7_cortexa9_0\bsp\ps7_cortexa9_0\libsrc\rtl_multiplier_v1_0\src\Makefile
```

```Makefile
COMPILER=
ARCHIVER=
CP=cp
COMPILER_FLAGS=
EXTRA_COMPILER_FLAGS=
LIB=libxil.a
 
RELEASEDIR=../../../lib
INCLUDEDIR=../../../include
INCLUDES=-I./. -I${INCLUDEDIR}
 
INCLUDEFILES=*.h
LIBSOURCES=$(wildcard *.c)
OUTS = *.o
OBJECTS = $(addsuffix .o, $(basename $(wildcard *.c)))
ASSEMBLY_OBJECTS = $(addsuffix .o, $(basename $(wildcard *.S)))
 
libs:
	echo "Compiling rtl_multiplier..."
	$(COMPILER) $(COMPILER_FLAGS) $(EXTRA_COMPILER_FLAGS) $(INCLUDES) $(LIBSOURCES)
	$(ARCHIVER) -r ${RELEASEDIR}/${LIB} ${OBJECTS} ${ASSEMBLY_OBJECTS}
	make clean
 
include:
	${CP} $(INCLUDEFILES) $(INCLUDEDIR)
 
clean:
	rm -rf ${OBJECTS} ${ASSEMBLY_OBJECTS}

```

s3 Makefiles are the same as s2_4

```PATH
D:\workspace\l2\s3\Zynq_CPU_wrapper_hw_platform_4\zynq_fsbl\zynq_fsbl_bsp\ps7_cortexa9_0\libsrc\rtl_multiplier_v1_0\src\Makefile
D:\workspace\l2\s3\Zynq_CPU_wrapper_hw_platform_4\ps7_cortexa9_0\standalone_ps7_cortexa9_0\bsp\ps7_cortexa9_0\libsrc\rtl_multiplier_v1_0\src\Makefile
```

```log
14:17:30 **** Incremental Build of configuration Debug for project hello_hls_rtl_multiplier_system ****
make all 
Generating bif file for the system project
generate_system_bif.bat 65204 D:/workspace/l2/s3/Zynq_CPU_wrapper_hw_platform_4/export/Zynq_CPU_wrapper_hw_platform_4/Zynq_CPU_wrapper_hw_platform_4.xpfm standalone_ps7_cortexa9_0 D:/workspace/l2/s3/hello_hls_rtl_multiplier_system/Debug/system.bif
sdcard_gen --xpfm D:/workspace/l2/s3/Zynq_CPU_wrapper_hw_platform_4/export/Zynq_CPU_wrapper_hw_platform_4/Zynq_CPU_wrapper_hw_platform_4.xpfm --sys_config Zynq_CPU_wrapper_hw_platform_4 --bif D:/workspace/l2/s3/hello_hls_rtl_multiplier_system/Debug/system.bif --bitstream D:/workspace/l2/s3/hello_hls_rtl_multiplier/_ide/bitstream/Zynq_CPU_wrapper_hw_platform_4.bit --elf D:/workspace/l2/s3/hello_hls_rtl_multiplier/Debug/hello_hls_rtl_multiplier.elf,ps7_cortexa9_0
creating BOOT.BIN using D:/workspace/l2/s3/hello_hls_rtl_multiplier/_ide/bitstream/Zynq_CPU_wrapper_hw_platform_4.bit
Error intializing SD boot data : Software platform XML error, sdx:qemuArguments value "Zynq_CPU_wrapper_hw_platform_4/qemu/qemu_args.txt" path does not exist D:/workspace/l2/s3/Zynq_CPU_wrapper_hw_platform_4/export/Zynq_CPU_wrapper_hw_platform_4/sw/Zynq_CPU_wrapper_hw_platform_4/qemu/qemu_args.txt, platform path D:/workspace/l2/s3/Zynq_CPU_wrapper_hw_platform_4/export/Zynq_CPU_wrapper_hw_platform_4, sdx:configuration Zynq_CPU_wrapper_hw_platform_4, sdx:image standard
make: *** [makefile:37: package] Error 1
14:17:33 Build Finished (took 3s.213ms)
```

Add qemu/qemu_args.txt under the following path:

```PATH
D:\workspace\l2\s3\Zynq_CPU_wrapper_hw_platform_4\export\Zynq_CPU_wrapper_hw_platform_4\sw\Zynq_CPU_wrapper_hw_platform_4
```

Please modify the Makefiles of the following paths to:

PATH:

```PATH
D:\workspace\l2\s2_5\Zynq_CPU_wrapper_hw_platform_5\zynq_fsbl\zynq_fsbl_bsp\ps7_cortexa9_0\libsrc\rtl_alu_v1_0\src\Makefile
D:\workspace\l2\s2_5\Zynq_CPU_wrapper_hw_platform_5\ps7_cortexa9_0\standalone_ps7_cortexa9_0\bsp\ps7_cortexa9_0\libsrc\rtl_alu_v1_0\src\Makefile
```

```Makefile
COMPILER=
ARCHIVER=
CP=cp
COMPILER_FLAGS=
EXTRA_COMPILER_FLAGS=
LIB=libxil.a
 
RELEASEDIR=../../../lib
INCLUDEDIR=../../../include
INCLUDES=-I./. -I${INCLUDEDIR}
 
INCLUDEFILES=*.h
LIBSOURCES=$(wildcard *.c)
OUTS = *.o
OBJECTS = $(addsuffix .o, $(basename $(wildcard *.c)))
ASSEMBLY_OBJECTS = $(addsuffix .o, $(basename $(wildcard *.S)))
 
libs:
	echo "Compiling rtl_alu..."
	$(COMPILER) $(COMPILER_FLAGS) $(EXTRA_COMPILER_FLAGS) $(INCLUDES) $(LIBSOURCES)
	$(ARCHIVER) -r ${RELEASEDIR}/${LIB} ${OBJECTS} ${ASSEMBLY_OBJECTS}
	make clean
 
include:
	${CP} $(INCLUDEFILES) $(INCLUDEDIR)
 
clean:
	rm -rf ${OBJECTS} ${ASSEMBLY_OBJECTS}

```
