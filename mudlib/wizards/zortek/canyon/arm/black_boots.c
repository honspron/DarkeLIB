inherit "/std/armour";

int used;

void init() {
  ::init();
  add_action("poof","invoke");
}

void create() {
  ::create();
  set_name("boots");
  set("id", ({ "boots", "boots of darkness" }) );
  set("short", "Boots of Darkness");
  set("long",@TEXT
These boots are of a supple jet black hide form an unidentifiable
creature.  Most of the sole of these boots are make of a semi-ridgid
metal and the heels appear to be of an obsidian type stone. 
TEXT
);
    set_material("/metal/unknown");
    set_weight(225);
    set_value(35000);
    set_type("boots");
    set_limbs(({"left foot", "right foot"}));
    set_ac(25);
    set_ac(100, "plasma");
    set_ac(100, "stun");
    set_enh_criticals(-1);
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
  if((string)this_player()->query_class() == "thief" ||
     (string)this_player()->query_class() == "nightblade" ||
     (string)this_player()->query_race() == "troll" ||
     (string)this_player()->query_race() == "half-orc" ||
     (string)this_player()->query_race() == "storm-giant" ||
     (string)this_player()->query_race() == "hill-giant") {
    write(@TEXT
Your body is racked with agony as the footwear scorches and begins
to char your skin.  Before you can fully remove them you find you
have incurred substancial damage.
TEXT
);
    this_player()->severed_limb("right foot");
    this_player()->severed_limb("left foot");
    this_player()->add_hp(-1*((int)this_player()->query_hp()-1));
    return 0;
  }
  write(@TEXT
Power seems to surge up from the ground conducted by the boots
into your body and you can sense that there might be a power
within them that you can invoke.
TEXT
);
  return 1;
}

int extra_removed() {
  write(@TEXT
The boots do not seem easily removed...However, with a great amount
of force and determination you rip the boots off!  Unfortunately,
your feet remain within...
TEXT
);
  this_player()->severed_limb("right foot");
  this_player()->severed_limb("left foot");
  return 1;
}
 
int poof(string str) {
  if(!str || present(str, this_player()) != this_object()) {
    notify_fail("Invoke what?\n");
    return 0;
  }
  if(used) {
    write("You fail to invoke any power within the boots.\n");
    return 1;
  }
  write (@TEXT
TEXT
);
  seteuid(getuid());
  say(this_player()->query_cap_name()+" utters a foul WORD.\n", this_player());
  "/std/spells/improved_invisibility"->spell_func(this_player(),this_player(),15,"",0);
  used = 1;
  return 1;
}
