KM_PATH = keyboards/splitkb/aurora/sofle_v2/keymaps/ureakim
DOCKER_CMD = docker run -it --rm -v qmk_firmware:/qmk_firmware -v ./.build:/qmk_firmware/.build -v ./${KM_PATH}:/qmk_firmware/${KM_PATH} -w /qmk_firmware qmkfm/qmk_cli

test:
	echo ${DOCKER_CMD}

.PHONY: init
init:
	${DOCKER_CMD} qmk setup -y

.PHONY: update
update:
	${DOCKER_CMD} git pull && git submodule sync --recursive && git submodule update --init --recursive

.PHONY: compile
compile: update
	${DOCKER_CMD} qmk compile -e CONVERT_TO=liatris -kb splitkb/aurora/sofle_v2/rev1 -km ureakim

.PHONY: flash
flash: update
	${DOCKER_CMD} qmk flash -c -e CONVERT_TO=liatris -kb splitkb/aurora/sofle_v2/rev1 -km ureakim
