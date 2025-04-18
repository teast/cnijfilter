# cnijfilter (mp495)

This is a copy from Canons own cnijfilter package that is used for several of Canons printers. I have applied (or wrote) some patches to make it work on my Gentoo system for mp495 printer.

## My solution

The solution I have done (because I have yet to figure out how to write correct ebuild files) is to create `mp495_build.sh` script for configure,build,install and symlink everything to make it work.

I have built this driver for mp495 64-bit arch into folder `/opt/mp495`. And then I have doen symlink to pretty much every file in `/opt/mp495`.
You will also need to do symlinks that only contains the library filenames up to (and included) ".so". For example `libcnbpcmcm369.so.8.0.1` should have a symlink `libcnbpcmcm369.so`.

## Architecture

This script was created to support 64-bit architecture. If you are using a 32-bit architecture (for example `i686`) you need to change `ARCH` variable in `mp495_build.sh` so it points to 32 instead of 64.

## Symlinks

I did a symlink to all files in `/opt/mp495/bin` to `/usr/bin`, example:

```bash
ln -s /opt/mp495/bin/printuimp495 /usr/bin
# etc
```bash

I did the same for all files in `/opt/mp495/lib/` including folders, example:

```bash
ln -s /opt/mp495/lib/libcnbpcmcm369.so.8.0.1 /usr/lib
ln -s /opt/mp495/lib/bjlib /usr/lib
ln -s /opt/mp495/lib/cusp/backend/cnijnet /usr/lib/cups/backend/cnijnet
# etc
```bash

And also, to have ".so" files I did:
```bash
cd /usr/lib
ln -s libcnbpcmcm369.so.8.0.1 libcnbpcmcm369.so
# etc
```bash

And I continue to do this for all folders/files found under `/opt/mp495`.

## How to build cnijfilter

You use `mp495_build.sh` (or take inspiration from it). In that file you have an "DESTDIR" variable and that is where the output files will be after an "install" instruction.

My recomendation is that you create an DESTDIR folder (for example `/opt/mp495`) that you have read-write access to. That way you can do configure,build and install as normal user and not fear any evil instructions from this script.

```bash
./mp495_build.sh configure
./mp495_build.sh build
./mp495_build.sh install
```

After you have done this it is time to do the actual "installation" by issue:

```bash
./mp495_build.sh symlink
```

If you want you can do an "dry run" before and see exactly what will be linked:

```bash
./mp495_build.sh symlinkdry
```

*NOTE!*
The old cnijfilter expected to find cups `backend` and `filter` folder under `/usr/lib/cups/` but that is not the case for my Gentoo system. On my system it is located under `/usr/libexec/cups`.
I recommendate you to check where `backend` folder is located on your system and update `mp495_build.sh" accordently.


## Extra info

If you have (like me) your mp495 printer located as an network printer then you could try and search for it by issuing following command:

```bash
/usr/libexec/cups/backend/cnijnet
```

And if you want to add your network printer to cups you could issue following command:
(replace 00-01-02-03-04-05 with the mac address you got from `cnijnet` command above)

```bash
LANG=C lpadmin -p mp495 -m canonmp495.ppd -v cnijnet:/00-01-02-03-04-05 -E
```

## Other printers from cnijfilter

cnijfilter support multiple printers (as you can see if you open `debian/rules` file and check variable `PRINTER_DEPEND_PKG`)

Here are an list of all supported printers and their corresponding id.

```
mp250   356
mp280   370
mp495   369
mg5100  373
mg5200  374
ip4800  375
mg6100  376
mg8100  377
```

If you would want to try and compile this for one of the other printers then I would recommendate you to replace all occurence of `mp495` and `369` in `mp495_build.sh`.
