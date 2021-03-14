{-
  WIP !

  Purpose:
   * get number of tests, T
   * get the number of pairs, N, for the each tests
   * get N (x, y) coordinates

  Run
	 * ghc --make -O2 hello_io.hs
   ( * or runhaskell hello_io.hs ?)

	Reference
    In order to tell us what it calculated, it has to change the state of an output device
     (usually the state of the screen), which then emits photons that travel to our brain
     and change the state of our mind, man.
 	http://learnyouahaskell.com/input-and-output

  TODO
    * getLine vs readLn
        see :t readLn
    * runhaskell crash
        "Access violation in generated code when reading 0xffffffffffffffff

        Attempting to reconstruct a stack trace..."

  #haskell_io #hs_io #hs_import
  -}
import Numeric.Natural

repeatNTimes 0 _ = return ()
repeatNTimes n action = do
  action
  repeatNTimes (n-1) action

{-
  * define "main"
  * do = do imperative
      "in a do block, the last action cannot be bound to a name"
  * <- vs let
    "So use <- when you want to bind results of I/O actions to names
    and you can use let bindings to bind pure expressions to names."
  * return is sort of the opposite to <-.
  * when: "if something then do some I/O action else return ()"

  * stuff: <-, ++, $, . (functions composition)
-}
main = do
{-   putStrLn "Hello, what's your name?"
   name <- getLine
   putStrLn $ "Now give me a number, " ++ name ++ "!"-}
   line <- getLine
   -- Natural is better than Int
   let no_pairs = (read line :: Natural)
   -- print = putStrLn . show
   print no_pairs
