{-
    Haskell survival kit

    1.  https://www.haskell.org/platform/windows.html
        2GB, it uses MSYS2 so it takes much time to ... everything (install, build)

    2.  ghc --make -O2 ./hello.hs

    Reference
        "A Gentle Introduction to Haskell, Version 98" (98 ?)
        https://www.haskell.org/tutorial/index.html

    tag_haskell, tag_hs
  -}
hello_world = putStrLn ("Hello World!")

-- "the entry point of a Haskell program (similar to the main function in C), and must have an IO type, usually IO ()."
main = do
   hello_world
