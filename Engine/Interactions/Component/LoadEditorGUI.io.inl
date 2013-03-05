
method(ComponentInteraction, Model, Irrlicht, EditorGUI, Avatar,

    LoadEditorGUI := ComponentInteraction clone lexicalDo(

        setReferent(mapSubdomains)

        referent at("component") setTrigger(
            irrComp : Irrlicht Component,
            guiComp : EditorGUI Component,
            avComp : Avatar Component
        )

        enter := method(
            guiComp setGui(irrComp gui) setGuiEvents(irrComp guiEvents) setAssets(irrComp assets) setCamera(irrComp camera)
            guiComp load
            self
        )
    )

    Model Graph registerInteraction(LoadEditorGUI)

    return LoadEditorGUI
)
