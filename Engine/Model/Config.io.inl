method(namespace_std,
    ModelModule := Module clone
    ModelModule lexicalDo(
        scripts := self scripts
        Graph := scripts Graph(ModelModule, namespace_std)
        Node := scripts Node(ModelModule)
        Link := scripts Link(ModelModule)
        Domain := scripts Domain()
        Interaction := scripts Interaction(ModelModule)
        Time := scripts Time()
        Structure := scripts Structure()
        Referent := scripts Referent()
    )
)
