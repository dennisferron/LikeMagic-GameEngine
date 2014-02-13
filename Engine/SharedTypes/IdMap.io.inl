method(namespace_std,

    IdMap := Object clone lexicalDo(

        appendProto(namespace_std)

        _map ::= nil

        // The purpose of the list when we have a map is that
        // the C++ map doesn't mark its objects, so we use the
        // list to ensure all the objects in it get marked.
        _list ::= nil

        init := method(
            set_map(namespace MapIntToIoObject tmp)
            set_list(list())
        )

        atPut := method(id, obj,
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
