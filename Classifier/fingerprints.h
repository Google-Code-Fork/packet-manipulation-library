#ifndef FINGERPRINT_H
#define FINGERPRINT_H

#include <vector>
#include <string>

class FingerPrint
{
	public:
		FingerPrint( std::string fingerPrint );
		FingerPrint();
		FingerPrint( const FingerPrint &n );
		~FingerPrint();

		//get functions
	  std::string  os() { return os_; }
		std::string desc() { return desc_; }
		uint8_t noDetail() { return noDetail_; }
		uint8_t generic() { return generic_; }
		uint8_t userland() { return userland_; }
		uint16_t windowSize() { return windowSize_; }
		uint8_t windowSizeMod() { return windowSizeMod_; }
		uint8_t dontFragment() { return dontFragment_; }
		uint8_t ttl() { return ttl_; }
		uint8_t zeroStamp() { return zeroStamp_; }
		uint16_t size() { return size_; }
		uint8_t optCount() { return tcpOptions_.size(); }
		std::vector<uint8_t> tcpOptions() { return tcpOptions_; }
		uint16_t wsc() { return wsc_; }
		uint16_t mss() { return mss_; }
		uint8_t wscMod() { return wscMod_; }
		uint8_t mssMod() { return mssMod_; }
		uint32_t quirks() { return quirks_; }
		uint32_t configFileLine() { return configFileLine_; }
		FingerPrint* next() { return next_; }

		bool hasNext() { next_ != NULL ? return true : return false; }

		//set functions
		void setFromFingerPrint( const std::string &fingerPrint );
		void setOS( std::string os ) { os_ = os; };
		void setDesc( std::string desc ) { desc_ = desc; }
		void setNoDetail( uint8_t noDetail ) { noDetail_ = noDetail; }
		void setGeneric( uint8_t generic ) { generic_ = generic; }
		void setUserland( uint8_t userland ) { userland_ = userland; }
		void setWindowSize( uint16_t windowSize ) { windowSize_ = windowSize; }
		void setWindowSizeMod( uint8_t windowSizeMod ) { windowSizeMod_ = windowSizeMod; }
		void setDontFragment( uint8_t dontFragment ) { dontFragment_ = dontFragment; } 
		void setTtl( uint8_t ttl ) { ttl_ = ttl; }
		void setZeroStamp( uint8_t zeroStamp ) { zeroStamp_ = zeroStamp; }
		void setSize( uint16_t size ) { size_ = size; }
		void setTcpOptions( std::vector< uint8_t > tcpOptions ) { tcpOptions_ = tcpOptions; }
		void setWsc( uint16_t wsc ) { wsc_ = wsc; }
		void setMss( uint16_t mss ) { mss_ = mss; }
		void setWscMod( uint8_t wscMod ) { wscMod_ = wscMod; }
		void setMssMod( uint8_t mssMod ) { mssMod_ = mssMod; }
		void setQuirks( uint32_t quirks ) { quirks_ = quirks; }
		void addQuirk( uint32_t quirk ) { quirks_ |= quirk; }
		void setConfigFileLine( uint32_t line ) { configFileLine_ = line; }
		void setNext( FingerPrint* next ) { next_ = next; }
		

	private:
		std::string os_;
		std::string desc_;
		uint8_t noDetail_;
		uint8_t generic_;
		uint8_t userland_;
		uint16_t windowSize_;
		uint8_t windowSizeMod_;
		uint8_t dontFragment_;
		uint8_t ttl_;
		uint8_t zeroStamp_;
		uint16_t size_;
		uint8_t optCount_;
		std::vector<uint8_t> tcpOptions_; 
		uint16_t wsc_;
		uint16_t mss_;
		uint8_t wscMod_;
		uint8_t mssMod_;
		uint32_t quirks_;
		uint32_t configFileLine_;
		FingerPrint* next_;

		static const uint32_t QUIRK_PAST; //P
		static const uint32_t QUIRK_ZEROID; //Z
		static const uint32_t QUIRK_IPOPT; //I
		static const uint32_t QUIRK_URG; //U
		static const uint32_t QUIRK_X2; //X
		static const uint32_t QUIRK_ACK; //A
		static const uint32_t QUIRK_T2; //T
		static const uint32_t QUIRK_FLAGS; //F
		static const uint32_t QUIRK_DATA; //D
		static const uint32_t QUIRK_BROKEN; //!
		static const uint32_t QUIRK_RSTACK; //K
		static const uint32_t QUIRK_SEQEQ; //Q
		static const uint32_t QUIRK_SEQ0; //0

		//Private Functions
		void setWindowFingerPrint( std::string fp );
		void setTTLFingerPrint( std::string fp );
		void setDontFragmentFingerPrint( std::string fp );
		void setSynSizeFingerPrint( std::string fp );
		void setOptionsFingerPrint( std::string fp );
		void setQuirksFingerPrint( std::string fp );
		void setOSGenreFingerPrint( std::string fp );
		void setDetailsFingerPrint( std::string fp );
}