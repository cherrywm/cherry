# 🍒

cherry (🍒) is a minimal floating window manager for [X11](https://www.x.org/releases/X11R7.7/doc/man/man1/Xorg.1.xhtml),
written in C, using [XCB](https://xcb.freedesktop.org/) and [Lua 5.3](https://www.lua.org/manual/5.3/).

🍒 takes inspiration from [awesome](https://github.com/awesomeWM/awesome) (regarding Lua configuration) as well as
[berry](https://github.com/JLErvin/berry) for the name.

## Configuration
All configuration is done through a configuration file, or the named pipe (discussed below).
A configuration file is not needed. Sensible defaults will be provided in the absence of one.

By default, 🍒 will look in the location specified by the `-c` option. If no option is provided, 🍒 will:
* check if the `XDG_CONFIG_HOME` environment variable exists.
    * if so, the resulting location will be: `$XDG_CONFIG_HOME/cherry/cherry.lua`.
    * if not, default to: `$HOME/.config/cherry/cherry.lua`.

🍒 will attempt to create a named FIFO pipe at the location specified by the config variable `fifo_path`, which defaults to `/tmp/cherry`.

Communication over this pipe can be done with `cherryc`. As of August 1 2020, you can use `cherryc` to:
* reload the configuration file: `-r`
* create new tags/switch to a pre-existing tag: `-t`
* specify a custom pipe location: `-f`

An example usage, combining all options, would be `cherryc -rtexample -f/tmp/example`. `cherryc` configuration does not persist.

## Development Details
Compiling 🍒 yourself is as easy as installing Lua 5.3 and XCB, cloning the repository, then running `make`.
Due to how tiny the 🍒 codebase is, full compilation should only take a few seconds at most.

`cherryc` can be compiled with `make cherryc`.


