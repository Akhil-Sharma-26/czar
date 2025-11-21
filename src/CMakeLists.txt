# Czar compiler executable
add_executable(czar
    main.cpp
)

# Set target properties
set_target_properties(czar PROPERTIES
    OUTPUT_NAME czar
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED ON
)

# Platform-specific linking
if(WIN32)
    # Windows-specific settings
    if(MSVC)
        set_target_properties(czar PROPERTIES
            WIN32_EXECUTABLE OFF  # Console application
        )
    endif()
endif()
