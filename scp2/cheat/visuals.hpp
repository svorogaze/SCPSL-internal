#pragma once
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
namespace Visuals {
    Unity::System_String pickupnames[] = {
        helper::to_unity_string(xorstr_("Janitor keycard")),
        helper::to_unity_string(xorstr_("Scientist keycard")),
        helper::to_unity_string(xorstr_("Orange keycard")),
        helper::to_unity_string(xorstr_("Zone Manager keycard")),
        helper::to_unity_string(xorstr_("Guard keycard")),
        helper::to_unity_string(xorstr_("Private keycard")),
        helper::to_unity_string(xorstr_("Engineer keycard")),
        helper::to_unity_string(xorstr_("Operative keycard")),
        helper::to_unity_string(xorstr_("Captain keycard")),
        helper::to_unity_string(xorstr_("Facility Manager keycard")),
        helper::to_unity_string(xorstr_("Chaos keycard")),
        helper::to_unity_string(xorstr_("O5 keycard")),
        helper::to_unity_string(xorstr_("Radio")),
        helper::to_unity_string(xorstr_("COM15")),
        helper::to_unity_string(xorstr_("Medkit")),
        helper::to_unity_string(xorstr_("Flashlight")),
        helper::to_unity_string(xorstr_("MicroHID")),
        helper::to_unity_string(xorstr_("Pills")),
        helper::to_unity_string(xorstr_("Cola")),
        helper::to_unity_string(xorstr_("Buckshot")),
        helper::to_unity_string(xorstr_("E11SR")),
        helper::to_unity_string(xorstr_("Crossvec")),
        helper::to_unity_string(xorstr_("5.56x45")),
        helper::to_unity_string(xorstr_("FSP9")),
        helper::to_unity_string(xorstr_("Logicer")),
        helper::to_unity_string(xorstr_("HE")),
        helper::to_unity_string(xorstr_("Flashbang")),
        helper::to_unity_string(xorstr_(".44")),
        helper::to_unity_string(xorstr_("7.62x39")),
        helper::to_unity_string(xorstr_("9x19")),
        helper::to_unity_string(xorstr_("COM18")),
        helper::to_unity_string(xorstr_("Ball")),
        helper::to_unity_string(xorstr_("Cap")),
        helper::to_unity_string(xorstr_("Adrenaline")),
        helper::to_unity_string(xorstr_("Painkillers")),
        helper::to_unity_string(xorstr_("Coin")),
        helper::to_unity_string(xorstr_("LArmor")),
        helper::to_unity_string(xorstr_("CArmor")),
        helper::to_unity_string(xorstr_("HArmor")),
        helper::to_unity_string(xorstr_("Revolver")),
        helper::to_unity_string(xorstr_("AK")),
        helper::to_unity_string(xorstr_("Shotgun")),
        helper::to_unity_string(xorstr_("Candy")),
        helper::to_unity_string(xorstr_("SCP2176")),
        helper::to_unity_string(xorstr_("SCP244")),
        helper::to_unity_string(xorstr_("SCP244")),
        helper::to_unity_string(xorstr_("SCP1853")),
        helper::to_unity_string(xorstr_("3-X")),
        helper::to_unity_string(xorstr_("COM45")),
        helper::to_unity_string(xorstr_("SCP1576")),
        helper::to_unity_string(xorstr_("Jailbird")),
        helper::to_unity_string(xorstr_("Anti-Cola")),
        helper::to_unity_string(xorstr_("FRMG0")),
        helper::to_unity_string(xorstr_("A7")),
        helper::to_unity_string(xorstr_("Lantern")),
        helper::to_unity_string(xorstr_("Gate A")),
        helper::to_unity_string(xorstr_("Gate B")),
        helper::to_unity_string(xorstr_("LCZ A")),
        helper::to_unity_string(xorstr_("LCZ A")),
        helper::to_unity_string(xorstr_("LCZ B")),
        helper::to_unity_string(xorstr_("LCZ B")),
        helper::to_unity_string(xorstr_("Nuke")),
        helper::to_unity_string(xorstr_("SCP049")),
        helper::to_unity_string(xorstr_("914"))
    };

