# Installation Guide

## Makefile: Building and managing the project

This project uses a set of Makefiles to compile and process source, audio, and images.

To compile parts of the project the tool `make` is required.

To compile everything, in the root of the repository, there is a Makefile which when
called upon by the tool `make`, it will compile everything into a Vircon32 cartridge and
will be dropped into `bin/`.

NOTE: with the normal build process, any warnings or errors generated will be stored in
text files in the particular category (**tool**.errors).

So if there is a failure, you can check out that file for clues:

    audio$ `cat wav2vircon.errors`
    images$ `cat png2vircon.errors`

In the `src/` directory, it is further broken out by tool:

    src$ `cat compile.errors`
    src$ `cat assemble.errors`
    src$ `cat packrom.errors`

### Help

A list of available options are available by running `make help` from the base directory.

    $ `make help`

### Debug builds

When building the project specifying the **debug** target to the Makefile, the normal
build messages will vanish in favor of actual commands being run and their output.

This can be useful if there is some sort of problem, one can better determine where
the issue is taking place.

    $ `make debug`

### Per-category processing

Should the need arise, you can also run `make` within the `audio`, `images`, or `src`
subdirectories, and it will attempt to make that component (note: as the audio and images
are prerequisities to packing the ROM, just building the code without previously getting
the audio and images processed will result in a build error).

    src$ `make`

### Cleaning

To clean out all the byproducts of building the project, the **clean** target can be
provided to **make**, which will (from the base Makefile) remove all byproducts from
the entire project, or (when specified to a category Makefile) remove just those in
that particular category.

    $ `make clean`

    or:

    audio$ `make clean`

This will remove any error output files as well, leaving the clean slate.

#### Good building hygiene

It is highly recommended to routinely clean out the project tree and rebuilding from
scratch (especially for **src/**).

A common practice would be something like (for just the code):

    src$ `make clean && make`

or (for the entire project):

    $ `make clean && make`

Probably would not be a bad idea to do a project-level **clean** before dealing with
any commits (don't want to accidentally add unnecessary files).
