select StudentId, StudentName, GroupName from (select * from Students where StudentName = :StudentName) R1 natural join Groups
