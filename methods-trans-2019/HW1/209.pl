while (<>) {
    s/\([^\)]+\)/\(\)/g;
    print ;
}