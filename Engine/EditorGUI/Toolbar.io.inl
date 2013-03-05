method(namespace_irr,

    Toolbar := Object clone lexicalDo(

        appendProto(namespace_irr)
        appendProto(namespace_irr core)
        appendProto(namespace_irr custom)

        gui ::= nil
        guiEvents ::= nil
        camera ::= nil
        assets ::= nil
        toolBar ::= nil
        inOutButton ::= nil
        zEquation ::= nil
        radiusKnob ::= nil

        levelMapButton ::= nil
    )

    Toolbar load := method(

        setToolBar(gui addToolBar(nil, 111))

        toolBar setMinSize(dimension2du tmp(1, 42))
        outImage := assets loadTextureFromFile("Media/button-push-out.png")
        inImage :=  assets loadTextureFromFile("Media/button-push-in.png")
        setInOutButton(toolBar addButton(112, "", "push in/out", outImage, inImage, true, true))
        gui addStaticText("Z(X,Y)=", recti tmpWithXYXY(50, 10, 80, 20), false, false, toolBar, 112, true)
        setZEquation(gui addEditBox("2", recti tmpWithXYXY(85, 5, 250, 38), true, toolBar, 113))
        zEquation setMultiLine(true)
        gui addStaticText("radius=", recti tmpWithXYXY(260, 10, 290, 20), false, false, toolBar, 114, true)
        setRadiusKnob(gui addSpinBox("1.0", recti tmpWithXYXY(300, 2, 350, 38), true, toolBar, 115))
        radiusKnob setDecimalPlaces(1)
        radiusKnob setStepSize(0.1)
        radiusKnob setRange(0.1, 1000)

        levelMapImage := assets loadTextureFromFile("Media/button-level-map.png")
        setLevelMapButton(toolBar addButton(116, "", "level map", levelMapImage, levelMapImage, false, true))
        guiEvents register(levelMapButton)
        levelMapButton onClick := block(
            camera setDistZ(-1.5*camera distZ)
        )
    )

    return Toolbar
)
