#define NO_LINK ({ "link", "delay", "store spell", "lesser elemental strike",\
  "elemental strike", "greater elemental strike", "summon", "transport", "distance harming", "harm", "teleport","power word, kill" })

inherit "/std/spells/spell";

void remove();
int clean_up();

void create() {
    ::create();
    set_property("name","link");
    set_property("skill","sorcery");
    set_property("casting time",2);
    set_property("base mp cost",10);
    set_property("dev cost", 101);
    set_property("fast dev cost", 285);
    set_property("spell level",16);
    set_property("moon","luna");
    set_property("caster message","");
    set_property("target message","");
    set_property("observer message","$C utters a few magical incantations.");
    set_property("spell type",({ }));
    set_property("no target", 1);
    set_property("prereq", "store spell");
    return;
}

void info() {
message("help",
"This is a very powerful spell which alllows you to prepare a "
"linked series of spells which may be cast later simultaneously!  "
"The amount of spells you can link together is equal to the power level "
"you cast the link spell at plus 1, i.e., power level 2 = 3 linked spells max.  "
"The casting time of this spell is equal to the sum of all the linked "
"spells' times.\n\n"
"To prepare a linked series of spells:\n"
"    cast *<pow> link at prepare <spell 1>, <spell 2>, <spell 3> etc.\n"
"Example:\n"
"  cast *2 link at prepare *3 fireball at $, *2 heal at diewarzau, *4 magic missile at bandit\n"
"\nTo cast the series of linked spells:\n"
"    cast *<pow> link at <target>\n"
"\nNOTES:\n"
"1.  If you use the $ sign when preparing your linked set of spells, as "
"above, it will be replaces with <target> at the time the linked set is cast.\n"
"2.  You must have enough magic points to cast ALL of the spells combined, or "
"none of them will go off.\n",
this_player());
}

int clean_up() {
  mixed *info;
  int i;
  
  info = call_out_info();
  i = sizeof(info);
  while(i--)
    if(info[i][0] == this_object() && intp(info[i][2]) && info[i][2] > 0 &&
       info[i][1] != "do_spell" && info[i][1] != "cast_spells_2") {
      call_out("remove",info[i][2]+1);
      return 1;
    }
  remove();
  return 0;
}

void spell_func(object caster, object at, int power, string args, int flag) {
  string tmp, arg, *spells, file;
  string tmp1, tmp2;
  int i, time, pow, cost, max;
  mapping spell_set;
  object *obs;

  if(args && sscanf(args, "prepare %s", tmp)) {
    if(flag) {
      message("info", "You spell fails miserably, draining you completely.", caster);
      caster->add_mp(-1 * (int)caster->query_mp());
      remove();
      return;
    }
    caster->set("linked spells", 0);
    spells = explode(tmp, ",");
    i = sizeof(spells);
    if(i > (power + 1)) {
      message("info", "The maximum number of spells you can link is "+
              "equal to power + 1.", caster);
      remove();
      return;
    }
    message("info", "Preparing linked spells...\n", caster);
    spell_set = allocate_mapping(i+2);
    obs = allocate(i);
    cost = 0;
    time = 0;
    max = i;
    for(i=0;i<max;i++) {
      while(strlen(spells[i]) > 0 && spells[i][0] == ' ')
        spells[i] = replace_string(spells[i], " ", "", 1);
      if(sscanf(spells[i], "*%d %s at %s", pow, tmp, arg) != 3) {
        arg = 0;
        if(sscanf(spells[i], "*%d %s", pow, tmp) != 2) {
          message("info", "Incorrect usage: "+spells[i]+"\n"+
                  "Should be: *<power> <spell> at <target> [with <args>].",
                 caster);
          caster->add_mp(props["mp cost"]);
          remove();
          return;
        }
      }
      if(member_array(tmp, NO_LINK) >= 0) {
	message("info", "The spell '"+tmp+"' cannot be linked.",
		caster);
	caster->add_mp(props["mp cost"]);
	remove();
	return;
      }
      message("info", "%^YELLOW%^%^BOLD%^Adding spell '"+tmp+"'...%^RESET%^", caster);
      if(pow > (int)caster->query_spell_level(tmp)) {
        message("info", "You do not know this spell at level "+
                pow+".\nSpell failed.", caster);
        caster->add_mp(props["mp cost"]);
        remove();
        return;
      }
      file = "/std/spells/"+replace_string(tmp, " ", "_");
      if(!file_exists(file+".c")) {
        message("info", "BUG!  File for this spell not found!!!",
                caster);
        caster->add_mp(props["mp cost"]);
        remove();
        return;
      }
      obs[i] = new(file);
      time += (int)obs[i]->query_property("casting time");
      cost += (int)obs[i]->query_property("base mp cost") * pow;
      obs[i]->set_property("casting time", 100);
      caster->set_casting(0);
      obs[i]->begin_casting(caster, arg, pow);
      while(!undefinedp(spell_set[tmp]))
        tmp += "#";
      spells[i] = tmp;
      obs[i]->set_property("name", tmp);
      spell_set[tmp] = allocate_mapping(5);
      spell_set[tmp]["file"] = file;
      if(file->query_property("no target")) {
        spell_set[tmp]["target"] = 0;
        spell_set[tmp]["arg"] = arg;
      }
      else  if(arg && sscanf(arg, "%s with %s", tmp1, tmp2) == 2) {
        spell_set[tmp]["arg"] = tmp2;
        spell_set[tmp]["target"] = tmp1;
      } else {
        spell_set[tmp]["arg"] = 0;
        spell_set[tmp]["target"] = arg;
      }
      spell_set[tmp]["power"] = pow;
      if(caster->query_element() && obs[i]->query_property("elemental spell"))
        spell_set[tmp] += ([ "element" : (string)caster->query_element() ]);
    }
    spell_set["cost"] = cost;
    spell_set["casting time"] = time;
    caster->set("spell keys", spells);
    call_out("add_spells_2", 4, spell_set, obs, caster);
    return;
  }
  else {
    spell_set = (mapping)caster->query("linked spells");
    if(!spell_set || !mapp(spell_set)) {
      message("info", "You have not prepared a linked set of spells.",
              caster);
      remove();
      return;
    }
    message("info", "%^CYAN%^You begin the complex incantations "+
            "associated with a linked spell casting.", caster);
    message("info", "%^CYAN%^%^BOLD%^"+(string)caster->query_cap_name() +
            " begains uttering a complex series of incantations.",
            environment(caster), ({ caster }));
    caster->set_casting(this_object());
    caster->set_magic_round(spell_set["casting time"]);
    call_out("cast_spells_2", spell_set["casting time"], spell_set, caster, args, power);
    return;
  }
}

