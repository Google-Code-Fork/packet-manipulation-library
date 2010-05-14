#include "../../../Test/QUnit.hpp"
#include "../tcp.h"
#include <iostream>
#include <netinet/in.h>

/*TCP packet used
 * Source Port: 80
 * Dest Port: 1629
 * Seq #: 0
 * Ack # 1
 * Header length: 28
 * Flags: CWR-0; ECN-0; Urgent-0; ACK-1; Push-0; Reset-0; Syn-1; Fin-0
 * Window size: 5720
 * Checksum: 0xd659
 * Options: 8 bytes
 *    - Maximum segment size: 1430 bytes (0x02040596)
 *    - NOP: 0x01
 *    - NOP: 0x01
 *    - SACK permitted: 0x0402
 */

class TcpTest
{
	public:
		TcpTest( std::ostream &out, int verboseLevel = QUnit::verbose ) : qunit(
				out, verboseLevel )
 		{
		}

		int run()
		{
			testConstruction();
			return qunit.errors();
		}

	private:
		QUnit::UnitTest qunit;

		void testConstruction()
		{
			//28 bytes tcp header taken from wireshark dump
			//(min header size = 20bytes; max size = 60bytes
			uint8_t bits[] = { 0x00, 0x50, 0x60, 0x5d, 0x48, 0x5b, 0x27, 0xa6, 0xd2,
				0xa5, 0xeb, 0xac, 0x70, 0x12, 0x16, 0x58, 0xd6, 0x59, 0x00, 0x00, 0x02, 0x04, 0x05, 0x96, 0x01, 0x01, 0x04, 0x02 };

			//construct tcp header from bytes above
			TCP tcp_1( bits, 28 );

			//copy tcp header
			TCP tcp_2( tcp_1 );

			//check is tcp
			QUNIT_IS_TRUE( tcp_1.isTCP() );
			QUNIT_IS_TRUE( tcp_2.isTCP() );

			//check source port
			QUNIT_IS_TRUE( tcp_1.sourcePort() == 0x0050 );
			//check set source port
			tcp_1.setSourcePort( 0x0099 );
			QUNIT_IS_TRUE( tcp_1.sourcePort() == 0x0099 );

			//check dest port
			QUNIT_IS_TRUE( tcp_1.destinationPort() == 0x065d );
			//check set dest port
			tcp_1.setDestinationPort( 0x0666 );
			QUNIT_IS_TRUE( tcp_1.destinationPort() == 0x0666 );

			//check seq #
			QUNIT_IS_TRUE( tcp_1.sequenceNumber() == 0x485b27a6 );
			//check seq #
			tcp_1.setSequenceNumber( 0x40506070 );
			QUNIT_IS_TRUE( tcp_1.sequenceNumber() == 0x40506070 );

			//check ack #
			QUNIT_IS_TRUE( tcp_1.acknowledgementNumber() == 0xd2a5ebac );
			//check set ack #
			tcp_1.setAcknowledgementNumber( 0x11223344 );
			QUNIT_IS_TRUE( tcp_1.acknowledgementNumber() == 0x11223344 );

			//check data offset
			QUNIT_IS_TRUE( tcp_1.dataOffset() == 0x70 );
			//check set data offset
			tcp_1.setDataOffset( 0x99 );
			QUNIT_IS_TRUE( tcp_1.dataOffset() == 0x99 );

			//check return reserved data after data offset
			QUNIT_IS_TRUE( tcp_1.x2() == 0x00 );
			//check set reserved data
			tcp_1.setX2( 0x01 );
			QUNIT_IS_TRUE( tcp_1.x2() == 0x01 );

			//check CWR flag
			QUNIT_IS_FALSE( tcp_1.CWR_Flag() );
			//check set CWR flag
			tcp_1.setCWR_Flag( true );
			QUNIT_IS_TRUE( tcp_1.CWR_Flag() );
			tcp_1.setCWR_Flag( false );
			QUNIT_IS_FALSE( tcp_1.CWR_Flag() );
			//set flag to true
			tcp_1.setCWR_Flag();
			QUNIT_IS_TRUE( tcp_1.CWR_Flag() );

			//check ECE flag
			QUNIT_IS_FALSE( tcp_1.ECE_Flag() );
			//check set ECE flag
			tcp_1.setECE_Flag( true );
			QUNIT_IS_TRUE( tcp_1.ECE_Flag() );
			tcp_1.setECE_Flag( false );
			QUNIT_IS_FALSE( tcp_1.ECE_Flag() );
			//set flag to true
			tcp_1.setECE_Flag();
			QUNIT_IS_TRUE( tcp_1.ECE_Flag() );

			//check URG flag
			QUNIT_IS_FALSE( tcp_1.URG_Flag() );
			//check set URG flag
			tcp_1.setURG_Flag( true );
			QUNIT_IS_TRUE( tcp_1.URG_Flag() );
			tcp_1.setURG_Flag( false );
			QUNIT_IS_FALSE( tcp_1.URG_Flag() );
			//set flag to true
			tcp_1.setURG_Flag();
			QUNIT_IS_TRUE( tcp_1.URG_Flag() );

			//check ACK flag
			QUNIT_IS_TRUE( tcp_1.ACK_Flag() );
			//check set ACK flag
			tcp_1.setACK_Flag( false );
			QUNIT_IS_FALSE( tcp_1.ACK_Flag() );
			tcp_1.setACK_Flag( true );
			QUNIT_IS_TRUE( tcp_1.ACK_Flag() );
			tcp_1.setACK_Flag( false ); //set back to false
			//set flag to true
			tcp_1.setACK_Flag();
			QUNIT_IS_TRUE( tcp_1.ACK_Flag() );

			//check PSH flag
			QUNIT_IS_FALSE( tcp_1.PSH_Flag() );
			//check set PSH flag
			tcp_1.setPSH_Flag( true );
			QUNIT_IS_TRUE( tcp_1.PSH_Flag() );
			tcp_1.setPSH_Flag( false );
			QUNIT_IS_FALSE( tcp_1.PSH_Flag() );
			//set flag to true
			tcp_1.setPSH_Flag();
			QUNIT_IS_TRUE( tcp_1.PSH_Flag() );

			//check RST flag
			QUNIT_IS_FALSE( tcp_1.RST_Flag() );
			//check set RST flag
			tcp_1.setRST_Flag( true );
			QUNIT_IS_TRUE( tcp_1.RST_Flag() );
			tcp_1.setRST_Flag( false );
			QUNIT_IS_FALSE( tcp_1.RST_Flag() );
			//set flag to true
			tcp_1.setRST_Flag();
			QUNIT_IS_TRUE( tcp_1.RST_Flag() );

			//check SYN flag
			QUNIT_IS_TRUE( tcp_1.SYN_Flag() );
			//check set SYN flag
			tcp_1.setSYN_Flag( false );
			QUNIT_IS_FALSE( tcp_1.SYN_Flag() );
			tcp_1.setSYN_Flag( true );
			QUNIT_IS_TRUE( tcp_1.SYN_Flag() );
			tcp_1.setSYN_Flag( false ); //set back to false
			//set flag to true
			tcp_1.setSYN_Flag();
			QUNIT_IS_TRUE( tcp_1.SYN_Flag() );

			//check FIN flag
			QUNIT_IS_FALSE( tcp_1.FIN_Flag() );
			//check set FIN flag
			tcp_1.setFIN_Flag( true );
			QUNIT_IS_TRUE( tcp_1.FIN_Flag() );
			tcp_1.setFIN_Flag( false );
			QUNIT_IS_FALSE( tcp_1.FIN_Flag() );
			//set flag to true
			tcp_1.setFIN_Flag();
			QUNIT_IS_TRUE( tcp_1.FIN_Flag() );

			//check then set window size
			QUNIT_IS_TRUE( tcp_1.windowSize() == 0x1658 );
			tcp_1.setWindowSize( 0x1111 );
			QUNIT_IS_TRUE( tcp_1.windowSize() == 0x1111 );

			//check then set checksum
			QUNIT_IS_TRUE( tcp_1.checksum() == 0xd659 );
			tcp_1.setChecksum( 0xd666 );
			QUNIT_IS_TRUE( tcp_1.checksum() == 0xd666 );

			//check then set urgent pointer
			QUNIT_IS_TRUE( tcp_1.urgentPointer() == 0x0000 );
			tcp_1.setUrgentPointer( 0x0001 );
			QUNIT_IS_TRUE( tcp_1.urgentPointer() == 0x0001 );

			//check the size
			QUNIT_IS_EQUAL( tcp_1.size(), tcp_2.size() );
			QUNIT_IS_TRUE( tcp_1.size() == 28 );

			//OPTIONS

		}
};
