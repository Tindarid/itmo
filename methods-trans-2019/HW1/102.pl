while (<>) {
    print if /^.*(\W+|\A)cat(\W+|\Z).*$/;
}