void remove() {
  remove_call_out("cast_spells_2");
  if(origin() == "call_other") destruct(this_object());
  ::remove();
}

void cast_spells_2(mapping spell_set, object caster, string arg, int power) {
  string *spells;
  object ob;
  int i, max;
  mapping val;

  spells = (string *)caster->query("spell keys");
  caster->set("spell keys", 0);
  caster->set("linked spells", 0);
  spells -= ({ "casting time" });
  spells -= ({ "cost" });
  caster->set_casting(0);
  if(spell_set["cost"] > (int)caster->query_mp()) {
    message("info", "You do not have enough mp to cast the spell set.",
            caster);
    remove();
    return;
  }
  message("info", "%^CYAN%^%^BOLD%^"+(string)caster->query_cap_name() +
          " casts a set of linked spells!", environment(caster),
          ({ caster }));
  i = sizeof(spells);
  if(i > (power +1)) {
    message("info", "%^CYAN%^Only the first "+
            sprintf("%d", power +1)+" of the spells go off.", caster);
    i = power + 1;
  }
  max = i;
  for(i=0;i<max;i++) {
    val = spell_set[spells[i]];
    ob = new(val["file"]);
    map_delete(val, "file");
    if(val["element"]) ob->set_element(val["element"]);
    map_delete(val, "element");
    val += ([ "caster" : caster ]);
    if(arg && val["target"])
      val["target"] = replace_string(val["target"], "$", arg);
    else if(arg && val["arg"])
      val["arg"] = replace_string(val["arg"], "$", arg);
    ob->do_spell(val);
  }
  remove();
  return;
}

int call_filter(mixed *item, object *obs) {
  if(member_array(item[0], obs) < 0) return 0;
  return 1;
}

void add_spells_2(mapping spell_set, object *obs, object caster) {
  mixed *info;
  mapping tmp;
  int i;

  info = filter_array(call_out_info(), "call_filter",
                      this_object(), obs);
  i = sizeof(info);
  while(i--) {
    if(info[i][0] && mapp(tmp = info[i][3]))
      spell_set[(string)((object)info[i][0])->query_property("name")] +=
        tmp;
    else {
      message("info", "%^CYAN%^Casting failed.", caster);
      caster->set("spell keys", 0);
      remove();
      return;
    }
  }
  i = sizeof(obs);
  while(i--) {
    if(!obs[i] || !objectp(obs[i])) {
      message("info", "%^CYAN%^Casting failed.", caster);
      caster->set("spell keys", 0);
      remove();
      return;
    }
    obs[i]->remove();
  }
  caster->set("linked spells", spell_set);
  message("info", "%^CYAN%^You have successfully prepared a linked "+
          "set of spells.\n"+
          sprintf("Total mp required: %d\nCasting time: %d\n",
                  spell_set["cost"], spell_set["casting time"]), caster);
  remove();
  return;
}
      
