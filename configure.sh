#!/bin/bash
MAKEFILE=global.mk
PWD=`pwd`

echo "Generating Makefile..."

echo "PWD=${PWD}" > $MAKEFILE
echo "PACKETDIR=${PWD}/Packet" >> $MAKEFILE
PACKETDIR=${PWD}/Packet
echo "INETDIR=${PACKETDIR}/Inet" >> $MAKEFILE
INETDIR="${PACKETDIR}/Inet"
echo "LINKDIR=${PACKETDIR}/Link" >> $MAKEFILE
LINKDIR="${PACKETDIR}/Link"
echo "TRANSDIR=${PACKETDIR}/Trans" >> $MAKEFILE
TRANSDIR="${PACKETDIR}/Trans"
echo "APPDIR=${PACKETDIR}/App" >> $MAKEFILE
APPDIR="${PACKETDIR}/App"

#######################################################
#
#  Different Object Groups that might be useful
#
#######################################################
APPSOURCE="${APPDIR}/app.cpp ${APPDIR}/raw.cpp"
TRANSSOURCE="${TRANSDIR}/tcp.cpp ${TRANSDIR}/udp.cpp ${TRANSDIR}/tcpOptions.cpp ${TRANSDIR}/trans.cpp"
INETSOURCE="${INETDIR}/inet.cpp ${INETDIR}/ipv4.cpp ${INETDIR}/icmp.cpp"
LINKSOURCE="${LINKDIR}/link.cpp ${LINKDIR}/ethernet.cpp ${LINKDIR}/mac.cpp"
PACKETSOURCE="${PACKETDIR}/packetBuilder.cpp ${PACKETDIR}/packet.cpp ${PACKETDIR}/packetBuffer.cpp ${APPSOURCE} ${TRANSSOURCE} ${INETSOURCE} ${LINKSOURCE}"
echo "APPSOURCE=${APPSOURCE}" >> $MAKEFILE
echo "TRANSSOURCE=${TRANSSOURCE}" >> $MAKEFILE
echo "INETSOURCE=${INETSOURCE}" >> $MAKEFILE
echo "LINKSOURCE=${LINKSOURCE}" >> $MAKEFILE
echo "PACKETSOURCE=${PACKETSOURCE}" >> $MAKEFILE

echo "APPOBJS=\$(APPSOURCE:%.cpp=%.o)" >> $MAKEFILE
echo "TRANSOBJS=\$(TRANSSOURCE:%.cpp=%.o)" >> $MAKEFILE
echo "INETOBJS=\$(INETSOURCE:%.cpp=%.o)" >> $MAKEFILE
echo "LINKOBJS=\$(LINKSOURCE:%.cpp=%.o)" >> $MAKEFILE
echo "PACKETOBJS=\$(PACKETSOURCE:%.cpp=%.o)" >> $MAKEFILE

############ HEADERS ##############

APPHEADERS="${APPDIR}/appData.h ${APPDIR}/app.h ${APPDIR}/raw.h"

TRANSHEADERS="${TRANSDIR}/tcp.h ${TRANSDIR}/udp.h ${TRANSDIR}/tcpOptions.h ${TRANSDIR}/trans.h ${TRANSDIR}/transData.h ${TRANSDIR}/eolOption.h ${TRANSDIR}/mssOption.h ${TRANSDIR}/noopOption.h ${TRANSDIR}/sackOption.h ${TRANSDIR}/sackPermittedOption.h ${TRANSDIR}/timeStampOption.h ${TRANSDIR}/wsOption.h"

INETHEADERS="${INETDIR}/inetData.h ${INETDIR}/inet.h ${INETDIR}/ipv4.h ${INETDIR}/icmp.h"

LINKHEADERS="${LINKDIR}/linkData.h ${LINKDIR}/link.h ${LINKDIR}/ethernet.h ${LINKDIR}/mac.h"

PACKETHEADERS="${PACKETDIR}/packetBuilder.h ${PACKETDIR}/packet.h ${PACKETDIR}/packetBuffer.h ${APPHEADERS} ${TRANSHEADERS} ${INETHEADERS} ${LINKHEADERS}"

echo "APPHEADERS=${APPHEADERS}" >> $MAKEFILE
echo "TRANSHEADERS=${TRANSHEADERS}" >> $MAKEFILE
echo "INETHEADERS=${INETHEADERS}" >> $MAKEFILE
echo "LINKHEADERS=${LINKHEADERS}" >> $MAKEFILE
echo "PACKETHEADERS=${PACKETHEADERS}" >> $MAKEFILE


############################################################################## 
#
#  TEST DIRECTORIES and FILES
#
##############################################################################

PACKETTESTDIR=${PACKETDIR}/TestCode
echo "PACKETTESTDIR=${PACKETTESTDIR}" >> $MAKEFILE
INETTESTDIR="${INETDIR}/TestCode"
echo "INETTESTDIR=${INETTESTDIR}" >> $MAKEFILE
LINKTESTDIR="${LINKDIR}/TestCode"
echo "LINKTESTDIR=${LINKTESTDIR}" >> $MAKEFILE
TRANSTESTDIR="${TRANSDIR}/TestCode"
echo "TRANSTESTDIR=${TRANSTESTDIR}" >> $MAKEFILE
APPTESTDIR="${APPDIR}/TestCode"
echo "APPTESTDIR=${APPTESTDIR}" >> $MAKEFILE

#### Files
PACKETTESTSOURCE=""
echo "PACKETTESTSOURCE=${PACKETTESTSOURCE}" >> $MAKEFILE
APPTESTSOURCE="${APPTESTDIR}/testRaw.cpp"
echo "APPTESTSOURCE=${APPTESTSOURCE}" >> $MAKEFILE
TRANSTESTSOURCE="${TRANSTESTDIR}/testTcp.cpp ${TRANSTESTDIR}/testUdp.cpp"
echo "TRANSTESTSOURCE=${TRANSTESTSOURCE}" >> $MAKEFILE
INETTESTSOURCE="${INETTESTDIR}/testIcmp.cpp ${INETTESTDIR}/testIPv4.cpp"
echo "INETTESTSOURCE=${INETTESTSOURCE}" >> $MAKEFILE
LINKTESTSOURCE="${LINKTESTDIR}/ethernetTest.cpp ${LINKTESTDIR}/macTest.cpp"
echo "LINKTESTSOURCE=${LINKTESTSOURCE}" >> $MAKEFILE

echo "PACKETTESTOBJS=\$(PACKETTESTSOURCE:%.cpp=%.o)" >> $MAKEFILE
echo "APPTESTOBJS=\$(APPTESTSOURCE:%.cpp=%.o)" >> $MAKEFILE
echo "TRANSTESTOBJS=\$(TRANSTESTSOURCE:%.cpp=%.o)" >> $MAKEFILE
echo "INETTESTOBJS=\$(INETTESTSOURCE:%.cpp=%.o)" >> $MAKEFILE
echo "LINKTESTOBJS=\$(LINKTESTSOURCE:%.cpp=%.o)" >> $MAKEFILE

