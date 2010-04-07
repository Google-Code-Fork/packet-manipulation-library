#ifndef TCP_OPTIONS_H
#define TCP_OPTIONS_H
#include <stdint.h>
#include <vector>
/*  TCP OPTIONS
 *
 *  Kind  Length               Meaning                            Reference
     0      -    End of Option List                  [RFC793]
     1      -    No-Operation                        [RFC793]
     2      4    Maximum Segment Size                [RFC793]
     3      3    WSOPT - Window Scale                [RFC1323]
     4      2    SACK Permitted                      [RFC2018]
     5      N    SACK                                [RFC2018]
     6      6    Echo (obsoleted by option 8)        [RFC1072]
     7      6    Echo Reply (obsoleted by option 8)  [RFC1072]
     8      10   TSOPT - Time Stamp Option           [RFC1323]
     9      2    Partial Order Connection Permitted  [RFC1693]
     10     3    Partial Order Service Profile       [RFC1693]
     11     6    CC                                  [RFC1644]
     12     6    CC.NEW                              [RFC1644]
     13     6    CC.ECHO                             [RFC1644]
     14     3    TCP Alternate Checksum Request      [RFC1146]
     15     N    TCP Alternate Checksum Data         [RFC1146]
     16          Skeeter                             [Stev_Knowles]
     17          Bubba                               [Stev_Knowles]
     18     3    Trailer Checksum Option             [Subbu_Subramaniam][Monroe_Bridges]
     19     18   MD5 Signature Option                [RFC2385]
     20          SCPS Capabilities                   [Keith_Scott]
     21          Selective Negative Acknowledgements [Keith_Scott]
     22          Record Boundaries                   [Keith_Scott]
     23          Corruption experienced              [Keith_Scott]
     24          SNAP                                [Vladimir_Sukonnik]
     25          Unassigned (released 2000-12-18)
     26          TCP Compression Filter              [Steve_Bellovin]
     27     8    Quick-Start Response                [RFC4782]
     28     4    User Timeout Option                 [RFC5482]
   29-252        Unassigned
    253     N    RFC3692-style Experiment 1 (*)      [RFC4727]
    254     N    RFC3692-style Experiment 2 (*)      [RFC4727]
*/


class TCPOption
{
	public:
		TCPOption( );
		//TCPOption( uint8_t kind );
		TCPOption( const TCPOption &t );
		virtual ~TCPOption( );

		virtual void setKind( uint8_t kind );
		virtual void setLength( uint8_t length );
		virtual void setData( std::vector< uint8_t > data );
		virtual void singleOctet( bool isit );

		virtual bool isSingleOctet( ) const { return isSingleOctet_; }
		virtual uint8_t kind() const { return kind_; }
		virtual uint8_t length() const { return length_; }
		virtual std::vector< uint8_t > data() const { return data_; }

		virtual std::vector< uint8_t > packetData() const; // packs up the bits as they appear on the network


	protected:
		uint8_t kind_;
		uint8_t length_;
		std::vector<uint8_t> data_;
		/*
		 * TCP Options come in 2 flavors
		 *
		 * case 1: A single octet of option kind
		 * case 2: An octet of option kind, an octet of option length
		 * 				 and the actual option data octets.
		 */
		bool isSingleOctet_; 

