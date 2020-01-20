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
    add_action("number_test","resist");
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

int number_test(string str){
float num;
buffer buf;
int n,z,num4;
string num2;
mixed entry;
float *r,num3;
float output;
    n = 1;
    indexer = ({});
//Load Data File Into Array
    while(n != 0){
         num2 = read_file("/wizards/maxwell/objects/etc/nfile.c",n,n);
         if(sscanf(num2,"%d/n",entry) == 1){
           if(entry == 0)
             n = 0;
           else {
                indexer += ({entry});
                n = n + 1;
           }
         }
         else
           n = 0;
    }
    write("The size of the array is "+sizeof(indexer));
//Options Section of Code
    if(!str)
       return 1;
    else {
         write("Resistor Tester[tm]");
         if(str == "1"){
           rm(UNETC+"output1.c");
           write("Section For 1k Ohm Resistor");
           n = 0;
           while(n < 1000){
              num = (random(100000)/100000.0);
              if(random(2) == 1)
                output = 1000.0 + num;
              else
                output = 1000.0 - num;
              write_file(UNETC+"output1.c",(output+"\n"));
              n = n + 1;
           }         
           write("Done");
           return 1;
         }
         if(str == "2"){
           write("Section For 4 400 Ohm Resistors");
           rm(UNETC+"output2.c");
           n = 0;
           r = ({});
           r = allocate(1001);
           while(n < 1000){
             z = 0;
             while(z < 5){
               num = (random(100000)/100000.0);             
               if(random(2) == 1)
                 num3 = (400 + num);
               else
                 num3 = (400 - num);
              r[z] = num3; 
              z = z + 1;
             }
             output = 1/((1/r[0])+(1/r[1])+(1/r[2])+(1/r[3]));
             write_file("/wizards/maxwell/objects/etc/output2.c",output+"\n");
             n = n + 1;
           }
           write("Done");
           return 1;
         }
         if(str == "3"){
           write("Section for 10 1k Ohm Resistors");
           rm(UNETC+"output3.c");
           r = ({});
           r = allocate(1001);
           n = 0;
           while(n < 1000){
              z = 0;          
              while(z < 10){
                num4 = random(sizeof(indexer));
                num = (random(100000)/100000.0);             
                if(random(2) == 1)
                  output = (indexer[num3] + num);
                else
                  output = (indexer[num3] - num);
                  r[z] = output;
                z = z + 1;
              }                            
              output = (1/((1/r[0])+(1/r[1])+(1/r[2])+(1/r[3])+(1/r[4])
                    +(1/r[5])+(1/r[6])+(1/r[7])+(1/r[8])+(1/r[9])));
              write_file(UNETC+"output3.c",output+"\n");
              n = n + 1;
           }
           write("Done");
           return 1;
        }     
        else
         write("Invalid Number Choice. Possible picks are 1,2,3");
        return 1;      
    }
}
mixed return_array(){
    return indexer;
}
