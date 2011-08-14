
// old start script path:
// ../../wayup/Script/wayup.io

// this start script path
// ../LikeMagic/Script/TestScripts/debugtest.io

doRelativeFile("../Io/bootstrap.io")

appendProto(LikeMagic)
appendProto(LikeMagic namespace)
appendProto(LikeMagic LM_Protos)

float_equal := method(left, right,
    (left - right) abs < 0.01
)

test_equal := method(expected, actual,
    if( float_equal(expected, actual),
        writeln("PASSED - ", call message argAt(1) code)
        return true
    ,
        writeln("FAILED - ", call message argAt(1) code, " Expected: ", expected, " Actual: ", actual)
        return false
    )
)

test_equal(2, ScriptUtil get_int(2))
test_equal(19.99, ScriptUtil get_double(19.99))
test_equal(1.99, ScriptUtil get_float(1.99))
