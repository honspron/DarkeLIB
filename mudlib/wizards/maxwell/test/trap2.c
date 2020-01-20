//Underground Mudlib
//Exit Trap Code [TM]
//Coded for DarkeMud by Maxwell
//Copyright 3.20.1996

#include "/adm/include/std.h"

string value,trap_type,trapped_exit,trap_active;
object *safe_players;

//string set_value(string str){
int set_value(string str){
    value = str;
    return 1;
}
object search_exit2(string str){
int plevel;
string pclass;
     if(str == trapped_exit){
//       write("You search the "+trapped_exit+".");
       plevel = this_player()->query_skill("perception");
       pclass = this_player()->query_class();
       if( pclass != "thief" && plevel >= 75){
        write("You find a trap!\nIt is an "+trap_type+" type. You "
        "can avoid it now that you have seen it.");
        return this_player();
       }
       write("You find nothing odd.");
       return 0;
     }
}
string detect_disarm_trap2(string str){
int dislevel,dlevel;
    if(str == ("disarm trap at "+trapped_exit)){
      dislevel = this_player()->query_level("disarm trap");
      if(dislevel >0){
        write("You attempt to disarm the trap on the "+trapped_exit);
        if(dislevel >= 75 && trap_active == "armed" ){
          write("You disarm the "+trap_type+" trap!");
          say(this_player()->query_cap_name()+" disarms a hidden trap."); 
          return "disarmed";
        }
        if(trap_active == "disarmed") write("The trap has already been "
          "disarmed!");
        else write("You fail to disarm the trap.");
        return "disarmed";
      }
    }      
    if(str == ("detect trap at "+trapped_exit)){
      dlevel = this_player()->query_skill("detect trap");
      if(dlevel > 0){
        if(dlevel >= 80){
          write("You detect a trap on the exit.\n"
          "It is a "+trap_type+" trap.");
       say(this_player()->query_cap_name()+" detects a hidden trap."); 
          return "detected";
        }
        write("You don't detect any trap on the exit.");
        return "armed";
      }
    }
    return 0;
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
int punish2,safe,lmd,lcd,hit;
string limb;

    safe = member_array(this_player(),safe_players);
    if( safe != -1 || trap_active == "disarmed"){
      write("You avoid the "+trap_type+" trap("+trap_active+") and pass "
     "through safely.\n");
      return 1;
    }
    write("You spring a hidden trap.");
    limb = this_player()->return_target_limb();
    lmd =  this_player()->query_max_dam(limb);
    lcd =  this_player()->query_dm(limb);
    if( trap_type == "Explosive"){
      write("BOOOOM!!\nA large explosion throws you to the side! Your "
      +limb+" is damaged in the blast!\n");
      this_player()->do_damage(limb,((lmd-lcd)/(random(4)+2)) );
      say("BOOOOOM!!\n"+this_player()->query_cap_name()+" is thrown to " 
      "the side as a large shockwave from an explosive trap rips into "
      +this_player()->query_possessive()+" "+limb+"!");
    return 1;
    }
    if( trap_type == "Hot Gas"){
      write("WHOOOSSHH!!\nA jet of hot gas sprays out at you! Your "
      +limb+" is burned by it!\n");
      say("WHOOOSH!!\n"+this_player()->query_cap_name()+" is sprayed "
      "with hot gas from a trap!!\n"+this_player()->query_cap_name()+"'s "
      +limb+" is damaged in the spray!");
      this_player()->do_damage(limb,((lmd-lcd)/(random(4)+2)) );
      return 1;
    }
    if(trap_type == "Poison Dart"){
      write("A poison tipped dart flies out of at you!");
      hit = random(4);
      if(hit == 1){
        write("SWHISH!!\nThe dart flies by your "+limb+", barely "+
        "missing you!!\n");
       say("SWHISH!!\n"+this_player()->query_cap_name()+" barely avoids "
      "a poison dart ejected from a trap!!\n");
        return 1;
      }  
      write("THUNK!!\nThe dart imbeds itself in your "+limb+"!!\nThe "
      "poison burns as it flows inside your body!\n");
       say("SWHISH!!\n"+this_player()->query_cap_name()+" is struck in the "
      +limb+" by a poison dart ejected from a trap!!\n");
      this_player()->do_damage(limb,((lmd-lcd)/(random(4)+4)) );
      this_player()->add_poisoning(random(150));
      return 1;
    }
}   

