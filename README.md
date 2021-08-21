# IP Anonymize

## About this module

Stale IP addresses clog up your database with useless data, not to 
mention, may be subject to subpoena by legal authorities in some 
jurisdictions.

The IP Anonymize module helps ensure users' privacy by implementing a
retention policy for IP addresses recorded in the database.  IP 
addresses are scrubbed on each cron run according to a configurable
retention period.  For example, you may wish to preserve IP addresses 
for a short while for purposes of identifying spam.

IP Anonymize cannot guarantee anonymity, as IP addresses are recorded at
least temporarily, and may also be logged elsewhere in the system such 
as webserver error logs.  For more robust anonymization, Cryptolog
module can be used to replace client IP addresses with ephemeral
identifiers.

## Requirements

* This module has no requirements yet.

## Installation

* Install this module using the official Backdrop CMS instructions at
  https://backdropcms.org/guide/modules.

* Visit the configuration page under Administration > Configuration > People > 
  IP address anonymization (admin/config/people/ip_anon) and enter the required 
  information.

 ## Issues

  Bugs and Feature requests should be reported in the Issue Queue:
  https://github.com/backdrop-contrib/ip_anon/issues.

## Current Maintainers

* Seeking maintainers.

## Credits

* Ported to Backdrop by [djzwerg](https://github.com/djzwerg)
* Originally developed for Drupal by [mfb](https://github.com/mfb)

## License

This project is GNU GPL v2 software. See the LICENSE.txt file in this directory for complete text.
