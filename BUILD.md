```bash
cmake --preset linux-amd64-debug # -DCMAKE_EXPORT_COMPILE_COMMANDS=ON for compile_commands.json
cmake --build --preset linux-amd64-debug --target gh2test_codegen
cmake --build --preset linux-amd64-debug --target gh2test

rexglue codgen

SDL_VIDEODRIVER=wayland LD_LIBRARY_PATH=/home/cisco/rexglue-sdk/lib/ ./out/build/linux-amd64-debug/gh2test --game_data_root ./assets
```

Shaders Cache: `.local/share/gh2test/cache/shaders/`