	public:
		static const uint8_t END_OF_LIST; 
	  static const uint8_t NO_OPERATION; 
		static const uint8_t MAXIMUM_SEGMENT_SIZE; 
		static const uint8_t WINDOW_SCALE; 
		static const uint8_t SACK_PERMITTED; 
		static const uint8_t SACK; 
		static const uint8_t ECHO; 
		static const uint8_t ECHO_REPLY; 
		static const uint8_t TIME_STAMP_OPTION; 
		static const uint8_t PARTIAL_ORDER_CONNECTION_PREMITTED; 
		static const uint8_t PARTIAL_ORDER_SERVICE_PROFILE; 
		static const uint8_t CC; 
		static const uint8_t CC_NEW; 
		static const uint8_t CC_ECHO; 
		static const uint8_t TCP_ALTERNATE_CHECKSUM_REQUEST; 
		static const uint8_t TCP_ALTERNATE_CHECKSUM_DATA; 
		static const uint8_t SKEETER; 
		static const uint8_t BUBBA; 
		static const uint8_t TRAILER_CHECKSUM_OPTION; 
		static const uint8_t MD5_SIGNATURE_OPTION; 
		static const uint8_t SCPS_CAPABILITIES; 
		static const uint8_t SELECTIVE_NEGATIVE_ACKNOWLEDGEMENTS; 
		static const uint8_t RECORD_BOUNDARIES; 
		static const uint8_t CORRUPTION_EXPERIENCED; 
		static const uint8_t SNAP; 
		static const uint8_t UNASSIGNED25; 
		static const uint8_t TCP_COMPRESSION_FILTER; 
		static const uint8_t QUICK_START_OPTION; 
		static const uint8_t USER_TIMEOUT_OPTION; 
		static const uint8_t UNASSIGNED29; 
		static const uint8_t UNASSIGNED30; 
		static const uint8_t UNASSIGNED31; 
		static const uint8_t UNASSIGNED32; 
		static const uint8_t UNASSIGNED33; 
		static const uint8_t UNASSIGNED34; 
		static const uint8_t UNASSIGNED35; 
		static const uint8_t UNASSIGNED36; 
		static const uint8_t UNASSIGNED37; 
		static const uint8_t UNASSIGNED38; 
		static const uint8_t UNASSIGNED39; 
		static const uint8_t UNASSIGNED40; 
		static const uint8_t UNASSIGNED41; 
		static const uint8_t UNASSIGNED42; 
		static const uint8_t UNASSIGNED43; 
		static const uint8_t UNASSIGNED44; 
		static const uint8_t UNASSIGNED45; 
		static const uint8_t UNASSIGNED46; 
		static const uint8_t UNASSIGNED47; 
		static const uint8_t UNASSIGNED48; 
		static const uint8_t UNASSIGNED49; 
		static const uint8_t UNASSIGNED50; 
		static const uint8_t UNASSIGNED51; 
		static const uint8_t UNASSIGNED52; 
		static const uint8_t UNASSIGNED53; 
		static const uint8_t UNASSIGNED54; 
		static const uint8_t UNASSIGNED55; 
		static const uint8_t UNASSIGNED56; 
		static const uint8_t UNASSIGNED57; 
		static const uint8_t UNASSIGNED58; 
		static const uint8_t UNASSIGNED59; 
		static const uint8_t UNASSIGNED60; 
		static const uint8_t UNASSIGNED61; 
		static const uint8_t UNASSIGNED62; 
		static const uint8_t UNASSIGNED63; 
		static const uint8_t UNASSIGNED64; 
		static const uint8_t UNASSIGNED65; 
		static const uint8_t UNASSIGNED66; 
		static const uint8_t UNASSIGNED67; 
		static const uint8_t UNASSIGNED68; 
		static const uint8_t UNASSIGNED69; 
		static const uint8_t UNASSIGNED70; 
		static const uint8_t UNASSIGNED71; 
		static const uint8_t UNASSIGNED72; 
		static const uint8_t UNASSIGNED73; 
		static const uint8_t UNASSIGNED74; 
		static const uint8_t UNASSIGNED75; 
		static const uint8_t UNASSIGNED76; 
		static const uint8_t UNASSIGNED77; 
		static const uint8_t UNASSIGNED78; 
		static const uint8_t UNASSIGNED79; 
		static const uint8_t UNASSIGNED80; 
		static const uint8_t UNASSIGNED81; 
		static const uint8_t UNASSIGNED82; 
		static const uint8_t UNASSIGNED83; 
		static const uint8_t UNASSIGNED84; 
		static const uint8_t UNASSIGNED85; 
		static const uint8_t UNASSIGNED86; 
		static const uint8_t UNASSIGNED87; 
		static const uint8_t UNASSIGNED88; 
		static const uint8_t UNASSIGNED89; 
		static const uint8_t UNASSIGNED90; 
		static const uint8_t UNASSIGNED91; 
		static const uint8_t UNASSIGNED92; 
		static const uint8_t UNASSIGNED93; 
		static const uint8_t UNASSIGNED94; 
		static const uint8_t UNASSIGNED95; 
		static const uint8_t UNASSIGNED96; 
		static const uint8_t UNASSIGNED97; 
		static const uint8_t UNASSIGNED98; 
		static const uint8_t UNASSIGNED99; 
		static const uint8_t UNASSIGNED100; 
		static const uint8_t UNASSIGNED101; 
		static const uint8_t UNASSIGNED102; 
		static const uint8_t UNASSIGNED103; 
		static const uint8_t UNASSIGNED104; 
		static const uint8_t UNASSIGNED105; 
		static const uint8_t UNASSIGNED106; 
		static const uint8_t UNASSIGNED107; 
		static const uint8_t UNASSIGNED108; 
		static const uint8_t UNASSIGNED109; 
		static const uint8_t UNASSIGNED110; 
		static const uint8_t UNASSIGNED111; 
		static const uint8_t UNASSIGNED112; 
		static const uint8_t UNASSIGNED113; 
		static const uint8_t UNASSIGNED114; 
		static const uint8_t UNASSIGNED115; 
		static const uint8_t UNASSIGNED116; 
		static const uint8_t UNASSIGNED117; 
		static const uint8_t UNASSIGNED118; 
		static const uint8_t UNASSIGNED119; 
		static const uint8_t UNASSIGNED120; 
		static const uint8_t UNASSIGNED121; 
		static const uint8_t UNASSIGNED122; 
		static const uint8_t UNASSIGNED123; 
		static const uint8_t UNASSIGNED124; 
		static const uint8_t UNASSIGNED125; 
		static const uint8_t UNASSIGNED126; 
		static const uint8_t UNASSIGNED127; 
		static const uint8_t UNASSIGNED128; 
		static const uint8_t UNASSIGNED129; 
		static const uint8_t UNASSIGNED130; 
		static const uint8_t UNASSIGNED131; 
		static const uint8_t UNASSIGNED132; 
		static const uint8_t UNASSIGNED133; 
		static const uint8_t UNASSIGNED134; 
		static const uint8_t UNASSIGNED135; 
		static const uint8_t UNASSIGNED136; 
		static const uint8_t UNASSIGNED137; 
		static const uint8_t UNASSIGNED138; 
		static const uint8_t UNASSIGNED139; 
		static const uint8_t UNASSIGNED140; 
		static const uint8_t UNASSIGNED141; 
		static const uint8_t UNASSIGNED142; 
		static const uint8_t UNASSIGNED143; 
		static const uint8_t UNASSIGNED144; 
		static const uint8_t UNASSIGNED145; 
		static const uint8_t UNASSIGNED146; 
		static const uint8_t UNASSIGNED147; 
		static const uint8_t UNASSIGNED148; 
		static const uint8_t UNASSIGNED149; 
		static const uint8_t UNASSIGNED150; 
		static const uint8_t UNASSIGNED151; 
		static const uint8_t UNASSIGNED152; 
		static const uint8_t UNASSIGNED153; 
		static const uint8_t UNASSIGNED154; 
		static const uint8_t UNASSIGNED155; 
		static const uint8_t UNASSIGNED156; 
		static const uint8_t UNASSIGNED157; 
		static const uint8_t UNASSIGNED158; 
		static const uint8_t UNASSIGNED159; 
		static const uint8_t UNASSIGNED160; 
		static const uint8_t UNASSIGNED161; 
		static const uint8_t UNASSIGNED162; 
		static const uint8_t UNASSIGNED163; 
		static const uint8_t UNASSIGNED164; 
		static const uint8_t UNASSIGNED165; 
		static const uint8_t UNASSIGNED166; 
		static const uint8_t UNASSIGNED167; 
		static const uint8_t UNASSIGNED168; 
		static const uint8_t UNASSIGNED169; 
		static const uint8_t UNASSIGNED170; 
		static const uint8_t UNASSIGNED171; 
		static const uint8_t UNASSIGNED172; 
		static const uint8_t UNASSIGNED173; 
		static const uint8_t UNASSIGNED174; 
		static const uint8_t UNASSIGNED175; 
		static const uint8_t UNASSIGNED176; 
		static const uint8_t UNASSIGNED177; 
		static const uint8_t UNASSIGNED178; 
		static const uint8_t UNASSIGNED179; 
		static const uint8_t UNASSIGNED180; 
		static const uint8_t UNASSIGNED181; 
		static const uint8_t UNASSIGNED182; 
		static const uint8_t UNASSIGNED183; 
		static const uint8_t UNASSIGNED184; 
		static const uint8_t UNASSIGNED185; 
		static const uint8_t UNASSIGNED186; 
		static const uint8_t UNASSIGNED187; 
		static const uint8_t UNASSIGNED188; 
		static const uint8_t UNASSIGNED189; 
		static const uint8_t UNASSIGNED190; 
		static const uint8_t UNASSIGNED191; 
		static const uint8_t UNASSIGNED192; 
		static const uint8_t UNASSIGNED193; 
		static const uint8_t UNASSIGNED194; 
		static const uint8_t UNASSIGNED195; 
		static const uint8_t UNASSIGNED196; 
		static const uint8_t UNASSIGNED197; 
		static const uint8_t UNASSIGNED198; 
		static const uint8_t UNASSIGNED199; 
		static const uint8_t UNASSIGNED200; 
		static const uint8_t UNASSIGNED201; 
		static const uint8_t UNASSIGNED202; 
		static const uint8_t UNASSIGNED203; 
		static const uint8_t UNASSIGNED204; 
		static const uint8_t UNASSIGNED205; 
		static const uint8_t UNASSIGNED206; 
		static const uint8_t UNASSIGNED207; 
		static const uint8_t UNASSIGNED208; 
		static const uint8_t UNASSIGNED209; 
		static const uint8_t UNASSIGNED210; 
		static const uint8_t UNASSIGNED211; 
		static const uint8_t UNASSIGNED212; 
		static const uint8_t UNASSIGNED213; 
		static const uint8_t UNASSIGNED214; 
		static const uint8_t UNASSIGNED215; 
		static const uint8_t UNASSIGNED216; 
		static const uint8_t UNASSIGNED217; 
		static const uint8_t UNASSIGNED218; 
		static const uint8_t UNASSIGNED219; 
		static const uint8_t UNASSIGNED220; 
		static const uint8_t UNASSIGNED221; 
		static const uint8_t UNASSIGNED222; 
		static const uint8_t UNASSIGNED223; 
		static const uint8_t UNASSIGNED224; 
		static const uint8_t UNASSIGNED225; 
		static const uint8_t UNASSIGNED226; 
		static const uint8_t UNASSIGNED227; 
		static const uint8_t UNASSIGNED228; 
		static const uint8_t UNASSIGNED229; 
		static const uint8_t UNASSIGNED230; 
		static const uint8_t UNASSIGNED231; 
		static const uint8_t UNASSIGNED232; 
		static const uint8_t UNASSIGNED233; 
		static const uint8_t UNASSIGNED234; 
		static const uint8_t UNASSIGNED235; 
		static const uint8_t UNASSIGNED236; 
		static const uint8_t UNASSIGNED237; 
		static const uint8_t UNASSIGNED238; 
		static const uint8_t UNASSIGNED239; 
		static const uint8_t UNASSIGNED240; 
		static const uint8_t UNASSIGNED241; 
		static const uint8_t UNASSIGNED242; 
		static const uint8_t UNASSIGNED243; 
		static const uint8_t UNASSIGNED244; 
		static const uint8_t UNASSIGNED245; 
		static const uint8_t UNASSIGNED246; 
		static const uint8_t UNASSIGNED247; 
		static const uint8_t UNASSIGNED248; 
		static const uint8_t UNASSIGNED249; 
		static const uint8_t UNASSIGNED250; 
		static const uint8_t UNASSIGNED251; 
		static const uint8_t UNASSIGNED252; 
		static const uint8_t RFC_3692_EXPERIMENT_1; 
		static const uint8_t RFC_3692_EXPERIEMNT_2; 
};

#endif
