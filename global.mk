PWD=/home/mkozma/tmp/PacMan
PACKETDIR=/home/mkozma/tmp/PacMan/Packet
INETDIR=/home/mkozma/tmp/PacMan/Packet/Inet
LINKDIR=/home/mkozma/tmp/PacMan/Packet/Link
TRANSDIR=/home/mkozma/tmp/PacMan/Packet/Trans
APPDIR=/home/mkozma/tmp/PacMan/Packet/App
APPSOURCE=/home/mkozma/tmp/PacMan/Packet/App/app.cpp /home/mkozma/tmp/PacMan/Packet/App/raw.cpp
TRANSSOURCE=/home/mkozma/tmp/PacMan/Packet/Trans/tcp.cpp /home/mkozma/tmp/PacMan/Packet/Trans/udp.cpp /home/mkozma/tmp/PacMan/Packet/Trans/tcpOptions.cpp /home/mkozma/tmp/PacMan/Packet/Trans/trans.cpp
INETSOURCE=/home/mkozma/tmp/PacMan/Packet/Inet/inet.cpp /home/mkozma/tmp/PacMan/Packet/Inet/ipv4.cpp /home/mkozma/tmp/PacMan/Packet/Inet/icmp.cpp
LINKSOURCE=/home/mkozma/tmp/PacMan/Packet/Link/link.cpp /home/mkozma/tmp/PacMan/Packet/Link/ethernet.cpp /home/mkozma/tmp/PacMan/Packet/Link/mac.cpp
PACKETSOURCE=/home/mkozma/tmp/PacMan/Packet/packetBuilder.cpp /home/mkozma/tmp/PacMan/Packet/packet.cpp /home/mkozma/tmp/PacMan/Packet/packetBuffer.cpp /home/mkozma/tmp/PacMan/Packet/App/app.cpp /home/mkozma/tmp/PacMan/Packet/App/raw.cpp /home/mkozma/tmp/PacMan/Packet/Trans/tcp.cpp /home/mkozma/tmp/PacMan/Packet/Trans/udp.cpp /home/mkozma/tmp/PacMan/Packet/Trans/tcpOptions.cpp /home/mkozma/tmp/PacMan/Packet/Trans/trans.cpp /home/mkozma/tmp/PacMan/Packet/Inet/inet.cpp /home/mkozma/tmp/PacMan/Packet/Inet/ipv4.cpp /home/mkozma/tmp/PacMan/Packet/Inet/icmp.cpp /home/mkozma/tmp/PacMan/Packet/Link/link.cpp /home/mkozma/tmp/PacMan/Packet/Link/ethernet.cpp /home/mkozma/tmp/PacMan/Packet/Link/mac.cpp
APPOBJS=$(APPSOURCE:%.cpp=%.o)
TRANSOBJS=$(TRANSSOURCE:%.cpp=%.o)
INETOBJS=$(INETSOURCE:%.cpp=%.o)
LINKOBJS=$(LINKSOURCE:%.cpp=%.o)
PACKETOBJS=$(PACKETSOURCE:%.cpp=%.o)
APPHEADERS=/home/mkozma/tmp/PacMan/Packet/App/appData.h /home/mkozma/tmp/PacMan/Packet/App/app.h /home/mkozma/tmp/PacMan/Packet/App/raw.h
TRANSHEADERS=/home/mkozma/tmp/PacMan/Packet/Trans/tcp.h /home/mkozma/tmp/PacMan/Packet/Trans/udp.h /home/mkozma/tmp/PacMan/Packet/Trans/tcpOptions.h /home/mkozma/tmp/PacMan/Packet/Trans/trans.h /home/mkozma/tmp/PacMan/Packet/Trans/transData.h /home/mkozma/tmp/PacMan/Packet/Trans/eolOption.h /home/mkozma/tmp/PacMan/Packet/Trans/mssOption.h /home/mkozma/tmp/PacMan/Packet/Trans/noopOption.h /home/mkozma/tmp/PacMan/Packet/Trans/sackOption.h /home/mkozma/tmp/PacMan/Packet/Trans/sackPermittedOption.h /home/mkozma/tmp/PacMan/Packet/Trans/timeStampOption.h /home/mkozma/tmp/PacMan/Packet/Trans/wsOption.h
INETHEADERS=/home/mkozma/tmp/PacMan/Packet/Inet/inetData.h /home/mkozma/tmp/PacMan/Packet/Inet/inet.h /home/mkozma/tmp/PacMan/Packet/Inet/ipv4.h /home/mkozma/tmp/PacMan/Packet/Inet/icmp.h
LINKHEADERS=/home/mkozma/tmp/PacMan/Packet/Link/linkData.h /home/mkozma/tmp/PacMan/Packet/Link/link.h /home/mkozma/tmp/PacMan/Packet/Link/ethernet.h /home/mkozma/tmp/PacMan/Packet/Link/mac.h
PACKETHEADERS=/home/mkozma/tmp/PacMan/Packet/packetBuilder.h /home/mkozma/tmp/PacMan/Packet/packet.h /home/mkozma/tmp/PacMan/Packet/packetBuffer.h /home/mkozma/tmp/PacMan/Packet/App/appData.h /home/mkozma/tmp/PacMan/Packet/App/app.h /home/mkozma/tmp/PacMan/Packet/App/raw.h /home/mkozma/tmp/PacMan/Packet/Trans/tcp.h /home/mkozma/tmp/PacMan/Packet/Trans/udp.h /home/mkozma/tmp/PacMan/Packet/Trans/tcpOptions.h /home/mkozma/tmp/PacMan/Packet/Trans/trans.h /home/mkozma/tmp/PacMan/Packet/Trans/transData.h /home/mkozma/tmp/PacMan/Packet/Trans/eolOption.h /home/mkozma/tmp/PacMan/Packet/Trans/mssOption.h /home/mkozma/tmp/PacMan/Packet/Trans/noopOption.h /home/mkozma/tmp/PacMan/Packet/Trans/sackOption.h /home/mkozma/tmp/PacMan/Packet/Trans/sackPermittedOption.h /home/mkozma/tmp/PacMan/Packet/Trans/timeStampOption.h /home/mkozma/tmp/PacMan/Packet/Trans/wsOption.h /home/mkozma/tmp/PacMan/Packet/Inet/inetData.h /home/mkozma/tmp/PacMan/Packet/Inet/inet.h /home/mkozma/tmp/PacMan/Packet/Inet/ipv4.h /home/mkozma/tmp/PacMan/Packet/Inet/icmp.h /home/mkozma/tmp/PacMan/Packet/Link/linkData.h /home/mkozma/tmp/PacMan/Packet/Link/link.h /home/mkozma/tmp/PacMan/Packet/Link/ethernet.h /home/mkozma/tmp/PacMan/Packet/Link/mac.h
PACKETTESTDIR=/home/mkozma/tmp/PacMan/Packet/TestCode
INETTESTDIR=/home/mkozma/tmp/PacMan/Packet/Inet/TestCode
LINKTESTDIR=/home/mkozma/tmp/PacMan/Packet/Link/TestCode
TRANSTESTDIR=/home/mkozma/tmp/PacMan/Packet/Trans/TestCode
APPTESTDIR=/home/mkozma/tmp/PacMan/Packet/App/TestCode
PACKETTESTSOURCE=
APPTESTSOURCE=/home/mkozma/tmp/PacMan/Packet/App/TestCode/testRaw.cpp
TRANSTESTSOURCE=/home/mkozma/tmp/PacMan/Packet/Trans/TestCode/testTcp.cpp /home/mkozma/tmp/PacMan/Packet/Trans/TestCode/testUdp.cpp
INETTESTSOURCE=/home/mkozma/tmp/PacMan/Packet/Inet/TestCode/testIcmp.cpp /home/mkozma/tmp/PacMan/Packet/Inet/TestCode/testIPv4.cpp
LINKTESTSOURCE=/home/mkozma/tmp/PacMan/Packet/Link/TestCode/ethernetTest.cpp /home/mkozma/tmp/PacMan/Packet/Link/TestCode/macTest.cpp
PACKETTESTOBJS=$(PACKETTESTSOURCE:%.cpp=%.o)
APPTESTOBJS=$(APPTESTSOURCE:%.cpp=%.o)
TRANSTESTOBJS=$(TRANSTESTSOURCE:%.cpp=%.o)
INETTESTOBJS=$(INETTESTSOURCE:%.cpp=%.o)
LINKTESTOBJS=$(LINKTESTSOURCE:%.cpp=%.o)
