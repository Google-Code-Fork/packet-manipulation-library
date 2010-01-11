

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
     11          CC                                  [RFC1644]
     12          CC.NEW                              [RFC1644]
     13          CC.ECHO                             [RFC1644]
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

const int END_OF_LIST = 0;
const int NO-OPERATION = 1;
const int MAXIMUM_SEGMENT_SIZE = 2;
const int WINDOW_SCALE = 3;
const int SACK_PERMITTED = 4;
const int SACK = 5;
const int ECHO = 6;
const int ECHO_REPLY = 7;
const int TIME_STAMP_OPTION = 8;
const int PARTIAL_ORDER_CONNECTION_PREMITTED = 9;
const int PARTIAL_ORDER_SERVICE_PROFILE = 10;
const int CC = 11;
const int CC_NEW = 12;
const int CC_ECHO = 13;
const int TCP_ALTERNATE_CHECKSUM_REQUEST = 14;
const int TCP_ALTERNATE_CHECKSUM_DATA = 15;
const int SKEETER = 16;
const int BUBBA = 17;
const int TRAILER CHECKSUM OPTION = 18;
const int MD5_SIGNATURE_OPTION = 19;
const int SCPS_CAPABILITIES = 20;
const int SELECTIVE_NEGATIVE_ACKNOWLEDGEMENTS = 21;
const int RECORD_BOUNDARIES = 22;
const int CORRUPTION_EXPERIENCED = 23;
const int SNAP = 24;
const int UNASSIGNED25 = 25;
const int TCP_COMPRESSION_FILTER = 26;
const int QUICK_START_OPTION = 27;
const int USER_TIMEOUT_OPTION = 28;
const int UNASSIGNED29 = 29;
const int UNASSIGNED30 = 30;
const int UNASSIGNED31 = 31;
const int UNASSIGNED32 = 32;
const int UNASSIGNED33 = 33;
const int UNASSIGNED34 = 34;
const int UNASSIGNED35 = 35;
const int UNASSIGNED36 = 36;
const int UNASSIGNED37 = 37;
const int UNASSIGNED38 = 38;
const int UNASSIGNED39 = 39;
const int UNASSIGNED40 = 40;
const int UNASSIGNED41 = 41;
const int UNASSIGNED42 = 42;
const int UNASSIGNED43 = 43;
const int UNASSIGNED44 = 44;
const int UNASSIGNED45 = 45;
const int UNASSIGNED46 = 46;
const int UNASSIGNED47 = 47;
const int UNASSIGNED48 = 48;
const int UNASSIGNED49 = 49;
const int UNASSIGNED50 = 50;
const int UNASSIGNED51 = 51;
const int UNASSIGNED52 = 52;
const int UNASSIGNED53 = 53;
const int UNASSIGNED54 = 54;
const int UNASSIGNED55 = 55;
const int UNASSIGNED56 = 56;
const int UNASSIGNED57 = 57;
const int UNASSIGNED58 = 58;
const int UNASSIGNED59 = 59;
const int UNASSIGNED60 = 60;
const int UNASSIGNED61 = 61;
const int UNASSIGNED62 = 62;
const int UNASSIGNED63 = 63;
const int UNASSIGNED64 = 64;
const int UNASSIGNED65 = 65;
const int UNASSIGNED66 = 66;
const int UNASSIGNED67 = 67;
const int UNASSIGNED68 = 68;
const int UNASSIGNED69 = 69;
const int UNASSIGNED70 = 70;
const int UNASSIGNED71 = 71;
const int UNASSIGNED72 = 72;
const int UNASSIGNED73 = 73;
const int UNASSIGNED74 = 74;
const int UNASSIGNED75 = 75;
const int UNASSIGNED76 = 76;
const int UNASSIGNED77 = 77;
const int UNASSIGNED78 = 78;
const int UNASSIGNED79 = 79;
const int UNASSIGNED80 = 80;
const int UNASSIGNED81 = 81;
const int UNASSIGNED82 = 82;
const int UNASSIGNED83 = 83;
const int UNASSIGNED84 = 84;
const int UNASSIGNED85 = 85;
const int UNASSIGNED86 = 86;
const int UNASSIGNED87 = 87;
const int UNASSIGNED88 = 88;
const int UNASSIGNED89 = 89;
const int UNASSIGNED90 = 90;
const int UNASSIGNED91 = 91;
const int UNASSIGNED92 = 92;
const int UNASSIGNED93 = 93;
const int UNASSIGNED94 = 94;
const int UNASSIGNED95 = 95;
const int UNASSIGNED96 = 96;
const int UNASSIGNED97 = 97;
const int UNASSIGNED98 = 98;
const int UNASSIGNED99 = 99;
const int UNASSIGNED100 = 100;
const int UNASSIGNED101 = 101;
const int UNASSIGNED102 = 102;
const int UNASSIGNED103 = 103;
const int UNASSIGNED104 = 104;
const int UNASSIGNED105 = 105;
const int UNASSIGNED106 = 106;
const int UNASSIGNED107 = 107;
const int UNASSIGNED108 = 108;
const int UNASSIGNED109 = 109;
const int UNASSIGNED110 = 110;
const int UNASSIGNED111 = 111;
const int UNASSIGNED112 = 112;
const int UNASSIGNED113 = 113;
const int UNASSIGNED114 = 114;
const int UNASSIGNED115 = 115;
const int UNASSIGNED116 = 116;
const int UNASSIGNED117 = 117;
const int UNASSIGNED118 = 118;
const int UNASSIGNED119 = 119;
const int UNASSIGNED120 = 120;
const int UNASSIGNED121 = 121;
const int UNASSIGNED122 = 122;
const int UNASSIGNED123 = 123;
const int UNASSIGNED124 = 124;
const int UNASSIGNED125 = 125;
const int UNASSIGNED126 = 126;
const int UNASSIGNED127 = 127;
const int UNASSIGNED128 = 128;
const int UNASSIGNED129 = 129;
const int UNASSIGNED130 = 130;
const int UNASSIGNED131 = 131;
const int UNASSIGNED132 = 132;
const int UNASSIGNED133 = 133;
const int UNASSIGNED134 = 134;
const int UNASSIGNED135 = 135;
const int UNASSIGNED136 = 136;
const int UNASSIGNED137 = 137;
const int UNASSIGNED138 = 138;
const int UNASSIGNED139 = 139;
const int UNASSIGNED140 = 140;
const int UNASSIGNED141 = 141;
const int UNASSIGNED142 = 142;
const int UNASSIGNED143 = 143;
const int UNASSIGNED144 = 144;
const int UNASSIGNED145 = 145;
const int UNASSIGNED146 = 146;
const int UNASSIGNED147 = 147;
const int UNASSIGNED148 = 148;
const int UNASSIGNED149 = 149;
const int UNASSIGNED150 = 150;
const int UNASSIGNED151 = 151;
const int UNASSIGNED152 = 152;
const int UNASSIGNED153 = 153;
const int UNASSIGNED154 = 154;
const int UNASSIGNED155 = 155;
const int UNASSIGNED156 = 156;
const int UNASSIGNED157 = 157;
const int UNASSIGNED158 = 158;
const int UNASSIGNED159 = 159;
const int UNASSIGNED160 = 160;
const int UNASSIGNED161 = 161;
const int UNASSIGNED162 = 162;
const int UNASSIGNED163 = 163;
const int UNASSIGNED164 = 164;
const int UNASSIGNED165 = 165;
const int UNASSIGNED166 = 166;
const int UNASSIGNED167 = 167;
const int UNASSIGNED168 = 168;
const int UNASSIGNED169 = 169;
const int UNASSIGNED170 = 170;
const int UNASSIGNED171 = 171;
const int UNASSIGNED172 = 172;
const int UNASSIGNED173 = 173;
const int UNASSIGNED174 = 174;
const int UNASSIGNED175 = 175;
const int UNASSIGNED176 = 176;
const int UNASSIGNED177 = 177;
const int UNASSIGNED178 = 178;
const int UNASSIGNED179 = 179;
const int UNASSIGNED180 = 180;
const int UNASSIGNED181 = 181;
const int UNASSIGNED182 = 182;
const int UNASSIGNED183 = 183;
const int UNASSIGNED184 = 184;
const int UNASSIGNED185 = 185;
const int UNASSIGNED186 = 186;
const int UNASSIGNED187 = 187;
const int UNASSIGNED188 = 188;
const int UNASSIGNED189 = 189;
const int UNASSIGNED190 = 190;
const int UNASSIGNED191 = 191;
const int UNASSIGNED192 = 192;
const int UNASSIGNED193 = 193;
const int UNASSIGNED194 = 194;
const int UNASSIGNED195 = 195;
const int UNASSIGNED196 = 196;
const int UNASSIGNED197 = 197;
const int UNASSIGNED198 = 198;
const int UNASSIGNED199 = 199;
const int UNASSIGNED200 = 200;
const int UNASSIGNED201 = 201;
const int UNASSIGNED202 = 202;
const int UNASSIGNED203 = 203;
const int UNASSIGNED204 = 204;
const int UNASSIGNED205 = 205;
const int UNASSIGNED206 = 206;
const int UNASSIGNED207 = 207;
const int UNASSIGNED208 = 208;
const int UNASSIGNED209 = 209;
const int UNASSIGNED210 = 210;
const int UNASSIGNED211 = 211;
const int UNASSIGNED212 = 212;
const int UNASSIGNED213 = 213;
const int UNASSIGNED214 = 214;
const int UNASSIGNED215 = 215;
const int UNASSIGNED216 = 216;
const int UNASSIGNED217 = 217;
const int UNASSIGNED218 = 218;
const int UNASSIGNED219 = 219;
const int UNASSIGNED220 = 220;
const int UNASSIGNED221 = 221;
const int UNASSIGNED222 = 222;
const int UNASSIGNED223 = 223;
const int UNASSIGNED224 = 224;
const int UNASSIGNED225 = 225;
const int UNASSIGNED226 = 226;
const int UNASSIGNED227 = 227;
const int UNASSIGNED228 = 228;
const int UNASSIGNED229 = 229;
const int UNASSIGNED230 = 230;
const int UNASSIGNED231 = 231;
const int UNASSIGNED232 = 232;
const int UNASSIGNED233 = 233;
const int UNASSIGNED234 = 234;
const int UNASSIGNED235 = 235;
const int UNASSIGNED236 = 236;
const int UNASSIGNED237 = 237;
const int UNASSIGNED238 = 238;
const int UNASSIGNED239 = 239;
const int UNASSIGNED240 = 240;
const int UNASSIGNED241 = 241;
const int UNASSIGNED242 = 242;
const int UNASSIGNED243 = 243;
const int UNASSIGNED244 = 244;
const int UNASSIGNED245 = 245;
const int UNASSIGNED246 = 246;
const int UNASSIGNED247 = 247;
const int UNASSIGNED248 = 248;
const int UNASSIGNED249 = 249;
const int UNASSIGNED250 = 250;
const int UNASSIGNED251 = 251;
const int UNASSIGNED252 = 252;
const int RFC_3692_EXPERIMENT_1 = 253;
const int RFC_3692_EXPERIEMNT_2 = 254;
