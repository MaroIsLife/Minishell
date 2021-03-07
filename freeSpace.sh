#!/bin/bash
reset=$'\033[0;39m'
blue=$'\033[0;34m'
cyan=$'\033[1;96m'
red=$'\033[0;31m'
green=$'\033[0;32m'


size=$(df -h | grep $USER |  awk '{printf("%s",$2)}')
used=$(df -h | grep $USER |  awk '{printf("%s",$3)}')
size_left=$(df -h | grep $USER |  awk '{printf("%s",$4)}')
# size_left=$(df -h | grep $USER |  awk '{printf("%.f",$4)}')
echo "\n${blue}/dev/disk3 folder:${reset}\n"
df -h | grep -v grep | grep Filesystem
df -h | grep -v grep | grep $USER
echo "${blue}\nHome folder:${reset}\n"
#du -hd1 | sort
echo "${red}$(du -hd1)${reset}\n"
#df -h | grep -v grep | grep $mougnou
echo "${blue}Folder size${reset}\n" ${red}$size${reset}
echo "\n${blue}Size used${reset}\n" ${red}$used${reset}
echo "\n${blue}Size left${reset}\n" ${red}$size_left${reset}
echo "\n"
sleep 1

read -n1 -p "${green}Delete Cache? [${red}Y${green}/${red}N${green}]${reset}" key
if [ "$key" = "y" ]; 
then
	echo "\n${green}Deleting Cache...${reset}"
    rm -rf ~/Library/Caches | 2>/dev/null
fi
echo "\n"
read -n1 -p "${green}Delete The Download folder? [${red}Y${green}/${red}N${green}]${reset}" key
if [ "$key" = "y" ]; 
then
	echo "\n${green}Deleting Download Folder...${reset}"
    rm -rf ~/Downloads/* | 2>/dev/null
fi
echo "\n" 
read -n1 -p "${green}Clean Brew? [${red}Y${green}/${red}N${green}]${reset} " key
if [ "$key" = "y" ]; 
then
	brew cleanup
fi
echo "\n"
read -n1 -p "${green}Delete Zcomp and 42 Junk files? [${red}Y${green}/${red}N${green}]${reset}" key
if [ "$key" = "y" ]; 
then
	echo "\n${green}Deleting Junk...${reset}"
    rm -rf ~/.zcomp* | 2>/dev/null
    rm -rf ~/.cocoa* | 2>/dev/null
fi