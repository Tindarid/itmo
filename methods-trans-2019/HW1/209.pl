while (<>) {
    s/\([^\)]+\)/\(\)/g;
    print ;
}
