/*
* Covariant Script Foreign Function Interface Extension
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
* Copyright (C) 2019 Michael Lee(李登淳)
* Email: mikecovlee@163.com
* Github: https://github.com/mikecovlee
*/
#include <covscript/dll.hpp>
#include <cstdlib>
#include <memory>
#include <ffi.h>

using dll_t=std::shared_ptr<cov::dll>;

class ffi_callable final {
    void(*func)();
public:
    ffi_callable(const dll_t& dll, const std::string& name):func(reinterpret_cast<void(*)()>(dll->get_address(name))) {}
    cs::var operator()(cs::vector& args) const
    {
        /*std::size_t args_size=args.size();
        ffi_cif f_cif;
        ffi_type *f_args=new ffi_type[args_size];
        void** f_values=new void*[args_size];
        ffi_arg rc;*/
        ffi_cif f_cif;
        if(ffi_prep_cif(&f_cif, FFI_DEFAULT_ABI, 0, &ffi_type_void, nullptr)==FFI_OK)
            ffi_call(&f_cif, func, nullptr, nullptr);
        return cs::null_pointer;
    }
};

void cs_extension_main(cs::name_space* ns)
{
	(*ns)
    .add_var("load", cs::make_cni([](const std::string& path)->dll_t{
        return std::make_shared<cov::dll>(path);
    }))
    .add_var("find", cs::make_cni([](const dll_t& dll, const std::string& name){
        return cs::var::make_protect<cs::callable>(ffi_callable(dll, name));
    }))
    .add_var("type_void", cs::var::make_constant<ffi_type*>(&ffi_type_void))
    .add_var("type_uint8", cs::var::make_constant<ffi_type*>(&ffi_type_uint8))
    .add_var("type_sint8", cs::var::make_constant<ffi_type*>(&ffi_type_sint8))
    .add_var("type_uint16", cs::var::make_constant<ffi_type*>(&ffi_type_uint16))
    .add_var("type_sint16", cs::var::make_constant<ffi_type*>(&ffi_type_sint16))
    .add_var("type_uint32", cs::var::make_constant<ffi_type*>(&ffi_type_uint32))
    .add_var("type_sint32", cs::var::make_constant<ffi_type*>(&ffi_type_sint32))
    .add_var("type_uint64", cs::var::make_constant<ffi_type*>(&ffi_type_uint64))
    .add_var("type_sint64", cs::var::make_constant<ffi_type*>(&ffi_type_sint64))
    .add_var("type_float", cs::var::make_constant<ffi_type*>(&ffi_type_float))
    .add_var("type_double", cs::var::make_constant<ffi_type*>(&ffi_type_double))
    .add_var("type_uchar", cs::var::make_constant<ffi_type*>(&ffi_type_uchar))
    .add_var("type_schar", cs::var::make_constant<ffi_type*>(&ffi_type_schar))
    .add_var("type_ushort", cs::var::make_constant<ffi_type*>(&ffi_type_ushort))
    .add_var("type_sshort", cs::var::make_constant<ffi_type*>(&ffi_type_sshort))
    .add_var("type_uint", cs::var::make_constant<ffi_type*>(&ffi_type_uint))
    .add_var("type_sint", cs::var::make_constant<ffi_type*>(&ffi_type_sint))
    .add_var("type_ulong", cs::var::make_constant<ffi_type*>(&ffi_type_ulong))
    .add_var("type_slong", cs::var::make_constant<ffi_type*>(&ffi_type_slong))
    .add_var("type_longdouble", cs::var::make_constant<ffi_type*>(&ffi_type_longdouble))
    .add_var("type_pointer", cs::var::make_constant<ffi_type*>(&ffi_type_pointer));
}