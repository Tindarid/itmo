while (<>) {
    print if /.*\([^\(\)]*\w+[^\(\)]*\).*/;
}
