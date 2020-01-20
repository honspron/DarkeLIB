inherit "/std/armour";

int lit, fuel, light_time;
object shadow;

void init() {
  ::init();
  add_action("light","invoke");
  add_action("extinguish","quell");
}

void create() {
  ::create();
  set_name("helm");
  set("id", ({ "helm", "great helm", "helm of darkness" }) );
  set("short", "Helm of Darkness");
  set("long", "This great helm is made of an unearthly jet coloured metal.");
  set_material("/metal/unknown");
  set_weight(195);
  set("value", 5000);
  set_type("helmet");
  set_limbs( ({ "head" }) );
  set_ac(15);
  set_wear( (: call_other, this_object(), "extra_worn" :) );
  set_remove( (: call_other, this_object(), "extra_removed"  :) );
  set_float_value(0.1);
  fuel = 4500+random(4500);
  lit = 0;
  shadow = 0;
  set_property("no save", 1);
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
  if((string)this_player()->query_class() == "paladin" ||
     (string)this_player()->query_class() == "necromancer" ||
     (string)this_player()->query_race() == "seraph" ||
     (string)this_player()->query_race() == "wraith" ) {
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
A chill runs down your spine and you feel power in the helm that
you might be able to invoke or quell.
TEXT
);
  return 1;
}

int extra_removed() {
  write("A chill runs up your spine.");
  return 1;
}
 
int light(string str) {
    if(!str || present(str, this_player()) != this_object()) {
        notify_fail("Invoke what?\n");
        return 0;
    }
    if(!fuel) {
        notify_fail("You notice no response or change.\n");
        return 0;
    }
    if(lit) {
        notify_fail("The helm is already active!\n");
        return 0;
    }
    write ("You invoke the power of the helm.\n");
    seteuid(getuid());
    say(this_player()->query_cap_name()+" utters a hollow WORD.\n", this_player());
    shadow = new("/std/spells/shadows/light_shad");
    shadow->set_light(-10);
    shadow->start_shadow(environment());
    delayed_call("go_dark", fuel);
    light_time = time();
    lit = 1;
    return 1;
}
 
int extinguish(string str) {
  if(!str || present(str, this_player()) != this_object()) {
      notify_fail("Quell what?\n");
      return 0;
  }
  if(!lit) {
      notify_fail("The helm is not active!\n");
      return 0;
  }
  write("You quell the power of the helm.\n");
  say(this_player()->query_cap_name()+" utters a hollow WORD.\n",
      this_player());
      fuel -= (light_time - time());
  if(shadow) shadow->external_destruct(shadow);
  remove_delayed_call("go_dark");
  lit = 0;
  return 1;
}
 
void go_dark() {
    if(shadow) shadow->external_destruct(shadow);
    fuel = 0;
    if(living(environment(this_object())))
	tell_object(environment(this_object()), "Your helm's power is exhausted.\n");
    set_destroy();
    set_value(10);
    lit = 0;
}

int move(mixed dest) {
    int x;
 
    if(lit && shadow)
      shadow->external_destruct(shadow);
    x = ::move(dest);
    if(lit) {
      seteuid(getuid());
      shadow = new("/std/spells/shadows/light_shad");
      shadow->set_light(-10);
      shadow->start_shadow(environment());
    }
    return x;
}
int query_lit() { return lit; }
int query_fuel() { return fuel; }
remove()
{
   if(lit && shadow)
      shadow->external_destruct(shadow);
   return ::remove();
}
