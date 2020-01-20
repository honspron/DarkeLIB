#include "/adm/include/std.h"
#include "/adm/include/move.h"
#include "/adm/include/daemons.h"
#include "/adm/include/bboard.h"
#include "/adm/include/security.h"
#include "/adm/include/dirs.h"

#define VOTE_DATA		"/d/damned/data/voteboard.o"
#define LEGAL_GUILDS		({ "arch-mage","chaotic-lord","cleric","elementalist","enchanter","fighter","necromancer","nightblade","paladin","sword-mage","thief","tinker","war-priest",})
#define LEGAL_GUILD_INIT	([ "arch-mage":0,"chaotic-lord":0,"cleric":0,"elementalist":0,"enchanter":0,"fighter":0,"necromancer":0,"nightblade":0,"paladin":0,"sword-mage":0,"thief":0,"tinker":0,"war-priest":0,])
#define VOTE_OK 		0
#define VOTE_ERROR		1
#define ALREADY_VOTED		2
#define BAD_VOTE		3

inherit OBJECT;

int max_posts;
string location, board_id;
string *edit_ok;
mapping title;

mapping votes;   // (["issue0":([who:1|0,]),"issue1":([who:1|0,]),])

int post_message(string str);

void init() {
    add_action("read_message", "read");
    add_action("remove_message", "remove");
    add_action("post_message", "propose");
    add_action("edit_message", "amend");
}

void create() {
  seteuid(getuid());
  votes = ([]);
  seteuid(UID_DAMNED_DATA);
  if(file_exists(VOTE_DATA))
    restore_object("/d/damned/data/voteboard");
  seteuid(getuid());
}

mapping query_all_votes() { return votes; }
mapping query_all_issues() { return votes; }
mapping query_votes(string issue) { return votes[issue]; }

int cast_vote(string issue, string guild, int vote) {
  string *issues,*guilds;
  int x;

  issues = keys(votes);
  if(member_array(issue, issues) == -1) return 0;
  guilds = keys(votes[issue]);
  if(member_array(guild, guilds) == -1) return 0;
  
  votes[issue][guild] = vote;
  
  seteuid(UID_DAMNED_DATA);
  save_object("/d/damned/data/voteboard");
  seteuid(getuid());
  return vote;
}
mapping query_issue(string issue) {
  return votes[issue];
}
int query_guild_vote(string issue, string guild) {
  return votes[issue][guild];
}

int post_message(string str) {
    if(!title) title = ([]);
    if(!str) {
	notify_fail("You must give a title for your post.\n");
	return 0;
    }
    if((int)BBOARD_D->get_num_posts(board_id) >= max_posts) {
	notify_fail("You will first have to remove a proposal -- Board Full!\n");
	return 0;
    }
    if(strlen(str) > 30) {
	notify_fail("Title cannot contain more than ~30 characters.\n");
	return 0;
    }
    if(title[this_player()]) write("Warning! You are already marked as posting!\n");
    str = ("Proposal "+(sizeof(votes))+":  "+str);
    title[this_player()] = str;
    write("You are adding:  "+str);
if (add_issue(str));
    this_player()->edit(BBOARD_EDIT+(string)this_player()->query_name(),
      "postit", this_object());
    return 1;
}

int add_issue(string str) {
  if(!votes) votes = ([]);
  votes[str] = LEGAL_GUILD_INIT;
  seteuid(UID_DAMNED_DATA);
  save_object("/d/damned/data/voteboard");
  seteuid(getuid());
  return 1;
}

varargs int postit() {
    int x;

    x = (int)BBOARD_D->post_message(board_id, title[this_player()]);
    if(x == BBOARD_OK) {
      write("Vote issue added.");
    }
    else if(x == EDIT_ABORT) {
      write("Edit aborted.\n");
      rm_issue(title[this_player()]);
    }
    else if(x == BAD_DATA) {
      write("Error in posting call.\n");
      rm_issue(title[this_player()]);
    }
    map_delete(title, this_player());
    seteuid(UID_DAMNED_DATA);
    save_object("/d/damned/data/voteboard");
    seteuid(getuid());
    return 1;
}

int reply_message(string str) {
    int number;

    if(!title) title = ([]);
    if(!str) {
	notify_fail("Reply to which message?\n");
	return 0;
    }
    if((int)BBOARD_D->get_num_posts(board_id) >= max_posts) {
	notify_fail("You will first have to remove a note.\n");
	return 0;
    }
    if(sscanf(str, "%d", number) != 1) {
	notify_fail("Invalid message number.\n");
	return 0;
    }
    number --;
    str = (string)BBOARD_D->get_title(board_id, number);
    str = "Re: "+str;
    return post_message(str);
}

