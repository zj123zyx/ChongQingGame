#!/bin/sh

# 

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
APP_ROOT="$DIR"
echo "  APP_ROOT            = $APP_ROOT"



scripts_dir=${APP_ROOT}/src
target_dir=${APP_ROOT}/

echo $scripts_dir
echo $target_dir

#cd ${scripts_dir}
#svn up || exit 1

cd $APP_ROOT/bin
sh compile_scripts.sh -i $scripts_dir  -o  $target_dir/scripts.zip  -e xxtea_zip -ek ZHUANYAN -es SLOTS_LOBBY
exit 0

