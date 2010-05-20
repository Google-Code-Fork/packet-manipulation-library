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
		TcpTest( std::ostream &out, int verboseLevel = QUnit::verbose );

		int run();

	private:
		QUnit::UnitTest qunit;

		void testConstruction();
};

