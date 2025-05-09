CMD="./build/bin/qt-library.app/Contents/MacOS/qt-library"

if [[ "$1" == "--cli" ]]; then
  CMD="$CMD --cli"
fi

$CMD
