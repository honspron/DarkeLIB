/*Drow Rogue coded by Cyric 04/20/99*/
#include <std.h>
#include "cyric.h"
inherit MONSTER;

void create()
{
    ::create();
    set_name("rogue");
    set("id",({"rogue","drow elf","drow","elf","thief"}));
    set_level(random(5)+20);
    set_short("drow rogue");
    set("long",@LONG
A broad grin crosses the rogue's face as he notices you.  His movement is deceptive and erratic, making it difficult to watch him for any length of time.  His deep black skin is contrasted sharply by his pure white hair.
LONG
    );
    set("race","drow-elf");
    set_gender("male");
    set_body_type("human");
    set_overall_ac(20);
    set_wielding_limbs(({"right hand","left hand"}));
    set_ac("right hand",5);
    set_melee_damage((["crushing":5,"cutting":5]));
    set_fingers(5);
    set_property("magic resistance",50);
    set_skill("dual attack",random(80)+100);
    set_skill("offhand training",random(80)+100);
    set_skill("thrown",random(80)+100);
    set_skill("blade",random(80)+100);
    set_skill("swimming",random(80)+100);
    set_skill("knife",random(80)+100);
    set_skill("pick pocket",random(80)+100);
    set_skill("trade lore",random(80)+100);
    set_skill("attack",random(80)+100);
    set_skill("perception",random(80)+100);
    set_skill("prospecting",random(80)+100);
    set_skill("dodge",random(80)+100);
    set_skill("parry",random(80)+100);
    set_skill("hide in shadows",random(80)+100);
    set_skill("appraisal",random(80)+100);
    set_skill("melee",random(80)+100);
    set_skill("compare",random(80)+100);
    set_skill("steal",random(80)+100);
    set_skill("stealth",random(80)+100);
    set_skill("consider lock",random(80)+100);
    set_skill("dance of daggers",random(80)+100);
    set_skill("detect trap",random(80)+100);
    set_skill("pick locks",random(80)+100);
    set_skill("back stab",random(80)+100);
    set_skill("disguise",random(80)+100);
    set_skill("peek",random(80)+100);
    set_skill("poison lore",random(80)+100);
    set_skill("stalk",random(80)+100);
    set_skill("invisibility art",random(80)+100);
    set_skill("offhand training",random(80)+100);
    set_skill("shadow",random(80)+100);
    set_skill("detect magic",random(80)+100);
    set_skill("reverse stroke",random(80)+100);
    set_skill("dual attack",random(80)+100);
    set_skill("martial arts",random(80)+100);
    set_skill("lock smithing",random(80)+100);

    new("/d/damned/virtual/broad-sword_6.weapon")->move(this_object());
    new("/d/damned/virtual/dagger_6.weapon")->move(this_object());
    force_me("wield sword in left hand");
    force_me("wield dagger in right hand");
    set_money("gold",random(350)+1);
    set_languages(({"common","drow"}));
    set_lang_prof("common",10);
    set_emotes(1,({
	"You sense something move past you.",
	"The shadows seem to swirl momentarily.",
      }),0);
    set_achats(1,({
	"The Rogue moves towards your blind spot.\n",
	"The Rogue vanishes briefly.\n",
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
	delayed_call("do_bstab",random(4)+5,TP);
	write_file(LOGS+"/rogue.log", TPQCN+
	  " pissed off a rogue at "+ctime(time())+
	  ".\n");
	return;
    }
}

void do_bstab(object tp)
{
    if(!tp || !present(tp, environment())) return;
    force_me("madlaugh");
    force_me("use back stab at "+(string)tp->query_name());
    return;
}
void do_warning(object tp)
{
    if(!tp || !present(tp, environment())) return;
    force_me("grin "+(string)tp->query_name());
    return;
}
