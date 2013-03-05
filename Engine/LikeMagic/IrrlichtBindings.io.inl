method(type_system, io_vm, Irrlicht_Bindings,

    Irrlicht_Bindings lexicalDo(
        add_bindings(type_system)
        add_bindings_irr(type_system)
        add_bindings_core(type_system)
        add_bindings_gui(type_system)
        add_bindings_video(type_system)
        add_bindings_scene(type_system)
        add_bindings_custom(type_system)
        add_bindings_irr_io(type_system)
        add_protos_irr(io_vm)
    )
)
