/* Monster By: Zortek for DarkeMud
 * Date:       031596
 * File:       anerax.c
 * Location:   /wizards/mon/
 * Used in:    /wizards/room/
 * Power:      High for this Domain (30+)
 * Notes:      Devil Lord
 */
#include <std.h>
inherit MONSTER;

void create() {
   object gem;
   int lev;
   ::create();
   lev = 30;
   set_level(lev);
   set_property("zor_mon", 1);
   set_property("enhance criticals", -3);
   set_name("anerax");
   set("id", ({"devil", "styx devil", "devil lord", "monster"}) );
   set("short", "Anerax, Lord of Styx");
//---------------------------------------------------------
   set("long", @LONG
Lord Anerax is the seated ruler over the Black Ferriers of the Damned.
While he is a styx devil, he is horribly mutated with scaley skin and
drab greyish coloring.  His head is also disporportionately large;
however, his jaws protrude forming almost a reptilian snout.
LONG
);
   set("race", "devil");
   set_gender("male");
   set_overall_ac(190);
   set_alignment(-900);
   set_money("electrum", random(10000)+random(10000));
   set_languages( ({"common",}) );
   set_combat_chance(50);
   set_casting_chance(50);

   set_skill("elementalism", 250);
   add_spell("elemental storm", "");
   set_spell_level("elemental storm", 6);

   set_body_type("human");
   set_property("melee damage", ([ "aether" : 35, ]));
   set("aggressive", 0);

   set_emotes(5, ({
     "Lord Anerax says in Common: Offer your soul and you may pass unharmed.",
     "Lord Anerax says in Common: Why have you come here?",
     "Lord Anerax says in Common: Home is but a casket ride away.",
    }), 0);
   set_achats(15, ({
     "Lord Anerax leaps beyond your reach.",
     "%^CYAN%^Lord Anerax splashes some dark liquid on you and you lose experience.%^RESET%^",
     "Lord Anerax curses you.",
    }) );
  gem = new("/wizards/zortek/canyon/obj/soul_gem");
  gem->set_devil_name("Anerax");
  gem->move(this_object());
}

string query_element() { return "water"; }
