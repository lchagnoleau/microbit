add_executable(${TARGET_NAME} main.c startup.c)
target_include_directories(${TARGET_NAME} PRIVATE
  drivers/CMSIS/inc
)
