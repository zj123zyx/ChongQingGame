#! /bin/sh

path="$(pwd)"

cd    $path/frameworks/runtime-src/proj.android/

rm -rf  assets/*
rm -rf  bin/*
rm -rf  gen/*
rm -rf  libs/armeabi/*

 # cd     $path/res/caipiao/

 # rm -rf  Archers
 # rm -rf  ForestSport
 # rm -rf  JungleAdventure
 # rm -rf  MagicMarbles
 # rm -rf  NewJungleRescue
 # rm -rf  TurboDrop

cd     $path/
cocos compile -p android -m release   &&  echo "完成 Android 打包 " && date #&& open $path/publish/android/







