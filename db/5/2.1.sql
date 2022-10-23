select StudentId, StudentName, GroupName from (select * from Students where StudentId = :StudentId) R1 natural join Groups
