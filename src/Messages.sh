#! /usr/bin/env bash
$EXTRACTRC `find . -name \*.rc` >> rc.cpp
$XGETTEXT *.cpp -o $podir/cuculus.pot
rm -f *.cpp
