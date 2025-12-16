call make clean -f Makefile TARGET=0 DEBUG=0
call make -f Makefile TARGET=0 DEBUG=0
call make clean -f Makefile TARGET=0 DEBUG=1
call make -f Makefile TARGET=0 DEBUG=1
call make clean -f Makefile TARGET=1 DEBUG=0
call make -f Makefile TARGET=1 DEBUG=0
call make clean -f Makefile TARGET=1 DEBUG=1
call make -f Makefile TARGET=1 DEBUG=1

rem xcopy /y ..\..\..\BuildFiles\EcoOS\arm64-v8a\StaticRelease\lib902ABA722D34417BB714322CC761620F.a %ECO_FRAMEWORK%\Eco.TaskScheduler1Lab\BuildFiles\EcoOS\arm64-v8a\StaticRelease\
rem xcopy /y ..\..\..\BuildFiles\EcoOS\arm64-v8a\DynamicRelease\902ABA722D34417BB714322CC761620F.so %ECO_FRAMEWORK%\Eco.TaskScheduler1Lab\BuildFiles\EcoOS\arm64-v8a\DynamicRelease\
