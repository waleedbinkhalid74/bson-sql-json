#!/bin/bash

show_help() {
    echo "Usage: $0 --scope <argument>"
    echo
    echo "Options:"
    echo "  --scope <argument>   Specify the scope to format (all, commit)"
    echo "  -h, --help           Show this help message"
}

if [ "$#" -eq 0 ]; then
    show_help
    exit 1
fi

# Parse the arguments
while [[ "$#" -gt 0 ]]; do
    case "$1" in
        --scope)
            SCOPE="$2"
            shift 2
            ;;
        -h|--help)
            show_help
            exit 0
            ;;
        *)
            echo "Unknown option: $1"
            show_help
            exit 1
            ;;
    esac
done

# Navigate to the src directory
cd ..

case "$SCOPE" in
    all)
    find ./src -name "*.cpp" -o -name "*.h" | xargs clang-format -i
    ;;
    commit)
    git diff --name-only HEAD | grep -E '\.(cpp|h|hpp)$' | xargs clang-format -i
    ;;
    *)
    echo "Unknown scope: $SCOPE"
    echo "Usage: $0 --scope <argument>(all|commit)"
    exit 1
    ;;
esac