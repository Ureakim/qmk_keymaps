#!/bin/bash
#set -x

# https://bioinfo-fr.net/astuce-ajouter-des-options-dans-un-script-bash-avec-getopt
function defaultargs() {
	QMK_BK=
	QMK_KB=
	QMK_KM=default
}

function usage(){
	printf "Usage :\n"
	printf "\t--bl                   : QMK bootloader name ;\n"
	printf "\t--kb                   : QMK keyboard name ;\n"
	printf "\t--km                   : QMK keymap name ;\n"
	printf "\t-h                     : Script help.\n"
}

function checkargs() {
	if [ -z  "$QMK_KB" ]
	then
		>&2 echo "no --kb argument: keyboard name is mandatory."
		exit 1
	fi

	if [ -z  "$QMK_KR" ]
	then
		>&2 echo "no --kr argument: keyboard model is mandatory."
		exit 1
	fi
}

function loadargs() {
	. $QMK_ENV/.env
}

function setup() {
	docker run -it --rm \
		-v qmk_firmware:/qmk_firmware \
		qmkfm/qmk_cli:latest \
		bash -c "qmk setup"
}

function clean() {
	rm -rf .build
}

function build() {
	docker run -it --rm \
		-v qmk_firmware:/qmk_firmware \
		-v ./.build:/qmk_firmware/.build \
		-v ./keyboards/$QMK_KB/keymaps/$QMK_KM:/qmk_firmware/keyboards/$QMK_KB/keymaps/$QMK_KM \
		-w /qmk_firmware \
		qmkfm/qmk_cli:latest \
		bash -c "qmk compile -e CONVERT_TO=$QMK_BL -kb $QMK_KB/$QMK_KR -km $QMK_KM && \
		chown -R $(id -u):$(id -g) /qmk_firmware/.build"
}

defaultargs

OPTS=$( getopt -o h -l setup,clean,bl:,kb:,km:,env: -- "$@" )
if [ $? != 0 ]
then
	exit 1
fi

eval set -- "$OPTS"

while true ; do
	case "$1" in
		-h) usage;
			exit 0;;
		--bl) QMK_BL=$2;
			shift 2;;
		--kb) QMK_KB=$2;
			shift 2;;
		--km) QMK_KM=$2;
			shift 2;;
		--kr) QMK_KR=$2;
			shift 2;;
		--env) QMK_ENV=$2;
			shift 2;;
		--setup) setup;
			exit 0;;
		--clean) clean;
			exit 0;;
		--) shift; break;;
	esac
done

# if the env var is set, ignore other vars and get them from the env file
if [ -z "$QMK_ENV" ]
then
	checkargs
else
	defaultargs
	loadargs
	checkargs
fi

echo "BL: $QMK_BL"
echo "KB: $QMK_KB"
echo "KM: $QMK_KR"
echo "KM: $QMK_KM"
build
