module Main where

import Control.Monad.State
import FileSystem
import Options.Applicative
import System.Exit
import System.IO

data Options = Options { directory :: FilePath }
data Command = Dir | Ls FilePath | Cd FilePath | Exit
data Commands = Commands { optCommand :: Command }

progOptions :: Parser Options
progOptions = Options
      <$> argument str (metavar "DIRECTORY")

commands :: Parser Command
commands = hsubparser
    ( command "cd"   (info (Cd <$> argument str (metavar "directory")) (progDesc "Change directory"))
   <> command "ls"   (info (Ls <$> argument str (metavar "directory")) (progDesc "List directory"))
   <> command "exit" (info (pure Exit) (progDesc "Exit"))
   <> command "dir"  (info (pure Dir) (progDesc "List current directory")))

commandsInfo :: ParserInfo Command
commandsInfo = info (commands <**> helper) idm

main :: IO ()
main = initWith =<< execParser opts
  where
    opts = info (progOptions <**> helper)
      ( fullDesc
     <> progDesc "Read DIRECTORY, manipulate it and write back"
     <> header "Simple file manager" )

initWith :: Options -> IO ()
initWith (Options dir) = do loaded <- loadOnStart dir
                            case loaded of
                              Left err       -> putStrLn $ "Cannot load, because " ++ err
                              Right resolved -> runStateT interactor resolved >> return ()

flushprint :: String -> IO ()
flushprint text = putStr text >> hFlush stdout

-- | Interactive shell
interactor :: StateT FSZipper IO ()
interactor = greeter >> executor >> interactor

-- | Prints greeting message
greeter :: StateT FSZipper IO ()
greeter = do zipper <- get
             lift $ flushprint (greeting zipper)

-- | Parses and executes commands
executor :: StateT FSZipper IO ()
executor = do line <- lift getLine
              case (execParserPure (prefs idm) commandsInfo (words line)) of
                Success parsed -> case parsed of
                               Dir  -> execDir
                               Ls _ -> lift $ flushprint "You typed ls\n"
                               Cd _ -> lift $ flushprint "You typed cd\n"
                               Exit -> execExit
                Failure e -> lift $ flushprint ((show helpInfo) ++ "\n")
                             where (helpInfo, _, _) = execFailure e ""
                CompletionInvoked _ -> error "no completion support"

-- | Exit
execExit :: StateT FSZipper IO ()
execExit = lift $ exitSuccess

-- | Replace this with ls .
execDir :: StateT FSZipper IO ()
execDir = do zipper <- get
             let (dir, _) = zipper
             lift $ flushprint (lsDirectory dir)
