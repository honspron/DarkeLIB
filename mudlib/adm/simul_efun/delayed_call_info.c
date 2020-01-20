//    A replacement for call_out_info.  Uses a single daemon
//    to manage delayed function calls.  Hopefully will
//    reduce overhead for some applications.

#define DELAY_D "/adm/daemon/delayed_function_d"

mixed *delayed_call_info() {
  return (mixed *)DELAY_D->delayed_function_info();
}

