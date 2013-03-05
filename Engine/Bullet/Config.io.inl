method(namespace_Bullet, namespace_Custom, Constants, PredefinedValues, Styles,
    BulletModule := Module clone
    BulletModule lexicalDo(
        scripts := self scripts
        ConstraintObj := scripts ConstraintObj()
        ConstraintBuilder := scripts ConstraintBuilder(namespace_Bullet, Styles ConstraintStyles)
        NodeAttribute := scripts NodeAttribute(namespace_Bullet, namespace_Custom)
        Component := scripts Component(BulletModule, namespace_Bullet, namespace_Custom)
        PhysicsShapes := scripts PhysicsShapes(namespace_Bullet, namespace_Custom, PredefinedValues)
        ShapeBuilder := scripts ShapeBuilder(namespace_Bullet)
        BodyBuilder := scripts BodyBuilder(namespace_Bullet, namespace_Custom)
        ShapeOffsets := scripts ShapeOffsets(namespace_Bullet, Constants)
    )
)
