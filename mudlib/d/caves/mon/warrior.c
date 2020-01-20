/*Drow Warrior coded by Cyric 04/20/99*/
#include <std.h>
#include "cyric.h"
inherit MONSTER;

void create()
{
    ::create();
    set_name("warrior");
    set("id",({"warrior","drow elf","drow","elf","fighter"}));
    set_level(random(5)+20);
    set_short("drow warrior");
    set("long",@LONG
Taller and larger than most drow, this warrior moves without a sound.  His eyes are strange, frenzied, violet windows to madness.  His white hair is pulled back into a pony tail, it resembles a white snake against his black skin.
LONG
    );
    set("race","drow-elf");
    set_gender("male");
    set_body_type("human");
    set_overall_ac(20);
    set_wielding_limbs(({"right hand","left hand"}));
    set_ac("right hand",5);
    set_melee_damage((["crushing":10,"cutting":5]));
    set_fingers(5);
    set_property("magic resistance",50);
    set_skill("blade",random(50)+80);
    set_skill("thrown",random(100)+120);
    set_skill("swimming",random(100)+120);
    set_skill("block",random(100)+120);
    set_skill("axe",random(100)+120);
    set_skill("knife",random(100)+120);
    set_skill("blunt",random(100)+120);
    set_skill("two handed blunt",random(100)+120);
    set_skill("two handed flail",random(100)+120);
    set_skill("two handed staff",random(100)+120);
    set_skill("trade lore",random(100)+120);
    set_skill("two handed blade",random(100)+120);
    set_skill("melee",random(100)+120);
    set_skill("body block",random(100)+120);
    set_skill("attack",random(100)+120);
    set_skill("two handed polearm",random(100)+120);
    set_skill("perception",random(100)+120);
    set_skill("consider",random(100)+120);
    set_skill("parry",random(100)+120);
    set_skill("flail",random(50)+80);
    set_skill("shield bash",random(100)+120);
    set_skill("compare",random(100)+120);
    set_skill("dodge",random(100)+120);
    set_skill("offhand training",random(100)+120);
    set_skill("whirlwind attack",random(100)+120);
    set_skill("sweep",random(100)+120);
    set_skill("combat awareness",random(100)+120);
    set_skill("reverse stroke",random(100)+120);
    set_skill("resist stun",random(100)+120);
    set_skill("dual attack",random(50)+80);
    set_skill("bash lock",random(100)+120);
    set_skill("focused attack",random(100)+120);
    set_skill("invisibility art",random(55)+30);
    set_class("fighter");

    new("/d/damned/virtual/broad-sword_6.weapon")->move(this_object());
    new("/d/damned/virtual/morning-star_6.weapon")->move(this_object());
    force_me("wield sword in left hand");
    force_me("wield star in right hand");
    set_money("gold",random(350)+1);
    set_languages(({"common","drow"}));
    set_lang_prof("common",10);
    set_emotes(1,({
	"You catch a glimpse of a Drow Warrior.",
      }),0);
    set_achats(1,({
	"The Warrior lashes out viciously.\n",
	"The Warrior moves with blinding speed.\n",
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
	delayed_call("do_whirl",0,TP);
	delayed_call("do_sweep",6,TP);
    write_file(LOGS+"/warrior.log", TPQCN+
      " pissed off a warrior at "+ctime(time())+
      ".\n");
	return;
    }
}

void do_whirl(object tp)
{
    if(!tp || !present(tp, environment())) return;
    force_me("growl "+(string)tp->query_name());
    force_me("use whirlwind attack");
    force_me("use focused attack");
    return;
}
void do_sweep(object tp)
{
    if(!tp || !present(tp, environment())) return;
    force_me("madlaugh");
    force_me("use sweep at "+(string)tp->query_name());
    return;
}
