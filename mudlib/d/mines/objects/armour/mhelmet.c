//           Maxwell's Underground Mud Library 
//            Dwarven Mining Helmet With Light        
inherit "/std/armour";

int fuel,burning,light_time,cfuel;
string short;
object shadow,helmet;

void init() {
     ::init();
    add_action("bud","light");    
    add_action("extinguish","extinguish");
    add_action("look_at","look");
    add_action("look_at","look at");
}

void create() {
    ::create();
    set_name("miner's helmet");
    set("id", ({ "helmet" }) );
    set("short", "A sturdy black miner's helmet");
    set("long", "The helmet is solid black. It has lots of scratches "
      "along the top where it has been bashed against the ceiling of the "
      "low mine tunnels.\nThere is a small bottle of fuel on the brim and "
      "a small wick. Above the fuel is a reflector for directing the "
      "light.");
    set_weight(100);
    set_value(150);
    set_type("helmet");
    set_limbs( ({ "head" }) );
    set_ac(15);
    set_wear("You strap the Miner's Helmet on your head." );
    fuel = 2000;
    short = ::query_short();
    helmet = this_object();
    cfuel = 2000;
}
int look_at(string str){
string *fuel_array,fuel_status;
int remaining_fuel;
       fuel_array = ({"bottle","fuel","fuel bottle"});
       if(member_array(str,fuel_array) != -1 ) {
         remaining_fuel = fuel;
         if(light_time == 0)
            fuel_status = "full.";
         else {
           cfuel -= (light_time - time());
           if(cfuel  >= 1500)
             fuel_status = "above 3/4.";
         
           else
            if(cfuel >= 1000)
              fuel_status = "above 1/2.";
           else
             if(cfuel >= 500)
               fuel_status = "above 1/4.";
           else
             fuel_status = "almost empty";
        }
        write("The fuel level in the bottle is "+fuel_status); 
        return 1;
        say(this_player()->query_cap_name()+" looks at the fuel bottle "
           "on "+this_player()->query_possessive()+" Miner's helmet.");
     }
     if(str == "wick"){
        write("The stubby black wick is drenched in fuel.");
        return 1;
     }
}
int bud(string str){
   if(str == "wick"){
      if(burning == 0){
        say(this_player()->query_cap_name()+" lights the "
          "wick on "+this_player()->query_possessive()+" Miner's "
          "helmet.\n");
        write("You light the wick on the Miner's Helmet. The flame "
           "quickly burns bright and the reflector radiates the light "
           "into the room.");
        light_time = time();
        shadow = new("/std/spells/shadows/light_shad");
        shadow->set_light(2);
        shadow->start_shadow(environment());
        delayed_call("burn_out",fuel);
        burning = 2;
        set_short(short+" (burning)");
        return 1;        
      }
      if(burning == 2){
        write("The helmet wick is already lit.");
        return 1;
      }
      else
        write("The helmet has run out of fuel.");
      return 1;
 }
 write("Light what?");
 return 1;
}
int burn_out(){
    if(shadow) shadow->external_destruct(shadow);
    burning = 3;
    set_short(short+" (out of fuel)");
    if( living(environment(helmet)) ) 
       tell_object(environment(), "Your helmet light " 
       "burns out.\n");
    return 1;
}
int extinguish(string str){
   if(str == "wick"){
    if(burning == 2){
       write("You extinguish the wick.\n");
       say(this_player()->query_cap_name()+" extinguishes the "
         "wick on "+this_player()->query_possessive()+" Miner's "
         "helmet.\n",this_player());
       set_short(short);
       if(shadow) shadow->external_destruct(shadow);
       remove_delayed_call("burn_out");
       fuel -= (light_time - time());
       burning = 0;
       return 1;
    }
    write("The wick is not burning.\n");
    return 1;
   }
   write("Extinguish what?\n");
   return 1;
}
int remove(){
     if( burning == 2 && shadow)
      if(shadow) shadow->external_destruct(shadow);
     return ::remove();
}

