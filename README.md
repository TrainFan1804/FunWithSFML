# Instruction

A collection of small programms to learn SFML and starting to explore graphical programming. You can explore all via a terminal interface. Just enter the number of the wanted programm.

1. How to Install
2. Overview
3. Misc

# How to Install

## Prerequisites

Make sure you have **SFML 2.5** and **CMake** installed.

## Installation

1. **Clone the repo**

```bash
git clone https://github.com/TrainFan1804/FunWithSFML.git
cd FunWithSFML
```

2. **Create build directory inside and move inside**

```bash
mkdir -p build
cd build
```

3. **Configure and build project with cmake**

```bash
cmake ..
cmake --build .
```

4. **Run the application starter**

```bash
chmod 744 run.sh
./run.sh
```

Make sure you are in the projects root directory!

5. **Have fun!**

Instead of installing manually you can use the install script.

```bash
chmod 744 install.sh
./install.sh
./run.sh
```

# Overview

## Hello World Triangle

![triangle_classic](docs/images/triangle_classic.png)

## Some little fun with squares and vector transformations

![square_party](docs/images/square_party.png)

## Working with keyboard inputs

![moving_one](docs/images/moving_one.png)

![moving_two](docs/images/moving_two.png)

## A small pong game

Here I tried to create a small game of pong.

![pong](docs/images/pong.png)

# Misc

This project use the Open Sans font. \
I doesn't test it on Windows or MacOS so I don't know if it will work on those.
