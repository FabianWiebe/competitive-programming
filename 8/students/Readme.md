# Compatibility

The executables were compiled for Windows, macOS and Linux and should require no
dependencies.

# Usage

```sh
# On macOS and Linux you may need to make the runner executable:
chmod +x $ARCH-$OS-runner

./$ARCH-$OS-runner testcase.in path/to/your-program
```

Lines starting with `$i: ok` indicate a successful test case, ones starting with `$i: err:` indicate a failed test case. `i/o error:` usually mean that your program behaved unexpectedly, ie. send malformed data (If this happens you may want to print everything you write to `cout` to `cerr` as well). Lines starting with `fc:` can be ignored.

Any data written to `stderr` by your program will be displayed for your convenience.

The runner may print lines like this:

```
note: 74 duplicate queries
note: 182 queries for known information
```

They do *not* indicate a failed test and you may ignore them. The first line shows the number of duplicate queries performed, you should be able to reduce this number to zero, if you so wish. The second line show the number of queries which are have in theory answered by previous queries (note that tracking that information is likely not possible without increasing the time complexity of your algorithm).
