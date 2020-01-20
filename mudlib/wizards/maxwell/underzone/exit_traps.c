//Underground Mudlib
//Exit Trap Code [TM]
//Coded for DarkeMud by Maxwell
//Copyright 3.20.1996
//Includes code from DarkeMud's Skills Detect/Disarm Traps
#include "/adm/include/std.h"
#include "under.h"

inherit ROOM;
 

string value,trap_type,trapped_exit,trap_active,sister_trap;
string party_name;
object *party_members;
object *safe_players,player;
int trap_level;

int init() {
    ::init();

    add_action("check_exit","look at"); 
    add_action("check_exit","look");
    set_search(trapped_exit,(: call_other,this_object(),"search_exit" :));      
    add_action("detect_disarm_trap","use");
  
}

int search_exit(string str){
int plevel,i;
string pclass;
     if(str == trapped_exit){
       plevel = this_player()->query_skill("perception");
       pclass = this_player()->query_class();
       if( this_player()->query_skill("detect trap") == 0){
         if(random(100) <  (plevel - (trap_level-6)*4) ||
           member_array(this_player(),safe_players) != -1 ) {
           write("You have located a trap!");
           if(member_array(this_player(),safe_players) != -1 ||
             trap_active == "disarmed"){
             if(trap_active == "disarmed") 
               write("The trap has been disarmed.");                   
             else
               write("You have already found this trap.");               
             return 1;
          }
          write("You can avoid it now that you have seen it.");
          if(this_player()->query_party() != 0){
            i = 0; 
            party_name = (this_player()->query_party());
            party_members = 
            ("/adm/daemon/party_d"->query_party_members(party_name));            
            write("Your party has been warned about the trap location!");
            while(i < sizeof(party_members)){
              if(!party_members[i] || !interactive(party_members[i]))
                continue;
              safe_players += ({party_members[i]});
              if(sister_trap != 0)
              call_other(sister_trap,"sister_safe",party_members[i]);
              if(party_members[i] != this_player())
                tell_player(party_members[i],
                this_player()->query_cap_name()+" warns you about a trap "
                "near you. You can avoid it now."); 
              i = i + 1; 
            }            
          }
          else {
            safe_players += ({this_player()});            
            if(sister_trap != 0)
              call_other(sister_trap,"sister_safe",this_player());
          }               
          return 1;
         }
         else {
            if(random(100) < 50)
              write("You don't detect a trap on "+trapped_exit);               
            else {
              write("OOPS!!!  You spring the trap!");
              if(trap_active == "disarmed") {
                write("You luck out, the trap has been disarmed!");
                return 1;
              } 
              this_object()->punisher(this_player());
           }
           return 1;
         }
       }
       write("You find nothing odd.");
       return 0;
     }
}
int detect_disarm_trap(string str){
int roll,lvl,i;
string command,target,desc;

    player = this_player();    
   if( sscanf(str,"%s at %s",command,target) );
    {
    if(command == "disarm trap" || command == "detect trap"){ 
      if(this_player()->query_skill("disarm trap") <= 0){
         write("You don't know that skill.");
         return 1;
      }
       if(command == ("disarm trap") ){
         if(target == trapped_exit){
            roll = trap_level;
            if(this_object()->query("trap bonus") == trapped_exit)
                roll -= 1+random(6);
            write("You fiddle with the trap on "+trapped_exit);
            say(this_player()->query_cap_name()+" tinkers with "+
               trapped_exit);
            call_out("do_disarm",5,this_object());
            return 1;
         }
       }
       if(command == ("detect trap") ){
          lvl = (player->query_skill("disarm trap"));
          if(lvl <= 0){
             write("You don't know that skill.");
             return 1;
          }
          if(target == trapped_exit){
          say(this_player()->query_cap_name() +
              " inspects "+trapped_exit+" for traps.");
             if(random(100) <  (lvl - (trap_level-6)*4) ||
                member_array(this_player(),safe_players) != -1 ) {
                write("You have located a trap!");
                switch(trap_level) {
                  case 1..4:
                    desc = "poorly constucted";
                   break;
                 case 5..6:
                   desc = "pretty cheap";
                   break;
                 case 7..10:
                   desc = "fairly decent";
                   break;
                 case 11..15:
                   desc = "well-constructed";
                   break;
                 case 16..19:
                   desc = "very intimidating";
                   break;
                 case 20..10000:
                   desc = "almost impossible to defeat";
                   break;
                }
                if(member_array(this_player(),safe_players) != -1 ||
                   trap_active == "disarmed"){
                   if(trap_active == "disarmed") 
                      write("The trap has been disarmed.");                   
                   else
                      write("You have already detected this trap.");               
                   return 1;
                }
          write("It is a "+desc+" trap. You can avoid it now that "
               "you have seen it.");
          if(this_player()->query_party() != 0){
            i = 0; 
            party_name = (this_player()->query_party());
            party_members = 
            ("/adm/daemon/party_d"->query_party_members(party_name));            
            write("Your party has been warned about the trap location!");
            while(i < sizeof(party_members)){
              safe_players += ({party_members[i]});
              if(sister_trap != 0)
              call_other(sister_trap,"sister_safe",party_members[i]);
              if(party_members[i] != this_player())
                tell_player(party_members[i],
                this_player()->query_cap_name()+" warns you about a trap "
                "near you. You can avoid it now."); 
              i = i + 1;
            }            
          }
          else {
            safe_players += ({this_player()});            
            if(sister_trap != 0)
              call_other(sister_trap,"sister_safe",this_player());
          }               
          return 1;
         }
         else {
           if(random(100) < 50){
              write("You don't detect a trap on "+trapped_exit);
           }
           else {
              write("OOPS!!!  You spring the trap!");
                   if(trap_active == "disarmed") {
                     write("You luck out, the trap has been disarmed!");
                     return 1;
                   } 
                   this_object()->punisher(this_player());
              }
              return 1;
          }
        }
    }
   }
  }   
}        
void do_disarm() {
int lvl;
  lvl = (player->query_skill("disarm trap"));
  if(trap_active == "disarmed"){
     tell_object(player,"The trap is already disarmed!");
     return;
  }
  if(random(100) < ( lvl - (trap_level -3)* 4)  ) {   
    tell_object(player,"You disarm the trap!");    
    trap_active = "disarmed";
    safe_players += ({player});
      if(sister_trap != 0){
          call_other(sister_trap,"sister_update","disarmed");
          call_other(sister_trap,"sister_safe",player);
      }
    return;
  }  
  else {
    if(random(100) < 50) {
      tell_object(player,"You are unable to do any good with the trap.");
      player->set("trap bonus", 0);
      return;
    }
    tell_object(player,"OOPS!!!  You spring the trap!");
    tell_room(environment(player),player->query_cap_name()+
            " accidently springs the trap!",player);
    this_object()->punisher(player);
    player->set("trap bonus", 0);
    return;
  }
}

