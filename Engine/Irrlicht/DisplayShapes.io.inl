method(namespace_irr, namespace_Custom, PredefinedValues,

    DisplayShapes := Object clone lexicalDo(

        appendProto(namespace_irr)
        appendProto(namespace_irr core)
        appendProto(PredefinedValues)

        geometry ::= nil

        none := method(nil)

        ball := method(style,
            geometry createSphereMesh(
                style radius, // radius
                16, // polyCountX
                16 // polyCountY
            )
        )

        box := method(style,
            geometry createCubeMesh(
                vector3df tmp(style xSize, style ySize, style zSize)
            )
        )

        cyl := method(style,
            geometry createCylinderMesh(
                style radius, // radius
                style length, // length
                16, // tessellation (number of quads around)
                style color, // color
                style closeEnds, // closeTop
                0 // oblique (undocumented)
            )
        )

        cylX := method(style,
            // Note: it is the shape offset with Bullet that
            // rotates the mesh to be a cylX or cylZ.
            cyl(style)
        )

        cylZ := method(style,
            // Note: it is the shape offset with Bullet that
            // rotates the mesh to be a cylX or cylZ.
            cyl(style)
        )

        cone := method(style,
            geometry createConeMesh(
                style radius, // radius
                style length, // length
                16, // tessellation (number of quads around)
                style color, // colorTop
                style color, // colorBottom
                0 // oblique (undocumented)
            )
        )

        coneX := method(style,
            geometry createConeMesh(
                style radius, // radius
                style length, // length
                16, // tessellation (number of quads around)
                style color, // colorTop
                style color, // colorBottom
                0 // oblique (undocumented)
            )
        )

        coneZ := method(style,
            geometry createConeMesh(
                style radius, // radius
                style length, // length
                16, // tessellation (number of quads around)
                style color, // colorTop
                style color, // colorBottom
                0 // oblique (undocumented)
            )
        )

        hills := method(style,

            xSize := style xSize / style xTiles
            zSize := style zSize / style zTiles
            tileSize := dimension2df tmp(xSize, zSize)
            tileCount := dimension2du tmp(style xTiles, style zTiles)
            material := nil
            hillHeight := style ySize
            countHills := dimension2df tmp(style xHills, style zHills)
            textureRepeatCount := dimension2df tmp(style xTextureRepeat, style zTextureRepeat)

            geometry createHillPlaneMesh(
                tileSize,
                tileCount,
                material,
                hillHeight,
                countHills,
                textureRepeatCount
            )
        )

        plane := method(style,

            xSize := style xSize / style xTiles
            zSize := style zSize / style zTiles
            tileSize := dimension2df tmp(xSize, zSize)
            tileCount := dimension2du tmp(style xTiles, style zTiles)
            material := nil
            textureRepeatCount := dimension2df tmp(style xTextureRepeat, style zTextureRepeat)

            geometry createPlaneMesh(
                tileSize,
                tileCount,
                material,
                textureRepeatCount
            )
        )

        cloth := method(style,
            mesh := DisplayShapes plane(style, geometry)
            mesh setHardwareMappingHint(EHM_STREAM, EBT_VERTEX)
            buf := mesh getMeshBuffer(0)
            buf setHardwareMappingHint(EHM_STREAM, EBT_VERTEX)
            return mesh
        )

        // TODO:  Find a way to pass in the mesh without putting an Irrlicht object into a generic style.
        mesh := method(style,
            if( style mesh == nil,
                Exception raise("Style display shape is 'mesh' but style mesh slot is nil.")
            )
            return style mesh
        )

        skybox := method(style,
            smgr addSkyBoxSceneNode(
                nil,    // up
                nil,    // down
                dummy1, // left
                dummy2, // right,
                dummy3, // front
                night,   // back
                nil,    // parent
                0       // id
            )
        )
    )
)
