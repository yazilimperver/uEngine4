freeglut kütüphanesi submodule olarak eklenmiştir.
uengine4 reposu klonlandıktan sonra, ilgili repoyu (freeglut)

```bash
git submodule update — recursive — remote
```

komutu ile almalısınız. Genel olarak statik kütüphane kullanımı tercih edilmektedir.
Windows üzerinde ilgili kütüphanenin oluşturulması için aşağıdaki komutlar çağrılabilir.

```bash
cmake -S . -B build  -D FREEGLUT_BUILD_DEMOS=OFF -D FREEGLUT_BUILD_STATIC_LIBS=ON
cmake --build build --config Release
cmake --build build --config Debug
cmake --install build --prefix install --config Debug
cmake --install build --prefix install --config Release
```

Linux üzerinde ilgili kütüphanenin oluşturulması için aşağıdaki komutlar çağrılabilir.

```bash
cmake -S . -B buildLinux  -D FREEGLUT_BUILD_DEMOS=OFF -D FREEGLUT_BUILD_STATIC_LIBS=ON
cmake --build buildLinux --config Release
cmake --build buildLinux --config Debug
cmake --install buildLinux --config Debug
cmake --install buildLinux --config Release
```