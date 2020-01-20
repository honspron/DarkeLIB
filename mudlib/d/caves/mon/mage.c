/*Drow Mage coded by Cyric 04/20/99*/
#include <std.h>
#include "cyric.h"
inherit MONSTER;

void create()
{
    ::create();
    set_name("mage");
    set("id",({"mage","drow elf","drow","elf","wizard"}));
    set_level(random(6)+20);
    set_short("drow mage");
    set("long",@LONG
Cloaked in ebon robes, this Drow glares at you hatefully.  He moves quickly, yet gracefully, sizing you up as an opponent.  An arrogant sneer briefly crosses his face.  A lock of long white hair falls from his hood as he begins to mutter something under his breath.
LONG);
    set("race","drow-elf");
    set_gender("male");
    set_body_type("human");
    set_overall_ac(20);
    set_wielding_limbs(({"right hand","left hand"}));
    set_ac("right hand",5);
    set_melee_damage((["crushing":10,"cutting":5]));
    set_fingers(5);
    set_property("magic resistance",50);
    set_skill("swimming",random(70)+110);
    set_skill("knife",random(70)+110);
    set_skill("two handed staff",random(70)+110);
    set_skill("conjuration",random(70)+110);
    set_skill("focus casting",random(70)+110);
    set_skill("trade lore",random(70)+110);
    set_skill("melee",random(70)+110);
    set_skill("attack",random(70)+110);
    set_skill("magery",random(70)+110);
    set_skill("perception",random(70)+110);
    set_skill("prospecting",random(70)+110);
    set_skill("consider",random(70)+110);
    set_skill("illusionism",random(70)+110);
    set_skill("fast casting",random(70)+500);
    set_skill("dodge",random(70)+110);
    set_skill("concentrate",random(70)+110);
    set_skill("detect magic",random(70)+110);
    set_skill("sorcery",random(70)+110);
    set_skill("spell sense",random(70)+110);
    set_skill("telepathy",random(70)+110);
    set_skill("invisibility art",random(70)+110);
    set_casting_chance(1);
    set_combat_chance(100);
    add_spell("darkness","$A");
    set_spell_level("darkness",random(6)+1);
    add_spell("burning hands","$A");
    set_spell_level("burning hands",random(6)+1);
    add_spell("faerie fire","$A");
    set_spell_level("faerie fire",random(6)+1);
    //add_spell("light","$(ME)");
    set_spell_level("light",random(6)+1);
    add_spell("magic missile","$A");
    set_spell_level("magic missile",random(6)+1);
    add_spell("shocking grasp","$(ME)");
    set_spell_level("shocking grasp",random(6)+1);
    add_spell("fireball","$A");
    set_spell_level("fireball",random(6)+1);
    //add_spell("clairvoyance","$A");
    set_spell_level("clairvoyance",random(6)+1);
    //add_spell("levitation","$(ME)");
    set_spell_level("levitation",random(6)+1);
    add_spell("ice dagger","$A");
    set_spell_level("ice dagger",random(6)+1);
    //add_spell("dark vision","$(ME)");
    set_spell_level("dark vision",random(6)+1);
    add_spell("power word, stun","$A");
    set_spell_level("power word, stun",6);
    //add_spell("summon familiar","$(ME)");
    set_spell_level("summon familiar",random(6)+1);
    add_spell("killing cloud","$A");
    set_spell_level("killing cloud",random(6)+1);
    add_spell("blur","$(ME)");
    set_spell_level("blur",random(6)+1);
    add_spell("lightning bolt","$A");
    set_spell_level("lightning bolt",random(6)+1);
    add_spell("power word, blind","$A");
    set_spell_level("power word, blind",random(6)+1);
    //add_spell("summon","$A");
    set_spell_level("summon",random(6)+1);
    add_spell("fire shield","$(ME)");
    set_spell_level("fire shield",random(6)+1);
    add_spell("mana drain","$A");
    set_spell_level("mana drain",random(6)+1);
    add_spell("mirror image","$(ME)");
    set_spell_level("mirror image",random(6)+1);
    add_spell("explosive fireball","$A");
    set_spell_level("explosive fireball",random(6)+1);
    add_spell("awareness","$(ME)");
    set_spell_level("awareness",random(6)+1);
    add_spell("see invisible","$(ME)");
    set_spell_level("see invisible",random(6)+1);
    //add_spell("teleport","$A");
    set_spell_level("teleport",random(6)+1);
    //add_spell("create teleport beacon","$(ME)");
    set_spell_level("create teleport beacon",random(6)+1);
    add_spell("vacuum bolt","$A");
    set_spell_level("vacuum bolt",random(6)+1);
    //add_spell("transport","$A");
    set_spell_level("transport",random(6)+1);
    //add_spell("invisiblity","$(ME)");
    set_spell_level("invisibility",6);
    //add_spell("call lightning","$A");
    set_spell_level("call lightning",random(6)+1);
    //add_spell("scry","$A");
    set_spell_level("scry",random(6)+1);
    //add_spell("delay","$A");
    set_spell_level("delay",random(6)+1);
    //add_spell("store spell","$A");
    set_spell_level("store spell",random(6)+1);
    //add_spell("dispel magic","$A");
    set_spell_level("dispel magic",random(6)+1);
    add_spell("counter spell","$A");
    set_spell_level("counter spell",random(6)+1);
    add_spell("haste","$(ME)");
    set_spell_level("haste",random(6)+1);
    //add_spell("summon greater familiar","$(ME)");
    set_spell_level("summon greater familiar",random(6)+1);
    //add_spell("link","$(ME)");
    set_spell_level("link",random(6)+1);
    add_spell("blizzard","$A");
    set_spell_level("blizzard",random(6)+1);
    //add_spell("stabilize familiar","$(ME)");
    set_spell_level("stabilize familiar",random(6)+1);
    add_spell("power word, kill","$A");
    set_spell_level("power word, kill",random(6)+1);
    add_spell("internal flame","$A");
    set_spell_level("internal flame",random(6)+1);
    //add_spell("suggestion","$A");
    set_spell_level("suggestion",random(6)+1);
    add_spell("dranaxar's anti-magic field","$A");
    set_spell_level("dranaxar's anti-magic field",random(6)+1);
    add_spell("meteor storm","$A");
    set_spell_level("meteor storm",random(6)+1);
    add_spell("mana vortex","$A");
    set_spell_level("mana vortex",random(6)+1);

    new("/d/damned/virtual/dagger_6.weapon")->move(this_object());
    force_me("wield dagger in left hand");
    force_me("use concentrate");
    set_money("gold",random(350)+1);
    set_languages(({"common","drow"}));
    set_lang_prof("common",10);
    set_emotes(1,({
	"You sense an arcane minion.",
      }),0);
    set_achats(1,({
	"You hear a low chanting.\n",
	"Someone mutters something that makes your blood run cold.\n",
      }));
}
void init()
{
    ::init();
    if(!TP->is_player()) return;
    if(wizardp(TP)) return;
    if(!TO->query_stealth())
    {
	force_me("use invisibility art");
	return;
    }
    if(random(5)==0)
    {
	delayed_call("do_warning",0,TP);
	delayed_call("do_cstun",random(4)+5,TP);
    write_file(LOGS+"/mage.log", TPQCN+
      " pissed off a mage at "+ctime(time())+
      ".\n");
	return;
    }
}

void do_cstun(object tp)
{
    if(!tp || !present(tp, environment())) return;
    force_me("madlaugh");
    return;
}
void do_warning(object tp)
{
    if(!tp || !present(tp, environment())) return;
    force_me("sneer "+(string)tp->query_name());
    force_me("cast *6 power word, stun at "+(string)tp->query_name());
    return;
}
