# smsd

**Warning: unmaintained since 2003!**

smsd is client/server system which allows more users to send message to
mobile phones with the help of smssend utility (tested with version 3.1).
Messages are queued and delivered at all events, which is good if mobile
operator limits number or rate of messages sent from one IP address.

## Compilation of smsdwake utility

E.g. `gcc -o smsdwake smsdwake.c (other compiler than gcc can be used).`

## Server adaptation

Ability to recover from errors reported by operator (like exceeded rate of
sent messages) depends on smssend's definition files (*.sms). The shipped
code handles paegas.sms and t-mobile.sms. If you use other operator change
the smsd's source after the line starting with '# FIX: codes and timeouts'.

## Server run
```
./smsd <options>

Available options:

  --no-syslog
      Do not log errors to syslog, but terminate.
  --pid-file
      Location of pid file (def. /var/run/smsd.pid).
  --spool-dir
      Message queue directory (def. /var/spool/smsd/).
```
It is necessary to ensure that both server and client can write to message
queue. It is also necessary to ensure that smsdwake utility has suid to the
same user as the one running smsd - process is that smsdclient stores new
message in the queue and runs smsdwake who wakes up smsd by signal which
then processes new message.

## Client run
```
./smsdclient <options> -- <operator> <specific parameters>

Available options:

  -ms, --msg-size
      Max. number of characters per message.
  -mm, --max-msg
      Max. number of messages per one mail (max is 9).
  -ss, --subject-size
      Max. message subject length (rest will be cut off).
  -ft, --from-type
      Type of From header processing: full (default), mail (only mail), user
      (only user name from mail).
  -fl, --from-list
      File with lines in the format shortcut=mail, which makes that header
      From is replaced by shortcut.
  -ff, --filter-file
      File with filter definitions. Each line is in the format: header
      filter action. Header is (case insensitive) name of mail header (e.g.
      From) or * for any header. Filter is text which must be contained in
      the header content (again case insensitive) or * for any value. Action
      is either 'reject' (drop immediately) or 'accept' (accept and stop
      checking). Filters are evaluated in the order in which they appear in
      the file.
  -i, --index
      Makes the sequence number appear at the beginning of each message.
  -r, --reverse
      Sends messages in reversed order.
  --no-syslog
      Do not log errors to syslog, but terminate.
  --pid-file
      Location of pid file (def. /var/run/smsd.pid).
  --spool-dir
      Message queue directory (def. /var/spool/smsd/).
  --nosend-file
      File name whose presence stops sending of the message (def. ~/.smsdclient.nosend).
```
Operator and his parameters are directly passed to smssend.

Message text is expected on standard input (can be easily placed in .forward
or similar system for mail forwarding).
