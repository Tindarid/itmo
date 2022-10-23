$start = 1;
$need_line = 0;
while (<>) {
    if (/^\s+$/) {
        if ($start == 0) {
            $need_line = 1;
        }
        next;
    }
    $start = 0;
    if ($need_line == 1) {
        print "\n";
    }
    $need_line = 0;
    s/^\s+//;
    s/\s+$//;
    s/\s+/ /g;
    print;
    print "\n";
}
