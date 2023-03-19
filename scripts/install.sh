#!/bin/bash

set -e

main() {
    echo "=== barista installer script (by twert) ==="
    # TODO: Ask before downgrade and print vers (Use barista -v to check version)
    cp ./build/barista /usr/bin
    if [[ -f /usr/bin/barista ]]; then
        echo ""
        echo "barista installed!"
    else 
        echo ""
        echo "barista not installed! (did you run as sudo?)"
    fi
}
main