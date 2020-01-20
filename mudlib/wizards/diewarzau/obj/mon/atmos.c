inherit "/std/monster";



void create() {

    ::create();

   set_name("atmos");

   set_id( ({ "atmos" }) );

    set_short("High mortal Atmos, Lord of Praxis");

   set("aggressive", 0);

  set_level(26);

    set_long("Atmos is the lord of Praxis and all high mortals.\n");

   set_alignment(1000);

   set("race", "human");

   set_max_hp(400000);

    set_lang_prof("common", 10);

   set_hp(400000);

  set_body_type("human");

}



void catch_tell(string str) {

  if(sscanf(str, "Mikus%*s"))

	call_out("say_stuff", 3);

}



void say_stuff() {

  force_me("speak common");

  force_me("say Yo, Mike...Charles says that he met these dudes that "+

	"will trade him Dark boosters for Elvish Hunters!!!!!!!");

}

