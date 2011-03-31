#include "tcpOptions.h"

const uint8_t TCPOption::END_OF_LIST = 0;
const uint8_t TCPOption::NO_OPERATION = 1;
const uint8_t TCPOption::MAXIMUM_SEGMENT_SIZE = 2;
const uint8_t TCPOption::WINDOW_SCALE = 3;
const uint8_t TCPOption::SACK_PERMITTED = 4;
const uint8_t TCPOption::SACK = 5;
const uint8_t TCPOption::ECHO = 6;
const uint8_t TCPOption::ECHO_REPLY = 7;
const uint8_t TCPOption::TIME_STAMP_OPTION = 8;
const uint8_t TCPOption::PARTIAL_ORDER_CONNECTION_PREMITTED = 9;
const uint8_t TCPOption::PARTIAL_ORDER_SERVICE_PROFILE = 10;
const uint8_t TCPOption::CC = 11;
const uint8_t TCPOption::CC_NEW = 12;
const uint8_t TCPOption::CC_ECHO = 13;
const uint8_t TCPOption::TCP_ALTERNATE_CHECKSUM_REQUEST = 14;
const uint8_t TCPOption::TCP_ALTERNATE_CHECKSUM_DATA = 15;
const uint8_t TCPOption::SKEETER = 16;
const uint8_t TCPOption::BUBBA = 17;
const uint8_t TCPOption::TRAILER_CHECKSUM_OPTION = 18;
const uint8_t TCPOption::MD5_SIGNATURE_OPTION = 19;
const uint8_t TCPOption::SCPS_CAPABILITIES = 20;
const uint8_t TCPOption::SELECTIVE_NEGATIVE_ACKNOWLEDGEMENTS = 21;
const uint8_t TCPOption::RECORD_BOUNDARIES = 22;
const uint8_t TCPOption::CORRUPTION_EXPERIENCED = 23;
const uint8_t TCPOption::SNAP = 24;
const uint8_t TCPOption::UNASSIGNED25 = 25;
const uint8_t TCPOption::TCP_COMPRESSION_FILTER = 26;
const uint8_t TCPOption::QUICK_START_OPTION = 27;
const uint8_t TCPOption::USER_TIMEOUT_OPTION = 28;
const uint8_t TCPOption::UNASSIGNED29 = 29;
const uint8_t TCPOption::UNASSIGNED30 = 30;
const uint8_t TCPOption::UNASSIGNED31 = 31;
const uint8_t TCPOption::UNASSIGNED32 = 32;
const uint8_t TCPOption::UNASSIGNED33 = 33;
const uint8_t TCPOption::UNASSIGNED34 = 34;
const uint8_t TCPOption::UNASSIGNED35 = 35;
const uint8_t TCPOption::UNASSIGNED36 = 36;
const uint8_t TCPOption::UNASSIGNED37 = 37;
const uint8_t TCPOption::UNASSIGNED38 = 38;
const uint8_t TCPOption::UNASSIGNED39 = 39;
const uint8_t TCPOption::UNASSIGNED40 = 40;
const uint8_t TCPOption::UNASSIGNED41 = 41;
const uint8_t TCPOption::UNASSIGNED42 = 42;
const uint8_t TCPOption::UNASSIGNED43 = 43;
const uint8_t TCPOption::UNASSIGNED44 = 44;
const uint8_t TCPOption::UNASSIGNED45 = 45;
const uint8_t TCPOption::UNASSIGNED46 = 46;
const uint8_t TCPOption::UNASSIGNED47 = 47;
const uint8_t TCPOption::UNASSIGNED48 = 48;
const uint8_t TCPOption::UNASSIGNED49 = 49;
const uint8_t TCPOption::UNASSIGNED50 = 50;
const uint8_t TCPOption::UNASSIGNED51 = 51;
const uint8_t TCPOption::UNASSIGNED52 = 52;
const uint8_t TCPOption::UNASSIGNED53 = 53;
const uint8_t TCPOption::UNASSIGNED54 = 54;
const uint8_t TCPOption::UNASSIGNED55 = 55;
const uint8_t TCPOption::UNASSIGNED56 = 56;
const uint8_t TCPOption::UNASSIGNED57 = 57;
const uint8_t TCPOption::UNASSIGNED58 = 58;
const uint8_t TCPOption::UNASSIGNED59 = 59;
const uint8_t TCPOption::UNASSIGNED60 = 60;
const uint8_t TCPOption::UNASSIGNED61 = 61;
const uint8_t TCPOption::UNASSIGNED62 = 62;
const uint8_t TCPOption::UNASSIGNED63 = 63;
const uint8_t TCPOption::UNASSIGNED64 = 64;
const uint8_t TCPOption::UNASSIGNED65 = 65;
const uint8_t TCPOption::UNASSIGNED66 = 66;
const uint8_t TCPOption::UNASSIGNED67 = 67;
const uint8_t TCPOption::UNASSIGNED68 = 68;
const uint8_t TCPOption::UNASSIGNED69 = 69;
const uint8_t TCPOption::UNASSIGNED70 = 70;
const uint8_t TCPOption::UNASSIGNED71 = 71;
const uint8_t TCPOption::UNASSIGNED72 = 72;
const uint8_t TCPOption::UNASSIGNED73 = 73;
const uint8_t TCPOption::UNASSIGNED74 = 74;
const uint8_t TCPOption::UNASSIGNED75 = 75;
const uint8_t TCPOption::UNASSIGNED76 = 76;
const uint8_t TCPOption::UNASSIGNED77 = 77;
const uint8_t TCPOption::UNASSIGNED78 = 78;
const uint8_t TCPOption::UNASSIGNED79 = 79;
const uint8_t TCPOption::UNASSIGNED80 = 80;
const uint8_t TCPOption::UNASSIGNED81 = 81;
const uint8_t TCPOption::UNASSIGNED82 = 82;
const uint8_t TCPOption::UNASSIGNED83 = 83;
const uint8_t TCPOption::UNASSIGNED84 = 84;
const uint8_t TCPOption::UNASSIGNED85 = 85;
const uint8_t TCPOption::UNASSIGNED86 = 86;
const uint8_t TCPOption::UNASSIGNED87 = 87;
const uint8_t TCPOption::UNASSIGNED88 = 88;
const uint8_t TCPOption::UNASSIGNED89 = 89;
const uint8_t TCPOption::UNASSIGNED90 = 90;
const uint8_t TCPOption::UNASSIGNED91 = 91;
const uint8_t TCPOption::UNASSIGNED92 = 92;
const uint8_t TCPOption::UNASSIGNED93 = 93;
const uint8_t TCPOption::UNASSIGNED94 = 94;
const uint8_t TCPOption::UNASSIGNED95 = 95;
const uint8_t TCPOption::UNASSIGNED96 = 96;
const uint8_t TCPOption::UNASSIGNED97 = 97;
const uint8_t TCPOption::UNASSIGNED98 = 98;
const uint8_t TCPOption::UNASSIGNED99 = 99;
const uint8_t TCPOption::UNASSIGNED100 = 100;
const uint8_t TCPOption::UNASSIGNED101 = 101;
const uint8_t TCPOption::UNASSIGNED102 = 102;
const uint8_t TCPOption::UNASSIGNED103 = 103;
const uint8_t TCPOption::UNASSIGNED104 = 104;
const uint8_t TCPOption::UNASSIGNED105 = 105;
const uint8_t TCPOption::UNASSIGNED106 = 106;
const uint8_t TCPOption::UNASSIGNED107 = 107;
const uint8_t TCPOption::UNASSIGNED108 = 108;
const uint8_t TCPOption::UNASSIGNED109 = 109;
const uint8_t TCPOption::UNASSIGNED110 = 110;
const uint8_t TCPOption::UNASSIGNED111 = 111;
const uint8_t TCPOption::UNASSIGNED112 = 112;
const uint8_t TCPOption::UNASSIGNED113 = 113;
const uint8_t TCPOption::UNASSIGNED114 = 114;
const uint8_t TCPOption::UNASSIGNED115 = 115;
const uint8_t TCPOption::UNASSIGNED116 = 116;
const uint8_t TCPOption::UNASSIGNED117 = 117;
const uint8_t TCPOption::UNASSIGNED118 = 118;
const uint8_t TCPOption::UNASSIGNED119 = 119;
const uint8_t TCPOption::UNASSIGNED120 = 120;
const uint8_t TCPOption::UNASSIGNED121 = 121;
const uint8_t TCPOption::UNASSIGNED122 = 122;
const uint8_t TCPOption::UNASSIGNED123 = 123;
const uint8_t TCPOption::UNASSIGNED124 = 124;
const uint8_t TCPOption::UNASSIGNED125 = 125;
const uint8_t TCPOption::UNASSIGNED126 = 126;
const uint8_t TCPOption::UNASSIGNED127 = 127;
const uint8_t TCPOption::UNASSIGNED128 = 128;
const uint8_t TCPOption::UNASSIGNED129 = 129;
const uint8_t TCPOption::UNASSIGNED130 = 130;
const uint8_t TCPOption::UNASSIGNED131 = 131;
const uint8_t TCPOption::UNASSIGNED132 = 132;
const uint8_t TCPOption::UNASSIGNED133 = 133;
const uint8_t TCPOption::UNASSIGNED134 = 134;
const uint8_t TCPOption::UNASSIGNED135 = 135;
const uint8_t TCPOption::UNASSIGNED136 = 136;
const uint8_t TCPOption::UNASSIGNED137 = 137;
const uint8_t TCPOption::UNASSIGNED138 = 138;
const uint8_t TCPOption::UNASSIGNED139 = 139;
const uint8_t TCPOption::UNASSIGNED140 = 140;
const uint8_t TCPOption::UNASSIGNED141 = 141;
const uint8_t TCPOption::UNASSIGNED142 = 142;
const uint8_t TCPOption::UNASSIGNED143 = 143;
const uint8_t TCPOption::UNASSIGNED144 = 144;
const uint8_t TCPOption::UNASSIGNED145 = 145;
const uint8_t TCPOption::UNASSIGNED146 = 146;
const uint8_t TCPOption::UNASSIGNED147 = 147;
const uint8_t TCPOption::UNASSIGNED148 = 148;
const uint8_t TCPOption::UNASSIGNED149 = 149;
const uint8_t TCPOption::UNASSIGNED150 = 150;
const uint8_t TCPOption::UNASSIGNED151 = 151;
const uint8_t TCPOption::UNASSIGNED152 = 152;
const uint8_t TCPOption::UNASSIGNED153 = 153;
const uint8_t TCPOption::UNASSIGNED154 = 154;
const uint8_t TCPOption::UNASSIGNED155 = 155;
const uint8_t TCPOption::UNASSIGNED156 = 156;
const uint8_t TCPOption::UNASSIGNED157 = 157;
const uint8_t TCPOption::UNASSIGNED158 = 158;
const uint8_t TCPOption::UNASSIGNED159 = 159;
const uint8_t TCPOption::UNASSIGNED160 = 160;
const uint8_t TCPOption::UNASSIGNED161 = 161;
const uint8_t TCPOption::UNASSIGNED162 = 162;
const uint8_t TCPOption::UNASSIGNED163 = 163;
const uint8_t TCPOption::UNASSIGNED164 = 164;
const uint8_t TCPOption::UNASSIGNED165 = 165;
const uint8_t TCPOption::UNASSIGNED166 = 166;
const uint8_t TCPOption::UNASSIGNED167 = 167;
const uint8_t TCPOption::UNASSIGNED168 = 168;
const uint8_t TCPOption::UNASSIGNED169 = 169;
const uint8_t TCPOption::UNASSIGNED170 = 170;
const uint8_t TCPOption::UNASSIGNED171 = 171;
const uint8_t TCPOption::UNASSIGNED172 = 172;
const uint8_t TCPOption::UNASSIGNED173 = 173;
const uint8_t TCPOption::UNASSIGNED174 = 174;
const uint8_t TCPOption::UNASSIGNED175 = 175;
const uint8_t TCPOption::UNASSIGNED176 = 176;
const uint8_t TCPOption::UNASSIGNED177 = 177;
const uint8_t TCPOption::UNASSIGNED178 = 178;
const uint8_t TCPOption::UNASSIGNED179 = 179;
const uint8_t TCPOption::UNASSIGNED180 = 180;
const uint8_t TCPOption::UNASSIGNED181 = 181;
const uint8_t TCPOption::UNASSIGNED182 = 182;
const uint8_t TCPOption::UNASSIGNED183 = 183;
const uint8_t TCPOption::UNASSIGNED184 = 184;
const uint8_t TCPOption::UNASSIGNED185 = 185;
const uint8_t TCPOption::UNASSIGNED186 = 186;
const uint8_t TCPOption::UNASSIGNED187 = 187;
const uint8_t TCPOption::UNASSIGNED188 = 188;
const uint8_t TCPOption::UNASSIGNED189 = 189;
const uint8_t TCPOption::UNASSIGNED190 = 190;
const uint8_t TCPOption::UNASSIGNED191 = 191;
const uint8_t TCPOption::UNASSIGNED192 = 192;
const uint8_t TCPOption::UNASSIGNED193 = 193;
const uint8_t TCPOption::UNASSIGNED194 = 194;
const uint8_t TCPOption::UNASSIGNED195 = 195;
const uint8_t TCPOption::UNASSIGNED196 = 196;
const uint8_t TCPOption::UNASSIGNED197 = 197;
const uint8_t TCPOption::UNASSIGNED198 = 198;
const uint8_t TCPOption::UNASSIGNED199 = 199;
const uint8_t TCPOption::UNASSIGNED200 = 200;
const uint8_t TCPOption::UNASSIGNED201 = 201;
const uint8_t TCPOption::UNASSIGNED202 = 202;
const uint8_t TCPOption::UNASSIGNED203 = 203;
const uint8_t TCPOption::UNASSIGNED204 = 204;
const uint8_t TCPOption::UNASSIGNED205 = 205;
const uint8_t TCPOption::UNASSIGNED206 = 206;
const uint8_t TCPOption::UNASSIGNED207 = 207;
const uint8_t TCPOption::UNASSIGNED208 = 208;
const uint8_t TCPOption::UNASSIGNED209 = 209;
const uint8_t TCPOption::UNASSIGNED210 = 210;
const uint8_t TCPOption::UNASSIGNED211 = 211;
const uint8_t TCPOption::UNASSIGNED212 = 212;
const uint8_t TCPOption::UNASSIGNED213 = 213;
const uint8_t TCPOption::UNASSIGNED214 = 214;
const uint8_t TCPOption::UNASSIGNED215 = 215;
const uint8_t TCPOption::UNASSIGNED216 = 216;
const uint8_t TCPOption::UNASSIGNED217 = 217;
const uint8_t TCPOption::UNASSIGNED218 = 218;
const uint8_t TCPOption::UNASSIGNED219 = 219;
const uint8_t TCPOption::UNASSIGNED220 = 220;
const uint8_t TCPOption::UNASSIGNED221 = 221;
const uint8_t TCPOption::UNASSIGNED222 = 222;
const uint8_t TCPOption::UNASSIGNED223 = 223;
const uint8_t TCPOption::UNASSIGNED224 = 224;
const uint8_t TCPOption::UNASSIGNED225 = 225;
const uint8_t TCPOption::UNASSIGNED226 = 226;
const uint8_t TCPOption::UNASSIGNED227 = 227;
const uint8_t TCPOption::UNASSIGNED228 = 228;
const uint8_t TCPOption::UNASSIGNED229 = 229;
const uint8_t TCPOption::UNASSIGNED230 = 230;
const uint8_t TCPOption::UNASSIGNED231 = 231;
const uint8_t TCPOption::UNASSIGNED232 = 232;
const uint8_t TCPOption::UNASSIGNED233 = 233;
const uint8_t TCPOption::UNASSIGNED234 = 234;
const uint8_t TCPOption::UNASSIGNED235 = 235;
const uint8_t TCPOption::UNASSIGNED236 = 236;
const uint8_t TCPOption::UNASSIGNED237 = 237;
const uint8_t TCPOption::UNASSIGNED238 = 238;
const uint8_t TCPOption::UNASSIGNED239 = 239;
const uint8_t TCPOption::UNASSIGNED240 = 240;
const uint8_t TCPOption::UNASSIGNED241 = 241;
const uint8_t TCPOption::UNASSIGNED242 = 242;
const uint8_t TCPOption::UNASSIGNED243 = 243;
const uint8_t TCPOption::UNASSIGNED244 = 244;
const uint8_t TCPOption::UNASSIGNED245 = 245;
const uint8_t TCPOption::UNASSIGNED246 = 246;
const uint8_t TCPOption::UNASSIGNED247 = 247;
const uint8_t TCPOption::UNASSIGNED248 = 248;
const uint8_t TCPOption::UNASSIGNED249 = 249;
const uint8_t TCPOption::UNASSIGNED250 = 250;
const uint8_t TCPOption::UNASSIGNED251 = 251;
const uint8_t TCPOption::UNASSIGNED252 = 252;
const uint8_t TCPOption::RFC_3692_EXPERIMENT_1 = 253;
const uint8_t TCPOption::RFC_3692_EXPERIEMNT_2 = 254;


TCPOption::TCPOption( ): kind_(0), length_(0), isSingleOctet_(false) 
{
}

TCPOption::TCPOption( const TCPOption &o )
{
	kind_ = o.kind_;
	length_ = o.length_;
	data_ = o.data_;
	isSingleOctet_ = o.isSingleOctet_;
}

TCPOption::~TCPOption()
{
}

void TCPOption::setKind( const uint8_t &kind )
{
	kind_ = kind;
}

void TCPOption::setLength( const uint8_t &length )
{
	length_ = length;
}

void TCPOption::setData( const std::vector< uint8_t > &data ) 
{
	data_ = data;
}

void TCPOption::singleOctet( const bool &isit )
{
	isSingleOctet_ = isit;
}

std::vector< uint8_t > TCPOption::packetData() const
{
	std::vector< uint8_t > data;
	data.push_back( kind_ );
	if( !isSingleOctet_ )
	{
		data.push_back( length_ );
		std::vector< uint8_t >::const_iterator itr;
		for( itr = data_.begin(); itr != data_.end(); ++itr )
		{
			data.push_back( *itr );
		}
	}
	return data;
}
