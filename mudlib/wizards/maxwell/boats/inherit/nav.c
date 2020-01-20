

//Global Nav Variables
  string *destination;
  mixed grid;

//Navigation Code
 int nav_fun(string str){
 object room;
 string path,dir,H1,H2,H3;
 int Bx,By,Cx,Cy,Tx,Ty;
 float dist,angle,nangle;

  destination=({"akkad","mines","kuril","akkad-dock"});
  if(!str || ( member_array(str,destination) == -1) ){
    write("What target location? Possible ones are "+
          implode(destination,","));
    return 1;
  }
  switch(str){
   case "akkad":
    Tx = 15;
    Ty = 15;
   break;
   case "mines":
    Tx = 35;
    Ty = 13;
   break;
   case "kuril":
    Tx = 24;
    Ty = 32;
   break;
   case "akkad-dock":
    Tx = 24;
    Ty = 19;
   break;
  }
  room = environment(this_object());
//  write("Filename of room is "+file_name(room));
  path = file_name(room);
  if(sscanf(path,"/d/damned/virtual/room_%d_%d.world",Bx,By))
    write("The ship is currently at the cords "+Bx+" "+By);
  else {
    write("No cords for this room");
    return 1;
  }
  Cx = (Bx-Tx);
  Cy = (By-Ty);
  dist = sqrt(pow(Cx,2)+pow(Cy,2));
  angle = (asin((By-Ty)/dist)*(180/(3.14)));
  if(Tx > Bx){
     nangle = 90 - angle;
  }
  if(Tx < Bx){
     nangle = 270 + angle;
  } 
  if(Bx == Tx && By < Ty)
     nangle = 180;
  if(nangle > 337.5 || nangle < 22.5)
    dir = "north";
  if(nangle > 22.5 && nangle < 67.5)
    dir = "northeast";
  if(nangle > 67.5 && nangle < 112.5)
    dir = "east";
  if(nangle > 112.5 && nangle < 157.5)
   dir = "southeast";
  if(nangle > 157.5 && nangle < 202.5)
   dir = "south";
  if(nangle > 202.5 && nangle < 247.5)
    dir = "southwest";
  if(nangle > 247.5 && nangle < 292.5)
    dir = "west";
  if(nangle > 292.5 && nangle < 337.5)
    dir = "northwest";  
  H1 = "N";
  H2 = "NE";
  H3 = "NW";
  write("Distance to Target is "+to_int(dist)+" clicks\n"
        "Angle to Target is "+to_int(nangle)+" degrees "+dir);
  return 1;
}

//Land Scanner Code

mixed scanner(){
int z,landtype,xline,yline,Bx,By,ypos;
object room,*targets,*inv;
string path;

  room = environment(this_object());
  path = file_name(room);
  grid = allocate(90);
//  write("The current room is "+path+" "+sizeof(all_inventory(room))+"\n");
  if(sscanf(path,"/d/damned/virtual/room_%d_%d.world",Bx,By)){  
    yline = (By-4);
    targets = ({});    
    while(yline <= (By+4)){
         ypos = 0;
         xline = (Bx-4);
         grid[yline] = allocate(15);
         while(ypos <= 9){ 
              if( (xline >=0 && xline <=40 )&&(yline >= 0 && yline <= 80)){
                room = find_object_or_load("/d/damned/virtual/room_"+
                       xline+"_"+yline+".world");
//                write("The value is "+room->query_short());
                inv = all_inventory(room);
                targets = filter_array(inv,"query_boat");
                landtype = (room->query_water());
//                write("X Y pos "+xline+" "+yline+" "+landtype);
                if(landtype == 1){
                  //Water Room
                  if(sizeof(targets) >= 1)
                    grid[yline][ypos] = "%^RED%^*";
                  else
                    grid[yline][ypos] = "%^BLUE%^#";
                }
                if(landtype == 0){
                   //Land Room
                  if(sizeof(targets) >= 1)
                    grid[yline][ypos] = "%^RED%^!";
                  else
                    grid[yline][ypos] = "%^GREEN%^L";
                }
                //Check to see if boat room
                if(yline == By && ypos == 4)
                    grid[yline][ypos] = "%^ORANGE%^B";                 
              }
              ypos = ypos + 1;
              xline = xline + 1;
         }      
         yline = yline + 1;
    }
    z = By - 4;
    write("\n        Surface  Scan\n");
    while(z <= (By+4) ){
//      write("The size is "+sizeof(grid));
      write("      "+grid[z][0]+" "+grid[z][1]+" "+grid[z][2]+" "+
            grid[z][3]+" "+grid[z][4]+" "+grid[z][5]+" "+grid[z][6]+
            " "+grid[z][7]+" "+grid[z][8]);
      z = z + 1;
    }
    write("\n %^RED%^* %^WHITE%^= Water Target "
          ": %^RED%^! %^WHITE%^= Land Target\n"
          " %^BLUE%^# %^WHITE%^= Water        "
          ": %^GREEN%^L %^WHITE%^= Land\n"
          " %^ORANGE%^B %^WHITE%^= Your current Position\n");
  }
  return 1;
}
