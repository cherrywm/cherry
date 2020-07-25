# 🍒

cherry (🍒) is a minimal window manager for [X11](https://www.x.org/releases/X11R7.7/doc/man/man1/Xorg.1.xhtml),
written in C, using [XCB](https://xcb.freedesktop.org/) and [Lua 5.3](https://www.lua.org/manual/5.3/).

🍒 takes inspiration from [awesome](https://github.com/awesomeWM/awesome) (regarding Lua configuration), and
[bspwm](https://github.com/baskerville/bspwm) for on-the-fly adjustments via messages, as well as
[berry](https://github.com/JLErvin/berry) for the name.

🍒 will eventually support tiling, tabbing and stacking. First-class support will eventually be provided for
rounded edges, gaps, opacity and blur.

## Configuration
Note: 🍒 **requires** an existing configuration file. The simplest possible one you can have is just an empty file,
as sensible defaults are provided for all options.

By default, 🍒 will look in the location specified by the `-c` option. If no option is provided, 🍒 will:
* check if the `XDG_CONFIG_HOME` environment variable exists.
    * if so, the resulting location will be: `$XDG_CONFIG_HOME/cherry/cherry.lua`.
    * if not, default to: `$HOME/.config/cherry/cherry.lua`.

🍒 listens not only for X events, but also for incoming events from a named pipe. By default, this pipe will be made
at `/tmp/cherry` but can be configured with the `fifo_location` Lua variable.

Note that no checks are made over the pipe location. Please make sure that this is a valid location.

## Development Details
Compiling 🍒 yourself is as easy as installing Lua 5.3 and XCB, cloning the repository, then running `make`.
Due to how tiny the 🍒 codebase is, full compilation should only take a few seconds at most.
