method(namespace_irr, namespace_Custom, PredefinedValues, Constants,

    SceneNodeBuilder := Object clone lexicalDo(

        appendProto(namespace_irr)
        appendProto(namespace_irr core)
        appendProto(PredefinedValues)

        SColor := namespace_irr video SColor

        shapeBuilder ::= nil
        sceneNodes ::= nil
        assets ::= nil

        buildSceneNode := method(style,

            sceneNode := nil

            if( style dispShape == "none",
                return nil
            )

            if( sceneNodes hasSlot(style dispShape) ,
                sceneNode = sceneNodes perform(style dispShape, style)
            ,
                shape := shapeBuilder create(style)
                sceneNode = sceneNodes default(style, shape)
            )

            if (sceneNode != nil,

                sceneNode setMaterialFlag(EMF_LIGHTING, true)

                // TODO: Also create material if wire frame
                if( style texture != nil,

                    texture := assets loadTextureFromFile(style texture)
                    sceneNode setMaterialTexture(0, texture)
                    sceneNode setMaterialType(EMT_SOLID)
                    //sceneNode setMaterialFlag(EMF_LIGHTING, false)
                    sceneNode setMaterialFlag(EMF_LIGHTING, true)

                    material := sceneNode getMaterial(0)

                    // Does this do any good?
                    material set_ColorMaterial(0)

                    // TODO:  Add shininess as a style property
                    material set_Shininess(50)

                    material set_SpecularColor(SColor tmpWithARGB(25, 25, 25, 25))

                    // Setting one of these (diffuse maybe?) really takes the depth out of lighting
                    // and makes a textured rigid body look dull
                    //material set_AmbientColor(SColor tmpWithARGB(255, 255, 255, 255))
                    //material set_DiffuseColor(SColor tmpWithARGB(255, 128, 128, 128))
                    //material set_EmissiveColor(SColor tmpWithARGB(255, 5, 5, 5))

                    // TODO:  Share node creation code among game objects.
                    // BUG: won't get called without texture file
                    material set_Wireframe(style wireframe)
                )
            )

            return sceneNode
        )
    )
)
