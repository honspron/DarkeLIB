#include <std.h>

#define MY_INV ({ "glove", "paperweight", "pen", "pocketknife", "figure" })

#define MAX_INV 25



inherit "/std/vault";



void clone_once();



void create() {

  ::create();

  set("short","Inn gift shop storage");

  set("long","Ditto for the short!");

  set_property("light", 2);

  set_property("indoors", 1);

  set_property("no scry", 1);

  set_property("no summon", 1);

  set_property("no teleport", 1);

  set_property("storage room", 1);

  set_exits( ([]) );

  return;

}



int my_inv_filter(object item) {

  int i;



  i = sizeof(MY_INV);

  while(i--) if(item->id(MY_INV[i])) return 1;

  return 0;

}



void remove_all(object *inv) {

  int i;





  i = sizeof(inv);

  while(i--) if(inv[i] && !living(inv[i]) && environment(inv[i]) ==

this_object()) inv[i]->remove();

  return;

}



void reset() {

  object bob, *inv;

  int i;



  ::reset();

  seteuid(getuid());

  inv = filter_array(all_inventory(this_object()), "my_inv_filter",

      this_object());

  call_out("remove_all", 5, inv);

  inv = all_inventory(this_object());

  if(sizeof(inv) > MAX_INV) {

    for(i=MAX_INV-1;i<sizeof(inv);i++) inv[i]->remove();

  }

  bob = present("shopkeeper", 

                find_object_or_load("/d/damned/inn/gift_shop"));



  if(bob) {

    message("info", "Fred says in Common: Wait a second.  I've got a new "+

            "shipment coming in...", environment(bob));

    call_out("finish_deliver", 4, bob);

  }

  clone_once();

  return;

}



void finish_deliver(object bob) {

  if(bob)

    message("info", "Fred says in Common: It's all here now.",

            environment(bob));

  return;

}



void clone_once() {

  object ob;

  int i;



  seteuid(getuid());

  for(i=1; i <= 10; i++) {

    ob = new("/wizards/tailwind/giftshop/wiz_fig");

    ob->move(this_object());

    ob = new("/wizards/tailwind/giftshop/pen");

    ob->move(this_object());

    ob = new("/wizards/tailwind/giftshop/paperweight");

    ob->move(this_object());

    if(i <= 7) {

      ob = new("/wizards/tailwind/giftshop/thrace_fig");

      ob->move(this_object());

      ob = new("/wizards/tailwind/giftshop/glove");

      ob->move(this_object());

    }

    if(i <= 5) {

      ob = new("/wizards/tailwind/giftshop/traer_fig");

      ob->move(this_object());

      ob = new("/wizards/tailwind/giftshop/pocketknife");

      ob->move(this_object());

    }

  }

  return;

}