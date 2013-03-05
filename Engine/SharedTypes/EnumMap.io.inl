
method(IdMap,

    // Maps an enum to an Io Object
    // Important: you should use only 1 type of enum with each instance of EnumMap.
    // Since it uses the integer of the enum value, if you added two different
    // types of enum with same integer value, they'd overwrite one another.

    EnumMap := Object clone lexicalDo(
        _map ::= nil
        IdMap := IdMap

        init := method(
            set_map(IdMap clone)
        )

        atPut := method(enum, obj,
            _map atPut(enum value, obj)
        )

        at := method(enum,
            _map at(enum value)
        )

        removeAt := method(enum,
            _map removeAt(enum value)
        )
    )
)
