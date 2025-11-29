# Space Invaders

---

## Setup

### Requirements

- **Visual Studio 2022**
- **vcpkg** installed and bootstrapped:

```bash
  git clone https://github.com/microsoft/vcpkg
  cd vcpkg
  bootstrap-vcpkg.bat
  vcpkg integrate install
```

---

## Dependencies

Defined in `vcpkg.json`:

```json
{
  "name": "space-invaders",
  "version-string": "1.0.0",
  "builtin-baseline": "4f8fe05871555c1798dbcb1957d0d595e94f7b57",
  "dependencies": [{ "name": "sfml", "version>=": "3.0.0" }, "gtest"]
}
```

Install all dependencies:

```bash
vcpkg install --triplet x64-windows
```

---

## Code Style

Uses **ClangFormat** for automatic formatting.

### Enable it in Visual Studio:

1. **Tools → Options → Text Editor → C/C++ → Code Style → Formatting → General**
2. Check:

   - Enable ClangFormat support
   - Run ClangFormat for all formatting scenarios
   - Use custom path to `clang-format.exe`
     (e.g. `C:\Program Files\Microsoft Visual Studio\2022\Enterprise\VC\Tools\Llvm\bin\clang-format.exe`)

3. Also install the **Clang Power Tools** VS extension, and enable **format on save** for ClangFormat

---

## Conventions

### Naming Conventions

- **Classes, Structs, Enums**: `PascalCase` (e.g., `GameState`, `EntityType`)
- **Methods/Functions**: `camelCase` (e.g., `moveLeft()`, `getScore()`)
- **Member Variables**: `m_camelCase` prefix (e.g., `m_player`, `m_scoreManager`)
- **Local Variables**: `camelCase` (e.g., `deltaTime`, `bulletPos`)
- **Constants**: `UPPER_SNAKE_CASE` (e.g., `SCREEN_WIDTH`, `ALIEN_SPEED`)
- **Namespaces**: `PascalCase` (e.g., `GameLogic`, `GameUI`)

### Best Practices

- Use smart pointers (`std::unique_ptr`, `std::shared_ptr`) instead of raw pointers for ownership
- Mark const methods that don't throw exceptions with `noexcept`
- Use forward slashes (`/`) in file paths for cross-platform compatibility
- Throw exceptions for critical errors rather than silently failing
- Follow RAII (Resource Acquisition Is Initialization) principles
- Use `#pragma once` for header guards

---
