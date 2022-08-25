#!/bin/bash

for i in {1..150000}
do
./gen > in.txt
./gen_line < in.txt >> test_games.txt
python lh.py < in.txt >> test_games.txt
done