
// old start script path:
// ../../wayup/Script/wayup.io

// this start script path
// ../LikeMagic/Script/TestScripts/debugtest.io

doRelativeFile("../Io/bootstrap.io")

appendProto(LikeMagic)
appendProto(LikeMagic namespace)
appendProto(LikeMagic LM_Protos)

get_test_ptr := method(v, ScriptUtil get_test_ptr(v))
ptr_addr_to_str := method(p, ScriptUtil ptr_addr_to_str(p))

say := method(msg, writeln(); writeln(); writeln(msg); writeln())

su := ScriptUtil tmp

say("before get ptr")

ptr := get_test_ptr("ABCD")

say("after get ptr, before unsafe_cast")

unsafe_ptr := ptr unsafe_ptr_cast

say("after unsafe_cast, before set field")

su set_ucharp_field(unsafe_ptr)

say("after set field, before print field")

writeln("uchar* after set: ", ptr_addr_to_str(su get_ucharp_field))

say("after print field")

writeln("void* before set: ", ptr_addr_to_str(su get_voidp_field))
su set_voidp_field(nil)
writeln("void* after set: ", ptr_addr_to_str(su get_voidp_field))


writeln("uchar* before set: ", ptr_addr_to_str(su get_ucharp_field))
su set_ucharp_field(nil)
writeln("uchar* after set: ", ptr_addr_to_str(su get_ucharp_field))

