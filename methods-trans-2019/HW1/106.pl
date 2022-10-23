while (<>) {
    print if /^.*(\W+|\A)(\d+)(\W+|\Z).*$/;
}
