
// This file is auto-copied from LikeMagic/Script/Io/*.
// Make sure you edit the original and not a copy.


// The LikeMagic object is a regular Io object that we use as a container to
// hold things like the C++ namespace and C++ classes objects.
LikeMagic := Object clone


// The bootstrap object is a temporary object pre-provided by the LikeMagic
// io_vm C++ code to provide the minimum functionality necessary to bootstrap
// the rest of the C++ namespace and classes system.

appendProto(bootstrap)

appendProto(bootstrap LM_Protos)

io_vm := LM_Protos io_vm
type_system := LM_Protos type_system

LikeMagic := Object clone

// Set up the root aka global namespace.
// Later this will be supplanted by the LikeMagic static methods object
// for global functions, but until then we need a place to put other classes
// and namespaces as they are registered.
LikeMagic namespace := Object clone

// What to do when a class is added.
io_vm set_onRegisterClass(block(abstract_class,

    className := abstract_class get_class_name
    cppNs := abstract_class get_namespace

    //writeln("register class ", className, " in ", cppNs to_string, " and LikeMagic type=", abstract_class get_type describe)

    // Look up the cpp namespace to get the Io object for it
    nsObj := find_namespace(cppNs)

    // The root namespace object is not inside the root namespace but rather one level up
    if (cppNs is_root and className == "namespace",
        nsObj := LikeMagic
    )

    // The abstract_class object is the type system representation of the class,
    // but we need to create a specialized proxy instance of the class that allows calling the "new" method.
    class_proto := io_vm proxy_to_io_obj(abstract_class create_class_proxy)

    // Note:  on class_proto can only call new or ProxyMethods.  AbstractClass defines a get_type that overrides the
    // proxy method get_type, so we must use lm_get_type instead.
    //writeln("class_proto type = ", class_proto type, " className = ", className)
    //writeln("class_proto LikeMagic type = ", class_proto lm_get_type describe)

    // If the slot already exists, append it to the new object so name lookup will work.
    if (nsObj hasSlot(className),
        existingObj := nsObj getSlot(className)
        if (existingObj type == "LikeMagic",
            msg := "Cannot add LikeMagic class twice (or two different ones with the same class name).  Note:  namespace=" .. (cppNs to_string) .. " and className=" .. className
            msg = msg .. "  Note: existing object LikeMagic type=" .. (existingObj get_type describe) .. " and new object LikeMagic type=" .. (class_proto lm_get_type describe)
            Exception raise(msg)
        ,
            //writeln("Consolidating namespace ", className)
            old_proto := nsObj getSlot(className)
            old_proto slotNames foreach(name,
                if (name != "type",
                    //writeln("Copying ", name)
                    class_proto setSlot(name, old_proto getSlot(name))
                )
            )
        )
    )

    nsObj setSlot(className, class_proto)

    return class_proto
))

/*
io_vm set_onRegisterMethod(block(abstract_class, method_name, call_target,
    ns := find_namespace(abstract_class get_namespace)
    class_proto := ns getSlot(abstract_class get_class_name)
    io_vm bind_method(class_proto, method_name, call_target)
))
*/

// Convert LikeMagic::Namespace object to the Io object associated with it.
find_namespace := method(ns,
    //writeln("find_namespace(", ns to_string, ")")
    if (ns is_root,
        //writeln("namespace ", ns to_string, " is root")
        return Lobby LikeMagic namespace
    ,
        parentNs := find_namespace(ns get_parent)
        if (parentNs hasSlot(ns get_name) not,
            //writeln("creating namespace ", ns get_name, " in ", ns get_parent to_string)
            parentNs setSlot(ns get_name, Object clone)
        )
        return parentNs getSlot(ns get_name)
    )
)

io_vm set_onAddProto(block(ns, name, obj,
    //writeln("onAddProto")
    //writeln("onAddProto, ns type=", ns type, " and name=", name, " and obj type=", obj type)
    //nsObj := find_namespace(ns)
    //writeln("nsObj = ", nsObj)
    //nsObj setSlot(name, obj)
    LM_Protos setSlot(name, obj)
))

type_system add_type_system_observer(io_vm)

print_namespace_tree := method(ns, name, depth,
    depth repeat(write("    "))
    writeln(name)
    ns slotNames foreach(name,
        print_namespace_tree(ns getSlot(name), name, depth+1)
    )
)

print_class_info := method(obj,
    methodNames := obj get_class get_method_names
    for(i, 0, methodNames size - 1,
        name := methodNames at_c(i)
        writeln(name)
    )
)

//print_namespace_tree(LikeMagic namespace, "global", 0)

//print_class_info(LikeMagic namespace Irrlicht)

//Lobby appendProto(LikeMagic)
//Lobby appendProto(LikeMagic namespace)


/*

The code below might be a good idea but I'm not sure that the architecture
of LikeMagic will support it at this time.  It looks like I would
need to unify CallTarget with Expression to make this work.

ExpressionBuilder := Object clone

ExpressionBuilder _parseArgs := method(symbols, args, sender,

    results := list()

    if (args != nil,
        args foreach(a,
            results append(_build_expr(symbols, a))
        )
    )
    return results
)

ExpressionBuilder _build_expr := method(symbols, rootMessage,

    if (root == nil,  Exception raise("Error in structure; nil message encountered."))

    ns := Likemagic namespace NamespacePath global

    curMsg := rootMessage
    while(nextMessage != nil,
        nextPart := type_system look_up(ns, curMsg name)

        if(nextPart is_namespace,
            ns := ns subspace(curMsg name)
        )

        args := _build_expr
    )
)

ExpressionBuilder build := method(

    if (call argCount < 1, Exception raise("build_expr - no expression passed!"))

    args := map()
    for (i, 0, call argCount - 2,
        a := call argAt(i)
        name := a name
        value := call sender perform(name)
        args atPut(name, value)
    )

    code := call argAt(argCount - 1)

    _build_expr(args, code)
)

*/
