# https://just.systems

default:
    echo 'Hello, world!'

build:
    echo 'Building the project...'
    g++ -std=c++17 src/*.cpp -Iinclude -o english-parser
