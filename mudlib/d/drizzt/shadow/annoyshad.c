inherit "/std/spells/shadows/shadow";

private object player;

string query_cap_name();

void sh_init( object ob )
{
    if( query_shadowing( ob ) )
    {
	tell_object( ob, "You are already shadowed by this." );
	call_out( "remove", 1 );
	return;
    } else tell_object( ob, "Now shadowing." );
    begin_shadow( ob );
    player = ob;
}

void remove_me()
{
    stop_shadow();
    remove();
}

void setenv( string s, mixed value )
{
    if( s == "TITLE" ) 
    {
	tell_object( player, this_player()->query_cap_name() +
	  " tried to change your title to " + value + "." );
	return;
    }
    return( player->setenv( s, value ) );
}

string query_title()
{
    string tmp, name, pos, race, age3, gender, classs, email;
    int hp, max_hp, mp, max_mp, age2;

    pos = possessive(player);
    race = this_player()->query_race();
    email = this_player()->query_email(); 
    classs = this_player()->query_class();
    hp = (int)this_player()->query_hp();
    max_hp = (int)this_player()->query_max_hp();
    mp = (int)this_player()->query_mp();
    max_mp = (int)this_player()->query_max_mp();    
    age2 = (int)this_player()->query_age();
      if(age2>86400) age3 = (age2/86400 + " Days");
      else if(age2>3600) age3 = (age2/3600) + " hours";
      else age3 = (age2/60) + " min";
     name = this_player()->query_cap_name();
    gender = this_player()->query_gender();
    switch( random( 10 ) )
    {
    case 0: tmp = "thinks " + name + " is the schiznit!"; break;
    case 1: tmp = "says: Drop the hammer!"; break;
    case 2: tmp = "is deleting "+name+" because he hates "+race+"'s";break; 
    case 3: tmp = "is ever changing. "; break;
    case 4: tmp = "is ignoring " + name;break;
    case 5: tmp = "thinks that "+name+" is too cheap to donate!";break;    
    case 6: tmp = "says: "+name+" has only played for "+age3;break;
    case 7: tmp = "... "+name+"'s email is "+email;break;
    case 8: tmp = "... "+name+" has hp("+hp+"/"+max_hp+
      "), mp("+mp+"/"+max_mp+")"; break;
  default: tmp = " Adventure, Excitement, a Jedi craves not these things!"; break;
    }
    return( query_cap_name() + " " + tmp );
}

string query_cap_name()
{
    string name, tmp;
    
    if(this_player())
    {
      name = this_player()->query_cap_name() + " oohh great one";
    } else {
    name = "Someone";
    }
    
    switch( random( 3 ) )
    {
    case 0: tmp = "DrIzZt"; break;
    default: tmp = "Drizz't Do'Urden"; break;
    }
    return tmp;
}

