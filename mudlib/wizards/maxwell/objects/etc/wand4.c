//    Maxwell's Underground Mudlib
//           Dwarven Cigar

#include "/adm/include/std.h"
#include "/adm/include/under.h"
inherit OBJECT;

string short;
float *indexer,*r,*r2;
int lit;
int *numlist;
int n870,
 n871,
 n872,
 n873,
 n874,
 n875,
 n876,
 n877,
 n878,
 n879,
 n880,
 n881,n882,n883,n884,n885,n886,n887,n888,n889,n890,n891,n892,n893,n894,
 n895,n896,n897,
 n898,n899,n900,n901,n902,n903,n904,n905,n906,n907,n908,n909,n910,n911,
 n912,n913,n914,n915,n916,n917,n918,n919,n920,n921,n922,n923,n924,n925;

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
    add_action("number_test2","lab");
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
float num3,total,num96,num97,num98,num99,num100,num101,num102;
mixed output;
    n = 1;
    indexer = ({});
//Load Data File Into Array
    while(n != 0){
         num2 = read_file("/wizards/maxwell/objects/etc/nfile.c",n,1);
         if(sscanf(num2,"%d\n",entry) == 1){
           if(entry == 0.0){
             n = 0;
             write("Ending Process");
           }
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
               num = (random(40));
                output = 80.0 + num;
              output= floor(output);
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
                num = (random(40));
                 num3 = (380 + num);
              r[z] = num3; 
              z = z + 1;
             }
             output = 1/((1/r[0])+(1/r[1])+(1/r[2])+(1/r[3]));
             output= floor(output);
             write_file("/wizards/maxwell/objects/etc/output2.c",output+"\n");
             n = n + 1;
           }
           write("Done");
           return 1;
         }
         if(str == "3"){
           write("Section For 10 1k Ohm Unknown Resistors");
           rm(UNETC+"output3.c");
           n = 0;
           r = ({});
           r2 = ({});
           r = allocate(1001);
           total = 0;
           while(n < 1000){
             z = 0;
             while(z < 10){
              num = (random(40));
              num3 = (980.0 + num);
              r[z] = num3; 
              total = total + num3;
              z = z + 1;
             }
              output = (1/((1/(r[0]+0.0))+(1/(r[1]+0.0))+(1/(r[2]+0.0))+(1/(r[3]+0.0))
                   +(1/(r[4]+0.0))+(1/(r[5]+0.0))+(1/(r[6]+0.0))+(1/(r[7]+0.0))+(1/(r[8]+0.0))
                   +(1/(r[9]+0.0))));
             output= floor(output);
//             switch(output){
//               case 96: num96 = num96+1;break;
//               case 97: num97 = num97+1;break;
//               case 98: num98 = num98+1;break;
//               case 99: num99 = num99+1;break;
//               case 100: num100 = num100+1;break;
//               case 101: num101 = num101+1;break;
//               case 102: num102 = num102+1;break; 
//             }              
             r2 += ({output});
             write_file("/wizards/maxwell/objects/etc/output3.c",output+"\n");
             n = n + 1;
           }
           write("Done");
           write("Ouput is "+num96+" 96's "+num97+" 97's "+num98+" 98's "+num99+" 99's "
                +num100+" 100's "+num101+" 101's "+num102+" 102's");        
           return 1;
         }
         if(str == "4"){
           write("Section for 10 1k Ohm Known Resistors");
           rm(UNETC+"output4.c");
           r = ({});
           r = allocate(1001);
           n = 0;
           while(n < 1000){
              z = 0;          
              while(z < 10){
                num4 = random(sizeof(indexer));
                   r[z] = (indexer[num4]);
                z = z + 1;
              }                            
              output = (1/((1/(r[0]+0.0))+(1/(r[1]+0.0))+(1/(r[2]+0.0))+(1/(r[3]+0.0))
                   +(1/(r[4]+0.0))+(1/(r[5]+0.0))+(1/(r[6]+0.0))+(1/(r[7]+0.0))+(1/(r[8]+0.0))
                   +(1/(r[9]+0.0)))); 
              if(output > 90.0){
               output= floor(output);
               write_file(UNETC+"output4.c",output+"\n");
               n = n + 1;
              }
           }
           write("Done");
           return 1;
        }     
        else
         write("Invalid Number Choice. Possible picks are 1,2,3");
        return 1;      
    }
}
mixed return_index(){
    return indexer;
}
mixed return_array(int str){
  if(!str) 
    return r2;
  return member_array(str,r2);
}
mixed number_test2(){
float rr1,rr2,rr3,rr4,rr5,rr6,rr7,rr8,rr9;
float rr10,rr11,rr12,rr13,rrp;
float output2,series1,series2;
int z,loc,number,num3,temp;
mixed counter;

//First Series
    rr1=31350.0;
    rr2=950.0;
    rr3=950.0;
    rr4=950.0;
    rr5=950.0;
    rr6=95.0;
    rr7=9.5;
    rr8=9.5;
    rr9=9.5;
//Second Series
    rr10=3135.0;
    rr11=3135.0;
    rr12=95.0;
    rr13=9.5;
    write("Begining Calculations");    
    rm("/wizards/maxwell/objects/etc/output5.c");
    z=0;
    rrp=0;
    counter = allocate(1000);
    numlist = ({});
    temp = 0;
    while(z<1000){
      series1=(rr1+random(3300)+rr2+(random(100))+rr3+(random(100))+rr4+(random(100))+
            rr5+(random(100))+rr6+(random(10))+rr7+(random(5)/10)+rr8+(random(5)/10)+
            rr9+(random(5)/10));
      series2=(rr10+(random(330))+rr11+(random(330))+rr12+(random(10))+
            rr13+(random(5)/10));
      rrp = 30115.0+random(610);
//      output2= (18*(series1/(series1+series2+rrp)));
      output2= (18*(series1/(series1+series2+rrp)));
      output2=(output2*100);
      output2=floor(output2);
      num3=to_int(output2);
      numlist += ({num3});
      if(num3 > temp)
        temp = num3;
      if(num3 == 870)
         n870 =n870 +1;
      if(num3 == 871)
         n871 =n871 +1;
      if(num3 == 872)
         n872 =n872 +1;
      if(num3 == 873)
         n873 =n873 +1;
      if(num3 == 874)
         n874 =n874 +1;
      if(num3 == 875)
         n875 =n875 +1;
      if(num3 == 876)
         n876 =n876 +1;
      if(num3 == 877)
         n877 =n877 +1;
      if(num3 == 878)
         n878 =n878 +1;
      if(num3 == 879)
         n879 =n879 +1;
      if(num3 == 880)
         n880 =n880 +1;
      if(num3 == 881)
         n881 =n881 +1;
      if(num3 == 882)
         n882 =n882 +1;
      if(num3 == 883)
         n883 =n883 +1;
      if(num3 == 884)
         n884 =n884 +1;
      if(num3 == 885)
         n885 =n885 +1;
      if(num3 == 886)
         n886 =n886 +1;
      if(num3 == 887)
         n887 =n887 +1;
      if(num3 == 888)
         n888 =n888 +1;
      if(num3 == 889)
         n889 =n889 +1;
      if(num3 == 890)
         n890 =n890 +1;
      if(num3 == 891)
         n891 =n891 +1;
      if(num3 == 892)
         n892 =n892 +1;
      if(num3 == 893)
         n893 =n893 +1;
      if(num3 == 894)
         n894 =n894 +1;
      if(num3 == 895)
         n895 =n895 +1;
      if(num3 == 896)
         n896 =n896 +1;
      if(num3 == 897)
         n897 =n897 +1;
      if(num3 == 898)
         n898 =n898 +1;
      if(num3 == 899)
         n899 =n899 +1;
      if(num3 == 900)
         n900 =n900 +1;
      if(num3 == 901)
         n901 =n901 +1;
      if(num3 == 902)
         n902 =n902 +1;
      if(num3 == 903)
         n903 =n903 +1;
      if(num3 == 904)
         n904 =n904 +1;
      if(num3 == 905)
         n905 =n905 +1;
      if(num3 == 906)
         n908 =n907 +1;
     if(num3 == 908)
         n908 =n908 +1;
      if(num3 == 909)
         n909 =n909 +1;
      if(num3 == 910)
         n910 =n910 +1;
      if(num3 == 911)
         n911 =n911 +1;
      if(num3 == 912)
         n912 =n912 +1;
      if(num3 == 912)
         n912 =n912 +1;
      if(num3 == 913)
         n913 =n913 +1;
     if(num3 == 914)
         n914 =n914 +1;
      if(num3 == 915)
         n915 =n915 +1;
      if(num3 == 916)
         n916 =n916 +1;
      if(num3 == 917)
         n917 =n917 +1;
      if(num3 == 918)
         n918 =n918 +1;
      if(num3 == 919)
         n919 =n919 +1;
      if(num3 == 920)
         n920 =n920 +1;
     if(num3 == 921)
         n921 =n921 +1;
      if(num3 == 922)
         n922 =n922 +1;
      if(num3 == 923)
         n923 =n923 +1;
      if(num3 == 924)
         n924 =n924 +1;
      if(num3 == 925)
         n925 =n925 +1;

//      loc = member_array(num3,counter);
//      write("Value "+loc+" "+num3);
//      if(counter[num3] == 0){
//        counter[num3] = allocate(100);
//        counter[num3][0] = ({num3});
//      }
//      number = (counter[num3][1]);
//      counter[num3][1] = ({number+1});      
//      write("Value "+sizeof(counter));
      write_file(UNETC+"output5.c",num3+"\n");
      z=z+1;
    }
    write("Done."+n870+" "+n871+" "+n872+" "+n873+" "+n874+" "+n875+" "+
          n876+" "+n877+" "+n878+" "+n879+" "+n880+" "+n881+" "+n882+" "+
          n883+" "+n884+" "+n885+" "+n886+" "+n887+" "+n888+" "+n889+" "+
          n890+" "+n891+" "+n892+" "+n893+" "+n894+" "+n895+" "+n896+" "+
          n897+" "+n898+" "+n899+" "+n900+" "+n901+" "+n902+" "+n903+" "+
          n904+" "+n905+" "+n906+" "+n907+" "+n908+" "+n909+" "+n910+" "+
          n911+" "+n912+" "+n913+" "+n914+" "+n915+" "+n916+" "+n917+" "+
          n918+" "+n919+" "+n920+" "+n921+" "+n922+" "+n923+" "+n924+" "+
          n925);
    write("The sizeof numlist is "+sizeof(numlist));
    return numlist;
}
mixed return_array2(){
int *tarray;
    tarray = ({});
    tarray = sort_array(numlist,1);
    return tarray;
}
