@_default:
    just --list

clean:
    rm -rf build

build preset='Release':
    cmake --preset {{preset}}
    cmake --build build/{{preset}}
