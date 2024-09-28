#!/bin/bash

g++ main.cpp game.cpp hero.cpp platform.cpp core.cpp -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -g
