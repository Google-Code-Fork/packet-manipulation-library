PWD=/home/scap/PacMan
PACKETDIR=/home/scap/PacMan/Packet
INETDIR=/home/scap/PacMan/Packet/Inet
LINKDIR=/home/scap/PacMan/Packet/Link
TRANSDIR=/home/scap/PacMan/Packet/Trans
APPDIR=/home/scap/PacMan/Packet/App
APPSOURCE=/home/scap/PacMan/Packet/App/app.cpp /home/scap/PacMan/Packet/App/raw.cpp
TRANSSOURCE=/home/scap/PacMan/Packet/Trans/tcp.cpp /home/scap/PacMan/Packet/Trans/udp.cpp /home/scap/PacMan/Packet/Trans/tcpOptions.cpp /home/scap/PacMan/Packet/Trans/trans.cpp
INETSOURCE=/home/scap/PacMan/Packet/Inet/inet.cpp /home/scap/PacMan/Packet/Inet/ipv4.cpp /home/scap/PacMan/Packet/Inet/icmp.cpp
LINKSOURCE=/home/scap/PacMan/Packet/Link/link.cpp /home/scap/PacMan/Packet/Link/ethernet.cpp /home/scap/PacMan/Packet/Link/mac.cpp
PACKETSOURCE=/home/scap/PacMan/Packet/packetBuilder.cpp /home/scap/PacMan/Packet/packet.cpp /home/scap/PacMan/Packet/packetBuffer.cpp /home/scap/PacMan/Packet/App/app.cpp /home/scap/PacMan/Packet/App/raw.cpp /home/scap/PacMan/Packet/Trans/tcp.cpp /home/scap/PacMan/Packet/Trans/udp.cpp /home/scap/PacMan/Packet/Trans/tcpOptions.cpp /home/scap/PacMan/Packet/Trans/trans.cpp /home/scap/PacMan/Packet/Inet/inet.cpp /home/scap/PacMan/Packet/Inet/ipv4.cpp /home/scap/PacMan/Packet/Inet/icmp.cpp /home/scap/PacMan/Packet/Link/link.cpp /home/scap/PacMan/Packet/Link/ethernet.cpp /home/scap/PacMan/Packet/Link/mac.cpp
APPOBJS=$(APPSOURCE:%.cpp=%.o)
TRANSOBJS=$(TRANSSOURCE:%.cpp=%.o)
INETOBJS=$(INETSOURCE:%.cpp=%.o)
LINKOBJS=$(LINKSOURCE:%.cpp=%.o)
PACKETOBJS=$(PACKETSOURCE:%.cpp=%.o)
APPHEADERS=/home/scap/PacMan/Packet/App/appData.h /home/scap/PacMan/Packet/App/app.h /home/scap/PacMan/Packet/App/raw.h
TRANSHEADERS=/home/scap/PacMan/Packet/Trans/tcp.h /home/scap/PacMan/Packet/Trans/udp.h /home/scap/PacMan/Packet/Trans/tcpOptions.h /home/scap/PacMan/Packet/Trans/trans.h /home/scap/PacMan/Packet/Trans/transData.h /home/scap/PacMan/Packet/Trans/eolOption.h /home/scap/PacMan/Packet/Trans/mssOption.h /home/scap/PacMan/Packet/Trans/noopOption.h /home/scap/PacMan/Packet/Trans/sackOption.h /home/scap/PacMan/Packet/Trans/sackPermittedOption.h /home/scap/PacMan/Packet/Trans/timeStampOption.h /home/scap/PacMan/Packet/Trans/wsOption.h
INETHEADERS=/home/scap/PacMan/Packet/Inet/inetData.h /home/scap/PacMan/Packet/Inet/inet.h /home/scap/PacMan/Packet/Inet/ipv4.h /home/scap/PacMan/Packet/Inet/icmp.h
LINKHEADERS=/home/scap/PacMan/Packet/Link/linkData.h /home/scap/PacMan/Packet/Link/link.h /home/scap/PacMan/Packet/Link/ethernet.h /home/scap/PacMan/Packet/Link/mac.h
PACKETHEADERS=/home/scap/PacMan/Packet/packetBuilder.h /home/scap/PacMan/Packet/packet.h /home/scap/PacMan/Packet/packetBuffer.h /home/scap/PacMan/Packet/App/appData.h /home/scap/PacMan/Packet/App/app.h /home/scap/PacMan/Packet/App/raw.h /home/scap/PacMan/Packet/Trans/tcp.h /home/scap/PacMan/Packet/Trans/udp.h /home/scap/PacMan/Packet/Trans/tcpOptions.h /home/scap/PacMan/Packet/Trans/trans.h /home/scap/PacMan/Packet/Trans/transData.h /home/scap/PacMan/Packet/Trans/eolOption.h /home/scap/PacMan/Packet/Trans/mssOption.h /home/scap/PacMan/Packet/Trans/noopOption.h /home/scap/PacMan/Packet/Trans/sackOption.h /home/scap/PacMan/Packet/Trans/sackPermittedOption.h /home/scap/PacMan/Packet/Trans/timeStampOption.h /home/scap/PacMan/Packet/Trans/wsOption.h /home/scap/PacMan/Packet/Inet/inetData.h /home/scap/PacMan/Packet/Inet/inet.h /home/scap/PacMan/Packet/Inet/ipv4.h /home/scap/PacMan/Packet/Inet/icmp.h /home/scap/PacMan/Packet/Link/linkData.h /home/scap/PacMan/Packet/Link/link.h /home/scap/PacMan/Packet/Link/ethernet.h /home/scap/PacMan/Packet/Link/mac.h
PACKETTESTDIR=/home/scap/PacMan/Packet/TestCode
INETTESTDIR=/home/scap/PacMan/Packet/Inet/TestCode
LINKTESTDIR=/home/scap/PacMan/Packet/Link/TestCode
TRANSTESTDIR=/home/scap/PacMan/Packet/Trans/TestCode
APPTESTDIR=/home/scap/PacMan/Packet/App/TestCode
PACKETTESTSOURCE=
APPTESTSOURCE=/home/scap/PacMan/Packet/App/TestCode/testRaw.cpp
TRANSTESTSOURCE=/home/scap/PacMan/Packet/Trans/TestCode/testTcp.cpp /home/scap/PacMan/Packet/Trans/TestCode/testUdp.cpp
INETTESTSOURCE=/home/scap/PacMan/Packet/Inet/TestCode/testIcmp.cpp /home/scap/PacMan/Packet/Inet/TestCode/testIPv4.cpp
LINKTESTSOURCE=/home/scap/PacMan/Packet/Link/TestCode/ethernetTest.cpp /home/scap/PacMan/Packet/Link/TestCode/macTest.cpp
PACKETTESTOBJS=$(PACKETTESTSOURCE:%.cpp=%.o)
APPTESTOBJS=$(APPTESTSOURCE:%.cpp=%.o)
TRANSTESTOBJS=$(TRANSTESTSOURCE:%.cpp=%.o)
INETTESTOBJS=$(INETTESTSOURCE:%.cpp=%.o)
LINKTESTOBJS=$(LINKTESTSOURCE:%.cpp=%.o)
