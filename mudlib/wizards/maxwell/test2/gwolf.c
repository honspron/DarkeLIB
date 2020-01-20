//           Maxwell's Underground Mud Library
//                     Wolf Guard


#include "/adm/include/std.h"
#define WEAP "/wizards/maxwell/objects/weapons/"
inherit MONSTER;

create() {
    ::create();
   set_name("Mikarty");
   set_id( ({ "Mikarty","dwarf","guard","mikarty" }) );
   set_short("Mine guard Mikarty");
   set_level(17);
   set("long", "Mikarty is standing before you wearing the traditional "
    "uniform of a Dwarf security officer.");
   set_gender("male");
   set("race", "dwarf");
   set_alignment(0);
   set("aggressive", 0);
   set_body_type("dwarf");
   set_wielding_limbs( ({"right hand","left hand"}) );
   set_emotes(10,
     ({ "Mikarty glances around.",
     "Mikarty mumbles something about tresspassers in the other tunnel.",
     "Mikarty flexes a muscle.",
     }),0 );
    set_achats(50,
    ({ "Mikarty loses his balance.",
     "Mikarty grunts.",
     "Mikarty smiles wickedly.",
     }) );

    switch(random(2)){
      case 0:new(WEAP+"spear")->move(this_object());
             force_me("wield spear in right hand and left hand");
             break;
      case 1:new(WEAP+"handaxe")->move(this_object());
             force_me("wield axe in right hand");
             break;
    }
    switch(random(3)){
      case 0:new("d/damned/virtual/leather-jacket.armour")->
                 move(this_object());
             force_me("wear jacket");
             break;
      case 1:new("d/damned/virtual/leather-vest.armour")->
                 move(this_object());
             force_me("wear vest");
             break;
      case 2:new("d/damned/virtual/leather-pants.armour")->
                 move(this_object());
             force_me("wear pants");
             break;
    }



}
int attack(){
string here,name;
     here=file_name(environment(this_object()));
     tell_room(here,"Testing");
     tell_room(here,"the player is currently "+name);
     return 1;
}
int attack2(){
object mon,wep,wep1,who;
     who = this_player();
     mon=present("mikarty");
     mon->force_me("say You killed my best wolf!");
     mon->force_me("say I shall avenge his death!!");
     switch(random(2)){
      case 0:wep1=new("/wizards/maxwell/objects/weapons/dagger");
             wep1->move(mon);
             wep = wep1->query_name();
             break;
      case 1:wep1=new("/wizards/maxwell/objects/weapons/handaxe");
             wep1->move(mon);
             wep = wep1->query_name();
             break;
     }

     mon->force_me("throw "+wep+" at "+who->query_name());
     mon->force_me("kill "+who->query_name());

}
