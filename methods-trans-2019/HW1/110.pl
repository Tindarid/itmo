while (<>) {
    print if /^.*(\W|\A)(\w+)\2(\W|\Z).*$/;
}

