/**
 * @file Player.h
 * @date 18-Jun-2023
 */

#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "kkb.h"

/** Player Class
 */
class Player : public ScrollObject
{
public:


protected:

                void            OnCreate();
                void            OnDelete();
                void            Update(const orxCLOCK_INFO &_rstInfo);


private:
                orxBOOL         OnCollide(ScrollObject *_poCollider, orxBODY_PART *_pstPart, orxBODY_PART *_pstColliderPart, const orxVECTOR &_rvPosition, const orxVECTOR &_rvNormal);

                orxS32          s32Force;
};

#endif // __PLAYER_H__
