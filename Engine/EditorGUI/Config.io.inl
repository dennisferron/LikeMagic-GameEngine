method(namespace_irr,

    EditorGUI := Module clone
    EditorGUI lexicalDo(
        scripts := self scripts
        Component := scripts Component(EditorGUI, namespace_irr)
        Toolbar := scripts Toolbar(namespace_irr)
    )
)
