#include <std.h>
#include "gen.h"

inherit OBJECT;

private static object shadow, shadow2;

void create()
{
    ::create();
    set_name( "gen" );
    set_id( ({ "gen", "a gentool", "gentool" }) );
    set_short( "a GenTool [" + GenVersion + "]" );
    set_long( "A small device which has several different colored buttons "
      "on it and an inscription labeled '" + GenVersion + "'.\n"
      "There is also a genhelp written into the side of the device.\n");
    set_weight( 0 );
    set_value( 0 );
}

int drop()
{
    write( "As you drop a GenTool, it disappears into several fragments." );
    tell_room( environment( this_player() ), "As " + this_player()
      ->query_cap_name() + " drops a GenTool, it disappears into several "
      "fragments.", ({ this_player() }) );
    call_out( "remove", 1 );
    return 0;
}

int get()
{
    return 1;
}

int give()
{
    write( "Your GenTool disappears into several fragments." );
    tell_room( environment( this_player() ), this_player()->query_cap_name() +
	       "'s GenTool disappears into several fragments.", ({ this_player() }) );
    call_out( "remove", 1 );
    return 0;
}

int put()
{
    write( "Your GenTool disappears into several fragments." );
    tell_room( environment( this_player() ), this_player()->query_cap_name() +
      "'s GenTool disappears into several fragments.", ({ this_player() }) );
    call_out( "remove", 1 );
    return 0;
}

void init()
{
    ::init();
    add_action( "help", "genhelp" );
    add_action( "shadme", "annoy" );
    add_action( "unshadme", "unannoy" );
    add_action( "shad311", "311me" );
    add_action( "un311shad", "un311");
    add_action( "shad", "annoyp" );
    add_action( "unshad", "unannoyp" );
    add_action( "color", "color" );
    add_action( "uncolor", "uncolor" );
    add_action( "word", "word" );
    add_action( "unword", "unword" );
}

int help(string s)
{
   write("Syntax: Color Curse - color & uncolor\n"
         "          Word Curse  - word & unword\n");
   if(wizardp(this_player())){
   write("        311 Shadow  - 311me & un311\n"
         "Player Annoy Shadow - annoy & unannoy\n");
   }
   return 1;
}

int shadme(string s)
{
    
    shadow = clone_object(AnnoyShadow);
    shadow->sh_init(this_player());
    return 1;
}

int unshadme(string s)
{
    object *obs;
    int i;
    obs = children(AnnoyShadow);
    i = sizeof(obs);
    while(i--) destruct(obs[i]);
    write("Annoyp Player Shadow is removed.");
    return 1;
}

int shad311(string s)
{
    shadow = clone_object(Shadow311);
    shadow->sh_init(this_player());
    return 1;
}

int un311shad(string s)
{
    object *obs;
    int i;
    obs = children(Shadow311);
    i = sizeof(obs);
    while(i--) destruct(obs[i]);
    write("311 Shadow is removed.");
    return 1;
}

int color(string s)
{
    shadow = clone_object(ColorCurse);
    shadow->sh_init(this_player());
    return 1;
}

int uncolor(string s)
{
    object *obs;
    int i;
    obs = children(ColorCurse);
    i = sizeof(obs);
    while(i--) destruct(obs[i]);
    write("Color Curse is removed.");
    return 1;
}

int word(string s)
{
    shadow = clone_object(WordCurse);
    shadow->sh_init(this_player());
    return 1;
}

int unword(string s)
{
    object *obs;
    int i;
    obs = children(WordCurse);
    i = sizeof(obs);
    while(i--) destruct(obs[i]);
    write("Word Curse is removed.");
    return 1;
}

int shad(string s)
{
    string filename;

    if(!s) return notify_fail( "Syntax: [shad <filename>\n" );
//    if(s[ 0..0 ] != "/" && s != "/") filename = (string)this_player()
//    	->get_path() + "/" + s; 
//    else filename = s;
    filename = "/wizards/"+(string)this_player()+"/shadow/"+s+".c";
    if(!file_exists(filename + ".c"))
	return notify_fail("You must choose a file that exists.\n");
    shadow2 = clone_object(MiscShadow);
    shadow2->sh_init(find_object(filename));
    write("Now shadowing "+filename+".");
    return 1;
}

int unshad(string s)
{
    object *obs;
    int i;

    obs = children(MiscShadow);
    i = sizeof(obs);
    while(i--) destruct(obs[i]);
    write("Unshadowed.");
    return 1;
}

