method(namespace_irr, PredefinedValues,

    SceneNodes := Object clone lexicalDo(

        smgr ::= nil
        assets ::= nil

        appendProto(namespace_irr)
        appendProto(namespace_irr core)
        appendProto(PredefinedValues)

        irr := namespace_irr

        loadTexture := method(style, key,
            assets loadTextureFromFile(style textureMap at(key))
        )

        skybox := method(style,
            smgr addSkyBoxSceneNode(
                loadTexture(style, "up"),
                loadTexture(style, "down"),
                loadTexture(style, "left"),
                loadTexture(style, "right"),
                loadTexture(style, "front"),
                loadTexture(style, "back"),
                nil,    // parent
                0       // id
            )
        )

        default := method(style, shape,

            sceneNode := smgr addMeshSceneNode(
                shape,  // mesh
                nil, // parent
                0,         // id
                vector3df tmp(style x, style y, -style z),    // position
                vector3df tmp,    // rotation
                vector3df tmp(style dispScaleX, style dispScaleY, style dispScaleZ), // scale
                false  // alsoAddIfMeshPointerZero
            )

            // Debugging - this creates the boxes and arrows
            /*
            sceneNode addChild(
                irr custom OrientationHelperSceneNode new(
                    1.0, // size
                    sceneNode, // parent
                    smgr, // mgr
                    0     // id
                )
            )
            */

            return sceneNode
        )
    )
)