    std::unordered_map<Unity::CObject*, int> pickups;
    std::vector<Unity::CObject*> players;
    Unity::CCamera* cchar = nullptr;
    Unity::CCamera* (__fastcall* getmain)();
    Unity::Vector3(__fastcall* w2s)(Unity::CCamera*, Unity::Vector3);
    using startfunc = int64_t(__fastcall*)(int64_t);
    std::vector<void*> hookedfuncs;
    
    using visibilityfunc = int64_t(__fastcall*)(int64_t*, int64_t);
    using rangefunc = int64_t(*)();
    using enablefogfunc = int64_t(*)(unsigned char, float);
    using setforcedfog = int64_t(*)(__int64, unsigned __int16);
    using visibility2func = bool(__fastcall*)(int64_t* a1, int64_t a2);
    std::vector<std::pair<Unity::Vector3, std::pair<int, int>>> possibletargets;
    using gettransformfunc = Unity::CTransform* (__fastcall*)(Unity::CComponent*);
    Unity::CObject* localplayerhub = nullptr;
    void fovchange() {
        
    }

    int64_t keycardpickupstarthk(int64_t x) {
        auto ptr = (Unity::CObject*)x;
        if (ptr != nullptr) {
            short kek = *((short*)((char*)ptr + 0x78)); //itempickupbase->Info(first field is type)
            if (kek >= 0 && kek < 55) {
                pickups[ptr] = kek;
            }
        }
        return ((startfunc)hookedfuncs[0])(x);

    }

    int64_t itempickupbaseondestroyhk(int64_t x) {
        pickups.erase((Unity::CObject*)x);
        return ((startfunc)hookedfuncs[1])(x);
    }

    int64_t itempickupbasestarthk(int64_t x) {
        auto ptr = (Unity::CObject*)x;
        if (ptr != nullptr) {
            short kek = *((short*)((char*)ptr + 0x78)); //itempickupbase->Info(first field is type)
            if (kek >= 0 && kek < 55 && kek != 12 && kek != 0x23 && kek != 0x36 && kek != 0xF
                && kek != 0x13 && kek != 0x16 && (kek < 0x1B || kek > 0x1D)) {
                pickups[ptr] = kek;
            }
        }
        return ((startfunc)hookedfuncs[2])(x);
    }
    
    int64_t scp244ondestroyhk(int64_t x) {
        pickups.erase((Unity::CObject*)x);
        return ((startfunc)hookedfuncs[3])(x);
    }

    int64_t roundsummarystarthk(int64_t x) {
        pickups.clear();
        possibletargets.clear();
        return ((startfunc)hookedfuncs[4])(x);
    }

    int64_t itempickupbasedestroyselfhk(int64_t x) {
        pickups.erase((Unity::CObject*)x);
        return ((startfunc)hookedfuncs[5])(x);
    }

    int64_t referencehubstarthk(int64_t x) {
        auto ptr = (Unity::CObject*)x;
        if (ptr) {
            Unity::CObject* netid = *((Unity::CObject**)((DWORD64)ptr + 0x78)); //referencehub->networkidentity
            if (netid) {
                if (!netid->GetPropertyValue<bool>(xorstr_("isLocalPlayer"))) players.push_back(ptr);
                else localplayerhub = ptr;
            }
        }
        return ((startfunc)hookedfuncs[6])(x);
    }

    int64_t referencehubdestroyhk(int64_t x) {
        auto ptr = (Unity::CObject*)x;
        for (auto& i : players) {
            if (i == ptr) {
                std::swap(i, players.back());
                players.pop_back();
                break;
            }
        }
        if (ptr == localplayerhub) {
            localplayerhub = nullptr;
        }
        return ((startfunc)hookedfuncs[7])(x);
    }

