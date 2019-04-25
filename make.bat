@mkdir build
@cd build
@mkdir imports
@gcc -c -static -fPIC -m32 -I..\libffi-win32 -I..\libffi-win32\include -I..\libffi-win32\src\x86 ..\libffi-win32\src\x86\win32.S ..\libffi-win32\src\x86\ffi.c ..\libffi-win32\src\closures.c ..\libffi-win32\src\prep_cif.c ..\libffi-win32\src\raw_api.c ..\libffi-win32\src\types.c
@g++ -std=c++14 -m32 -I%CS_DEV_PATH%\include -I.. -I..\libffi-win32 -I..\libffi-win32\include -I..\libffi-win32\src\x86 -shared -static -fPIC -s -O3 ..\ffi.cpp *.o -o .\imports\ffi.cse -L%CS_DEV_PATH%\lib -lcovscript