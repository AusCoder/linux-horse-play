#! /bin/bash
if [ "$#" -ne 1 ]; then
        echo "need one file!";
        exit 1;
fi

PORT=3022;
VMUSER="vmarchie"
DIR="kermod"

scp -P $PORT $1 ${VMUSER}@localhost:~/kermod;
