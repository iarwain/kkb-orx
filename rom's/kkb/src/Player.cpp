/**
 * @file Player.cpp
 * @date 18-Jun-2023
 */

#include "Player.h"

void Player::OnCreate()
{
  orxInput_EnableSet(orxConfig_GetCurrentSection(), orxTRUE);
}

void Player::OnDelete()
{
}

void Player::Update(const orxCLOCK_INFO &_rstInfo)
{
  PushConfigSection();

  // Inputs
  const orxSTRING zInputSet = orxInput_GetCurrentSet();
  orxInput_SelectSet(orxConfig_GetCurrentSection());
  if(orxInput_HasBeenActivated("MoveLeft"))
  {
    s32Force--;
  }
  else if(orxInput_HasBeenActivated("MoveRight"))
  {
    s32Force++;
  }
  s32Force = orxCLAMP(s32Force, -orxConfig_GetS32("MaxForce"), orxConfig_GetS32("MaxForce"));

  // Movement
  orxVECTOR vPos, vSize;

  orxConfig_PushSection("Runtime");
  ScrollObject *poScene = kkb::GetInstance().GetObject(orxConfig_GetU64("Scene"));
  orxConfig_PopSection();
  if(poScene)
  {
    orxVector_Mulf(&vSize, &poScene->GetSize(vSize), 0.5f);
  }

  GetPosition(vPos);
  if(vPos.fX <= -vSize.fX)
  {
    s32Force  = orxMAX(0, s32Force);
    vPos.fX   = -vSize.fX;
  }
  else if(vPos.fX >= vSize.fX)
  {
    s32Force  = orxMIN(0, s32Force);
    vPos.fX   = vSize.fX;
  }
  SetPosition(vPos);
  SetSpeed({orxS2F(s32Force) * orxConfig_GetFloat("PlaneSpeed"), 0.0f, 0.0f});

  // Anim
  const orxSTRING zAnim = "Idle";
  if(s32Force < 0)
  {
    zAnim = "Left";
  }
  else if(s32Force > 0)
  {
    zAnim = "Right";
  }
  SetAnim(zAnim);

  orxInput_SelectSet(zInputSet);
  PopConfigSection();
}

orxBOOL Player::OnCollide(ScrollObject *_poCollider, orxBODY_PART *_pstPart, orxBODY_PART *_pstColliderPart, const orxVECTOR &_rvPosition, const orxVECTOR &_rvNormal)
{
  // Let's crash everyone
  SetAnim("Crash");
  if(_poCollider)
  {
    _poCollider->SetAnim("Crash");
  }

  // ... and go to the game over
  kkb::GetInstance().CreateObject("GameOver");

  return orxTRUE;
}
