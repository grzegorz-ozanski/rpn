# Code Coverage in CI (Windows & Linux)

This guide summarizes reliable ways to collect and visualize code coverage in GitHub Actions on both **Windows** and **Linux** runners.

---

## ✅ Summary

### ✅ Windows Runner + MSVC

- **OpenCppCoverage works well** via MSVC.
- **Supports inline functions and headers (`.hpp`)**.
- GUI installer prompts UAC ➜ **not suitable for CI**.
- Use **Chocolatey** instead:

```powershell
choco install opencppcoverage -y
```

- Runner has admin rights, so UAC is bypassed.
- OpenCppCoverage is installed at:

```
C:\Program Files\OpenCppCoverage\OpenCppCoverage.exe
```

> 🟡 `refreshenv` is **not required** if using full path.

### ✅ Linux Runner + GCC

- Use `lcov` and `genhtml`:

```bash
sudo apt update
sudo apt install -y lcov
```

- Works only with GCC/Clang.
- Collects `.gcda`/`.gcno` files.

```bash
lcov --directory build --capture --output-file coverage.info
lcov --remove coverage.info '*/_deps/*' '/usr/*' --output-file coverage.info.cleaned
genhtml coverage.info.cleaned --output-directory coverage
```

---

## ⚠️ Pitfalls and Differences

| Feature                          | OpenCppCoverage            | lcov/gcov                      |
|----------------------------------|----------------------------|--------------------------------|
| Inline code in headers           | ✅ Included                | ❌ Ignored (if no `.gcno`)    |
| Visual Studio/MSVC support       | ✅ Native                  | ❌ Not supported              |
| Linux/GCC support                | ❌                         | ✅ Native                     |
| Chocolatey install (CI-friendly) | ✅                         | ✅ (`apt install`)            |
| UAC-free install                 | ✅ (`choco`)               | ✅                            |
| CLI flags                        | Windows-style              | GCC/gcov specific              |

---

## 🛠 Notes on Chocolatey and `PATH`

- Chocolatey **does** add OpenCppCoverage to the system PATH _if_ the installer supports it.
- The Chocolatey wrapper **may run with elevated privileges**, even if `UAC` would block the GUI installer.
- `refreshenv` is **optional** unless you rely on `PATH` implicitly.

### Optional `refreshenv`:

```powershell
refreshenv
```

Or explicitly use full path:

```powershell
& "C:\Program Files\OpenCppCoverage\OpenCppCoverage.exe" --help
```

---

## 📁 Coverage File Tips

- `lcov` includes unwanted system/dep headers unless filtered.
- Use `lcov --remove ...` to filter noise.
- Use `grep 'SF:' coverage.info.cleaned` to list included files.

---

## ✅ Conclusion

For C++ projects with tests:

- ✅ **Use OpenCppCoverage** on **Windows + MSVC**
- ✅ **Use lcov** on **Linux + GCC**
- ❌ Avoid lcov if header coverage is critical

If you want working GitHub Actions examples, feel free to ask!