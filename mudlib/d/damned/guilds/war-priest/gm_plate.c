// Coder: %^GREEN%^nEv!N%^RESET%^
// Darkemud
// GM Plate for the Priests of K'thach

#include <move.h>
#include <std.h>

inherit "/std/armour";
inherit AUTOLOAD;
  
void create() {
    ::create();
    set("id", ({ "platemail", "plate", "mail", "armour", "armor" }));
    set("short", "a suit of ancient platemail");
    set("long",
	"Forged centuries ago, this suit of armour has withstood countless "
	"battles.  Blessed by the Priests of K'thach it gives the wearer "
	"incredible protection against dishonorable attacks..."
    );
    set_limbs(({"torso"}));
    set_weight(400);
// nothing really special here, just is very good against impaling attack
// forms
    set_ac(60);
    set_ac(200, "impaling");
    set_wear((: call_other,this_object(), "make_me_gm" :));
// later this armour will have a chance to shatter any weapon used to
// backstab the wearer
    set_material("metal/davistone");
    set_enh_critical(-1);
    set_value(0);
   return;
}

int query_always_keep() { return 1; }
int make_me_gm() {
object ob;

  seteuid(getuid());
  ob= new("d/damned/guilds/war-priest/war-priest_obj");
  ob->make_me_master(this_player());
  return 1;
}
