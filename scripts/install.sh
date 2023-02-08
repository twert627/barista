#!/bin/bash

main() {
    echo "=== barista installer script (by twert) ==="
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