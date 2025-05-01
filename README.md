# Leros LLVM/Clang Integration

[![Leros](https://leros-dev.github.io/img/leros-logo.png)](https://leros-dev.github.io/)

This repository contains the LLVM/Clang backend and related infrastructure for the [Leros](https://leros-dev.github.io/) processor architecture.

## ⚠️ Project Status: Broken

**This repository is currently broken and not usable. Two major issues must be fixed:**

### 1. TableGen Generates Invalid C/C++ Code

TableGen currently produces invalid code such as:

```
case 0: return !() && !();
error: expected expression
```

This cryptic error is triggered when a pseudo-instruction is defined with an **empty pattern list** (`[]`) in TableGen and is then used as the result (right-hand side) of a `Pat` pattern. TableGen expects any instruction or pseudo used in a pattern to have a non-empty pattern list describing how it should be matched or lowered. Failing to do so leads to broken generated C++ code and inscrutable compiler errors.

### 2. Outdated Leros Clang Codebase

The entire Leros-specific Clang codebase is outdated and requires a careful update to be compatible with modern LLVM/Clang releases.

---

## About Leros

Leros is a simple stack-based processor designed for research and education. More information can be found at the [Leros website](https://leros-dev.github.io/).

## Getting Involved

- **Do not expect this repository to build or work until the above issues are resolved.**
- Contributions to fix TableGen and update the Leros Clang backend are welcome.

## Resources

- [Leros Documentation](https://leros-dev.github.io/)
- [LLVM Getting Started](https://llvm.org/docs/GettingStarted.html)
- [LLVM Discourse forums](https://discourse.llvm.org/)


