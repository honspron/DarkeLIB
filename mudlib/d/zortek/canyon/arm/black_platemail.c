#include <std.h>

inherit ARMOUR;

int used;

void init() {
  ::init();
  add_action("poof","invoke");
}

void create() {
  ::create();
  set_name("platemail");
  set("id", ({"platemail", "platemail of darkness"}));
  set("short","Platemail of Darkness");
  set("long",@TEXT
This suit of platemail is of the blackest jet coloured material and
the craftsmanship is of the finest caliber.  The type of metal is
unidentifiable and there are no significant markings to be found.
TEXT
);
  set_material("/metal/unknown");
  set_type("platemail");
  set_ac(25);
  set_ac(100, "disruption");
  set_enh_critical(-2);
  set_limbs( ({"torso"}) );
  set_weight(450);
  set_value(12500);
  set_wear( (: call_other, this_object(), "extra_worn" :) );
  set_remove( (: call_other, this_object(), "extra_removed"  :) );
  set_property("no save", 1);
  used = 0;
}

int extra_worn() {
  object ob;
  if((int)this_player()->query_level() < 15 + random(10)) {
    write(@TEXT
Images of hellish nightmares flood your mind.  The screams that begin
to issue from your lungs are other worldly wails of pain and madness.
Before you lose consciousness, your heart explodes from its chest
cavity and the room is sprayed with a crimson mist.  The last image
you see is you body engulfed in darke flames...
TEXT
);
    this_player()->die();
    environment(this_object())->remove();
    this_object()->remove();
    return 0;
  }
  if((string)this_player()->query_class() == "chaos lord" ||
     (string)this_player()->query_race() == "sword demon") {
    write(@TEXT
Your body is racked with agony as the platemail scorches and begins
to char your skin.  A piercing magenta light seems to cause the fluid
in your eyes to boil.  Before you can fully remove the armour you find
you have incurred substancial damage.
TEXT
);
    ob = new("/std/spells/shadows/blind_shadow");
    ob->start_shadow(this_player());
    // Yes it is an intentional perm blindness shadow
    this_player()->add_hp(-1*((int)this_player()->query_hp()-1));
    return 0;
  }
  write(@TEXT
A powerful feeling of evil washes over your body and you can sense
that their might be a power within this armour that you can invoke.
TEXT
);
  return 1;
}

int extra_removed() {
  write(@TEXT
You peel off the armour that wants to stick to your skin.
TEXT
);
  return 1;
}
 
int poof(string str) {
  if(!str || present(str, this_player()) != this_object()) {
    notify_fail("Invoke what?\n");
    return 0;
  }
  if(used) {
    write("You fail to invoke any power within the platemail.\n");
    return 1;
  }
  write (@TEXT
TEXT
);
  seteuid(getuid());
  say(this_player()->query_cap_name()+" utters a foul WORD.\n", this_player());
  "/std/spells/awareness"->spell_func(this_player(),this_player(),15,"",0);
  used = 1;
  return 1;
}
