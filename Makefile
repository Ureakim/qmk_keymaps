# builder dans un volume et chown le .build a la fin
USER = $(shell id -u $(whoami)):$(shell id -g $(whoami))
KM_TARGET = liatris
KM_KB = splitkb/aurora/sofle_v2
KM_KM = ureakim
KM_PATH = keyboards/${KM_KB}/keymaps/${KM_KM}
DOCKER_QMK_IMG = qmkfm/qmk_cli:latest
DOCKER_CMD = docker run -it --rm
DOCKER_FW_VOL = -v qmk_firmware:/qmk_firmware
DOCKER_USER_VOL = -v ./.build:/qmk_firmware/.build -v ./${KM_PATH}:/qmk_firmware/${KM_PATH}
DOCKER_WORKSPACE = -w /qmk_firmware
DOCKER_INIT_CMD = ${DOCKER_CMD} ${DOCKER_FW_VOL} ${DOCKER_WORKSPACE} ${DOCKER_QMK_IMG} /bin/bash -c
DOCKER_BUILD_CMD = ${DOCKER_CMD} ${DOCKER_FW_VOL} ${DOCKER_USER_VOL} ${DOCKER_WORKSPACE} ${DOCKER_QMK_IMG} /bin/bash -c
QMK_ARGS = -e CONVERT_TO=${KM_TARGET} -kb ${KM_KB} -km ${KM_KM}
CHOWN_FW_CMD = chown -R ${USER} /qmk_firmware/.build

.PHONY: setup
setup:
	${DOCKER_INIT_CMD} "qmk setup -y"

.PHONY: update
update:
	${DOCKER_INIT_CMD} "git pull && make git-submodules"

.PHONY: clean
clean:
	rm -rf ./.build

.PHONY: compile
compile: update
	${DOCKER_BUILD_CMD} "${CHOWN_FW_CMD} && qmk compile ${QMK_ARGS} && ${CHOWN_FW_CMD}"

.PHONY: flash
flash: update
	${DOCKER_BUILD_CMD} "${CHOWN_FW_CMD} && qmk flash -c ${QMK_ARGS}"
