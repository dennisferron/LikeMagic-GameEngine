
// old start script path:
// ../../wayup/Script/wayup.io

// this start script path
// ../LikeMagic/Script/Io/debugtest.io

doRelativeFile("bootstrap.io")

appendProto(LikeMagic)
appendProto(LikeMagic namespace)
appendProto(LikeMagic LM_Protos)

get_test_ptr := method(v, ScriptUtil get_test_ptr(v))
ptr_addr_to_str := method(p, ScriptUtil ptr_addr_to_str(p))

su := ScriptUtil tmp

/*
writeln("void* before set: ", ptr_addr_to_str(su get_voidp_field))
su set_voidp_field(get_test_ptr("ABCD") unsafe_ptr_cast)
writeln("void* after set: ", ptr_addr_to_str(su get_voidp_field))

writeln("uchar* before set: ", ptr_addr_to_str(su get_ucharp_field))
su set_ucharp_field(get_test_ptr("ABCD") unsafe_ptr_cast)
writeln("uchar* after set: ", ptr_addr_to_str(su get_ucharp_field))
*/

writeln("void* before set: ", ptr_addr_to_str(su get_voidp_field))
su set_voidp_field(nil)
writeln("void* after set: ", ptr_addr_to_str(su get_voidp_field))

writeln("uchar* before set: ", ptr_addr_to_str(su get_ucharp_field))
su set_ucharp_field(nil)
writeln("uchar* after set: ", ptr_addr_to_str(su get_ucharp_field))

