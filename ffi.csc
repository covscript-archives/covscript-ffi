import ffi
var dll=ffi.load("./test.so")
var test=ffi.find(dll, "test")
system.out.println(dll.test(0,1))