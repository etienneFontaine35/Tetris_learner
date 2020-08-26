#! /bin/bash

g++ -std=c++11 -Wall main.cpp grid.cpp graphics.cpp game_manager.cpp player.cpp -o Tetris_learner -lsfml-window -lsfml-graphics -lsfml-system -lboost_serialization
