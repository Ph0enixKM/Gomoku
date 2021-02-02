doxygen
if [[ "$OSTYPE" == "darwin"* ]]; then
    open docs/html/index.html
else
    xdg-open docs/html/index.html
fi