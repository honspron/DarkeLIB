#include <security.h>
#define AbNormal 1

inherit "/std/spells/shadows/shadow";

private object shadowee;

void sh_init( object ob )
{
    begin_shadow( ob );
    shadowee = ob;
}

void remove_me()
{
    stop_shadow();
    remove();
}

