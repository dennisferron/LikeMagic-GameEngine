
// This file is auto-copied from LikeMagic/Script/Io/*.
// Make sure you edit the original and not a copy.


// The LikeMagic object is a regular Io object that we use as a container to
// hold things like the C++ namespace and C++ classes objects.
LikeMagic := Object clone


// The bootstrap object is a temporary object pre-provided by the LikeMagic
// IoVM C++ code to provide the minimum functionality necessary to bootstrap
// the rest of the C++ namespace and classes system.

bootstrap do(

    // CxxProto is just a proto we use for all LikeMagic type sys objs.
    // Move CxxProto object from bootstrap object to LikeMagic object.
    LikeMagic CxxProto := CxxProto

    // IoVM bind_method(proto, name) is the only predefined function so far.
    // The only protos are IoVM and type_system.  (Maybe CxxProto.)

    // Just declare that the IoVM supports some methods and poof they will exist.
    // You don't even need to provide a call target for them.  It works because
    // in actuality all the LikeMagic IoVM methods all map to one C function,
    // and LikeMagic decides what function actually invoke based on message name.
    IoVM bind_method(IoVM, "set_onRegisterMethod")
    IoVM bind_method(IoVM, "set_onRegisterClass")
    IoVM bind_method(IoVM, "set_onRegisterBase")

    // What to do when a method is added.
    IoVM set_onRegisterMethod(
        block(class, name, call_target,
            class_proto := LikeMagic find_class(abstract_class)
            IoVM bind_method(class_proto, name)
        )
    )

    // What to do when a class is added.
    IoVM set_onRegisterClass(
        block(abstract_class,
            ns := abstract_class get_namespace
            writeln("TODO:  IoVM previously looked up the class proto in a C++ data container by type id to clone it.")
            writeln("TODO:  Add the class proto to the IoVM protos container.")
        )
    )

    // What to do when a base is added.
    IoVM set_onRegisterBase(
        block(abstract_class, base,
            LikeMagic find_class(abstract_class) appendProto(LikeMagic find_class(base))
        )
    )

    // A hack to allow the LikeMagic find_class method to work before
    // namespace support and AbstractClass bindings:  before namespaces,
    // make find look up the slot in the bootstrap object.
    // After namespace support is in place, find_class will be replaced
    // with a different version that uses namespaces.
    LikeMagic find_class := method(abstract_class,
        IoVM bind_method(abstract_class, "get_class_name")
        getSlot(abstract_class get_class_name)
    )

    // Register the IoVM as a type system observer so that
    // our register_class, register_method, etc. things will get input.
    IoVM bind_method(type_system, "add_type_system_observer")
    type_system add_type_system_observer(IoVM)

    // Create the bindings for the minimum typesystem objects needed to make
    // namespace support work.  This will add protos for AbstractClass
    // and Namespace, and will attach methods to get the namespace info.
    IoVM bind_method(type_system, "add_bindings")
    type_system add_bindings

    // Now replace the bootstrap find_class implementation with
    // the version that knows about namespaces.
    LikeMagic find_class := method(abstract_class,
        create_namespace(abstract_class get_namespace, abstract_class get_class_name)
        get_namespace getSlot(abstract_class get_class_name)
    )

    // And rebind everything, thus populating the namespaces.
    type_system add_bindings
)

// Don't need the bootstrap object anymore, hide the evidence.
removeSlot("bootstrap")

