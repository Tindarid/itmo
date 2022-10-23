delete from Runs where SessionId in (select SessionId from Sessions natural join Teams where TeamName = :TeamName)
