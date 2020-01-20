//    Maxwell's Underground Mudlib
//           Dwarven Cigar

#include "/adm/include/std.h"
#include "under.h"
inherit OBJECT;

string short;
mixed *indexer;
int lit;
create() {
    ::create();
   set_id(({"wand","magic wand","Maxwell's wand"}));
   set_name("Maxwell's Wand");
   short = "a long wooden wand";
   set_short(short);
   set("long", "The thin wand is has been passed down through the "
       "generations of a long line of wizards. It has several "
       "darke stains on its surface.");
   set_weight(5);
   set_value(0);
}
int get() { 
    write("You grab the wand and feel its energy!");
    return 1;
}
int init(){
    ::init();
    add_action("number_test","test");
    add_action("check_zone","zone");
}
int check_zone(string str){
int found,mortals,i;
object *targets;
string loc,*eloc;
     if(wizardp(this_player()) != 1){
       write("I don't think so little one..\n"
             "The wand winks out of existance!");
       this_object()->remove();
       return 1;
     }
     if(!str){
       write("Syntax is 'zone <wizard-name>'");
       return 1;
     }
     i = 1;
     found = 0;
     mortals = 0;
     targets = users();
     write("\nBegining Zone Scan...\n");
     while(i < sizeof(targets)){
       loc = file_name(environment(targets[i]));
       if(loc != 0)
       eloc = explode(loc,"/" );
       if(member_array(str,eloc) != -1){
         write(targets[i]->query_cap_name()+" ("+getuid(targets[i])+") "
         "located in zone at "+loc); 
         found = found + 1;
       }
       if(wizardp(targets[i]) != 1) mortals = mortals + 1;
       i = i + 1;
     }
     if(found > 0)
       write("\nNumber of players located in zone: "+found+" About "
       +found+"/"+mortals+" of total mortal population");
     else
       write("Unable to locate any players in that zone. Zone maybe "
             "void of life or your wizname maybe invalid.");
     return 1;
} 

int number_test(){
float num;
buffer buf;
int n,z;
string num2;
mixed entry;
      num = (random(100000)/100000.0);
      write("The number is "+num);
      buf = read_buffer("/wizards/maxwell/elem.c");
      write("The size is "+sizeof(buf));
    n = 1;
    z = 0;
    indexer = ({});
    while(n != 0){
        num2 = read_file("/wizards/maxwell/objects/etc/nfile.c",n,n);
         if(sscanf(num2,"%d/n",entry) == 1){
           if(entry == 0)
             n = 0;
           else {
          indexer += ({entry});
             n = n + 1;
             z = z + 1;
           }
       }
       else
         n = 0;
    }
    write("The size of the array is "+sizeof(indexer));
    return 1;
}
mixed return_array(){
    return indexer;
}
