#!/usr/bin/env bash
##
## mkxml - generate XML file for game
##
#######################################################################################

#######################################################################################
##
## Declare and validate variables
##
GAME="${1}"
[ -z "${GAME}" ] && GAME="game"
TITLE="fall2025/data game"

#######################################################################################
##
## Generate XML heading
##
echo    '<?xml version="1.0" encoding="UTF-8" standalone="no" ?>'      >  ${GAME}.xml
echo    '<rom-definition version="1.0">'                               >> ${GAME}.xml
echo -n '    <rom type="cartridge" title="'                            >> ${GAME}.xml
echo -n "${TITLE}"                                                     >> ${GAME}.xml
echo    '" version="1.0" />'                                           >> ${GAME}.xml

#######################################################################################
##
## Append the VBIN section
##
echo -n '<binary path="'                                               >> ${GAME}.xml
echo -n "../src/${GAME}.vbin"                                          >> ${GAME}.xml
echo    '" />'                                                         >> ${GAME}.xml

#######################################################################################
##
## Determine the textures, generate and append the section
##
VTEXFILES=$(/bin/ls -1 ../images/*.vtex 2> /dev/null)

#######################################################################################
##
## If there are no detected textures, generate an empty tag
##
if [ -z "${VTEXFILES}" ]; then
    echo '<textures />'                                                >> ${GAME}.xml

#######################################################################################
##
## otherwise generate a subtag for each detected VTEX
##
else
    echo '<textures>'                                                  >> ${GAME}.xml
    for file in ${VTEXFILES}; do
        echo -n '    <texture path="'                                  >> ${GAME}.xml
        echo -n "${file}"                                              >> ${GAME}.xml
        echo '" />'                                                    >> ${GAME}.xml
    done
    echo '</textures>'                                                 >> ${GAME}.xml
fi

#######################################################################################
##
## Determine the sounds, generate and append the section
##
VSNDFILES=$(/bin/ls -1 ../sounds/*.vsnd 2> /dev/null)

#######################################################################################
##
## If there are no detected sounds, generate an empty tag
##
if [ -z "${VSNDFILES}" ]; then
    echo '<sounds />'                                                  >> ${GAME}.xml

#######################################################################################
##
## otherwise generate a subtag for each detected VSND
##
else
    echo '<sounds>'                                                    >> ${GAME}.xml
    for file in ${VSNDFILES}; do
        echo -n '    <sound path="'                                    >> ${GAME}.xml
        echo -n "${file}"                                              >> ${GAME}.xml
        echo '" />'                                                    >> ${GAME}.xml
    done
    echo '</sounds>'                                                   >> ${GAME}.xml
fi

#######################################################################################
##
## and finally, close up our ROM definition
##
echo '</rom-definition>'                                               >> ${GAME}.xml

exit
