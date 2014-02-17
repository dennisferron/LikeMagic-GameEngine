
method(module, namespace_irr, namespace_Custom, MainWindow, PredefinedValues, ScriptUtil,

    Component := Object clone lexicalDo(

        // Don't be confused, self here refers to the context
        // outside the lexicalDo, not to Component.  If you said 'self'
        // inside a method in Component, then self would be Component.
        module := module

        appendProto(PredefinedValues)
        appendProto(namespace_irr)
        appendProto(namespace_irr core)
        appendProto(namespace_irr custom)
        appendProto(namespace_irr video)
        appendProto(namespace_Custom)

        SColor := namespace_irr video SColor

        // Configuration args aren't visible after lexicalDo finishes,
        // so we must store them in the proto for the init method to use them.
        namespace_irr := namespace_irr
        MainWindow := MainWindow
        UserInterface := module UserInterface
        ScriptUtil := ScriptUtil

        mediaPath := method(ScriptUtil get_script_path .. "../")

        events ::= nil
        eventDispatch ::= nil
        keyboard ::= nil
        mouse ::= nil
        guiEvents ::= nil

        device ::= nil
        driver ::= nil
        smgr   ::= nil
        videoData ::= nil
        assets ::= nil

        sound ::= nil
        gui ::= nil
        collMan ::= nil
        meshMan ::= nil

        sceneNodeBuilder ::= nil

        // window title
        title ::= nil

        deviceTimer ::= nil
        frames := 0
        backColor := SColor tmpWithARGB(255,0,8,16)

        camera ::= nil

        graph := nil
        setGraph := method(value,
            updateSlot("graph", value)
            mouse setGraph(value)
        )

        init := method(

            setEventDispatch(UserInterface EventDispatch clone)
            setEvents(eventDispatch eventReceiver)

            setGuiEvents(UserInterface GuiEvents clone)
            writeln("EET_GUI_EVENT is >>>", EET_GUI_EVENT value)
            writeln("<<<")
            writeln("EDT_BURNINGSVIDEO is >>>", EDT_BURNINGSVIDEO value)
            writeln("<<<")
            eventDispatch addHandler(EET_GUI_EVENT,
                block(event,
                    guiEvents handle(event)
                )
            )

            windowSize := dimension2du tmp(MainWindow sizeX, MainWindow sizeY)
            deviceType := list(EDT_OPENGL, EDT_BURNINGSVIDEO, EDT_SOFTWARE, EDT_NULL) at(3)
            setDevice(namespace_irr createDevice(deviceType, windowSize, 16, false, false, false, events))

            if (device == nil,
                Exception raise("Failed to create irrlicht device")
            )

            setDeviceTimer(device getTimer)

            setDriver(device getVideoDriver)

            setAssets(module Assets clone setAssetPath(mediaPath) setDriver(driver))

            setSmgr(device getSceneManager)

            setCamera(
                module Camera clone setSmgr(smgr) setDriver(driver)
            )
            camera createNode

            shapeBuilder := module ShapeBuilder clone setDisplayShapes(
                module DisplayShapes clone setGeometry(
                    smgr getGeometryCreator
                )
            )

            sceneNodes := module SceneNodes clone setSmgr(smgr)
            setSceneNodeBuilder(
                module SceneNodeBuilder clone setAssets(assets) setShapeBuilder(shapeBuilder) setSceneNodes(
                    sceneNodes setAssets(assets)
                )
            )

            setVideoData(SExposedVideoData tmp)

            //if( CppFunc hasSlot("createIrrKlangDevice"),
            //	setSound(CppFunc createIrrKlangDevice(ESOD_AUTO_DETECT, ESEO_DEFAULT_OPTIONS, nil, IRR_KLANG_VERSION))
            //)

            smgr addLightSceneNode(
                nil, // parent
                vector3df tmpWithXYZ(0, 500, -50), // position
                SColorf tmpWithRGBA(1,1,1,1), // color
                200, // radius
                0 // id
            )

            smgr setAmbientLight(SColorf tmpWithRGBA(0.2, 0.2, 0.2, 0.2))

            setGui(device getGUIEnvironment)

            setCollMan(smgr getSceneCollisionManager)
            setMeshMan(smgr getMeshManipulator)

            setTitle(ScriptUtil get_string(driver getName) .. "  FPS: ")

            setKeyboard(module UserInterface Keyboard clone)
            eventDispatch addHandler(EET_KEY_INPUT_EVENT,
                block(event,
                    keyboard handle(event)
                )
            )

            setMouse(module UserInterface Mouse clone)
            mouse setGui(gui)
            mouse setCollMan(collMan)
            mouse setDriver(driver)
            mouse setIrrComp(self)
            eventDispatch addHandler(EET_MOUSE_INPUT_EVENT,
                block(event,
                    mouse handle(event)
                )
            )
        )

        addNode := method(node,
            sceneNode := sceneNodeBuilder buildSceneNode(node style)
            if( sceneNode != nil,
                nodeAttr := module NodeAttribute clone setStyle(node style) setSceneNode(sceneNode)
                nodeAttr setFlagBits(FlagBits_of_ISceneNode tmp(nodeAttr sceneNode)) setIsMouseDraggable
                node addAttribute(
                    nodeAttr
                )
            )
        )

        playSound := method(file,
            if(sound != nil,
                sound play2D(file, false, false, false, ESM_AUTO_DETECT, false)
            )
        )

        dispose := method(
            //objList foreach(obj, obj dispose)
            //device drop
        )

        beforeGraphics := method(
            driver beginScene(true, true, backColor, videoData, nil)
        )

        onGraphics := method(timeElapsed,

            // Keep the camera in sync with the player position
            //camera update

            // Draws debug lines to show where the windowbox of the camera is.
            //camera drawBox

            // !!! Graphics happens here !!!
            smgr drawAll

            // !!! Menu UI happens here !!!
            //if (menu != nil, menu draw)

            // !!! If you don't draw the environment at the end none of your GUI elements show up! !!!
            gui drawAll
        )

        afterGraphics := method(
            driver endScene

            frames = frames + 1
            if (frames % 10 == 0,
                device setWindowCaption(title .. (driver getFPS asString))
            )
        )

        shouldRun := method(
            return device run
        )

        nodeToGameObj := method(node,
            anim := ScriptObjAnimator findIn(node)
            if(anim == nil,
                nil
            ,
                anim getScriptObj
            )
        )

        removeObj := method(obj,
            if(obj != nil,
                obj dispose
            )
        )
    )
)
