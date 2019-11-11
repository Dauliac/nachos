# Author: github.com/dauliac
# Date:   11/11/19
# Version: 0.0.1
# Description:

set -e # Crash on error
set -u # Crash on undefined variable

LOGIN_1="jdauliac"
LOGIN_2="tveloso"
GROUP="G2"
TP_NUMBER=$1

SECRET=pP6gzA

DIR=$(realpath $(dirname ${BASH_SOURCE[0]})) # Folder where this script is

RAPORT=${DIR}/rapports/rapport_tp${TP_NUMBER}.pdf
TMP_RAPPORT=${DIR}rapport.pdf
ARCHIVE=${DIR}/${LOGIN_1}-${LOGIN_2}.tar.gz
DEST=/net/stockage/aguermou/NACHOS/TP${TP_NUMBER}/${GROUP}


#################
# Functions zone
#################

give_up() {
    cp ${RAPORT} ${TMP_RAPPORT}
    make -C ${DIR}/code indent clean all

    tar cvfz ${ARCHIVE} ${TMP_RAPPORT} ${DIR}/code/
    rm -f ${TMP_RAPPORT}

    chmod a+r ${ARCHIVE}
    chmod og-w ${ARCHIVE}
    are_you_sure
    mv ${ARCHIVE} ${DEST}
    printf "Everything is good !\n bye"
    exit 0
}

are_you_sure() {
    read -r -n 1 -p "Please verify you archive before continue. Is it okey ? (y/n)" SEND
    echo
    if [[ $SEND =~ ^[Yy]$ ]]
    then
        echo "Let's go"
    else
        exit 1
    fi
}

check() {
    if [[ ! -d ${DIR}/rapports ]]; then
        printf """${DIR}/rapports does not exist
        Please create this folder and put you rapports inside with name:
        rapports/rapport_td<NUMBER>.pdf"""
        exit 1
    fi
    if [[ ! -f "${RAPORT}" ]]; then
        printf "${RAPORT} does not exist\n Please put your rapport here with this name"
        exit 1
    fi
    if [[ ! -d ${DEST} ]]; then
        printf """${DEST} does not exist
        Are you on CREMI computer ?"""
        exit 1
    fi
}


#################
# Run zone
#################
check
read -r -n 1 -p "resources are okey, do you want to continue ? (y/n)" RESOURCES_INPUT
echo
if [[ $RESOURCES_INPUT =~ ^[Yy]$ ]]
then
    printf "Welcome in danger zone\n"
    give_up
fi
