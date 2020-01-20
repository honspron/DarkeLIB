#include <move.h>

#include <std.h>



inherit "/std/armour";

inherit AUTOLOAD;



void create() {

  ::create();

  set("id", ({ "circlet", }));

  set_name("circlet");

  set("short", "Circlet of the Great Oracle");

  set("long",@TEXT

This is a thin silver band, several inches wide that wraps about and

across the forehead.  In the center is a stunningly beautiful star

saphire that seems to radiate an unearthly light.

TEXT

);

  set_limbs(({"head"}));

  set_weight(25);



  set_ac(25);

  set_ac(50, "psychic");

  set_ac(50, "constriction");

  

  set_wear((: call_other,this_object(), "make_me_gm" :));

  set_enh_critical(-1);

  set_value(50000);

  return;

}



int query_always_keep() { return 1; }



int make_me_gm() {

  object ob;

  int x;

  

  seteuid(getuid());

  x = this_player()->query_level();

  if((string)this_player()->query_name() != "guildmaster")

  if((string)this_player()->query_class() != "seer" ||

     random(100) + x < 50) {

    write(@TEXT%^MAGENTA%^

Your mind is flooded with an overflow of images, thoughts, and

the conversations of millions of people...As your ears begin to

bleed you feel the circlet begin to constrict and tighten about

your head...splitting pain is the last thing you feel as your

skull begins to crack, your brain begins to simmer, and your

body disolves into a vaporous mist. 

TEXT

);

    say("%^MAGENTA%^"+this_player()->query_cap_name()+" screams in agony as "+

    this_player()->query_objective()+" places a silvery circlet upon "+

    this_player()->query_possessive()+" head.  Blood begins to spurt from "+

    this_player()->query_possessive()+" ears and his skull begins to crack "+

    "as the circlet beging to crush bone and brain matter.  As the last moans "+

    "and wimperings can be heard "+this_player()->query_cap_name()+"'s body "+

    "begins to vaporize.");

  

    message("shout", "The Demiurge shouts:  "+

        this_player()->query_cap_name()+

        " foolishly and arrogantly felt "+

        this_player()->query_objective()+

        " was worthy to be the Great Oracle!  "+

        capitalize(this_player()->query_possessive())+

        " death was far from swift or painless.", users());

    this_player()->set_property("no corpse",1);

    this_player()->die();

    this_object()->remove();

    return;

  }

  ob= new("d/damned/guilds/seer/items/seer_obj");

  ob->make_me_master(this_player());

  return 1;

}

