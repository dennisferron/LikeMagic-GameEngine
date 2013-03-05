method(namespace_std,
    SharedTypes := Module clone lexicalDo(
        scripts := self scripts
        Color := scripts Color()
        IdMap := scripts IdMap(namespace_std)
        EnumMap := scripts EnumMap(IdMap)
    )
)
