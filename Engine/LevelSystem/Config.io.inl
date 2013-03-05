method(namespace_Bullet, namespace_irr, namespace_Custom, namespace_TPS, Structure, Styles, ScriptUtil,
    LevelSystem := Module clone lexicalDo(
        scripts := self scripts
        //LevelEditor := scripts LevelEditor(namespace_Bullet, namespace_irr, namespace_Custom, Structure, Styles)
        Props := scripts Props(namespace_Bullet, namespace_irr, namespace_Custom, Structure, Styles)
        Tile := scripts Tile(namespace_irr, namespace_Custom, namespace_TPS, Styles, ScriptUtil)
        Terrain := scripts Terrain(namespace_irr, namespace_Custom, namespace_TPS, Tile, Styles, ScriptUtil)
    )
)
