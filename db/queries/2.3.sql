select distinct TeamId
from Runs R, Sessions S
where Accepted = 1 and ContestId = :ContestId and R.SessionId = S.SessionId
