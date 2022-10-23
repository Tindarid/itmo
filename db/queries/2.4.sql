select ContestId, Letter from Problems P where not exists (
  select ContestId, Letter
  from Runs R, Sessions S
  where Accepted = 1 and R.SessionId = S.SessionId and P.ContestId = S.ContestId and P.Letter = R.Letter
)
