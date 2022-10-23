select S.StudentId, StudentName, GroupName
from Students S, Groups G
where S.GroupId = G.GroupId
