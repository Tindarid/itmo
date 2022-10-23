select RunId, SessionId, Letter, SubmitTime from Runs natural join 
  (select SessionId from Sessions where ContestId = :ContestId) R1
where Accepted = 1
