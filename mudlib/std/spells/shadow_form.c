inherit "/std/spells/spell";



void create() {

    ::create();

    set_property("name","shadow form");

    set_property("skill","necromancy");

    set_property("casting time",39);

    set_property("base mp cost",67);

    set_property("dev cost", 52);

    set_property("fast dev cost", 149);

    set_property("spell level", 10);

    set_property("moon","luna");

    set_property("caster message","You cast shadow form.");

    set_property("target message","");

    set_property("observer message","$C casts shadow form.");

    set_property("spell type",({ }));

    set_property("no target", 1);

    set_property("duration", 180);

    return;

}



void info() {

message("help",

"This spell turns you into an immaterial shadow.  As such, you "

"may not attack and may not be attacked.  You may also "

"pass through doors unhindered.",

this_player());

}



void spell_func(object caster, object at, int power, string args, int flag) {

  object ob, ob2, *inv, *tmp;

  int i, bucks;

  string *currs;



  at = caster;

  if(at->shadow_form()) {

    message("info", "You "+

        " already have shadow from.", caster);

    remove();

    return;

  }

  if(flag) {

    message("info", "You accidentally turn all of "+(string)at->query_cap_name()+

        "'s possesions into shadows, never to return.", caster);

    message("info", "You accidentally turns all of your "+

        " possesions into shadows, never to return.", at);

    inv = all_inventory(at);

    i = sizeof(inv);

    while(i--) if(inv[i]->query_short() && !inv[i]->drop()) inv[i]->remove();

    remove();

    return;

  }

  inv = (object *)at->query_attackers();

  i = sizeof(inv);

  at->cease_all_attacks();

  while(i--) {

    tmp = (object *)inv[i]->query_attackers();

    while(tmp && member_array(at, tmp)) tmp -= ({ at });

    if(tmp) inv[i]->set_attackers(tmp);

    else inv[i]->set_attackers(({}));

  }

  inv = all_inventory(at);

  i = sizeof(inv);

  message("info", "You drop your whole inventory on the ground, including all of your money.", at);

  message("info", (string)at->query_cap_name()+

        " drops "+possessive(at)+ " inventory on the ground.",

        environment(at), ({ at }));

  while(i--) {

    if(inv[i]->drop()) continue;

    if(!inv[i]->query_short()) continue;

    inv[i]->move(environment(at));

  }

  currs = (string *)caster->query_currencies();

  if(currs && (i=sizeof(currs))) {

    ob = new("/std/obj/coins");

    while(i--) {

      bucks = (int)caster->query_money(currs[i]);

      if(bucks < 0) continue;

      ob->add_money(currs[i], bucks);

      caster->add_money(currs[i], -1*bucks);

    }

    ob->move(environment(caster));

  }

  ob = new("/std/spells/shadows/shadow_shadow");

  ob2 = new("/wizards/diewarzau/obj/misc/shadow_ob");

  ob->set_shadow_ob(ob2);

  ob2->move(at);

  ob->start_shadow(at, props["duration"], "%^BLUE%^%^BOLD%^Sheadow form wears off.");

  call_out("remove_ob", props["duration"], ob2);

  return;

}



void remove_ob(object what) {

  what->remove();

  remove();

  return;

}



