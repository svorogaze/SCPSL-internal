#include "visuals.hpp"
namespace aimbot {
	Unity::Vector3 curtarget(0, 0, 0);
	Unity::Quaternion quaternion;
	Unity::Quaternion quaternion2;
	bool canshoot = false;
	constexpr unsigned int playermask = (1 << 17) | (1 << 2) | (1 << 13);
	struct RelativePosition {
		short PositionX; // 0x0
		short PositionY; // 0x2
		short PositionZ; // 0x4
		BYTE WaypointId; // 0x6
		bool OutOfRange; // 0x7
	};

	struct ShotMessage {
		uint32_t TargetNetId;
		RelativePosition TargetPosition;
		Unity::Quaternion TargetRotation;
		unsigned short ShooterWeaponSerial;
		RelativePosition ShooterPosition;
		Unity::Quaternion ShooterCameraRotation;
	};

	int getdist(std::pair<int, int>& pr) {
		return (pr.first - 960) * (pr.first - 960) + (pr.second - 540) * (pr.second - 540);
	}
	using lookatfunc = void(__fastcall*)(Unity::CTransform*, Unity::Vector3*);
	using getkeydownfunc = int64_t(__fastcall*)(unsigned int);
	using lookrotationfunc = Unity::Quaternion*(__fastcall*)(Unity::Quaternion&, Unity::Vector3&);
	void gettarget() {
		static getkeydownfunc fu = (getkeydownfunc)((DWORD64)IL2CPP::Globals.m_GameAssembly + 0x2270BC0);
		if (!fu(326) && !fu(327)) return;
		auto ptr = Visuals::getmain();
		if (!ptr || !Visuals::gt) return;
		static bool(__fastcall * linecast)(Unity::Vector3, Unity::Vector3, uint32_t) = (bool(__fastcall*)(Unity::Vector3, Unity::Vector3, uint32_t))IL2CPP::Class::Utils::GetMethodPointer(xorstr_("UnityEngine.Physics"), xorstr_("Linecast"), 3);
		std::sort(Visuals::possibletargets.begin(), Visuals::possibletargets.end(), [](auto& a, auto& b) {
			return getdist(a.second) < getdist(b.second);
		});
		auto transform = Visuals::gt((Unity::CComponent*)ptr);
		Unity::Vector3 poss = transform->GetPosition();
		for (auto& [vec3, dist] : Visuals::possibletargets) {
			if (!linecast(poss, vec3, 1208238081u)) {
				canshoot = true;
				curtarget = vec3;
				curtarget.x -= poss.x, curtarget.y -= poss.y, curtarget.z -= poss.z;
				static lookrotationfunc lookrotate = (lookrotationfunc)((DWORD64)IL2CPP::Globals.m_GameAssembly + 0x220F790);
				quaternion = *lookrotate(quaternion, curtarget);
				break;
			}
		}
	}
	using clientcalc = bool(__fastcall*)(uint64_t*, ShotMessage*);
	clientcalc origfunc = nullptr;
	bool clientcalculatehithk(uint64_t* ths, ShotMessage* shot) {
		auto res = origfunc(ths, shot);
		if (canshoot) {
			shot->ShooterCameraRotation = quaternion;
			return true;
		}
		return res;
	}

	using randomizeray = int64_t(__fastcall*)(int64_t, int64_t*, int64_t);
	int64_t randomizerayhk(int64_t a, int64_t* b, int64_t c) {
		return a;
	}
	struct attachmentparameter {
		int parameter;
		float value;
	};
	using attachmentparametervaluepair = void(__fastcall*)(attachmentparameter*, int, float);
	void attachmentparameterhk(attachmentparameter* stru, int name, float x) {
		if (name == 17) {
			x = 0;
		}
		if (name == 9 || name == 7) {
			x = 0;
		}
		stru->parameter = name; 
		stru->value = x;
	}
};