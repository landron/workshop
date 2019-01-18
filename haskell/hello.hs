{- 
    Haskell survival kit

    1.  https://www.haskell.org/platform/windows.html
        2g, it uses MSYS2 so it takes much time to ... everything (install, build)

    2.  ghc --make -O2 ./hello.hs

    tag_haskell, tag_hs
  -}
hello_world = putStrLn ("Hello World")

main = do
   hello_world