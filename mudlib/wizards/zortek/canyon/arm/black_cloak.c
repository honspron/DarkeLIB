inherit "/std/armour";

void create() {
    ::create();
    set_name("cloak");
    set("id", ({ "cloak", "cloak of darkness" }) );
    set("short", "The Cloak of Darkness");
    set("long", @TEXT
This heavy cloak is of the darkest jet in colour.  The colour of death!
TEXT
);
    set_weight(103);
    set_value(1250);
    set_type("cloak");
    set_limbs( ({ "torso" }) );
    set_ac(17);
    set_wear( (: call_other, this_object(), "extra_worn" :) );
    set_remove( (: call_other, this_object(), "extra_removed"  :) );
}

int extra_worn() {
  if((int)this_player()->query_level() >= 15 + random(10)) {
    this_player()->set_property("wiz light",3);
    write("You feel the chill of a cold, damp night envelope you.");
    return 1;
  }
  else {
    write(@TEXT
The chill fingers of death and darkness take a firm grip upon your
heart and enshroud your soul...spasms rack your body and then...
TEXT
);
    say(this_player()->query_cap_name() + "suddenly colapses in spasms.");
    this_player()->die();
    return 0;
  }
}

int extra_removed() {
    this_player()->remove_property("wiz light");
    write("The chill of night leaves you.");
    return 1;
}
