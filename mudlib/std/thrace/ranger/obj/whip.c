#include <move.h>

inherit "/std/weapon";

int set_up(int pow);
object shad;
  
void create() {
    ::create();
    set("id", ({ "whip", "vine whip"}));
    set_name("whip");
    set("short", "vine whip");
    set("long","This whip is fashioned from the finest vines to be found in the land, it looks as if someone spent quite a bit of time working on this.");
    set_type("whip");
    set_property("no add quality", 1);
    set_wield((: call_other, this_object(), "wield_me" :));
    set_up(this_object()->query_property("pow"));

    return;
}

int set_up(int pow){
      set_property("pow", pow);
    switch(pow){
       case 1:
          set_short("%^GREEN%^%^BOLD%^A crappy vine whip%^RESET%^");
          break;   
       case 2:
          set_short("%^GREEN%^%^BOLD%^A decent vine whip%^RESET%^");
          break;
       case 3:
          set_short("%^GREEN%^%^BOLD%^A good vine whip%^RESET%^");
          break;
       case 4:
          set_short("%^GREEN%^%^BOLD%^A superb vine whip%^RESET%^");
          break;
       case 5:
          set_short("%^GREEN%^%^BOLD%^A great vine whip%^RESET%^");
          break;
       case 6:
          set_short("%^GREEN%^%^BOLD%^An AWESOME vine whip%^RESET%^");
          break;
    }
    set_wc(pow*7, "impact");
    set_wc(pow, "cutting");
    set_quality(pow);
    set_decay_rate(pow*250);
    set_verb("crack");
}

int wield_me(){
      add_action("whip_person", "whip");
      return 1;
}

int whip_person(string person){
    object ob, ob2;
    int tparry, tdodge, tdex, tskill;
    int wwhip, wdex;
    ob=find_player(person);
    if(!present(ob,environment(this_object()->query_wielded()))) {
       message("info", "You can't whip people who aren't here",this_object()->query_wielded());
       return 1;
    }
    tparry=ob->query_skill("parry");
    tdodge=ob->query_skill("dodge");
    tdex=ob->query_stats("dexterity");
    wwhip=this_object()->query_wielded()->query_skill("whip");
    wdex=this_object()->query_wielded()->query_stats("dexterity");
    ob2=this_object()->query_wielded();
    if(tparry>wwhip){
      message("info", ob->query_cap_name()+" parries your attack with ease.",ob2);
      message("info", "You parry "+ob2->query_cap_name()+" whip attack with ease.",ob);
      return 1;
    }
    if(tdodge>wwhip){
      message("info", ob->query_cap_name()+" dodges your attack with ease.",ob2);
      message("info", "You dodge "+ob2->query_cap_name()+" whip attack with ease.",ob);
      return 1;
    }
    if(tdodge>tparry){
      tskill=tdodge;
    }
    if(tparry>tdodge){
       tskill=tparry;
    }
    if((wwhip+wdex)>(tskill+tdex)){
       ob->do_damage((string)ob->return_target_limb(), 2 * (random(30)+1));
       do_critical(ob2, ob, "impact B");
       do_critical(ob2, ob, "stun C");
       message("info", "You crack "+ob->query_cap_name()+" with your whip!",ob2);
       message("info", ob2->query_cap_name()+" cracks you with a whip!",ob);
       ob->kill_ob(ob2, 0);
       return 1;
    }
    if((wwhip+wdex)<(tskill+tdex)){
       message("info", "You try to whip "+ob->query_cap_name()+" but miss!",ob2);
       message("info", ob2->query_cap_name()+" tries to whip you but misses",ob);
       ob->kill_ob(ob2, 0);
       return 1;
    }
      
}

