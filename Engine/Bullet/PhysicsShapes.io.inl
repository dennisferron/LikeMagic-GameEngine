method(namespace_Bullet, namespace_Custom, PredefinedValues,

    PhysicsShapes := Object clone lexicalDo(
        appendProto(namespace_Bullet)
        appendProto(namespace_Custom)
        appendProto(PredefinedValues)

        none := method(nil)

        ball := method(style,
            btSphereShape new(style radius)
        )

        box := method(style,
            btBoxShape new(btVector3 tmp(style xSize / 2, style ySize / 2, style zSize / 2))
        )

        cyl := method(style,
            btCylinderShape new(btVector3 tmp(style radius, style length/2, style radius))
        )

        cylX := method(style,
            btCylinderShapeX new(btVector3 tmp(style length/2, style radius, style radius))
        )

        cylZ := method(style,
            btCylinderShapeZ new(btVector3 tmp(style radius, style radius, style length/2))
        )

        cone := method(style,
            btConeShape new(style radius, style length)
        )

        coneX := method(style,
            btConeShapeX new(style radius, style length)
        )

        coneZ := method(style,
            btConeShapeZ new(style radius, style length)
        )

        hills := method(style, dispShape,

            xSize := style xSize / style xTiles
            zSize := style zSize / style zTiles
            xTiles := style xTiles
            zTiles := style zTiles

            // Bullet does not provide a way to scale heightfields on X,Z
            // so we have to scale the final shape instead - by changing the style.
            //style setPhysScaleX(xSize * style dispScaleX)
            //style setPhysScaleZ(zSize * style dispScaleZ)
            style setPhysScaleX(1)
            style setPhysScaleZ(1)

            // However, when using float bullet uses the irrlicht mesh height directly
            // so it doesn't need to be scaled except by the same as the irrlicht obj is scaled
            style setPhysScaleY(style dispScaleY)

            tileSize := dimension2df tmp(xSize, zSize)
            tileCount := dimension2du tmp(xTiles, zTiles)
            material := nil
            hillHeight := style ySize
            countHills := dimension2df tmp(style xHills, style zHills)
            textureRepeatCount := dimension2df tmp(style xTextureRepeat, style zTextureRepeat)

            heightStickWidth := style xTiles
            heightStickLength := style zTiles

            upAxis := 1  // 0 = X, 1 = Y, 2 = Z

            heightDataType := PHY_FLOAT

            // bullet ignores scale when the heightfield type is float!!
            // (See line 159 in btHeightfieldTerrainShape.cpp)
            // The correct height will be set by getting it from the mesh directly anyway.
            heightScale := 0.0

            // I think this changes which diagonal the quad is split on to make triangles - ?
            flipQuadEdges := false

            buf := dispShape getMeshBuffer(0)

            minX := nil
            maxX := nil
            minY := nil
            maxY := nil
            minZ := nil
            maxZ := nil

            check_nan := method(f, name, x, y, z,
                if(ScriptUtil is_nan(f),
                    writeln(name, " is nan at ", x, ", ", y, ", ", z)
                )
            )

            for(i, 0, buf getVertexCount - 1,
                pos := buf getPosition_c(i)
                if (minX == nil or pos get_X < minX, minX = pos get_X)
                if (minY == nil or pos get_Y < minY, minY = pos get_Y)
                if (minZ == nil or pos get_Z < minZ, minZ = pos get_Z)

                if (maxX == nil or pos get_X > maxX, maxX = pos get_X)
                if (maxY == nil or pos get_Y > maxY, maxY = pos get_Y)
                if (maxZ == nil or pos get_Z > maxZ, maxZ = pos get_Z)

                check_nan(pos get_X, "pos X", pos get_X, pos get_Y, pos get_Z)
                check_nan(pos get_Y, "pos Y", pos get_X, pos get_Y, pos get_Z)
                check_nan(pos get_Z, "pos Z", pos get_X, pos get_Y, pos get_Z)
            )

            writeln("minX = ", minX, " maxX = ", maxX)

            // Irrlicht adds 1 more to X and Z tiles so we have to as well.
            xTiles = xTiles + 1
            zTiles = zTiles + 1

            // Bullet does NOT save the heightfield array!!  So we need to create with new, not tmp.
            heightfieldData := NativeArray_of_float new(xTiles * zTiles)

            for(i, 0, buf getVertexCount - 1,
                pos := buf getPosition_c(i)
                xCell := (xTiles-1) * (pos get_X - minX) / (maxX - minX)
                zCell := (zTiles-1) * (pos get_Z - minZ) / (maxZ - minZ)

                if (ScriptUtil is_nan(pos get_Z), writeln("cell ", xCell, ", ", zCell, " is nan!"))

                if (xCell < 0 or xCell >= xTiles, Exception raise("xCell " .. xCell .. " out of bounds for heightfield " .. xTiles .. " by " .. zTiles))
                if (zCell < 0 or zCell >= zTiles, Exception raise("zCell " .. zCell .. " out of bounds for heightfield " .. xTiles .. " by " .. zTiles))

                cellPos := xCell + xTiles * zCell

                heightfieldData at_put(cellPos, pos get_Y)
            )

            minHeight := minY
            maxHeight := maxY

            if (ScriptUtil is_nan(minHeight), Exception raise("Bad irrlicht heightmap"))

            btHeightfieldTerrainShape new(
                heightStickWidth,
                heightStickLength,
                heightfieldData begin_nc,
                heightScale,
                minHeight,
                maxHeight,
                upAxis,
                heightDataType,
                flipQuadEdges
            )
        )

        mesh := method(style, dispShape,

            meshBuf := dispShape getMeshBuffer(0)  // frame 0

            if (meshBuf getVertexType != EVT_STANDARD, Exception raise("The mesh's vertex data not in the standard format."))
            if (meshBuf getIndexCount < 3,
                writeln("Cannot create physshape for mesh, the mesh has no triangles.")
                return
            )

            bulletMesh := btIndexedMesh tmp

            bulletMesh set_m_numTriangles(meshBuf getIndexCount / 3)

            triangleIndexBase := meshBuf getIndices_nc
            triangleIndexBaseCasted := triangleIndexBase unsafe_ptr_cast

            bulletMesh set_m_triangleIndexBase(triangleIndexBaseCasted)

            vertexBase := meshBuf getVertices_nc
            vertexBaseCasted := vertexBase unsafe_ptr_cast
            bulletMesh set_m_vertexBase(vertexBaseCasted)

            indexSize := 2 // 16 bits, 2 bytes
            bulletMesh set_m_triangleIndexStride(3 * indexSize)
            bulletMesh set_m_numVertices(meshBuf getVertexCount)
            bulletMesh set_m_vertexStride(S3DVertex get_class get_size)

            // This will be set when the bullet mesh buf is added to the triangle index vertex array object
            //bulletMesh set_m_indexType(PHY_SHORT)

            // This defaults to whatever bullet is built with (floats or doubles).  For Irrlicht I'm sure we want only floats.
            bulletMesh set_m_vertexType(PHY_FLOAT)

            // Cant' figure out how to set the indexType properly here, and a comment indicates this constructor is only for backwards compatibility.
            // Best to use the default constructor and addIndexedMesh where you can specify the index type.
            //meshInterface := btTriangleIndexVertexArray new(numTriangles, indices unsafe_ptr_cast, indexStride, numVertices, vertices unsafe_ptr_cast, vertexStride)

            meshInterface := btTriangleIndexVertexArray new()
            meshInterface addIndexedMesh(bulletMesh, PHY_SHORT)

            return btBvhTriangleMeshShape new(meshInterface, true, true)
        )
    )
)
