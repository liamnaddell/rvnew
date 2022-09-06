# What is this?

This is a research project targeting RV64, specifically the qemu virt machine

## What is the goal?

I don't really have one, I'm more interested in learning how the cpu works, specifically its initialization and configuration.

## Building and running

`make` builds

`make qemu` runs the kernel over a gdb server, use `make gdb` to connect

`make qemu2` runs the kernel without gdb

`make test` runs the test suite over a gdb server, use `make testgdb` to connect


## Contributing

Please contribute tests, documentation, code cleaning, anything that helps make the code more correct and comprehensible
