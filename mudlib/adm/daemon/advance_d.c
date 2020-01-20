//	/adm/daemon/advanced.c
//	from the Nightmare mudlib
//	the advancment daemon
//	created by Descartes of Borg 05 december 1992

#include <rooms.h>
#include <daemons.h>

#define MY_CLASS_HALL  "/d/standard/"+class+"_hall"

int get_exp(int lev);
int get_stat_cost(int x, int lev);
string previous_title(object tp);
varargs string get_new_title(object tp, int new_lev);

void create() { seteuid(getuid()); }

int get_exp(int lev) {
    int val;
    float fl_exp, fl_lev;
    
    fl_lev = (lev > 50)?50.0:to_float(lev);
    fl_exp = 7.79548 * pow(fl_lev,5.0) - 82.9248 * pow(fl_lev,4.0) +
      186.513 * pow(fl_lev,3.0) + 5660.54 * pow(fl_lev,2.0) -
	23101.2 * fl_lev + 28145.4;
    val = to_int(fl_exp);
    if(lev > 50) val += (lev - 50) * (val - get_exp(49));
    return val;
}


int get_stat_cost(int x, int lev) {
    int z;

    if(x==1) z = ((lev/10)*(lev/10)*10000) + (lev/3)*1000;
    else z = (lev/7)*(lev/7)*(lev*900);
    if(z < 1000) z = 1000;
    return z;
}

/*
varargs string get_new_title(object tp, int lev) {
    string gen, title, my_class;

    gen = (string)tp->query_gender();
    my_class = (string)tp->query_race();
    switch(lev) {
    default:
    case 1..3:
      title = "Novice";
      break;
    case 4..6:
      title = "Apprentice";
      break;
    case 7..10:
      title = "Journeyman";
      break;
    case 11..14:
      title = "Craftsman";
      break;
    case 15..17:
      title = "Artisan";
      break;
    case 18..19:
      title = "Expert";
      break;
    case 20..24:
      if(gen == "female")
        title = "Mistress";
      else
        title = "Master";
      break;
    case 25..30:
      title = "Adept";
      break;
    case 31..1000:
      title = "Grand "+((gen == "female")?"Lady":"Lord");
      break;
    }
    title += " $N the ";
    title += capitalize((string)tp->query_race());
    return title;
}
*/

varargs string get_new_title(object tp, int lev) {
    string gen, title, my_class, rank;

    gen = (string)tp->query_gender();
      my_class = lower_case((string)tp->query_class());
    switch(lev) {
    default:
    case 1..3:
      rank = "novice";
      break;
    case 4..6:
      rank = "apprentice";
      break;
    case 7..10:
      rank = "journeyman";
      break;
    case 11..14:
      rank = "craftsman";
      break;
    case 15..17:
      rank = "artisan";
      break;
    case 18..19:
      rank = "expert";
      break;
    case 20..24:
      rank = "master";
      break;
    case 25..30:
      rank = "adept";
      break;
    case 31..1000:
      rank = "grand";
      break;
    }
    if(file_size("/data/pretitles/"+my_class+"/"+rank+".pt") > -1){
        title = read_file( "/data/pretitles/"+my_class+"/"+rank+".pt", 1, 1 );
        title = replace_string(title, "\n", "");

    }
    else {
        title = capitalize(rank);
    }

    title += " $N the ";
    title += capitalize((string)tp->query_race());
    return title;
}

int advance(object who) {
    int dev_pts, spec_pts, new_lev, lev, exp;
    int adv,s_con,s_str,s_int,s_wis;
    int i;
int no_add_dev;
no_add_dev = who->query("no add dev");
if(no_add_dev >= 1) who->set("no add dev", 0);

    if(wizardp(who))
      return 0;
    lev = (int)who->query_level();
    new_lev = lev + 1;
    exp = (int)who->query_exp();
    dev_pts = 0;
    spec_pts = 0;
    while(get_exp(new_lev) < exp) {
      dev_pts += (int)who->query_property("dev point base") * new_lev * 2;
      if(new_lev > 10)
        spec_pts += new_lev/4;
      tell_object(who, "%^BOLD%^Congratulations, you have attained %^RESET%^%^BOLD%^%^RED%^level " +
	    new_lev + "%^RESET%^.");
#if 0
// commented out until exp/adv/dev mods are finalized
// this is where people are getting their exp bank reset
     if(who->query_property("old exp") && !who->query("no add dev")) {
	message("info", "You have forfeited all of the exp in your exp bank!",
		who);
	who->set_property("old exp", 0);
      }
#endif
        who->setenv("TITLE",get_new_title(who, new_lev));
      if(!undefinedp(who->query_property("hp advance")))
	adv = (int)who->query_property("hp advance");
      else adv = 10;
      s_con = (int)who->query_base_stats("constitution");
      message("info","Your unmodified constitution:%^CYAN%^  "+s_con+"%^RESET%^", who);
      s_str = (int)who->query_base_stats("strength");
      message("info","Your unmodified strength:%^CYAN%^  "+s_str+"%^RESET%^", who);
      adv += adv * (s_con - 50) / 100;
      if(adv < 0) adv = 0;
      who->set_max_hp((int)who->query_max_hp() + adv);
      adv = (s_con + s_str) / 6;
      for(i = 1; i <= 3; i++) {
	if(random(100) < adv) {
	  if(undefinedp(who->query_property("base hp regen")))
	    who->set_property("base hp regen", 3);
	  who->set_property("base hp regen", (int)who->query_property("base hp regen") + 1);
	}
      }
      if(!undefinedp(who->query_property("mp advance")))
        adv = (int)who->query_property("mp advance");
      else adv = 10;
      s_int = (int)who->query_base_stats("intelligence");
      message("info","Your unmodified intelligence:%^CYAN%^  "+s_int+"%^RESET%^", who);
      s_wis = (int)who->query_base_stats("wisdom");
      message("info","Your unmodified wisdom:%^CYAN%^  "+s_wis+"%^RESET%^", who);
      adv += adv * ( s_int - 50) / 100;
      if(adv < 0) adv = 0;
      who->set_max_mp((int)who->query_max_mp() + adv);
      adv = (s_wis + s_int) / 6;
      for(i = 1; i <= 3; i++) {
        if(random(100) < adv) {
          if(undefinedp(who->query_property("base mp regen")))
            who->set_property("base mp regen", 3);
          who->set_property("base mp regen", (int)who->query_property("base mp regen") + 1);
        }
      }
      if(arrange_string((string)who->query_race(), 4) == "were")
        who->set_skill("control change", (int)who->query_base_skill("control change")
			+ random(3)+1);
      new_lev++;
    }
    new_lev--;
    if(new_lev > lev) {
      who->add_dev(dev_pts);
      if(who->query_property("sp points"))
        spec_pts += (int)who->query_property("sp points");
      who->set_property("sp points", spec_pts);
    }
if(no_add_dev >= 1) who->set("no add dev", no_add_dev);
    return new_lev;
}

string previous_title(object tp) {
    string pre, post, str;

    str = (string)tp->getenv("TITLE");
    if(sscanf(str, "%s $N %s", pre, post) != 2) {
	sscanf(str, "$N %s", post);
    }
    return post;
}

void log_death(string str) { log_file("kills", str); }





