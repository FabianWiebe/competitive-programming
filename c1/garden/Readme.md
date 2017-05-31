# Compatibility

The executables were compiled for Windows, macOS and Linux and should require no
dependencies.

# Usage

```sh
# On macOS and Linux you may need to make the runner executable:
chmod +x $ARCH-$OS-runner

./$ARCH-$OS-runner testcase.in path/to/your-program
```

Lines starting with `$i: ok` indicate a successful test case, ones starting with `$i: err:` indicate a successful test case. `i/o error:` usually mean that your program behaved unexpectedly, ie. send malformed data. Lines starting with `fc:` can be ignored.

Any data written to `stderr` by your program will be displayed for your convenience.
