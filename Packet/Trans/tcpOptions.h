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

const uint8_t END_OF_LIST = 0;
const uint8_t NO_OPERATION = 1;
const uint8_t MAXIMUM_SEGMENT_SIZE = 2;
const uint8_t WINDOW_SCALE = 3;
const uint8_t SACK_PERMITTED = 4;
const uint8_t SACK = 5;
const uint8_t ECHO = 6;
const uint8_t ECHO_REPLY = 7;
const uint8_t TIME_STAMP_OPTION = 8;
const uint8_t PARTIAL_ORDER_CONNECTION_PREMITTED = 9;
const uint8_t PARTIAL_ORDER_SERVICE_PROFILE = 10;
const uint8_t CC = 11;
const uint8_t CC_NEW = 12;
const uint8_t CC_ECHO = 13;
const uint8_t TCP_ALTERNATE_CHECKSUM_REQUEST = 14;
const uint8_t TCP_ALTERNATE_CHECKSUM_DATA = 15;
const uint8_t SKEETER = 16;
const uint8_t BUBBA = 17;
const uint8_t TRAILER_CHECKSUM_OPTION = 18;
const uint8_t MD5_SIGNATURE_OPTION = 19;
const uint8_t SCPS_CAPABILITIES = 20;
const uint8_t SELECTIVE_NEGATIVE_ACKNOWLEDGEMENTS = 21;
const uint8_t RECORD_BOUNDARIES = 22;
const uint8_t CORRUPTION_EXPERIENCED = 23;
const uint8_t SNAP = 24;
const uint8_t UNASSIGNED25 = 25;
const uint8_t TCP_COMPRESSION_FILTER = 26;
const uint8_t QUICK_START_OPTION = 27;
const uint8_t USER_TIMEOUT_OPTION = 28;
const uint8_t UNASSIGNED29 = 29;
const uint8_t UNASSIGNED30 = 30;
const uint8_t UNASSIGNED31 = 31;
const uint8_t UNASSIGNED32 = 32;
const uint8_t UNASSIGNED33 = 33;
const uint8_t UNASSIGNED34 = 34;
const uint8_t UNASSIGNED35 = 35;
const uint8_t UNASSIGNED36 = 36;
const uint8_t UNASSIGNED37 = 37;
const uint8_t UNASSIGNED38 = 38;
const uint8_t UNASSIGNED39 = 39;
const uint8_t UNASSIGNED40 = 40;
const uint8_t UNASSIGNED41 = 41;
const uint8_t UNASSIGNED42 = 42;
const uint8_t UNASSIGNED43 = 43;
const uint8_t UNASSIGNED44 = 44;
const uint8_t UNASSIGNED45 = 45;
const uint8_t UNASSIGNED46 = 46;
const uint8_t UNASSIGNED47 = 47;
const uint8_t UNASSIGNED48 = 48;
const uint8_t UNASSIGNED49 = 49;
const uint8_t UNASSIGNED50 = 50;
const uint8_t UNASSIGNED51 = 51;
const uint8_t UNASSIGNED52 = 52;
const uint8_t UNASSIGNED53 = 53;
const uint8_t UNASSIGNED54 = 54;
const uint8_t UNASSIGNED55 = 55;
const uint8_t UNASSIGNED56 = 56;
const uint8_t UNASSIGNED57 = 57;
const uint8_t UNASSIGNED58 = 58;
const uint8_t UNASSIGNED59 = 59;
const uint8_t UNASSIGNED60 = 60;
const uint8_t UNASSIGNED61 = 61;
const uint8_t UNASSIGNED62 = 62;
const uint8_t UNASSIGNED63 = 63;
const uint8_t UNASSIGNED64 = 64;
const uint8_t UNASSIGNED65 = 65;
const uint8_t UNASSIGNED66 = 66;
const uint8_t UNASSIGNED67 = 67;
const uint8_t UNASSIGNED68 = 68;
const uint8_t UNASSIGNED69 = 69;
const uint8_t UNASSIGNED70 = 70;
const uint8_t UNASSIGNED71 = 71;
const uint8_t UNASSIGNED72 = 72;
const uint8_t UNASSIGNED73 = 73;
const uint8_t UNASSIGNED74 = 74;
const uint8_t UNASSIGNED75 = 75;
const uint8_t UNASSIGNED76 = 76;
const uint8_t UNASSIGNED77 = 77;
const uint8_t UNASSIGNED78 = 78;
const uint8_t UNASSIGNED79 = 79;
const uint8_t UNASSIGNED80 = 80;
const uint8_t UNASSIGNED81 = 81;
const uint8_t UNASSIGNED82 = 82;
const uint8_t UNASSIGNED83 = 83;
const uint8_t UNASSIGNED84 = 84;
const uint8_t UNASSIGNED85 = 85;
const uint8_t UNASSIGNED86 = 86;
const uint8_t UNASSIGNED87 = 87;
const uint8_t UNASSIGNED88 = 88;
const uint8_t UNASSIGNED89 = 89;
const uint8_t UNASSIGNED90 = 90;
const uint8_t UNASSIGNED91 = 91;
const uint8_t UNASSIGNED92 = 92;
const uint8_t UNASSIGNED93 = 93;
const uint8_t UNASSIGNED94 = 94;
const uint8_t UNASSIGNED95 = 95;
const uint8_t UNASSIGNED96 = 96;
const uint8_t UNASSIGNED97 = 97;
const uint8_t UNASSIGNED98 = 98;
const uint8_t UNASSIGNED99 = 99;
const uint8_t UNASSIGNED100 = 100;
const uint8_t UNASSIGNED101 = 101;
const uint8_t UNASSIGNED102 = 102;
const uint8_t UNASSIGNED103 = 103;
const uint8_t UNASSIGNED104 = 104;
const uint8_t UNASSIGNED105 = 105;
const uint8_t UNASSIGNED106 = 106;
const uint8_t UNASSIGNED107 = 107;
const uint8_t UNASSIGNED108 = 108;
const uint8_t UNASSIGNED109 = 109;
const uint8_t UNASSIGNED110 = 110;
const uint8_t UNASSIGNED111 = 111;
const uint8_t UNASSIGNED112 = 112;
const uint8_t UNASSIGNED113 = 113;
const uint8_t UNASSIGNED114 = 114;
const uint8_t UNASSIGNED115 = 115;
const uint8_t UNASSIGNED116 = 116;
const uint8_t UNASSIGNED117 = 117;
const uint8_t UNASSIGNED118 = 118;
const uint8_t UNASSIGNED119 = 119;
const uint8_t UNASSIGNED120 = 120;
const uint8_t UNASSIGNED121 = 121;
const uint8_t UNASSIGNED122 = 122;
const uint8_t UNASSIGNED123 = 123;
const uint8_t UNASSIGNED124 = 124;
const uint8_t UNASSIGNED125 = 125;
const uint8_t UNASSIGNED126 = 126;
const uint8_t UNASSIGNED127 = 127;
const uint8_t UNASSIGNED128 = 128;
const uint8_t UNASSIGNED129 = 129;
const uint8_t UNASSIGNED130 = 130;
const uint8_t UNASSIGNED131 = 131;
const uint8_t UNASSIGNED132 = 132;
const uint8_t UNASSIGNED133 = 133;
const uint8_t UNASSIGNED134 = 134;
const uint8_t UNASSIGNED135 = 135;
const uint8_t UNASSIGNED136 = 136;
const uint8_t UNASSIGNED137 = 137;
const uint8_t UNASSIGNED138 = 138;
const uint8_t UNASSIGNED139 = 139;
const uint8_t UNASSIGNED140 = 140;
const uint8_t UNASSIGNED141 = 141;
const uint8_t UNASSIGNED142 = 142;
const uint8_t UNASSIGNED143 = 143;
const uint8_t UNASSIGNED144 = 144;
const uint8_t UNASSIGNED145 = 145;
const uint8_t UNASSIGNED146 = 146;
const uint8_t UNASSIGNED147 = 147;
const uint8_t UNASSIGNED148 = 148;
const uint8_t UNASSIGNED149 = 149;
const uint8_t UNASSIGNED150 = 150;
const uint8_t UNASSIGNED151 = 151;
const uint8_t UNASSIGNED152 = 152;
const uint8_t UNASSIGNED153 = 153;
const uint8_t UNASSIGNED154 = 154;
const uint8_t UNASSIGNED155 = 155;
const uint8_t UNASSIGNED156 = 156;
const uint8_t UNASSIGNED157 = 157;
const uint8_t UNASSIGNED158 = 158;
const uint8_t UNASSIGNED159 = 159;
const uint8_t UNASSIGNED160 = 160;
const uint8_t UNASSIGNED161 = 161;
const uint8_t UNASSIGNED162 = 162;
const uint8_t UNASSIGNED163 = 163;
const uint8_t UNASSIGNED164 = 164;
const uint8_t UNASSIGNED165 = 165;
const uint8_t UNASSIGNED166 = 166;
const uint8_t UNASSIGNED167 = 167;
const uint8_t UNASSIGNED168 = 168;
const uint8_t UNASSIGNED169 = 169;
const uint8_t UNASSIGNED170 = 170;
const uint8_t UNASSIGNED171 = 171;
const uint8_t UNASSIGNED172 = 172;
const uint8_t UNASSIGNED173 = 173;
const uint8_t UNASSIGNED174 = 174;
const uint8_t UNASSIGNED175 = 175;
const uint8_t UNASSIGNED176 = 176;
const uint8_t UNASSIGNED177 = 177;
const uint8_t UNASSIGNED178 = 178;
const uint8_t UNASSIGNED179 = 179;
const uint8_t UNASSIGNED180 = 180;
const uint8_t UNASSIGNED181 = 181;
const uint8_t UNASSIGNED182 = 182;
const uint8_t UNASSIGNED183 = 183;
const uint8_t UNASSIGNED184 = 184;
const uint8_t UNASSIGNED185 = 185;
const uint8_t UNASSIGNED186 = 186;
const uint8_t UNASSIGNED187 = 187;
const uint8_t UNASSIGNED188 = 188;
const uint8_t UNASSIGNED189 = 189;
const uint8_t UNASSIGNED190 = 190;
const uint8_t UNASSIGNED191 = 191;
const uint8_t UNASSIGNED192 = 192;
const uint8_t UNASSIGNED193 = 193;
const uint8_t UNASSIGNED194 = 194;
const uint8_t UNASSIGNED195 = 195;
const uint8_t UNASSIGNED196 = 196;
const uint8_t UNASSIGNED197 = 197;
const uint8_t UNASSIGNED198 = 198;
const uint8_t UNASSIGNED199 = 199;
const uint8_t UNASSIGNED200 = 200;
const uint8_t UNASSIGNED201 = 201;
const uint8_t UNASSIGNED202 = 202;
const uint8_t UNASSIGNED203 = 203;
const uint8_t UNASSIGNED204 = 204;
const uint8_t UNASSIGNED205 = 205;
const uint8_t UNASSIGNED206 = 206;
const uint8_t UNASSIGNED207 = 207;
const uint8_t UNASSIGNED208 = 208;
const uint8_t UNASSIGNED209 = 209;
const uint8_t UNASSIGNED210 = 210;
const uint8_t UNASSIGNED211 = 211;
const uint8_t UNASSIGNED212 = 212;
const uint8_t UNASSIGNED213 = 213;
const uint8_t UNASSIGNED214 = 214;
const uint8_t UNASSIGNED215 = 215;
const uint8_t UNASSIGNED216 = 216;
const uint8_t UNASSIGNED217 = 217;
const uint8_t UNASSIGNED218 = 218;
const uint8_t UNASSIGNED219 = 219;
const uint8_t UNASSIGNED220 = 220;
const uint8_t UNASSIGNED221 = 221;
const uint8_t UNASSIGNED222 = 222;
const uint8_t UNASSIGNED223 = 223;
const uint8_t UNASSIGNED224 = 224;
const uint8_t UNASSIGNED225 = 225;
const uint8_t UNASSIGNED226 = 226;
const uint8_t UNASSIGNED227 = 227;
const uint8_t UNASSIGNED228 = 228;
const uint8_t UNASSIGNED229 = 229;
const uint8_t UNASSIGNED230 = 230;
const uint8_t UNASSIGNED231 = 231;
const uint8_t UNASSIGNED232 = 232;
const uint8_t UNASSIGNED233 = 233;
const uint8_t UNASSIGNED234 = 234;
const uint8_t UNASSIGNED235 = 235;
const uint8_t UNASSIGNED236 = 236;
const uint8_t UNASSIGNED237 = 237;
const uint8_t UNASSIGNED238 = 238;
const uint8_t UNASSIGNED239 = 239;
const uint8_t UNASSIGNED240 = 240;
const uint8_t UNASSIGNED241 = 241;
const uint8_t UNASSIGNED242 = 242;
const uint8_t UNASSIGNED243 = 243;
const uint8_t UNASSIGNED244 = 244;
const uint8_t UNASSIGNED245 = 245;
const uint8_t UNASSIGNED246 = 246;
const uint8_t UNASSIGNED247 = 247;
const uint8_t UNASSIGNED248 = 248;
const uint8_t UNASSIGNED249 = 249;
const uint8_t UNASSIGNED250 = 250;
const uint8_t UNASSIGNED251 = 251;
const uint8_t UNASSIGNED252 = 252;
const uint8_t RFC_3692_EXPERIMENT_1 = 253;
const uint8_t RFC_3692_EXPERIEMNT_2 = 254;

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

		virtual bool isSingleOctet( ) { return isSingleOctet_; }
		virtual uint8_t kind() { return kind_; }
		virtual uint8_t length() { return length_; }
		virtual std::vector< uint8_t > data() { return data_; }

		virtual std::vector< uint8_t > packetData(); // packs up the bits as they appear on the network


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
};

#endif
