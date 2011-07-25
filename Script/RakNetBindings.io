

// Get RakNet binding functions
LikeMagic namespace Bindings RakNet do(
    add_bindings(type_system)
    add_bindings_raknet(type_system)
    add_bindings_serializers(type_system)
    add_bindings_replicas(type_system)
    add_protos(io_vm)
)

