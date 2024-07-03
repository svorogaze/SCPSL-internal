#include <cstdint>
#include "../resolver/IL2CPP_Resolver.hpp"
#include "../xorstr/xorstr.hpp"
#include "helper.hpp"
#include "gui.hpp"
#include <vector>
#include <chrono>
#include <ctime>
#include <map>
#include <vector>
#include <unordered_set>
#include <iostream>
namespace Misc {
	using inrangefunc = bool(__fastcall*)(int64_t*, Unity::Vector3*);
	bool inrange(int64_t* thisp, Unity::Vector3* position) {
		return false;
	}
	struct VoiceMessage {
		void* ReferenceHub;
		int channel;
		int datalength;
		void* data;
		bool speakernull;
	};

	using processmesagefunc = int64_t(__fastcall*)(int64_t*, VoiceMessage*);
	std::vector<void*> hookedfuncs;
	int64_t processmessagehk(int64_t* thisp, VoiceMessage* vptr) {
		vptr->channel = 5;
		return ((processmesagefunc)hookedfuncs[0])(thisp, vptr);
	}
	using clientrecievefunc = void(__fastcall*)(VoiceMessage*, int64_t, int64_t, int64_t);
	void clientreceivehk(VoiceMessage* vptr, int64_t a, int64_t b, int64_t c) {
		vptr->channel = 5;
		((clientrecievefunc)hookedfuncs[1])(vptr, a, b, c);
	}
	using getflagsfunc = int64_t(__fastcall*)(void*);
	int64_t getflagsforuserhk(void* refhub) {
		return 15;
	}
	/*
	Unity::CObject* voicemodulebase(Unity::CObject* pthis) {
		pthis->SetPropertyValue("")
	}
	*/
	using getkeydownfunc = int64_t(__fastcall*)(unsigned int);
	getkeydownfunc ispressed;
	using serverprocessfall = void(__fastcall*)(Unity::CObject*);
	void serverprocessfallhk(Unity::CObject* thisp) {
		thisp->SetPropertyValue<float>("Speed", 0.f);
		thisp->SetPropertyValue("Velocity", Unity::Vector3(0.f, 0.f, 0.f));
		((serverprocessfall)hookedfuncs[2])(thisp);
	}

};