    int64_t visibilitycheck(int64_t* x, int64_t b) {
        return 0;
    }

    int64_t getrange() {
        return 100000ll;
    }

    int64_t enablefogtypehk(unsigned char c, float a) {
        a = 0;
        return ((enablefogfunc)hookedfuncs[8])(c, a);
    }

    int64_t setforcedfoghk(__int64 a1, unsigned __int16 a2) {
        a2 = 0;
        return ((setforcedfog)hookedfuncs[9])(a1, a2);
    }

    bool validatevisiblityhk(int64_t* a, int64_t b) {
        return true;
    }

    struct HitboxIdentity : Unity::CObject {
        int64_t getdmgmult() {
            return *(int64_t*)((char*)this + 0x28);
        }
    };
    std::vector<Unity::CObject*> elevators;

    int64_t elevatoronstarthk(Unity::CObject* ptr) {
        if (ptr) elevators.push_back(ptr);
        return ((startfunc)hookedfuncs[11])((int64_t)ptr);
    }

    int64_t elevatorondestroyhk(Unity::CObject* ptr) {
        for (auto& i : elevators) {
            if (i == ptr) {
                std::swap(elevators.back(), i);
                elevators.pop_back();
                break;
            }
        }
        return ((startfunc)hookedfuncs[12])((int64_t)ptr);
    }


