/**
 * @file kkb.cpp
 * @date 18-Jun-2023
 */

#define __SCROLL_IMPL__
#include "kkb.h"
#undef __SCROLL_IMPL__

#include "Player.h"

#define orxBUNDLE_IMPL
#include "orxBundle.h"
#undef orxBUNDLE_IMPL

#ifdef __orxMSVC__
/* Requesting high performance dedicated GPU on hybrid laptops */
__declspec(dllexport) unsigned long NvOptimusEnablement        = 1;
__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
#endif // __orxMSVC__

void kkb::Update(const orxCLOCK_INFO &_rstInfo)
{
  if(orxInput_IsActive("Quit"))
  {
    orxEvent_SendShort(orxEVENT_TYPE_SYSTEM, orxSYSTEM_EVENT_CLOSE);
  }
  else if(orxInput_HasBeenActivated("Restart"))
  {
    orxConfig_PushSection("Runtime");
    if(ScrollObject *poScene = GetObject(orxConfig_GetU64("Scene")))
    {
      poScene->SetLifeTime(orxFLOAT_0);
    }
    orxConfig_PopSection();
    CreateObject("Scene");
  }
}

orxSTATUS kkb::Init()
{
  CreateObject("Scene");

  return orxSTATUS_SUCCESS;
}

orxSTATUS kkb::Run()
{
  return orxSTATUS_SUCCESS;
}

void kkb::Exit()
{
  orxBundle_Exit();
}

void kkb::BindObjects()
{
  ScrollBindObject<Player>("Player");
}

orxSTATUS kkb::Bootstrap() const
{
  orxBundle_Init();

  orxResource_AddStorage(orxCONFIG_KZ_RESOURCE_GROUP, orxBUNDLE_KZ_RESOURCE_STORAGE, orxFALSE);
  orxResource_AddStorage(orxCONFIG_KZ_RESOURCE_GROUP, orxBUNDLE_KZ_RESOURCE_STORAGE "kkb.obr", orxFALSE);
  orxResource_AddStorage(orxCONFIG_KZ_RESOURCE_GROUP, "../data/config", orxFALSE);

  return orxSTATUS_SUCCESS;
}

int main(int argc, char **argv)
{
  kkb::GetInstance().Execute(argc, argv);

  return EXIT_SUCCESS;
}
