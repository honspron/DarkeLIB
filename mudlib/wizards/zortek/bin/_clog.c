/* $Header: /mud/tkv/bin/system/RCS/_clog.c,v 1.1 1995/06/30 22:10:34 mudriver Exp $
 * $Log: _clog.c,v $
 * Revision 1.1  1995/06/30  22:10:34  mudriver
 * Initial revision
 *
 * Written by <unknown>
 * Fixed/Formatted by Zortek@TKV
 */

#include <std.h>
inherit         DAEMON;

private string *files,
               *coders;
object          tp;
string          me;

void 
create()
{
  ::create();
    coders = ({	});
    files = ({ });
}

int 
get_ref()
{
    return member_array(me, coders);
}
void 
push_coder(string file)
{
    coders += ({ me });
    files += ({ file });
}
void 
pop_coder(int ref)
{
    coders -= ({ coders[ref] });
    files -= ({ files[ref] });
}
int 
cmd_clog(string path)
{
    string          tmp;

    tp = this_player();
    me = (string) tp->query_name();

    if (!path)
	path = (string) tp->get_path();
    path = resolv_path((string) tp->get_path(), path);
    push_coder(path + "/CHANGE_LOG");
    write("Editing CHANGE_LOG for " + path + "\n");
    tp->edit("/tmp/changelog_" + me, "changelog_done",
	this_object());
    return 1;
}

void 
changelog_done()
{
    string          old,
                    msg,
                    infile,
                    clfile;
    string         *lines,
                   *newlines;
    int             count,
                    i,
                    j;

    infile = (string) tp->query_edit_filename();
    seteuid(geteuid(tp));
    msg = read_file(infile);
    if (msg == "" || !msg)
	return;
    clfile = files[get_ref()];
    old = read_file(clfile);
    rm(clfile);
    write_file(clfile, ctime(time()) + "   " +
	(string) tp->query_rname() + "   (" +
	(string) tp->query_true_name() + " at " +
	query_ip_name(tp) + ")\n\n\t* ");
    lines = explode(msg, " ");
    if (lines)
	for (i = 0; i < sizeof(lines); i++) {
	    newlines = explode(lines[i], "\n");
	    if (!newlines)
		newlines = ( {
		    lines[i]
		    }
	    );
	    for (j = 0; j < sizeof(newlines); j++) {
		if (newlines[j] == 0)
		    continue;
		if (count + strlen(newlines[j]) >= 65) {
		    write_file(clfile, "\n\t");
		    count = 0;
		}
		write_file(clfile, newlines[j] + " ");
		count += strlen(newlines[j]) + 1;
	    }
	}
    write_file(clfile, "\n\n");
    if (old)
	write_file(clfile, old);
    rm(infile);
    seteuid(getuid());
    write("Updated CHANGE_LOG.\n");
    pop_coder(get_ref());
}

void 
abort()
{
    write("CHANGE_LOG entry aborted!\n");
    return;
}

int 
help()
{
    write(@TEXT
Syntax:  clog [directory]

Updates the CHANGE_LOG file in either the current directory (if no directory
is specified) or the directory listed.  This command places you in the basic
editor (same as bulletin boards) and reformats your message to the standard
format for all CHANGE_LOGs when you are done.

PLEASE NOTE!!! CLOG all changes. (especially important ones...if you have to
ask your self whether or not to make an entry then you should by default.)

See also:elog, replog, todo.
TEXT
);
    return 1;
}