int check_exit(string str){
string clevel;
int dlevel,plevel;
    if(str == trapped_exit){
      plevel = this_player()->query_skill("perception");
      clevel = this_player()->query_class();
      if(clevel == "thief"){
       dlevel = this_player()->query_skill("detect trap");
       if(dlevel >= 75)
        write("You notice something strange about the "+trapped_exit);
       else
        write("You notice nothing unusual.");
      }
      if(clevel != "thief"){
        if(plevel >= 75)
         write("You notice something strange about the "+trapped_exit);
       else
        write("You notice nothing unusual.");
      }
      return 1;     
    }
}
int trap_check(){
int punish2,safe;

    safe = member_array(this_player(),safe_players);
    if( safe != -1 || trap_active == "disarmed"){
     if(safe == -1 && trap_active == "disarmed")
        return 1;  
     write("You avoid the "+trap_type+" trap("+trap_active+") and pass "
           "through safely.\n");
      return 1;
    }
  if( living(this_player()) && this_player()->is_player() ){
    write("You spring a hidden trap.");
    this_object()->punisher(this_player());
    }
    return 1;
}
int punisher(object target){
object here;
string limb,limb2;
int lmd,lcd,hit,dam;
    if(wizardp(target) == 1 && (target->query_name()) != "maxwell"){
       tell_object(target,"You pass through the trap without harm.\n");
       return 1;    
    }
    if(living(target) && (!target->is_player() && !target->is_pet() ))
       return 1;
    if(target->query_ghost())
       return 1;
    here = environment(target);
    limb = target->return_target_limb();
    limb2 = target->return_target_limb();
    lmd =  target->query_max_dam(limb);
    lcd =  target->query_dm(limb);   
   if( trap_type == "Explosive"){      
     if(random(100) < 25){
      while(limb == "head" || limb == "torso" || limb == limb2){
         limb = target->return_target_limb(); 
      }     
      tell_object(target,"BOOOOM!!\nA large explosion throws you to the " 
        "side! Your "+limb2+" is damaged and your "+limb+" is blown off "
        "in the blast!!\n");       
      target->do_damage(limb,lmd*2);
      target->check_on_limb(limb);
      tell_room(here,"BOOOOOM!!\n"+target->query_cap_name()+" is thrown to " 
      "the side as a large shockwave from an explosive trap rips into "
      +target->query_possessive()+" "+limb2+" and blows "+
       target->query_possessive()+" "+limb+" clean off in a "
      "bloody gush!!",target);
      dam = 1;
      while(dam == 1)
        dam = (random(4)+3);       
        target->do_damage(limb2,((lmd-lcd)/dam) );
        target->check_on_limb(limb2);
      return 1; 
       }
      tell_object(target,"BOOOOM!!\nA large explosion throws you to the " 
        "side! Your "+limb+" is damaged in the blast!\n");
      dam = 1;
      while(dam == 1)
           dam = (random(4)+3);
       
      target->do_damage(limb,((lmd-lcd)/dam) );
      target->check_on_limb(limb);
      tell_room(here,"BOOOOOM!!\n"+target->query_cap_name()+" is thrown to " 
      "the side as a large shockwave from an explosive trap rips into "
      +target->query_possessive()+" "+limb+"!",target);
    return 1;
    }
    if( trap_type == "Hot Gas"){
      tell_object(target,"WHOOOSSHH!!\nA jet of hot gas sprays out at you! "
        "Your "+limb+" is burned by it!\n");
      tell_room(here,"WHOOOSH!!\n"+target->query_cap_name()+" is "
        "sprayed with hot gas from a trap!!\n"+target->query_cap_name()+
        "'s "+limb+" is damaged in the spray!",target);
      dam = 1;
      while(dam == 1)
           dam = (random(4)+3);
      target->do_damage(limb,((lmd-lcd)/(dam)) );
      target->check_on_limb(limb);
      return 1;
    }
    if(trap_type == "Poison Dart"){
      tell_object(target,"A poison tipped dart flies out of at you!");
      hit = random(4);
      if(hit == 1){
        tell_object(target,"SWHISH!!\nThe dart flies by your "+limb+
           ", barely missing you!!\n");
       tell_room(here,"SWHISH!!\n"+target->query_cap_name()+
           " barely avoids a poison dart ejected from a trap!!\n",target);
        return 1;
      }  
      tell_object(target,"THUNK!!\nThe dart imbeds itself in your "
        +limb+"!!\nThe poison burns as it flows inside your body!\n");
      tell_room(here,"SWHISH!!\n"+target->query_cap_name()+" is struck "
         "in the "+limb+" by a poison dart ejected from a trap!!\n",target);
      dam = 1;
      while(dam == 1)
           dam = (random(4)+3);
      target->do_damage(limb,((lmd-lcd)/(dam)) );
      target->add_poisoning(random(150));
      target->check_on_limb(limb);
      return 1;
    }
}   

void sister_safe(object pobject){
     safe_players += ({pobject});
     return; 
}
void sister_update(string condition){
    if(condition == "active" || condition == "disarmed")
       trap_active = condition;
    return;
}
mixed query_safe_players(){
     return safe_players;
}
void disarm_trap(){
    trap_active = "disarmed";
    if(sister_trap != 0)
       call_other(sister_trap,"sister_update","disarmed");
}      
 
