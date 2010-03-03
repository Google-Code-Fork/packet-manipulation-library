#ifndef FINGERPRINT_H
#define FINGERPRINT_H
#include <string>
#include "signatures.h"
#include <vector>
#include "../Packet/packet.h"



class PacketFingerprint
{
	public:
		static const uint16_t NoSignature = 0x0;
		static const uint16_t SynSignatures = 0x1;
		static const uint16_t SynAckSignatures = 0x2;
		static const uint16_t RstSignatures = 0x4;
		static const uint16_t OpenSignatures = 0x8;

	public:
		PacketFingerprint( uint16_t useSignature = (SynSignatures | SynAckSignatures |
					RstSignatures | OpenSignatures) );
		PacketFingerprint( const PacketFingerprint &n );
		~PacketFingerprint();

		void usePacket( Packet p );
		//void useHttp( Http http );

	private:
		//! Initialize all the databases
		void init( uint16_t useSignature );
		void initSyn();
		void initSynAck();
		void initRst();
		void initOpen();
		static inline uint8_t sighash( uint8_t tsize, uint8_t optcnt, uint8_t df, uint32_t quirks )
		{
			return static_cast<uint8_t>( ((tsize << 1) ^ (optcnt << 1) ^ (df) ^ (quirks) ) & 0x0F );
		}

	private: //member variables
		static std::vector< Signature* > synHashLookup_;
		static std::vector< Signature > synSignatures_;
		static std::vector< Signature* > synAckHashLookup_;
		static std::vector< Signature > synAckSignatures_;
		static std::vector< Signature* > rstHashLookup_;
		static std::vector< Signature > rstSignatures_;
		static std::vector< Signature* > openHashLookup_;
		static std::vector< Signature > openSignatures_;
		static bool hasBeenInit_;


	private: //constant data
		static const int SIGHASH_SIZE;
		static const std::string SYN_DB;
		//! Syn-Ack signatures
		static const std::string SYNACK_DB;
		//! RST and RST-ACK signatures
		static const std::string RST_DB;
		//! Open DB (not very relaible)
		static const std::string OPEN_DB;

		//! Number of signatures allowed in the config file
		static const int MAXSIGS;
		//! Max signature line length
		static const int MAXLINE;
		/*! Maximum distance from a host to be taken seriously. Between 35 and 64
		     is sane. Making it too high might result in some (very rare) false
		     positives, too low will result in needless UNKNOWNs. */
		static const int MAXDIST;

		/*! Maximum number of TCP packet options. Some systems really like to
		 *    put lots of NOPs there. */
		static const int MAXOPT;

		/*! Max. reasonable DNS name length */
		static const int MY_MAXDNS;

		/*! Query cache for -S option. This is only the default. Keep it sane -
		 *    increase this if your system gets lots of traffic and you get
		 *    RESP_NOMATCH 
		 *       too often. */
		static const int DEFAULT_QUERY_CACHE;

		/*! Maximum timestamp difference (hours) between two masquerade  
		 *    signatures to be considered sane; should be reasonably high, as some
		 *       systems might be running at higher timestamp change frequencies
		 *          than usual. */
		static const int MAX_TIMEDIF;

		/* Packet dump - bytes per line; this is a sane setting. */
		static const int PKT_DLEN;

		/* Display no more than PKT_MAXPAY bytes of payload in -X mode. */
		static const int PKT_MAXPAY;

		/* Size limit for size wildcards - see p0fr.fp for more information. */
		static const int PACKET_BIG;

		/* Packet snap length. This is passed to libpcap, and should be never
		 *    below 100 or such. Keep it reasonably low for performance reasons. */
		static const int PACKET_SNAPLEN;

		/* Query timeout on -Q socket. You must send data QUERY_TIMEOUT seconds
		 *    after establishing a connection. Set this to zero to disable timeouts
		 *       (not really recommended). */
		static const int QUERY_TIMEOUT;


};

#endif
