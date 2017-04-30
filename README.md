# LPC 812 base frame project

To prevent redoing lots of work every time this is my to go repo that is copied when starting LPC812 development. 

## Libraries used

Uses the [lpc81x chip](https://github.com/Squantor/lpc_chip_81x) library also fitted with a codeblocks makefile project.

## Other features

This is a codeblocks project and has support for debugging with [Black Magic Probe](https://github.com/blacksphere/blackmagic/wiki). This has two targets, debug and release. You can also run from the commandline by using `make release` or `make debug` for release or debug targets, to clean just run `make clean`. Makefile has been based on [generic makefile for C](https://github.com/mbcrawfo/GenericMakefile), I have removed automatic searching for files and some other simplifications.

### Code::Blocks Debugger Attach commands

These lines are executed by GDB in codeblocks after attachment:
```
monitor swdp_scan
attach 1
set mem inaccessible-by-default off
set {int}0x40048000 = 2
load bin/debug/periph_blinky.elf
compare-sections
start
```

## Issues

Currently I get a mismatch error when executing compare-sections, no idea why, question still pending to the developers of the black magic probe.
