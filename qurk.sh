#!/bin/bash
#set -x

# https://bioinfo-fr.net/astuce-ajouter-des-options-dans-un-script-bash-avec-getopt
function defaultargs() {
	QMK_BK=
	QMK_KB=
	QMK_KM=default
}

function usage() {
	printf "Usage :\n"
	printf "\t--setup                  : Setup the QMK environment\n"
	printf "\t--it                     : Run the docker image in interactive mode\n"
	printf "\t--clean                  : Clean the firmware folder\n"
	printf "\t--compile                : Build a new QMK firmware in the firmware folder\n"
	printf "\t\t--bl                   : QMK bootloader name (promicro)\n"
	printf "\t\t--kb*                  : QMK keyboard name\n"
	printf "\t\t--km                   : QMK keymap name (default)\n"
	printf "\t\t--kr*                  : QMK model name\n"
	printf "\t\t--env                  : Path to a folder with a .env file\n"
	printf "\t\t                       : Take priority over any other args\n"
	printf "\t-h	                     : Script help\n"
}

function checkargs() {
	if [ -z "$QMK_KB" ]; then
		echo >&2 "no --kb argument: keyboard name is mandatory."
		exit 1
	fi

	if [ -z "$QMK_KR" ]; then
		echo >&2 "no --kr argument: keyboard model is mandatory."
		exit 1
	fi
}

function loadargs() {
	if [ ! -f "$QMK_ENV/.env" ]; then
		echo >&2 "no .env file in $QMK_ENV"
		exit 1
	fi

	. $QMK_ENV/.env
}

function firmwarename() {
	case $QMK_BL in
	liatris)
		QMK_FW="${QMK_KB//\//_}_${QMK_KR}_${QMK_KM}_${QMK_BL}.uf2"
		break
		;;
	*)
		QMK_FW="${QMK_KB//\//_}_${QMK_KR}_${QMK_KM}.hex"
		break
		;;
	esac
}

function interactive() {
	docker run -it --rm \
		-v qmk_firmware:/qmk_firmware \
		-w /qmk_firmware \
		qmkfm/qmk_cli:latest
}

function setup() {
	docker run -it --rm \
		-v qmk_firmware:/qmk_firmware \
		qmkfm/qmk_cli:latest \
		bash -c "qmk setup -y"
}

function clean() {
	rm -rf firmware/*
}

function build() {
	docker run -it --rm \
		-v qmk_firmware:/qmk_firmware \
		-v ./keyboards/$QMK_KB/keymaps/$QMK_KM:/qmk_firmware/keyboards/$QMK_KB/keymaps/$QMK_KM \
		-v ./firmware:/firmware \
		-w /firmware \
		qmkfm/qmk_cli:latest \
		bash -c "qmk compile -e CONVERT_TO=$QMK_BL -kb $QMK_KB/$QMK_KR -km $QMK_KM && \
			cp /qmk_firmware/$QMK_FW /firmware && \
			chown -R $(id -u):$(id -g) /firmware"
}

OPTS=$(getopt -o h -l it,setup,clean,compile,bl:,kb:,km:,env: -- "$@")
if [ $? != 0 ]; then
	exit 1
fi

eval set -- "$OPTS"

while true; do
	case "$1" in
	-h)
		usage
		exit 0
		;;
	--setup)
		setup
		exit 0
		;;
	--clean)
		clean
		exit 0
		;;
	--it)
		interactive
		exit 0
		;;
	--compile)
		shift
		while true; do
			case "$1" in
			--bl)
				QMK_BL=$2
				shift 2
				;;
			--kb)
				QMK_KB=$2
				shift 2
				;;
			--km)
				QMK_KM=$2
				shift 2
				;;
			--kr)
				QMK_KR=$2
				shift 2
				;;
			--env)
				QMK_ENV=$2
				shift 2
				;;
			--setup)
				setup
				exit 0
				;;
			--clean)
				clean
				exit 0
				;;
			--)
				shift
				break
				;;
			esac
		done
		break
		;;
	*)
		usage
		exit 1
		;;
	esac
done

defaultargs
# if the env var is set, ignore other vars and get them from the env file
if [ ! -z "$QMK_ENV" ]; then
	loadargs
fi
checkargs
firmwarename

echo "KB: $QMK_KB"
echo "KR: $QMK_KR"
echo "KM: $QMK_KM"
echo "BL: $QMK_BL"
echo "FW: $QMK_FW"
build
