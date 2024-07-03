#pragma once
#include "framework.h"
#include "cheat/globals.hpp"
#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>
#include <MinHook.h>
#include "resolver/IL2CPP_Resolver.hpp"
#include <cstdint>
#include "xorstr/xorstr.hpp"
#pragma comment(lib, "libMinHook.x64.lib")
#include "cheat/visuals.hpp"
#include "cheat/aimbot.hpp"
#include "cheat/misc.hpp"
using onguifunc =  void**(__fastcall*)(int64_t);

void memcpy_s(PVOID address, char* val, int bytes)
{
    DWORD d, ds;
    VirtualProtect(address, bytes, PAGE_EXECUTE_READWRITE, &d);
    memcpy(address, val, bytes);
    VirtualProtect(address, bytes, d, &ds);
}
using recoilconstructor = void(__fastcall*)(int64_t, float, float, float, int, int);
recoilconstructor trump;
void recoilconstructorhk(int64_t a, float b, float c, float d, int e, int f) {
    b = 0, c = 0, d = 0, e = 0, f = 0;
    trump(a, b, c, d, e, f);
}
void norecoil() {
    recoilconstructor ptr = (recoilconstructor)((DWORD64)IL2CPP::Globals.m_GameAssembly + 0x574520);
    auto res = MH_CreateHook(ptr, &recoilconstructorhk, (LPVOID*)(&trump));
    MH_EnableHook(ptr);
}

//make function of getinaccuracy always return 0
void noinaccuracy() {
    DWORD64 functionaddress = (DWORD64)IL2CPP::Globals.m_GameAssembly + Globals::FireArmBaseStatsGetInaccuracy;
    memcpy_s((PVOID)functionaddress, (char*)Globals::inaccuracyreplacement, 5);
    functionaddress = (DWORD64)IL2CPP::Globals.m_GameAssembly + Globals::FireArmRecoilPatterGetInaccuracy;
    memcpy_s((PVOID)functionaddress, (char*)Globals::inaccuracyreplacement, 5);
    functionaddress = (DWORD64)IL2CPP::Globals.m_GameAssembly + Globals::AutomaticActionFullautoInaccuracyget;
    memcpy_s((PVOID)functionaddress, (char*)Globals::inaccuracyreplacement, 5);
}

LPVOID ptr;


Unity::CGameObject* pointer = nullptr;

void ourmain() {
    static auto start = std::chrono::high_resolution_clock::now();
    auto cur = std::chrono::high_resolution_clock::now();
    static bool flag = true;
    static int64_t(*disablefogcontroller)() = (int64_t(*)())IL2CPP::Class::Utils::GetMethodPointer(xorstr_("CustomRendering.FogController"), xorstr_("OnDisable"));
    if (std::chrono::duration<double, std::milli>(cur - start).count() > 5000) {
        disablefogcontroller();
        start = cur;
        if (pointer) pointer->Destroy();
        pointer = Unity::GameObject::CreatePrimitive(Unity::GameObject::m_ePrimitiveType::Default);
        static Unity::il2cppClass* m_pSystemTypeClass = IL2CPP::Class::Find(xorstr_("Mirror.GUIConsole"));
        static Unity::il2cppObject* m_syst = IL2CPP::Class::GetSystemType(m_pSystemTypeClass);
        pointer->AddComponent(m_syst);
    }
}


BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    
    MH_STATUS res;
    onguifunc func;
    Visuals::visibilityfunc f2 = nullptr;
    Visuals::startfunc startfu;
    Visuals::rangefunc f3 = nullptr;
    Visuals::enablefogfunc f4 = nullptr;
    Visuals::hookedfuncs.resize(15);
    Misc::hookedfuncs.resize(20);
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        
        AllocConsole();
        freopen(xorstr_("CONOUT$"), "w", stdout);
        res = MH_Initialize();

        IL2CPP::Initialize();
        norecoil();
        noinaccuracy();
        //set up hooks
        {
            func = (onguifunc)((DWORD64)IL2CPP::Globals.m_GameAssembly + Globals::MirrorConsoleOnGUI);
            MH_CreateHook(func, &Visuals::visuals, &ptr);
            MH_EnableHook(func);

            Visuals::getmain = (Unity::CCamera * (__fastcall*)())IL2CPP::Class::Utils::GetMethodPointer(xorstr_("UnityEngine.Camera"), xorstr_("get_main"));
            Visuals::w2s = (Unity::Vector3(__fastcall*)(Unity::CCamera*, Unity::Vector3))IL2CPP::Class::Utils::GetMethodPointer(xorstr_("UnityEngine.Camera"), xorstr_("WorldToScreenPoint"));

            startfu = (Visuals::startfunc)IL2CPP::Class::Utils::GetMethodPointer(xorstr_("InventorySystem.Items.Keycards.KeycardPickup"), "Start");
            res = MH_CreateHook(startfu, &Visuals::keycardpickupstarthk, &Visuals::hookedfuncs[0]);
            MH_EnableHook(startfu);

            startfu = (Visuals::startfunc)IL2CPP::Class::Utils::GetMethodPointer(xorstr_("InventorySystem.Items.Pickups.ItemPickupBase"), "OnDestroy");
            res = MH_CreateHook(startfu, &Visuals::itempickupbaseondestroyhk, &Visuals::hookedfuncs[1]);
            res = MH_EnableHook(startfu);

            startfu = (Visuals::startfunc)IL2CPP::Class::Utils::GetMethodPointer(xorstr_("InventorySystem.Items.Pickups.ItemPickupBase"), "Start");
            res = MH_CreateHook(startfu, &Visuals::itempickupbasestarthk, &Visuals::hookedfuncs[2]);
            res = MH_EnableHook(startfu);

            startfu = (Visuals::startfunc)IL2CPP::Class::Utils::GetMethodPointer("InventorySystem.Items.Usables.Scp244.Scp244DeployablePickup", "OnDestroy");
            res = MH_CreateHook(startfu, &Visuals::scp244ondestroyhk, &Visuals::hookedfuncs[3]);
            res = MH_EnableHook(startfu);

            startfu = (Visuals::startfunc)IL2CPP::Class::Utils::GetMethodPointer("RoundSummary", "Start");
            res = MH_CreateHook(startfu, &Visuals::roundsummarystarthk, &Visuals::hookedfuncs[4]);
            res = MH_EnableHook(startfu);

            startfu = (Visuals::startfunc)IL2CPP::Class::Utils::GetMethodPointer("InventorySystem.Items.Pickups.ItemPickupBase", "DestroySelf");
            res = MH_CreateHook(startfu, &Visuals::itempickupbasedestroyselfhk, &Visuals::hookedfuncs[5]);
            res = MH_EnableHook(startfu);

            startfu = (Visuals::startfunc)IL2CPP::Class::Utils::GetMethodPointer("ReferenceHub", "Start");
            res = MH_CreateHook(startfu, &Visuals::referencehubstarthk, &Visuals::hookedfuncs[6]);
            res = MH_EnableHook(startfu);

            startfu = (Visuals::startfunc)IL2CPP::Class::Utils::GetMethodPointer("ReferenceHub", "OnDestroy");
            res = MH_CreateHook(startfu, &Visuals::referencehubdestroyhk, &Visuals::hookedfuncs[7]);
            res = MH_EnableHook(startfu);

            f3 = (Visuals::rangefunc)IL2CPP::Class::Utils::GetMethodPointer("PlayerRoles.FirstPersonControl.FpcVisibilityController", "get_NormalMaxRangeSqr");
            res = MH_CreateHook(f3, &Visuals::getrange, NULL);
            res = MH_EnableHook(f3);

            f3 = (Visuals::rangefunc)IL2CPP::Class::Utils::GetMethodPointer("PlayerRoles.FirstPersonControl.FpcVisibilityController", "get_SurfaceMaxRangeSqr");
            res = MH_CreateHook(f3, &Visuals::getrange, NULL);
            res = MH_EnableHook(f3);

            f2 = (Visuals::visibilityfunc)((DWORD64)IL2CPP::Globals.m_GameAssembly + 0x4F6150);
            res = MH_CreateHook(f2, &Visuals::visibilitycheck, NULL);
            res = MH_EnableHook(f2);

            f4 = (Visuals::enablefogfunc)IL2CPP::Class::Utils::GetMethodPointer("CustomRendering.FogController", "EnableFogType");
            res = MH_CreateHook(f4, &Visuals::enablefogtypehk, &Visuals::hookedfuncs[8]);
            res = MH_EnableHook(f4);

            Visuals::setforcedfog f5 = (Visuals::setforcedfog)IL2CPP::Class::Utils::GetMethodPointer("CustomRendering.FogController", "set_ForcedFog");
            res = MH_CreateHook(f5, &Visuals::enablefogtypehk, &Visuals::hookedfuncs[9]);
            res = MH_EnableHook(f5);

            Visuals::visibility2func f6 = (Visuals::visibility2func)IL2CPP::Class::Utils::GetMethodPointer("PlayerRoles.Visibility.VisibilityController", "ValidateVisibility");
            res = MH_CreateHook(f6, &Visuals::validatevisiblityhk, NULL);
            res = MH_EnableHook(f6);

            aimbot::clientcalc f7 = (aimbot::clientcalc)IL2CPP::Class::Utils::GetMethodPointer("InventorySystem.Items.Firearms.Modules.StandardHitregBase", "ClientCalculateHit");
            res = MH_CreateHook(f7, &aimbot::clientcalculatehithk, (LPVOID*)&aimbot::origfunc);
            res = MH_EnableHook(f7);

            aimbot::randomizeray f8 = (aimbot::randomizeray)IL2CPP::Class::Utils::GetMethodPointer("InventorySystem.Items.Firearms.Modules.SingleBulletHitreg", "ServerRandomizeRay");
            res = MH_CreateHook(f8, &aimbot::randomizerayhk, NULL);
            res = MH_EnableHook(f8);

            aimbot::attachmentparametervaluepair f9 = (aimbot::attachmentparametervaluepair)((DWORD64)IL2CPP::Globals.m_GameAssembly + 0x551990);
            res = MH_CreateHook(f9, &aimbot::attachmentparameterhk, NULL);
            res = MH_EnableHook(f9);

            std::vector<std::string> disableeffects = { "CustomRendering.FogEffect" , "CustomRendering.FadeEffect",
            "CustomRendering.Grayscale", "CustomRendering.BlurEffect", "CustomRendering.RadialBlur", "CustomRendering.DoubleVision",
            "CustomRendering.VignetteRefraction", "CustomRendering.CustomVignette", "CustomRendering.Darken",
            "CustomRendering.Ripples", "CustomRendering.DistanceEffect", "CustomRendering.Scanlines", "CustomRendering.ScreenDissolve",
            "CustomRendering.Glitch", "CustomRendering.Static", "CustomRendering.BloodHit", "CustomRendering.Lighten"};
            
            Visuals::returnbool f10;
            for (const auto& str : disableeffects) {
                f10 = (Visuals::returnbool)(IL2CPP::Class::Utils::GetMethodPointer(str.c_str(), "IsActive"));
                res = MH_CreateHook(f10, &Visuals::isactivehk, NULL);
                res = MH_EnableHook(f10);
            }
            

            Visuals::updatetype f11 = (Visuals::updatetype)(IL2CPP::Class::Utils::GetMethodPointer("CustomRendering.FogController", "Update"));
            res = MH_CreateHook(f11, &Visuals::fogcontrollerhk, &Visuals::hookedfuncs[10]);
            res = MH_EnableHook(f11);

            Misc::inrangefunc f12 = (Misc::inrangefunc)(IL2CPP::Class::Utils::GetMethodPointer("TeslaGate", "InRange"));
            res = MH_CreateHook(f12, &Misc::inrange, NULL);
            res = MH_EnableHook(f12);

            f12 = (Misc::inrangefunc)(IL2CPP::Class::Utils::GetMethodPointer("TeslaGate", "IsInIdleRange"));
            res = MH_CreateHook(f12, &Misc::inrange, NULL);
            res = MH_EnableHook(f12);

            f12 = (Misc::inrangefunc)(IL2CPP::Class::Utils::GetMethodPointer("TeslaGate", "PlayerInHurtRange"));
            res = MH_CreateHook(f12, &Misc::inrange, NULL);
            res = MH_EnableHook(f12);

            f12 = (Misc::inrangefunc)(IL2CPP::Class::Utils::GetMethodPointer("TeslaGate", "PlayerInRange"));
            res = MH_CreateHook(f12, &Misc::inrange, NULL);
            res = MH_EnableHook(f12);
            /*
            Misc::processmesagefunc f13 = (Misc::processmesagefunc)(IL2CPP::Class::Utils::GetMethodPointer("PlayerRoles.Voice.VoiceModuleBase", "ProcessMessage"));
            res = MH_CreateHook(f13, &Misc::processmessagehk, &Misc::hookedfuncs[0]);
            res = MH_EnableHook(f13);

            Visuals::validatevisiblityfunc f14 = (Visuals::validatevisiblityfunc)(IL2CPP::Class::Utils::GetMethodPointer("PlayerRoles.PlayableScps.Scp939.Scp939VisibilityController", "ValidateVisibility"));
            res = MH_CreateHook(f14, &Visuals::validatevisibility939hk, NULL);
            res = MH_EnableHook(f14);

            Misc::clientrecievefunc f15 = (Misc::clientrecievefunc)(IL2CPP::Class::Utils::GetMethodPointer("VoiceChat.Networking.VoiceTransceiver", "ClientReceiveMessage"));
            res = MH_CreateHook(f15, &Misc::clientreceivehk, &Misc::hookedfuncs[1]);
            res = MH_EnableHook(f15);

            Misc::getflagsfunc f16 = (Misc::getflagsfunc)(IL2CPP::Class::Utils::GetMethodPointer("PlayerRoles.Voice.VoiceChatReceivePrefs", "GetFlagsForUser"));
            res = MH_CreateHook(f16, &Misc::getflagsforuserhk, NULL);
            if (res != MH_OK) {
                std::cout << MH_StatusToString(res);
            }
            res = MH_EnableHook(f16);
            */
            startfu = (Visuals::startfunc)(IL2CPP::Class::Utils::GetMethodPointer("Interactables.Interobjects.ElevatorDoor", "Start"));
            res = MH_CreateHook(startfu, &Visuals::elevatoronstarthk, &Visuals::hookedfuncs[11]);
            if (res != MH_OK) {
                std::cout << MH_StatusToString(res);
            }
            res = MH_EnableHook(startfu);

            startfu = (Visuals::startfunc)(IL2CPP::Class::Utils::GetMethodPointer("Interactables.Interobjects.ElevatorDoor", "OnDestroy"));
            res = MH_CreateHook(startfu, &Visuals::elevatorondestroyhk, &Visuals::hookedfuncs[12]);
            if (res != MH_OK) {
                std::cout << MH_StatusToString(res);
            }
            res = MH_EnableHook(startfu);
            
            Misc::ispressed = (Misc::getkeydownfunc)((DWORD64)IL2CPP::Globals.m_GameAssembly + 0x2270B40);

        }
        IL2CPP::Callback::Initialize();
        IL2CPP::Callback::OnLateUpdate::Add(aimbot::gettarget);
        IL2CPP::Callback::OnLateUpdate::Add(ourmain);
        
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

