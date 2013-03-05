method(Interaction,

    LinkInteraction := Interaction clone lexicalDo(
        init := method(
            setSubdomains(list("fromNode", "toNode", "style", "link", "component"))
        )
    )
)
