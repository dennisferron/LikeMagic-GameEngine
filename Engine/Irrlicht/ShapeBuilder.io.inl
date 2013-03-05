method(namespace_irr, namespace_Custom, PredefinedValues,

    ShapeBuilder := Object clone lexicalDo(

        appendProto(namespace_irr)
        appendProto(namespace_irr core)
        appendProto(PredefinedValues)

        displayShapes ::= nil

        create := method(style,

            dispShape := displayShapes perform(style dispShape, style)

            if (dispShape != nil and style alternateTextureWrap == true,
                changeTextureWrap(dispShape)
            )

            if (dispShape != nil and style onTextureWrap != nil,
                style onTextureWrap call(dispShape)
            )

            return dispShape
        )

        changeTextureWrap := method(mesh,

            buf := mesh getMeshBuffer(0)

            minX := nil
            maxX := nil
            minZ := nil
            maxZ := nil

            // Find the extents so we can scale our texture coords to 0..1
            for(i, 0, buf getVertexCount - 1,
                pos := buf getPosition_c(i)
                if (minX == nil or pos get_X < minX, minX = pos get_X)
                if (minZ == nil or pos get_Z < minZ, minZ = pos get_Z)
                if (maxX == nil or pos get_X > maxX, maxX = pos get_X)
                if (maxZ == nil or pos get_Z > maxZ, maxZ = pos get_Z)
            )

            scaleX := 1/(maxX - minX)
            scaleZ := 1/(maxZ - minZ)

            for(i, 0, buf getVertexCount - 1,
                pos := buf getPosition_c(i)
                tcoords := buf getTCoords_nc(i)
                tcoords set_X( (pos get_X - minX) * scaleX )
                tcoords set_Y( (pos get_Z - minZ) * scaleZ )
            )

            buf setDirty(EBT_VERTEX)
        )
    )
)
