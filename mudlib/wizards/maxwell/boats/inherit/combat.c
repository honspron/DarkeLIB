//Combat Code

//Global Combat Var 
  int right_packed,left_packed,rounds,armour;
  int *heading_deg;
  string heading,*acpt_heading;

int shell(string str){
float Xt,Yt,Xb,Yb,Angle,angle,R,Hd;
int z,hpos;
object target;
object *inven,room;
string S,path,type;

  if(!str){
    write("What do you want to fire?");
    return 1;
  }
  room = environment(this_object());
  path = file_name(room);
  if(sscanf(path,"/d/damned/virtual/room_%d_%d.world",Xb,Yb)){  
    if(sscanf(str,"%s %s %d %d",S,type,angle,R)){
       if(type != "cannon" || (S != "right" && S != "left")){
         write("Fire what?");
         return 1;
       }
       hpos = member_array(heading,acpt_heading);
       if(hpos == -1)
          Hd = 0;
       else          
          Hd = (heading_deg[hpos] );
       if(S == "right"){
         if(right_packed == 0){
            write("The right cannon is not packed!");
            return 1;
         }
         Angle = (Hd + angle)*((3.14)/180);
         right_packed = 0;
         write("The right angle is "+Angle);
       }
       else {
         if(left_packed == 0){
            write("The left cannon is not packed!");
            return 1;
         } 
         left_packed = 0;
         Angle = (Hd - angle)*((3.14)/180); 
         write("The left angle is "+Angle);
         S = "left";
       }
       Xt = Xb + (R*(sin(Angle)));
       Yt = Yb - (R*(cos(Angle)));
       write("Xt "+Xt+" Yt"+Yt+" Angle "+Angle+" Hd "+Hd+" "+angle);
       if(Yt >= (floor(Yt)+0.5))
         Yt = (floor(Yt)+1);
       else
         Yt = floor(Yt);
       if(Xt >= (floor(Xt)+0.5))
         Xt = (floor(Xt)+1);
       else
         Xt = floor(Xt);      
       write("The angle is "+Angle+" on the "+S+" side with a range of "
             +R+".");
       write("The shell will land at "+to_int(Xt)+" "+to_int(Yt));
       target = find_object("/d/damned/virtual/room_"+to_int(Xt)+
         "_"+to_int(Yt)+".world");
       tell_room(environment(this_object()),"The cannons on the ship "
         "explode into fire and flames as a cannon flies into the "
         "distance!");
       tell_object(this_object(),"The cannons explode into flames!");
       if(target){
         tell_room(target,
          "You hear a loud whistle and can see a dark object falling into "
          "the area around you!\n"
          "BOOOM!!!\n"
          "A huge explosion shakes the ground and sends debris flying!");
         write("Room found and target hit!");
         inven = all_inventory(target);
         z = 0;
         while( z < sizeof(inven) ){
           if(living(inven[z])){
             tell_object(inven[z],"The blast and flying debris rip "
               "into your "+inven[z]->return_limb()+"!!");
             tell_object(this_object(),inven[z]->query_cap_name()+" was "
               "hit in the blast!");
           }
           else {
             if(inven[z]->query_property("ship") == 1){
                inven[z]->shell_hit();
                write("Your cannon shot hit a boat!");
             }
           }
         z = z+1;
        }
     }
     else
      write("Room not found!");
   }
   else
    write("What cannon do you want to fire, how many degress and what "
          "range?");
  }
  else
    write("You can't fire the cannons from this room!");    
  return 1;
}
int shell_hit(){
    if(armour > 0){
       tell_object(this_object(),"The deck of the boat shakes "
       "as a large explosion blows debris in front of you!!");
       tell_room(environment(this_object()),"The ship is rocked "
       "to the side as a large explosion erupts on it!!");
       armour = armour - 1;
    }
     else {
       tell_object(this_object(),"The boat shutters under "
       "the force of another explosion! The hull is breaking "
       "up and sinking fast!");
       tell_room(environment(this_object()),"A large explosion "
       "sends a huge blast wave into the side of the boat! It "
       "takes on water and begins to sink!");
        this_object()->remove();
     }
    return 1;
}
int pack_cannon(string str){
    if(str == "right cannon" || str == "left cannon"){
      if(rounds <= 0){
         write("You do not have enough powder!");
         return 1;
      }
      write("You start to pack the "+str+".");
      call_out("end_pack",5,this_player(),this_object(),str); 
    }
    else
     write("Pack which cannon?");
    return 1;
}             
int end_pack(object ob,object ob2,string str){
   if(environment(ob) != ob2)
      return 1;
   if(str == "right cannon")
     right_packed = 1;
   if(str == "left cannon")
     left_packed = 1;
   rounds = rounds - 1;
   message("info","You finish packing the "+str,ob);   
   return 1;
} 
int check_rounds(string str){
   if(str == "rounds"){
     write("You have "+rounds+" left in the hopper.");
     return 1;
   }
}
mixed return_info(){
   write("The right/left pack values are "+right_packed+" "+left_packed);
   return 1;
}
