#pragma once
#include "../resolver/IL2CPP_Resolver.hpp"
#include "globals.hpp"

namespace GUI {
	using labelfunc = __int64(__fastcall*)(Unity::Rect, Unity::System_String&);
	using set_colorfunc = __int64(__fastcall*)(Unity::Color);

	void changecolor(Unity::Color col) {
		static void* m_pMethod = IL2CPP::Class::Utils::GetMethodPointer(xorstr_("UnityEngine.GUI"), xorstr_("set_color"));
		reinterpret_cast<set_colorfunc>(m_pMethod)(col);
	}


	void drawlabel(Unity::Rect r, Unity::System_String& us) {
		static labelfunc label = (labelfunc)(IL2CPP::Class::Utils::GetMethodPointer(xorstr_("UnityEngine.GUI"), xorstr_("Label")));
		label(r, us);
	}
	
};