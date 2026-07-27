# EVO PlatformIO example

Open this folder as a PlatformIO project. Select either the `EVO_X1E` or
`EVO_X1P` environment, then build and upload normally.

From a terminal in this folder:

```text
pio run -e EVO_X1E
pio run -e EVO_X1P
```

The shared environment contains the framework, local library dependency,
USB serial setting, and C++17 requirement. Each controller environment only
selects its PlatformIO board and compile-time EVO controller definition.
