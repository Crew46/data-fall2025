# Build/Development Guide

## Makefile: Building and managing the project

This  project uses  a set  of Makefiles  to compile  and process  source,
sounds, and images.

### Build the components

To compile parts of the project  the tool `make` is required. The default
action is  to compile all  the separate components,  but NOT to  pack the
cartridge:

    $ make

Do **NOTE**: this will do everything except the final step of packing the
cartridge. They are  currently separated as one may just  want to test if
code compiles cleanly and not generate  a cartridge. The behaviour can be
changed as  we progress with  the project and find  a full build  is more
desirable.

### Pack the cartridge

To pack up all the built components into a Vircon32 cartridge, run:

    $ make cart

... from the base of the project. It will be deposited into `bin/`.

### Build and pack

To  do everything  (including pack  the cartridge),  in the  root of  the
repository, we merely add "**all**" as an argument to `make`:

    $ make all

### Build and pack and run

If the machine  you are running Vircon32  on is the same  machine you are
building on, you can also run the game in the emulator immediately upon a
successful build:

    $ make run

### Capturing warnings and errors

NOTE:   with  the   normal  build   process,  any   warnings  or   errors
generated  will  be stored  in  text  files  in the  particular  category
(**tool**.errors).

So if there is a failure, you can check out that file for clues:

    sounds$ cat wav2vircon.errors
    images$ cat png2vircon.errors

In the `src/` directory, it is further broken out by tool:

    src$ cat compile.errors
    src$ cat assemble.errors

And should there be an issue with packing the cartridge:

    data$ cat packrom.errors

**Note**: if  there are no  warnings or errors,  the files may  exist but
will be empty.

### Help

A list of available options are available by running `make help` from the
base directory.

    $ make help

### Debug builds

When  building  the  project  specifying  the  **debug**  target  to  the
Makefile,  the normal  build  messages  will vanish  in  favor of  actual
commands being run and their output.

This can  be useful  if there  is some  sort of  problem, one  can better
determine where the issue is taking place.

    $ make debug

### Per-category processing

Should  the need  arise, you  can also  run `make`  within the  `sounds`,
`images`,  or `src`  subdirectories, and  it  will attempt  to make  that
component (note: as  the sounds and images are  prerequisities to packing
the ROM, just building the code without previously getting the sounds and
images processed will result in a build error).

    src$ make

### Cleaning

To clean  out all the byproducts  of building the project,  the **clean**
target can be  provided to **make**, which will (from  the base Makefile)
remove all  byproducts from the entire  project, or (when specified  to a
category Makefile) remove just those in that particular category. It will
actually call upon the `Makefile.clean`  files that reside in the various
directories. To wit:

    $ make clean

    or:

    sounds$ make clean

This will remove any error output files as well, leaving the clean slate.

#### Good building hygiene

It is  highly recommended  to routinely  clean out  the project  tree and
rebuilding from scratch (especially for **src/**).

A common practice would be something like (for just the code):

    src$ make clean && make

or (for the entire project):

    $ make clean && make

Probably would not  be a bad idea to do  a project-level **clean** before
dealing  with any  commits (don't  want to  accidentally add  unnecessary
files).
