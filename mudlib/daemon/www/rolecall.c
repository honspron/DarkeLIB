/*
 *   ROLECALL - GENERATES A WWW LIST OF ALL USERS IN THE  *
 *   MUD WHO ARE NOT INVISIBLE.                           *
 *   CODED ON: 9/23/96 FOR DARKEMUD LIBRARY               *
 *   CODED BY: SHADOWRAITH                                *
 */

#include "/adm/include/daemons.h"

#define FILE_NAME "/www/wholist.html"

void html();             //HTML Function
int body(object *list);  //WHO Filter
int sort_by_level (object alpha, object bravo);  //SORT (From /cmds/mortal/_who.c)

object *everyone;        //List of all Users

void create() {
   seteuid( "www" );
	html();
	return;
}

void html() {
   int tot, nrbt;
	
   everyone = users();
   everyone = sort_array(everyone,"sort_by_level",this_object());
   nrbt = (int)EVENTS_D->query_next_reboot() - time();
	
   rm(FILE_NAME);
   write_file(FILE_NAME,"<HEAD>\n");
   write_file(FILE_NAME,"<TITLE>Players in Darke Domain</TITLE>\n");
   write_file(FILE_NAME,"</HEAD>\n\n");
   write_file(FILE_NAME,"<BODY BGCOLOR = \"#000000\" "+
      "LINK = \"#7000E0\" TEXT = \"#FF0000\" VLINK = \"#900000\" "+
      "ALINK = \"#C000FF\" >\n"); 
   write_file(FILE_NAME,"<CENTER>"+
      "</CENTER><H5><CENTER><FONT SIZE=+2>P</FONT>LAYERS <FONT SIZE"+
      " = +2>L</FONT>IVING AND <FONT SIZE = +2>D</FONT>YING IN "+
      "<FONT SIZE = +2>D</FONT>ARKE <FONT SIZE = +2>D</FONT>OMAIN"+
      "</CENTER><CENTER>( "+ctime(time())+ " )</H5><HR SIZE = 4>\n"+
      "** Hidden and Invisible Players are Not Shown **\n" );
   write_file(FILE_NAME,"</CENTER>\n<BODY>\n");
   write_file(FILE_NAME,"<UL>\n");
   tot = body(everyone);
   write_file(FILE_NAME,"</UL>\n<hr>\n");
   write_file(FILE_NAME,"<CENTER>Total of " + tot +
      " players.</CENTER><CENTER>[Next Reboot " + 
      ctime( time() + nrbt ) + "]</CENTER>\n");
   write_file(FILE_NAME,"</BODY>");
   return;
   }

int body (object *list) {
   int i, j, tot;
   string players, highms, wizards, arches, legends;
   players="";highms="";wizards="";arches="";legends="";

   i = sizeof(list);

   while (j < i) {
      if ( !list[j]->query_invis() && !hiddenp(list[j]) ) {
         if( archp(list[j]) ) 
            arches += "<LI>"+ eliminate_colour( list[j]->query_cap_name() ) + "\n";
         else if ( wizardp(list[j]) )
            wizards += "<LI>"+ eliminate_colour( list[j]->query_cap_name() ) + "\n";
         else if ( legendp(list[j]) )
            legends += "<LI>"+ eliminate_colour( list[j]->query_cap_name() )+ "\n";
         else if ( high_mortalp(list[j]) )
            highms += "<LI>"+ eliminate_colour( list[j]->query_cap_name() )+ "\n";
         else
            players += "<LI>"+ eliminate_colour( list[j]->query_cap_name() )+ "\n";
         tot += 1;
         }
      j++;
      }
   write_file(FILE_NAME, "<CENTER><H3>Arches</H3>\n" + arches + "\n</CENTER>");
   write_file(FILE_NAME, "<CENTER><H3>Wizards</H3>\n" + wizards + "\n</CENTER>");
   write_file(FILE_NAME, "<CENTER><H3>Legends</H3>\n" + legends + "\n</CENTER>");
   write_file(FILE_NAME, "<CENTER><H3>High Mortals</H3>\n" + highms + "\n</CENTER>");
   write_file(FILE_NAME, "<CENTER><H3>Mortals</H3>\n" + players + "\n</CENTER>");
   return tot;
}

int sort_by_level(object alpha, object beta) {
    int a, b;

    a = (int)alpha->query_level();
    b = (int)beta->query_level();
    if(!intp(a) || !intp(b)) return 0;
    if(a > b) return -1;
    if(b > a) return 1;
    a = wizardp(alpha);
    b = wizardp(beta);
    if(!alpha->query_name() && !beta->query_name())
	return 0;
    else if (!alpha->query_name()) return -1;
    else if(!beta->query_name()) return 1;
    if( (a && b) || (!a && !b) )
	return strcmp((string)alpha->query_name(), (string)beta->query_name());
    if(a) return 1;
    return -1;
}
