
#define ASSERT_NOT_NULL(value) \
    CHECK((value) != nullptr); \
    if ((value) == nullptr) \
        throw std::logic_error(std::string("Pointer should not be null: ") + #value);
