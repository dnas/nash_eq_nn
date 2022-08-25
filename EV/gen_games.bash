#!/bin/bash
make gen
make gen_line
make convert
rm train_ev.txt
rm train_games.txt
rm train.txt
for i in {1..1000000}
do
./gen > in.txt
./gen_line < in.txt >> train_games.txt
python lh.py < in.txt >> train_games.txt
done
./convert < train_games.txt > train_ev.txt
make gen_train
./gen_train >> train.txt
cat train_ev.txt >> train.txt
cat test_ev.txt >> train.txt
make NN_EV
./NN_EV > results.txt