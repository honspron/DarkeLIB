// smart scout

#include "mansion.h"

inherit MONSTER;

create() {
  ::create();
    set_name("scout");
    set_id( ({ "scout" }) );
    set_short("An elven scout");
    set("race", "wild-elf");
    set_gender("male");
    set_long("This is not just any ordinary scout.  Upon closer "+
        "inspection you observe that he wears an insignia identifying "+
        "him as one of the 'Eagle Division's finest.  He must be here "+
        "inspecting the mansion.  He looks very cautious.");
    set_body_type("human");
    set_level(14);
    set_skill("melee", 50);
    set_skill("dodge", 80);
    set_skill("parry", 70);
    set_overall_ac(40);
    set_stats("strength", 150);
    set_stats("dexterity", 150);
    set_max_hp(1200);
    set_hp(1200);
    set_languages(({"common", "elvish"}));
    set_lang_prof("common",10);
    set_lang_prof("wild-elvish",10);
    set_property("handedness", "right hand");
    new("/d/damned/virtual/broad-sword_4.weapon")-> 
      move(this_object());
    new("/d/damned/virtual/breast-plate.armour")->
      move(this_object());
    new("/d/damned/virtual/large-shield.armour")-> 
      move(this_object());
    force_me("wield sword in right hand");
    force_me("wear plate");
    force_me("wear shield on left hand");
    set_emotes(5, ({
                   "The scout shakes his head.",
                   "The scout sighs.",
                   }), 0);
    set_speech(5,"common",({
          "This is obviously a set up.",
          "We were sent on a suicide mission.",
          "Fools.",
          "Did you hear that?",
        }),0);
}
