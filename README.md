# OpenDAW

Fix git submodle add

```bash
git config --global http.version HTTP/1.1
git config --global --unset http.version
```

```bash
git clone https://github.com/timkingsmill/OpenDAW.git 
cd OpenDaw
git submodule update --init --recursive
cmake -Bbuild
cmake --build build --config Release --target surge-staged-assets
```
