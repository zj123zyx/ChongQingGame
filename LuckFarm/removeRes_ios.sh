#!/usr/bin/env bash

VERSION=1.4
USERDOWNLOAD_SUBPATH="userdownload"
IOS_PRE_PATH="res"

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
RES_PATH="$DIR/../../../static/casino_cn/ios/$VERSION/app/res/$VERSION"
UPDATE_AD_PATH="$DIR/../../../static/casino_cn/ios/$VERSION/app/update_ad/$VERSION"
USER_DOWNLOAD_PATH="$DIR/../../../static/casino_cn/ios/$VERSION/app/userdownload/"

SCRIPTS_LIST=`ls -1 $DIR/src`
RES_LIST=`ls -1 $RES_PATH`
UPDATE_AD_LIST=`ls -1 $UPDATE_AD_PATH`
USER_DOWNLOAD_VERSION_LIST=`ls -1 $USER_DOWNLOAD_PATH`

# =====================================================================================
# removeScriptFiles
# ======================================================================================
function removeScriptFiles()
{
	local file_list=$1

	for file in $file_list; do
		echo $DIR/src/$file
		rm -r $DIR/src/$file
	done

	cp -r $DIR/cocos $DIR/src
}

# =====================================================================================
# pref_path sample: 'slotmachine' in 'assets/res/slotmachine/machineicon' 
# ======================================================================================
function removeRESFiles()
{
	local file_list=$1
	local pref_path=$2 

	local fileFullPath
	local child_file_list
	local assets_res_file

	for file in $file_list; do

		fileFullPath=$RES_PATH/$pref_path/$file
		assets_res_file=$IOS_PRE_PATH$pref_path/$file

		if [[ -d $fileFullPath ]]; then
			child_file_list=`ls -1 $fileFullPath`
			removeRESFiles "${child_file_list[@]}" $pref_path/$file

		elif [[ -e $assets_res_file ]]; then
			rm $assets_res_file
			echo "Remove: $assets_res_file"
		else			
			echo "**ERROR** res file: $assets_res_file not found."
#	exit 1
		fi
	
	done

}

# =====================================================================================
# removeUpdateAdFiles
# ======================================================================================
function removeUpdateAdFiles()
{
	local file_list=$1
	local pref_path=$2 

	local fileFullPath
	local child_file_list
	local assets_res_file

	for file in $file_list; do

		fileFullPath=$UPDATE_AD_PATH/$pref_path/$file
		assets_res_file=$IOS_PRE_PATH$pref_path/$file

		if [[ -d $fileFullPath ]]; then
			child_file_list=`ls -1 $fileFullPath`
			removeRESFiles "${child_file_list[@]}" $pref_path/$file

		elif [[ -e $assets_res_file ]]; then
			rm $assets_res_file
			echo "Remove: $assets_res_file"
		else			
			echo "**ERROR** res file: $assets_res_file not found."
		fi
	
	done

}


function remove_USER_DOWNLOAD_Files()
{
	local version=$1
	local file_list=$2
	local pref_path=$3

	local fileFullPath
	local child_file_list
	local assets_res_file

	for file in $file_list; do

		fileFullPath=$USER_DOWNLOAD_PATH/$version/$USERDOWNLOAD_SUBPATH/$pref_path/$file
		assets_res_file=$IOS_PRE_PATH$pref_path/$file

		if [[ -d $fileFullPath ]]; then
			child_file_list=`ls -1 $fileFullPath`
			remove_USER_DOWNLOAD_Files $version "${child_file_list[@]}" $pref_path/$file

		elif [[ -f $assets_res_file ]]; then
			rm $assets_res_file
			echo "Remove: $assets_res_file"
		else		
			echo "**ERROR** userdownload file: $assets_res_file not found."
#			exit 1
		fi
	
	done

}


echo " ====== removeRESFiles ====== "
#   removeScriptFiles "${SCRIPTS_LIST[@]}"  

echo " ====== removeRESFiles ====== "
removeRESFiles "${RES_LIST[@]}"

echo " ====== removeUpdateAdFiles ====== "
removeUpdateAdFiles "${UPDATE_AD_LIST[@]}"

echo ""
echo " ====== remove_USER_DOWNLOAD_Files ====== "

for versionFolder in $USER_DOWNLOAD_VERSION_LIST; do
	versionFileList=`ls -1 $USER_DOWNLOAD_PATH/$versionFolder/$USERDOWNLOAD_SUBPATH`
	remove_USER_DOWNLOAD_Files $versionFolder "${versionFileList[@]}"
done




