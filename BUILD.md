```bash
cmake --preset linux-amd64-debug
cmake --build --preset linux-amd64-debug --target gh2test_codegen
cmake --build --preset linux-amd64-debug --target gh2test

./out/build/linux-amd64-debug/gh2test ./assets/
```