add_executable(${TARGET_NAME}
    main.c
    startup.c
)
target_include_directories(${TARGET_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/extern/nrfx/templates
    ${CMAKE_SOURCE_DIR}/extern/nrfx/mdk
    ${CMAKE_SOURCE_DIR}/extern/nrfx/hal
    ${CMAKE_SOURCE_DIR}/extern/nrfx
    ${CMAKE_SOURCE_DIR}/extern/CMSIS/CMSIS/Core/Include
    ${CMAKE_SOURCE_DIR}/extern/CMSIS/Device/ARM/ARMCM4/Include/
)
target_compile_definitions(${TARGET_NAME} PRIVATE
    NRF52833_XXAA
)
