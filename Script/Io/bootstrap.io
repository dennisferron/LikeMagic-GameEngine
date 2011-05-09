
// This file is auto-copied from LikeMagic/Script/Io/*.
// Make sure you edit the original and not a copy.


// The LikeMagic object is a regular Io object that we use as a container to
// hold things like the C++ namespace and C++ classes objects.
LikeMagic := Object clone


// The bootstrap object is a temporary object pre-provided by the LikeMagic
// IoVM C++ code to provide the minimum functionality necessary to bootstrap
// the rest of the C++ namespace and classes system.

appendProto(bootstrap)

appendProto(bootstrap LM_Protos)

IoVM := LM_Protos IoVM
type_system := LM_Protos type_system

LikeMagic := Object clone

LikeMagic namespace := Object clone

// What to do when a class is added.
IoVM set_onRegisterClass(
    block(abstract_class,
        className := abstract_class get_class_name
        cppNs := abstract_class get_namespace

        writeln("register class ", className, " in namespace ", cppNs to_string)

        // Look up the cpp namespace to get the Io object for it
        nsObj := find_namespace(cppNs)

        // The abstract_class object is the type system representation of the class,
        // but we need to create a specialized proxy instance of the class that allows calling the "new" method.
        class_proto := abstract_class create_class_proxy

        // If the slot already exists, append it to the new object so name lookup will work.
        if (nsObj hasSlot(className),
            if (nsObj getSlot(className) type == "LikeMagic",
                Exception raise("Cannot add LikeMagic class twice (or two different ones) for same class_name: " .. cppNs to_string .. "::" .. className)
            ,
                writeln("moving Io object namespace to proto for ", className)
                class_proto appendProto(nsObj getSlot(className))
            )
        )

        nsObj setSlot(className, class_proto)
    )
)

// Convert LikeMagic::Namespace object to the Io object associated with it.
find_namespace := method(ns,
    if (ns is_root,
        return Lobby LikeMagic namespace
    ,
        parentNs := find_namespace(ns get_parent)
        if (parentNs hasSlot(ns get_name) not,
            parentNs setSlot(ns get_name, Object clone)
        )
        return getSlot(ns get_name)
    )
)

type_system add_type_system_observer(IoVM)

/*
bootstrap do(

    // LM_Proxy is just a proto we use for all LikeMagic type sys objs.
    // Move LM_Proxy object from bootstrap object to LikeMagic object.
    LikeMagic LM_Proxy := LM_Proxy


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

*/
