select TeamName from Teams natural join (
  select distinct TeamId from (
    select distinct ContestId, TeamId from Teams natural join Contests
    except
    select distinct ContestId, TeamId from Sessions natural join Runs where Accepted = 1
  ) R1
) R2
