{-# LANGUAGE Rank2Types #-}

module Task6
    ( cd
    , file
    , ls
    ) where

import Lens.Micro (Traversal', filtered, traversed, (^?))
import Task5

-- | Try to change directory to specified
cd :: FilePath -> Traversal' FS FS
cd dir = contents.traversed.filtered (\node -> any (== dir) (node^?_dir.name))

-- | List directory
ls :: Traversal' FS FilePath
ls = contents.traversed.name

-- | Try to get filename by filename (if exists)
file :: FilePath -> Traversal' FS FilePath
file filename = contents.traversed.filtered (\node -> any (== filename) (node^?_file.name)).name
