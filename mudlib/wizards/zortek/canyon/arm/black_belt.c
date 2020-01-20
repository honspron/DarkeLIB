inherit "/std/armour";

int used;

void init() {
  ::init();
  add_action("poof","invoke");
}

void create() {
    ::create();
    set_name("belt");
    set("id", ({ "belt", "belt of darkness" }) );
    set("short", "Belt of Darkness");
    set("long", @TEXT
This wide belt appears to be make of a jet black crushed velvet
fabric and has a obsidian disk like fastener at one end.
TEXT
);
  set_weight(105);
  set_value(82000);
  set_type("belt");
  set_ac(25);
  set_ac(150, "electricity");
  set_ac(150, "fire");
  set_ac(150, "cold");
  set_ac(150, "vacuum");
  set_limbs( ({ "torso" }) );
  set_material("/metal/obsidian");
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
  if((string)this_player()->query_class() == "elementalist" ||
     (string)this_player()->query_class() == "arch-mage" ||
     (string)this_player()->query_race() == "salamander" ||
     (string)this_player()->query_race() == "sylph" ||
     (string)this_player()->query_race() == "pech" ||
     (string)this_player()->query_race() == "nereid" ) {
    write(@TEXT
Your body is wracked with pain and you colapse to the ground in a
pile of quivering flesh...You then hear a moaning voice,
    "%^RED%^Deathhh isss tooo gooood forr yooo...Curssss Theee...
     from Helllss Heart Cursss Theee!%^RESET%^"
You then feel weak, confused, and dizzy.  
TEXT
);
    ob = new("/std/spells/shadows/curse_shadow");
    ob->set_curse(-1*(100+random(50)));
    ob->start_shadow(this_player(), 4800,
      "%^BOLD%^%^RED%^A HELLISH CURSE HAS WORN OFF!!!%^RESET%^");
    this_player()->add_hp(-1*((int)this_player()->query_hp()-1));
    return 0;
  }
  write(@TEXT
Your body shivers as a darkness decends upon your soul and you become
aware of a forboding power within the belt that may be invoked.
TEXT
);
  return 1;
}

int extra_removed() {
  write("A mild depression washes over you.");
  return 1;
}
 
int poof(string str) {
    if(!str || present(str, this_player()) != this_object()) {
        notify_fail("Invoke what?\n");
        return 0;
    }
    if(used) {
        write("You fail to invoke any power within the belt.\n");
        return 1;
    }
    write ("You invoke the power of the belt.\n");
    seteuid(getuid());
    say(this_player()->query_cap_name()+" utters a foul WORD.\n", this_player());
    "/std/spells/silent_walk"->spell_func(this_player(),this_player(),15,"",0);
    used = 1;
    return 1;
}
