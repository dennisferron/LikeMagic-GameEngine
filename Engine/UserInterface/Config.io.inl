method(namespace_irr,
    Module clone lexicalDo(
        scripts := self scripts
        UserInterfaceRepresentation := scripts UserInterfaceRepresentation()
        MainWindow := scripts MainWindow()

        // TODO:  Split Menu between logical part and graphical / irrlicht part
        //Menu := scripts Menu(namespace_irr)
    )
)
