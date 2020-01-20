//    A cute little janitor to sweep up the goo!



inherit "/std/monster";



int mop_count;

object puddle;



void set_puddle(object ob) {

  puddle = ob;

}



void create() {

  ::create();

  set_level(10);

  set_exp(1000000);

  set_name("janitor");

  set_id(({ "janitor" }));

  set("race", "high-man");

  set_body_type("human");

  set_short("A janitor is mopping up.");

  set_long("This short janitor is clad in a leather "+

    "apron, and mops up a small puddle of goo with a "+

    "mop.");

  mop_count = 3;

  call_out("mop_up", 8);

}



void mop_up() {

  string *exits;

  int i;

  

  if(!environment()) {

    remove();

    return;

  }

  message("info", "The janitor mops up the puddle.",

    environment());

  mop_count--;

  if(mop_count <= 0) {

    exits = (string *)environment()->query_exits();

    if(!exits || !(i=sizeof(exits))) {

      exits = ({ "out" });

      i = 1;

    }

    if(i == 1) i = 0;

    else i = random(i);

    message("info", "%^GREEN%^%^BOLD%^The janitor leaves "+

      exits[i], environment());

    if(puddle) puddle->remove();

    remove();

  }

  call_out("mop_up", 30);

  return;

}



