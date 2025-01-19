@_default:
    just --list

clean:
    rm -rf build

build preset='Release':
    cmake --preset {{preset}}
    cmake --build build/{{preset}}

erase:
    pyocd erase --mass

flash: (build)
    pyocd load build/Release/src/microbit.elf

debug: (build "Debug")
    #!/usr/bin/env bash
    pyocd gdbserver &
    GDB_PID=$!
    echo "GDB PID: $GDB_PID"
    sleep 1
    arm-none-eabi-gdb build/Debug/src/microbit.elf -ex "target remote localhost:3333" -ex "load" -ex "b main" -ex "c"
    kill $GDB_PID