    gettransformfunc gt = nullptr;
    Unity::System_String strtest = helper::to_unity_string("GUI/Text Shader");
    Unity::System_String color1 = helper::to_unity_string("_Color");
    Unity::System_String color2 = helper::to_unity_string("_Color2");
    using serverprocessfall = void(__fastcall*)(Unity::CObject*);
    void __fastcall visuals(int64_t x) {
            cchar = nullptr;
            auto ptr = getmain();
            possibletargets.clear();
            if (ptr && localplayerhub) {
                if (!gt) gt = (gettransformfunc)IL2CPP::Class::Utils::GetMethodPointer("UnityEngine.Component", "get_transform");
                auto cptr = (Unity::CComponent*)ptr;
                auto ptr2 = gt(cptr);

                GUI::changecolor(Unity::Color(1.f, 1.f, 1.f, 1.f));
                for (auto pr : pickups) {
                    Unity::Vector3 screen(0, 0, 0);
                    Unity::Vector3 pos = pr.first->GetPropertyValue<Unity::Vector3>("Position");
                    ptr->WorldToScreen(pos, screen);
                    screen.y = 1080 - screen.y;
                    if (screen.z > 0.01 && screen.x > 0 && screen.x < 1920 && screen.y > 0 && screen.y < 1080) {
                        GUI::drawlabel(Unity::Rect(screen.x, screen.y, screen.x + 100, screen.y + 100), pickupnames[pr.second]);
                    }
                }
                

                GUI::changecolor(Unity::Color(0.5f, 0.215f, 0.807f, 1.f));
                for (auto& pr : elevators) {
                    Unity::Vector3 screen(0, 0, 0);
                    Unity::Vector3 pos = pr->GetPropertyValue<Unity::Vector3>("TargetPosition");
                    int type = pr->GetPropertyValue<int>("Group");
                    pos.y += 1;
                    ptr->WorldToScreen(pos, screen);
                    screen.y = 1080 - screen.y;
                    if (screen.z > 0.01 && screen.x > 0 && screen.x < 1920 && screen.y > 0 && screen.y < 1080) {
                        GUI::drawlabel(Unity::Rect(screen.x, screen.y, screen.x + 100, screen.y + 100), *(pickupnames + type + 55));
                    }
                }
                static void* get_singptr = IL2CPP::Class::Utils::GetMethodPointer("Scp914.Scp914Controller", "get_Singleton");
                Unity::CObject* controller914 = ((Unity::CObject * (*)())(get_singptr))();
                if (controller914) {
                    Unity::CTransform* intake = controller914->GetPropertyValue<Unity::CTransform*>("IntakeChamber");
                    Unity::CTransform* output = controller914->GetPropertyValue<Unity::CTransform*>("OutputChamber");
                    if (intake && output) {
                        Unity::Vector3 pos1, pos2;
                        pos1 = intake->GetPosition();
                        pos2 = output->GetPosition();
                        pos1.x = (pos1.x + pos2.x) / 2;
                        pos1.y = (pos1.y + pos2.y) / 2;
                        pos1.z = (pos1.z + pos2.z) / 2;
                        Unity::Vector3 screen(0, 0, 0);
                        ptr->WorldToScreen(pos1, screen);
                        screen.y = 1080 - screen.y;
                        if (screen.z > 0.01 && screen.x > 0 && screen.x < 1920 && screen.y > 0 && screen.y < 1080) {
                            GUI::drawlabel(Unity::Rect(screen.x, screen.y, screen.x + 100, screen.y + 100), *(pickupnames + 63));
                        }
                    }
                }


                auto ptr3 = *((Unity::CObject**)((DWORD64)localplayerhub + 0x88));
                if (!ptr) return;
                auto ptr4 = *((Unity::CObject**)((DWORD64)ptr3 + 0x80));
                if (!ptr4) return;
                BYTE cp = ptr4->GetPropertyValue<BYTE>("Team");
                
                
                std::sort(players.begin(), players.end());
                players.erase(std::unique(players.begin(), players.end()), players.end());

                for (auto pr : players) {
                    Unity::CObject* playerrolemanager = *((Unity::CObject**)((DWORD64)pr + 0x88)); //referencehub->roleManager
                    if (!playerrolemanager) continue;
                    Unity::CObject* playerrole = *((Unity::CObject**)((DWORD64)playerrolemanager + 0x80)); //rolemanager->_curRole
                    if (!playerrole) continue;

                    Unity::System_String* str = playerrole->GetPropertyValue<Unity::System_String*>("RoleName");
                    BYTE cp2 = playerrole->GetPropertyValue<BYTE>("Team");
                    if (!str || str->m_iLength == 0 || str->m_iLength == 4 || str->m_wString[0] == 'O' || (str->m_wString[0] == 'S' && str->m_wString[1] == 'p')) continue;
                    auto color = playerrole->GetPropertyValue<Unity::Color>("RoleColor");
                    int len = str->m_iLength;
                    //chams
                    if (cp2 != 5 && !(len >= 2 && str->m_wString[len - 1] == '9' && str->m_wString[len - 2] == '7')) {
                        Unity::CObject* fpcmodule = playerrole->GetPropertyValue<Unity::CObject*>("FpcModule");
                        if (fpcmodule) {
                            Unity::CObject* charactermodel = fpcmodule->GetPropertyValue<Unity::CObject*>("CharacterModelInstance");
                            if (charactermodel) {
                                Unity::il2cppArray<Unity::CObject*>* renderers = *(Unity::il2cppArray<Unity::CObject*>**)((char*)charactermodel + 0x58);
                                if (renderers) {
                                    for (uintptr_t u = 0U; renderers->m_uMaxLength > u; ++u) {
                                        Unity::CObject* renderer = renderers->At(u);
                                        if (!renderer) continue;
                                        Unity::CObject* material = renderer->GetPropertyValue<Unity::CObject*>("material");
                                        if (!material) continue;
                                        using shaderfindfunc = void* (__fastcall*)(Unity::System_String*);
                                        static shaderfindfunc find = (shaderfindfunc)(IL2CPP::Class::Utils::GetMethodPointer("UnityEngine.Shader", "Find"));
                                        static void* shader = find(&strtest);
                                        if (material->GetPropertyValue<void*>("shader") != shader) {
                                            material->SetPropertyValue<void*>("shader", shader);
                                            using setcolor = int64_t(__fastcall*)(Unity::CObject*, Unity::System_String*, Unity::Color&);
                                            static setcolor set = (setcolor)((DWORD64)IL2CPP::Globals.m_GameAssembly + 0x21EE560);
                                            set(material, &color1, color);
                                            set(material, &color2, color);
                                        }
                                    }
                                }
                            }
                        }
                    }

                    
                    if (cp != 5 && cp2 != 5 && cp != cp2 && !(cp == 1 && cp2 == 3) && !(cp == 2 && cp2 == 4)) {
                        Unity::Vector3 pos;
                        pos = playerrole->GetPropertyValue<Unity::Vector3>("CameraPosition");
                        pos.y -= 0.5;
                        Unity::Vector3 screen(0, 0, 0);
                        ptr->WorldToScreen(pos, screen);
                        screen.y = 1080 - screen.y;
                        screen.x -= 40;

                        if (screen.z > 0.01 && screen.x > 0 && screen.x < 1920 && screen.y > 0 && screen.y < 1080) {
                            screen.x += 40;
                            if (len >= 2 && str->m_wString[len - 1] == '9' && str->m_wString[len - 2] == '7') {
                                GUI::changecolor(color);
                                auto cptr = (Unity::CComponent*)playerrole;
                                GUI::drawlabel(Unity::Rect(screen.x, screen.y, screen.x + 100, screen.y + 100), *str);
                            }
                            else {
                                Unity::CObject* fpcmodule = playerrole->GetPropertyValue<Unity::CObject*>("FpcModule");
                                Unity::CObject* charactermodel = fpcmodule->GetPropertyValue<Unity::CObject*>("CharacterModelInstance");
                                int len = str->m_iLength;
                                if (!(len >= 6 && str->m_wString[4] == '4')) {
                                    Unity::il2cppArray<HitboxIdentity*>* hitboxes = *(Unity::il2cppArray<HitboxIdentity*>**)((char*)charactermodel + 0x60);
                                    int dmg = -1;
                                    for (uintptr_t u = 0U; hitboxes->m_uMaxLength > u; ++u) {
                                        HitboxIdentity* hitbox = hitboxes->At(u);
                                        if (hitbox->getdmgmult() > dmg) {
                                            dmg = hitbox->getdmgmult();
                                            pos = hitbox->GetPropertyValue<Unity::Vector3>("CenterOfMass");
                                        }
                                    }
                                }
                                if (screen.x < 1920 && cp != 5 && cp2 != 5 && cp != cp2 && !(cp == 1 && cp2 == 3) && !(cp == 2 && cp2 == 4) && !(len >= 2 && str->m_wString[len - 1] == '9' && str->m_wString[len - 2] == '7')) {
                                    possibletargets.push_back({ pos, {screen.x, screen.y} });
                                }
                            }
                        }
                    }
                }
            }
            

    }

    using returnbool = bool(__fastcall*)(int64_t);
    bool isactivehk() {
        return false;
    }
    using updatetype = Unity::CObject* (__fastcall*)(Unity::CObject*);

    Unity::CObject* fogcontrollerhk(Unity::CObject* x) {
        Unity::il2cppArray<Unity::CObject*>* fogsettings = *(Unity::il2cppArray<Unity::CObject*>**)((char*)x + 0x20);
        if (fogsettings) {
            for (uintptr_t u = 0U; fogsettings->m_uMaxLength > u; ++u) {
                Unity::CObject* fogsetting = fogsettings->At(u);
                if (!fogsetting) continue;
                *(float*)((char*)fogsetting + 0x24) = 0;
                *(float*)((char*)fogsetting + 0x28) = 100000000.f;
            }
        }
        return ((updatetype)Visuals::hookedfuncs[10])(x);
    }

    bool isactivehktrue() {
        return true;
    }
    using validatevisiblityfunc = bool(__fastcall*)(int64_t*, int64_t*);
    bool validatevisibility939hk(int64_t* thisp, int64_t* referencehub) {
        return true;
    }


}