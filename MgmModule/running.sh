#!/bin/bash/

rm logpy.csv
rm log.csv

python3 test.py

./a.out

git add log.csv logpy.csv

git commit -m "changes"

git push origin master


