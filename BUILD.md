```bash
cmake --preset linux-amd64-debug
rexglue codegen
cmake --build --preset linux-amd64-debug --target gh2test

LD_LIBRARY_PATH=/home/cisco/rexglue-sdk/lib/ ./out/build/linux-amd64-debug/gh2test --game_data_root ./assets --render_target_path_vulkan=fsi
```