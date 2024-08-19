# Contribution:
Thank you for expressing interest and helping with this project! Here is a guide for contribution.

## Git Commit guidlines:
- feat: The new feature you're adding to a particular application
- fix: A bug fix
- style: Feature and updates related to styling
- update | refactor: Refactoring or updating a specific section of the codebase
- test: Everything related to testing
- docs: Everything related to documentation
- chore: Regular code maintenance.[ You can also use emojis to represent commit types]

## Branch names:
Use `camelCasing`. Prefix your branch name with the type of change you are making, followed by the specific change. Seperate the two with a `/` delimeter. \

e.g.
```
fix/loaderMemoryLeak
```

## Semantics:
- Declare variables in `camelCase`.
- Declare classes in `UpperCamelCase`.
- Header files should be suffixed with `.h`, not `.hpp`.
- Do not use `_variable` or `m_variable` - use the `this` keyword.
- Avoid using raw pointers declared with `new`, use smart pointers like `std::unique_ptr<T>()` or `std::shared_ptr<T>()` instead.
