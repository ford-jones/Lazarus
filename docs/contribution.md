# Contribution:
Thank you for expressing interest and helping with this project! Here is a guide for contribution.

## Git Commit guidlines:
- feat: The new feature you're adding to a particular application
- fix: A bug fix
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

## CI:
There are two continuous-integration workflows upstream which you should be aware of.
1. `create-release.yml`:
  - This workflow creates and publishes a new release.
  - To trigger, create a tag and then push to main with the `SemVer` number prefixed with a `v`, like so:
```
git tag v1.0.0
git push origin v1.0.0 
```

2. `changelog.yml`
  - This workflow creates changelogs based on the commit messages merged upstream since the last release. This workflow triggers on merge to branch `main`.
  - On merge be sure to insert the `SemVer` tag.
