method(module, namespace_irr,
    Component := Object clone lexicalDo(
        module := module

        gui ::= nil
        guiEvents ::= nil
        assets ::= nil
        camera ::= nil
        tb ::= nil

        init := method(
            setTb(module Toolbar clone)
        )

        load := method(
            tb setGui(gui) setGuiEvents(guiEvents) setAssets(assets) setCamera(camera)
            tb load
            self
        )
    )
)
