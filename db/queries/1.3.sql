select TeamName from Teams natural join
  (select TeamId from Teams except select distinct TeamId from Sessions natural join Runs where Accepted = 1) R1
