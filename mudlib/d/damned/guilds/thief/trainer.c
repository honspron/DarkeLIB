//           Maxwell's Underground Mud Library
//                Thief Trainer


#include <std.h>
#include <under.h>
inherit MONSTER;
inherit UNEQP;

object money;
create() {
    ::create();
   set_name("markus");
   set_id( ({ "markus","Markus","trainer" }) );
   set_short("Markus the multi-talented Trainer");
   set_level(20);
   set_max_hp(2500);
   set_hp(2500);
   set("long", "Markus is standing before you in all his glory.");
   set_gender("male");
   set("race", "dwarf");
   set_alignment(0);
   set_wielding_limbs( ({"right hand","left hand"}) );
   set_body_type("human");
   set_emotes(2,
      ({ "Markus flexes his muscle.",
      "Markus glances at you.",
      "Markus grins evilly",}),0 );
    set_achats(25,
      ({ "Markus loses his balance.",
      "Markus grunts.",
      "Markus smiles wickedly.",}) );
// Spell Code
    set_combat_chance(80);
    add_spell("heal","$(ME)"); 
    set_spell_level("heal",6);
    add_spell("harm","$A");
    set_spell_level("harm",6);
//    add_spell("internal flame","$A");
//    set_spell_level("internal flame",2); 
// Skills For Spells and Combat
    set_skill("conjuration",95);
    set_skill("prayer",95);
    set_skill("resist stun",115);
    set_skill("two handed blunt",115);
    set_skill("two handed polearm",115);
    set_skill("two handed flail",115);
    set_skill("two handed blade",115);
    set_skill("parry",115);
    set_skill("defense",115);
    set_skill("dodge",120);  
// Money Code
    money=new("std/obj/coins");
    money->set_money("gold",(random(50)+200));
    money->move(this_object());
//Equipment Code
    mob = this_object();
    wield_hand = "right hand";
//Misc
    set("aggressive",0 );
    set_languages( ({
        "dwarvish","elvish","middle-english","thri'krien","serra",
        "gnollish",
        "undead-tongue","yin","common","catfolk","pix","rachk" }) );
   
}

void die(object who) {

  ::die(who);
  return;

}
void directed_message(object from,string str) {
string req,skill;

     if( sscanf(str,"%s %s",req,skill) == 2){
       if(req == "train"){  
         if(from->query_class() != "thief" && !wizardp(from)){
           force_me("tell "+getuid(this_player())+" You're not a member "
             "of my guild!");
           return;
         }             
         force_me("tell "+getuid(this_player())+" You wanna train eh?");     
         if(!present(from)){
           force_me("tell "+getuid(this_player())+" Maybe you should "
              "come to the guild training room to learn fool!.");
           return;
         }            
         call_other(environment(this_object()),"train_skill",skill,from);
       }
      else if(req == "list" && skill == "skills"){
          if(from->query_class() != "thief" && !wizardp(from)){
           force_me("tell "+getuid(this_player())+" You're not a member "
             "of my guild!");
           return;
         }            
         force_me("tell "+getuid(this_player())+" Here are the "
           "skills I can train you in!");
         call_other(environment(this_object()),"list_skills","skills");
         }
      else
         force_me("tell "+getuid(this_player())+" eh? I'm here to help "
         "you train your skills! Not to listen to you babble!");
      return;
     }
     if(str == "train")
        force_me("tell "+getuid(this_player())+" What do you want to "
         "train?");
     else if(str == "help")
        force_me("tell "+getuid(this_player())+" I'm here to help you "
         "train new skills. Just tell me what you want to train or "
         "you can ask to see the list of skills.");
     else
        force_me("tell "+getuid(this_player())+" If you're totally "
         "clueless you could try asking me for help!");    
     return;
}

