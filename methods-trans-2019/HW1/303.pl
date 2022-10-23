my $text = "";
while (my $line = <>) {
    $text .= $line;
}

my @links = ();
while ($text =~ s/<a(.*?)href=["'](?<link>.*?)["'](.*?)>//) {
    $link = $+{link};
    print "$link\n"
    push(@links, $link);
}

#print "\n";
#foreach (@links) {
#  print "$_\n";
#}
