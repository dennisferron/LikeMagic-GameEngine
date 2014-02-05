method(namespace_std,

    IdMap := Object clone lexicalDo(

        appendProto(namespace_std)

        _map ::= nil

        // The purpose of the list when we have a map is that
        // the C++ map doesn't mark its objects, so we use the
        // list to ensure all the objects in it get marked.
        _list ::= nil

        init := method(
            set_map(map_of_s32_IoObject tmp)
            set_list(list())
        )

        atPut := method(id, obj,
            writeln("atPut _map is: ")
            writeln(_map)
            _map atPut(id, obj)
            _list append(obj)
            obj
        )

        at := method(id,
            _map at(id)
        )

        removeAt := method(id,
            _map removeAt(id)
        )
    )
)
