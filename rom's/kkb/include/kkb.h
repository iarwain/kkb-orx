/**
 * @file kkb.h
 * @date 18-Jun-2023
 */

#ifndef __kkb_H__
#define __kkb_H__

#define __NO_SCROLLED__
#include "Scroll.h"

/** Game Class
 */
class kkb : public Scroll<kkb>
{
public:


private:

                orxSTATUS       Bootstrap() const;

                void            Update(const orxCLOCK_INFO &_rstInfo);

                orxSTATUS       Init();
                orxSTATUS       Run();
                void            Exit();
                void            BindObjects();


private:
};

#endif // __kkb_H__
