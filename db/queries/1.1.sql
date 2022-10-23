select RunId, SessionId, Letter, SubmitTime, Accepted
from Runs natural join Sessions natural join Problems
where ContestId = :ContestId and TeamId = :TeamId
