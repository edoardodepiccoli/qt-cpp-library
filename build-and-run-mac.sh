set -e

./build.sh

if [[ "$1" == "--cli" ]]; then
  ./run-mac.sh --cli
else
  ./run-mac.sh
fi
