select distinct TeamName
from Runs R, Sessions S, Teams T
where Accepted = 1 and Letter = :Letter and ContestId = :ContestId and R.SessionId = S.SessionId and T.TeamId = S.TeamId