int edit_message(string str) {
    int number, x;

    if(!title) title = ([]);
    if(!str) {
	notify_fail("You must specify which message you wish to edit.\n");
	return 0;
    }
    if(sscanf(str, "%d", number) != 1) {
	notify_fail("Invalid message number.\n");
	return 0;
    }
    number --;
    title[this_player()] = (string)BBOARD_D->get_title(board_id, number);
    x = (int)BBOARD_D->edit_note(board_id, number);
    if(x==BBOARD_OK) {
	write(title[this_player()]+": "+number+"\n");
	write("Editing post.\n");
	this_player()->edit(BBOARD_EDIT+(string)this_player()->query_name(), "edit_stop_ed", this_object());
	return 1;
    }
    else if(x == INVALID_MSG) write("Invalid message number.\n");
    else if(x == ILLEGAL_ACCESS) write("You may only edit your own posts.\n");
    else write("Error in editing post.\n");
    map_delete(title, this_player());
    return 1;
}
void edit_stop_ed() {
    int x;

    x = (int)BBOARD_D->post_message(board_id, title[this_player()]);
    if(x == BBOARD_OK) write("Message edited.\n");
    else write(title[this_player()] + " "+x+"\n");
    map_delete(title, this_player());
    rm((string)this_player()->query_edit_filename());
}


int remove_message(string str) {
    int number, x;

    if(!str) {
	notify_fail("You must specify which note you wish to remove!\n");
	return 0;
    }
    if(sscanf(str, "%d", number) != 1) {
        notify_fail("Invalid message number!\n");
	return 0;
    }
    number --;
    x = (int)BBOARD_D->remove_message(board_id, number);
    if(x==BBOARD_OK) write("Message "+(number+1)+" removed.\n");
    else if(x == INVALID_MSG) write("Invalid message number.\n");
    else if(x == ILLEGAL_ACCESS) write("You may only remove your own posts.\n");
    else write("Error "+x+" in removing post.\n");
    return 1;
}
int rm_issue(string str) {
  string *issues;
  int x;

  issues = keys(votes);
  if(member_array(str, issues) == -1) return 0;
  map_delete(votes, str);
  seteuid(UID_DAMNED_DATA);
  save_object("/d/damned/data/voteboard");
  seteuid(getuid());
  return 1;
}

int read_message(string str) {
    int number;
    mapping msg;
    string *lines;

    if(!str)
	number = 1 + (int)BBOARD_D->get_new_post(board_id, (string)this_player()->query_name());
    else if(sscanf(str, "%d", number) != 1) {
	notify_fail("Invalid message number.\n");
	return 0;
    }
    msg = (mapping)BBOARD_D->get_message(board_id, number-1);
    if(!msg) {
	notify_fail("Invalid message number.\n");
	return 0;
    }
    lines = ({ "Message "+number+" by "+capitalize(msg["owner"])+": "+msg["title"] });
    lines += explode(msg["message"], "\n");
    this_player()->more(lines);
    BBOARD_D->set_read(board_id, (string)this_player()->query_name(), number-1);
    return 1;
}

string query_long(string junk) {
    string borg;

    borg = ::query_long();
    borg += "Board commands: <post [title]>, <edit [#]>, <read [(#)]>, <answer [#]>,\n";
    borg += "and <remove [#]>.\n";
    borg += "There are "+(int)BBOARD_D->get_num_posts(board_id)+" messages posted.\n";
    borg += (string)BBOARD_D->display_board(board_id);
    return borg;
}

void set_board_id(string str) {
    if(board_id) return;
    board_id = str;
}

string query_board_id() { return board_id; }

void set_max_posts(int x) { max_posts = x; }

int query_max_posts() { return max_posts; }

void set_location(string file) {
    if(location) return;
    location = file;
    ::move(location);
}

int move(mixed dest) { return MOVE_NOT_ALLOWED; }

int get() { return 0; }

int drop() { return 1; }

void set_edit_ok(string *who) {
    if(!who) edit_ok = ({});
    else edit_ok = who;
}

string *query_edit_ok() {
    if(!edit_ok) return ({});
    return edit_ok;
}

void clean_up() { return; }
