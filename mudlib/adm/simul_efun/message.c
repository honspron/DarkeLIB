//   Allows message to be supplied with 0 as a third arg, in
//    which case it does nothing.  A compat. fixer.
//    Diewarzau 4/23/96

varargs void message(string type, string mess, mixed to, mixed exclude) {
  if(!to) return;
  efun::message(type, mess, to, exclude);
  return;
}
