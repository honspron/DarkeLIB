//  Wizard:   Khojem
//  Monster:  peon
//  File:     peon.c

#include "/adm/include/std.h"

inherit MONSTER;

int chk_my_mon();

object clone_ob;

create() {
  ::create();
    set_name("peon");
    set_id( ({ "peon"}) );
    set_level(1);
    set_short("peon");
    set_long("A little piss-ant." 
      );
    set("race", "human");
    set_body_type("human");
    set_stats("dexterity", 20);
    set_stats("intelligence", 60);
    set_wimpy(0);
    set_moving(1);
    set_speed(60);
    clone_ob=environment(this_object());
 }

int chk_my_mon() { return 1;}

void die(object ob) {
  ::die();
  clone_ob->decrement_mob("peon");
}

